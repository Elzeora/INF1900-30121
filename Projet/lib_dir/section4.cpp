#include <section4.h>



//******************************************************************************/
//* nom: parcourirSection4                                                                                                                                 /
//* description: permet de realiser le parcours 4, soit le suivi des boites blanches 
//* Parametre d'entree  : struc moteur
//* Parametre de sortie : aucun
//******************************************************************************/
void parcoursSection4(struct moteur *m) {

	bool end = false;
	bool carre = false;
	uint8_t nbCarre = 0;

	while (!end) {
		allumerDelSenseur();

		//lorsqu'il est dans les rectangles
		if (carre) {
			switch (lireSenseurComplet()) {
			case capteur5: {
				m->droite = vitesse4Elever;
				m->gauche = compensateur;
				break;
			}
			case capteur1: {
				m->droite = 0;
				m->gauche = vitesse4Elever;
				break;
			}
			case capteur0: {
				m->droite = vitesse4Elever;
				m->gauche = vitesse4Elever;
				break;
			}
			case capteur12345:
			case capteur321  :
			case capteur543  :
			case capteur4321 :
			case capteur5432 : {
				m->droite = vitesse4Elever;
				m->gauche = vitesse4Elever;
				ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
				produireSon(81); //Nous avons pris la note la plus aigu
				_delay_ms(50);
				arreterSon();
				_delay_ms(20);
				produireSon(81); 
				_delay_ms(50);
				arreterSon();
				_delay_ms(200);
				carre = false;
				nbCarre ++;
				if (nbCarre == 3) {
					end = true;
					ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
					_delay_ms(200);
				}
				break;
			}
			}

		} else {
			//lorsqu'il nest pas dans les rectangles
			switch (lireSenseurComplet()) {
			case capteur3: {
				m->droite = vitesse4Normal;
				m->gauche = vitesse4Normal;
				break;
			}
			case capteur2  :
			case capteur21 : {
				m->droite = vitesse4Elever;
				m->gauche = compensateur;
				break;
			}
			case capteur5  :
			case capteur54 : {
				m->droite = 0;
				m->gauche = vitesse4Elever;
				break;
			}
			case capteur32: {
				m->droite = vitesse4Elever;
				m->gauche = compensateur;
				break;
			}
			case capteur34: {
				m->droite = 0;
				m->gauche = vitesse4Elever;
				break;
			}
			case capteur0: {
				m->droite = 0;
				m->gauche = compensateur;
				break;
			}
			case capteur321 :
			case capteur543 :
			case capteur12345: {
				m->droite = vitesse4Elever;
				m->gauche = vitesse4Elever;
				ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
				produireSon(81); //Nous avons pris la note la plus aigu
				_delay_ms(50);
				arreterSon();
				_delay_ms(20);
				produireSon(81); 
				_delay_ms(50);
				arreterSon();
				_delay_ms(200);
				carre = true;
				break;
			}
			}
		}
		ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);


	}
	ajustementPWMBetter(0, 0, 0, 0);
}


