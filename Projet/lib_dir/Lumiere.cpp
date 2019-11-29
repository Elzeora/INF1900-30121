#include <Lumiere.h>


//******************************************************************************/
//* nom: allumerLumiere
//* description: setter qui change la couleur de la lumiere (ou qui la ferme si couleur == Off)
//*				ATTENTION: pour la lumiere ambre, il faut utiliser cette methode dans une boucle
//* Parametre d'entree  : Couleur couleur
//* Parametre de sortie : aucun
//******************************************************************************/
void allumerLumiere(Couleur couleur) {
	switch (couleur) {
	case Vert:
		PORTB = 1;
		break;
	case Rouge:
		PORTB = 2;
		break;

	case Ambre:
		PORTB = 1;
		_delay_ms(15);
		PORTB = 2;
		_delay_ms(10);
		break;
	case Off:
		PORTB = 0;
		break;

	}
}

//******************************************************************************/
//* nom: clignoterLumiere
//* description: methode de clignotement qui clignote 1 fois, a la frequence de 2 fois par secondes. La duree de clignotement doit se faire a l'appel de la fonction
//* Parametre d'entree  : Couleur couleur
//* Parametre de sortie : aucun
//******************************************************************************/
void clignoterLumiere (Couleur couleur) {
	allumerLumiere(couleur);
	_delay_ms(250);
	allumerLumiere(Off);
	_delay_ms(250);

}


