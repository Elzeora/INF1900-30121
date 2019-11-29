#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SORTIE 0xff
#define ENTREE 0x00
#define PWM (8000000/38000/2)-1

#define ETEINT 0
#define VERT 2       
#define ROUGE 1

volatile uint8_t compteur = 0;
volatile uint8_t minuterieExpiree =0;
		 uint8_t NBHAUT = 0;


void partirMinuterie ( uint16_t duree ) {
minuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1 = 0;
OCR1A = duree;
TCCR1A = 0 ; 
TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);  // demarre timer1 avec un prescaler de 1024
TCCR1C = 0;
TIMSK1 |= (1 << OCIE1A) ;
}


ISR (INT0_vect ) {
	if(!minuterieExpiree){
    _delay_ms (30);
        if (PIND & 0x04){
        	        	while((PIND & 0x04) != 0){}
    	compteur++;
    	if(compteur == 10){
    		compteur = 1;
    	}
    	partirMinuterie(7812*2); // 8'000'000/1024= 7812
        }   
    }
}


ISR (TIMER1_COMPA_vect) {
minuterieExpiree = 1;
}


void initialisation ( void ) {
cli ();
DDRC = SORTIE; // PORT C est en mode sortie
EIMSK |= (1 << INT0) ; // cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes
EICRA |= (1 << ISC00) ; //sensibilise les interruptions externes aux changements de niveau du bouton-poussoir en ajustant le registre EICRA
sei ();
}

//******************************************************************************/
//* nom : initiationIR
//* description : Une fonction qui initie les registre pour utiliser le PWM pour avec l'émetteur IR
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void initiationIR(){
//Définir la sortie sur les broches 3 et 4
DDRB |= 1 << DDB3 | 1 << DDB2;
//mettre 0 à la broche 3       ~(not)
PORTB &= ~(1 << PB2);
// WGM00 Permet de rentrer dans le mode PWM 8-bit phase correcte, COM1A1  permet l'activation de OC1A 
TCCR0A = 1 << WGM01 | 1 << COM0A0; 
//Prescaler qui permet de diviser l'horloge par 1
TCCR0B = (1 << CS00); 
}


//******************************************************************************/
//* nom : debuterSequence
//* description : Une fonction qui envoie la sequence de début lors d'une transmission IR 
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void debuterSequence(){
	OCR0A = PWM;
	_delay_us(2400);
	OCR0A = 0;
	_delay_us(600);
}

//******************************************************************************/
//* nom : continuerSequence
//* description : Une fonction qui envoie sois une valeur 1 ou 0 selon le bool entre
//* Parametre d'entree  : bool frontMontant si true envoie 1 ,sinon envoie 0
//* Parametre de sortie : aucun
//******************************************************************************/
void continuerSequence(bool frontMontant){
	OCR0A = PWM;
	_delay_us(600);
	if(frontMontant){ //permet d'envoyer 1 sinon envoie 0
		_delay_us(600);
		NBHAUT++;
	}
	OCR0A = 0;
	_delay_us(600);
}

//******************************************************************************/
//* nom : TransmettrePWM
//* description : Une fonction qui envoie une sequence en IR selon une valeur à l'infinie avec
//  un delais de 45ms entre chaque debut
//* Parametre d'entree  : bool frontMontant si true envoie 1 ,sinon envoie 0
//* Parametre de sortie : aucun
//******************************************************************************/	
void transmettrePWM(uint8_t valeur){
		initiationIR();
	for(;;){
		debuterSequence();					
		continuerSequence(valeur & 1);			//bit1
		continuerSequence((valeur >> 1) & 1);	//bit2
		continuerSequence((valeur >> 2) & 1);	//bit3
		continuerSequence((valeur >> 3) & 1);	//bit4
		continuerSequence(0);					//bit5
		continuerSequence(0);					//bit6
		continuerSequence(0);					//bit7
		continuerSequence(1);					//bit8
		continuerSequence(0);					//bit9
		continuerSequence(0);					//bit10
		continuerSequence(0);					//bit11
		continuerSequence(0);					//bit12
		OCR0A = 0;
		_delay_ms(24.6);	 //temps a attendre si juste des 1
		NBHAUT = 5 - NBHAUT; //trouver le nombre de zéro pour ajuster si pas juste des zéros
		for(uint8_t i=0;i<NBHAUT;i++)
			_delay_ms(0.6);
		NBHAUT = 0;
		
	}
}

int main() {	
	initialisation(); 
	do {
		if(compteur==9){
		PORTC = ROUGE;
		}
		if(compteur==1){
			PORTC=VERT;
		}
	} while ( minuterieExpiree == 0);
	cli ();

	transmettrePWM(compteur);
  	return 0; 
}