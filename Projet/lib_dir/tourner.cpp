#include "tourner.h"


//******************************************************************************/
//* nom: tourner                                                                                                                                /
//* description: permet de tourner a 90° et de changer de section
//* Parametre d'entree  : struc moteur, etatInitial et etatPresent
//* Parametre de sortie : aucun
//******************************************************************************/
void tourner(struct moteur *m, uint8_t etatInitial, uint8_t &etatPresent) {
	bool end = false;
	while (!end) {
		switch (lireSenseurComplet()) {

			case capteur3: {
				m->droite = vitesseTNormal;
				m->gauche = vitesseTNormal;

				break;
			}

			case capteur1  :
			case capteur2  :
			case capteur21 : {
				m->droite = vitesseTElever;
				m->gauche = compensateur;
				break;
			}

			case capteur5  :
			case capteur4  :
			case capteur54 : {
				m->droite = 0;
				m->gauche = vitesseTElever;
				break;
			}

			case capteur32: {
				m->droite = vitesseTElever;
				m->gauche = vitesseTFaible;
				break;
			}

			case capteur34: {
				m->droite = vitesseTFaible;
				m->gauche = vitesseTElever;
				break;
			}

			case capteur4321:
			case capteur321: {
				m->droite = vitesseTNormal;
				m->gauche = vitesseTNormal;
				etatPresent++;
				if(etatPresent > 4){
					etatPresent = 1;
				}
					ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
					_delay_ms(1000);
					if(etatPresent == etatInitial){
						end = true;
					}else{

						ajustementPWMBetter(125- compensateur,125, 1, 0);
						  if(etatPresent==1){
                             _delay_ms(100);
                          }
						while (lireSenseurComplet() != capteur3) {
						}
						end = true;
					}
					break;
			}
		}
				ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
	}
						ajustementPWMBetter(0,0,0,0);
						_delay_ms(500);
	
}