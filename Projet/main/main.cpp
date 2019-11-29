#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

#include <librairie.h>
#include <variable.h>
#include <capteur.h>

#include <section1.h>
#include <section2.h>
#include <segment.h>
#include <section4.h>
#include <tourner.h>
#include <receptionIR.h>


#define SORTIE 0xFF
#define ENTREE 0x00
#define ETEINT 0



volatile uint8_t minuterieExpiree =0;
volatile uint8_t compteur =0;
volatile bool interruption = false;

//******************************************************************************/
//* nom: partirMinuterie                                                                                                                                /
//* description: fonction qui set les registres pour utiliser le timer1 comme minuterie
//* Parametre d'entree  : uint16_t duree
//* Parametre de sortie : aucun
//******************************************************************************/
void partirMinuterie ( uint16_t duree ) {
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée
	TIFR1 = 1 << OCF1A; // on enable le flag pour pouvoir reutiliser l'interruption par minuterie
	TCNT1 = 0;
	OCR1A = duree;
	TCCR1A = 0 ; 
	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);  // demarre timer1 avec un prescaler de 1024
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A) ;
}

//******************************************************************************/
//* nom: arreterMinuterie                                                                                                                               /
//* description: desactive le registre pour arreter la minuterie
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void arreterMinuterie(){
	//desactive la minuterie
	TIMSK1 &= ~(1 << OCIE1A);
}

//******************************************************************************/
//* nom: ISR                                                                                                                               /
//* description: fonction d'interruption pour la minuterie. S'execute lorsque cette
//*				derniere est expiree.
//* Parametre d'entree  : TIMER1_COMPA_vect
//* Parametre de sortie : aucun
//******************************************************************************/
ISR (TIMER1_COMPA_vect) {
	minuterieExpiree = 1;
	arreterMinuterie();
}

//******************************************************************************/
//* nom: ISR                                                                                                                               /
//* description: fonction d'interruption pour le bouton poussoir sur la carte. 
//*				S'execute lorsque ce dernier est appuye. Un delais de 2 secondes 
//*				est accorde pour appuyer, apres quoi le signal est enregistre
//* Parametre d'entree  : INT0_vect 
//* Parametre de sortie : aucun
//******************************************************************************/
ISR (INT0_vect ) {	
	if(!minuterieExpiree){
    _delay_ms (30); // anti-rebond
        if (PIND & 0x04){
        	while((PIND & 0x04) != 0){} // pour eviter d'activer plusieurs fois par accident
    	compteur++;
    	if(compteur == 10){
    		compteur = 1;
    	}
		interruption = true; // variable qui permet de quitter la boucle de la reception de l'IR
    	partirMinuterie(7812*2); // 8'000'000/1024= 7812 == 2 secondes
        }   
    }
}

//******************************************************************************/
//* nom: initialisation                                                                                                                               /
//* description: initialise les variables et les registres pour permettre l'interruption
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void initialisation () {
	cli (); //empeche le interruptions
	DDRC = SORTIE; 
	DDRA= ENTREE;
	DDRB= SORTIE;
	DDRD= 0b11000000;
	EIMSK |= (1 << INT0) ; // cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes
	EICRA |= (1 << ISC00) ; //sensibilise les interruptions externes aux changements de niveau du bouton-poussoir en ajustant le registre EICRA
	interruption = false;
	minuterieExpiree = 0;
	sei (); //reactive les interruptions
}

int main() {
  	initialisation();

	//variable pour le moteur
	struct moteur m{0,compensateur};

	//Enum des 4 differents sections du parcours, commencant avec 1
	enum etat{Section1 = 1, Section2, Section3, Section4};
	
	//On appelle recevoirIR qui renvoie 
	uint8_t etatInit = recevoirIR(interruption);

	//Si on ne recoit pas de IR, le bouton interrupt sur la carte peut choisir le debut du parcours
	if (etatInit == 0){
		while(minuterieExpiree == 0){
			etatInit = compteur;
		}
		compteur = 0;
	}

	//Transfert de variable, pour conserver l'etat initial
	uint8_t etatPresent = etatInit;

	//variable qui sert a quitter la boucle du parcours
	bool finDuParcours = false;

	//boucle du parcours
	while(!finDuParcours){

		switch(etatPresent){
			//Section 1, soit la matrice des points
			case Section1 : {

				PORTC = 0b00000001; // del qui indique quel section est appelee
				_delay_ms(1000);

				//Boucle pour suivre la ligne jusqua la ligne noire
				bool end =false;
				while(!end){
					switch (lireSenseurComplet()) {
						case capteur3: { // tout droit
							m.droite = vitesse4Normal;
							m.gauche = vitesse4Normal;
							break;
						}
						case capteur2: { // ajustement vers la gauche
							m.droite = vitesse4Elever;
							m.gauche = compensateur;
							break;
						}
						case capteur4: { // ajustement vers la droite
							m.droite = 0;
							m.gauche = vitesse4Elever;
							break;
						}
						//ligne noire
						case capteur4321:
						case capteur321:
						case capteur543:
						case capteur5432:
						case capteur12345: {
							m.gauche = compensateur;
							m.droite = 0;
							end = true;
							break;
						}
					}
					//fonction qui ajuster le pwm des moteurs
					ajustementPWMBetter(m.gauche - compensateur, m.droite, 0, 0);
				}

				ajustementPWMBetter(0,0,0,0); // arret des moteurs

				//Recevoir un IR qui indique quel a point il faut se rendre
				initialisation();
				uint8_t valeur = recevoirIR(interruption);
				
				//Si le IR ne fonction ne marche pas, il faut pouvoir utiliser le bouton
				//interrupt de la carte
				if (valeur == 0){
					while(minuterieExpiree == 0){
						valeur = compteur;
					}
					compteur =0;
				}	

				//Fonction qui se rend au point recu precedemment	
				choisirPoint(&m, valeur);
				break;
			}

			//Section 2, soit la le parcours avec les courbes
			case Section2 : {

				//Allumer la del indiquant la section
				PORTC = 0b00000010;
				 _delay_ms(1000);

				//Fonction qui effectue le parcours
				parcoursSection2(&m);
				break;
			}

			//Section 3, soit le decodage des segments
			case Section3 : {

				//Allumer la del indiquant la section
				PORTC = 0b00000100;
				 _delay_ms(1000);

				//Fonction qui effectue le parcours
				parcoursSection3(&m);
				break;
			}

			//Section 4, soit le suivi des boites blanches
			case Section4: {

				//Allumer la del indiquant la section
				PORTC = 0b00001000;
				_delay_ms(1000);	

				//Fonction qui effectue le parcours
				parcoursSection4(&m);
				break;
			}
		}
		
		//En sortant de chaque section, il faut effectuer un tour de 90,
		tourner(&m,etatInit,etatPresent);
		if(etatInit == etatPresent){// si on est a la fin, ne pas tourner
			finDuParcours =true;
		}
		
	}

	//Routine qui indique que le robot a termine le parcours
	produireSon(81);
	_delay_ms(2000);
	arreterSon();

	return 0;
} 