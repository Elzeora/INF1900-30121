#include <section2.h>

//******************************************************************************/
//* nom: parcourirSection2                                                                                                                                   /
//* description: permet de realiser le parcours 2 qui suit la ligne et ralentit dans les courbe
//* Parametre d'entree  : struc moteur
//* Parametre de sortie : aucun
//******************************************************************************/
void parcoursSection2(struct moteur *moteur) {
	int compteur = 0;
	int virage = 0;
	bool fin = false;
	int directionDroite = 0, directionGauche = 0;

	while (!fin) {
		allumerDelSenseur();

		if ((TempsDebutCourbe1 < compteur && compteur < TempsFinCourbe1) || (TempsDebutCourbe2 < compteur && compteur < TempsFinCourbe2)) {

			switch (lireSenseurComplet()) {

			case capteur3: { //centre
				moteur->droite = vitesse2Faible;
				moteur->gauche = vitesse2Faible;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur2: {//ajustement
				moteur->droite = vitesse2Faible;
				moteur->gauche = vitesse2Faible - 20;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur4: {//ajustement
				moteur->droite = vitesse2Faible - 20;
				moteur->gauche = vitesse2Faible;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur1 :
			case capteur21:
			case capteur32: {
				moteur->droite = vitesse2Faible;
				moteur->gauche = compensateur;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur5 :
			case capteur54:
			case capteur34: {
				moteur->droite = 0;
				moteur->gauche = vitesse2Faible;
				directionDroite = 0;
				directionGauche = 0;
				break;

			}
			case capteur321 : 		// dans ces deux cas, on veut faire un tour de 90 vers la gauche
			case capteur4321: {
				if (virage == 2) {
					fin = true;
					moteur->droite = 0;
					moteur->gauche = compensateur;
					directionDroite = 0;
					directionGauche = 0;
				}
				else {	//Dabord on avance pour mettre le centre de gravite du robot sur le coin tournant
					ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 0, 0);
					_delay_ms(Delay_Avancer_Pour_Tourner);
					//Le robot tourne jusqua trouver ligne
					while (lireSenseurComplet() != capteur3) {
						ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 1, 0);
					}
					ajustementPWMBetter(0, 0, 0, 0);
					virage++;
				}

				break;
			}
			case capteur543:
			case capteur5432: { // dans ces deux cas, on veut faire un tour de plus de 90 vers la droite{
				if (virage == 2) {
					fin = true;
					moteur->droite = 0;
					moteur->gauche = compensateur;
					directionDroite = 0;
					directionGauche = 0;
				}
				else { //Dabord on avance pour mettre le centre de gravite du robot sur le coin tournant
					ajustementPWMBetter(vitesse2Elever - compensateur, vitesse2Elever, 0, 0);
					_delay_ms(Delay_Avancer_Pour_Tourner);
					//Le robot tourne jusqua trouver ligne
					while (lireSenseurComplet() != capteur3) {
						ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 0, 1);
					}
					ajustementPWMBetter(0, 0, 0, 0);
					virage++;
				}
				break;
			}
			}
		}
		else {
			switch (lireSenseurComplet()) {

			case capteur3: { //centre
				moteur->droite = vitesse2Elever;
				moteur->gauche = vitesse2Elever;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur2: {//ajustement
				moteur->droite = vitesse2Elever;
				moteur->gauche = vitesse2Faible;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur4: {//ajustement
				moteur->droite = vitesse2Faible;
				moteur->gauche = vitesse2Elever;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur1:
			case capteur21:
			case capteur32: {
				moteur->droite = vitesse2Elever;
				moteur->gauche = compensateur;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur5:
			case capteur54:
			case capteur34: {
				moteur->droite = 0;
				moteur->gauche = vitesse2Elever;
				directionDroite = 0;
				directionGauche = 0;
				break;
			}
			case capteur321: 		// dans ces deux cas, on veut faire un tour de 90 vers la gauche
			case capteur4321: {
				if (virage == 2) {
					fin = true;
					moteur->droite = 0;
					moteur->gauche = compensateur;
					directionDroite = 0;
					directionGauche = 0;
				}
				else {	//Dabord on avance pour mettre le centre de gravite du robot sur le coin tournant
					ajustementPWMBetter(vitesse2Normal - compensateur, vitesse2Normal, 0, 0);
					_delay_ms(Delay_Avancer_Pour_Tourner);
					//Le robot tourne jusqua trouver ligne
					while (lireSenseurComplet() != capteur3) {
						ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 1, 0);
					}
					ajustementPWMBetter(0, 0, 0, 0);
					virage++;
				}
				break;
			}
			case capteur543:
			case capteur5432: { // dans ces deux cas, on veut faire un tour de plus de 90 vers la droite{
				if (virage == 2) {
					fin = true;
					moteur->droite = 0;
					moteur->gauche = compensateur;
					directionDroite = 0;
					directionGauche = 0;
				}
				else { //Dabord on avance pour mettre le centre de gravite du robot sur le coin tournant
					ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 0, 0);
					_delay_ms(Delay_Avancer_Pour_Tourner);
					//Le robot tourne jusqua trouver ligne
					while (lireSenseurComplet() != capteur3) {
						ajustementPWMBetter(vitesse2Faible - compensateur, vitesse2Faible, 0, 1);
					}
					ajustementPWMBetter(0, 0, 0, 0);
					virage++;
				}
				break;
			}
			}
		}
		//ajustementPWMBetter((moteur.gauche - compensateur)-raletissement,(moteur.droite)-raletissement, directionGauche,directionDroite);
		ajustementPWMBetter((moteur->gauche - compensateur), (moteur->droite), directionGauche, directionDroite);
		compteur++;
		if (compteur == TempsFinCourbe2)
		{
			fin= true;
		}
	}
	ajustementPWMBetter(0, 0, 0, 0);
}