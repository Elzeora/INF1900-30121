#include <capteur.h>




//******************************************************************************/
//* nom : lireSenseur()
//* description : permet de lire un capteur selon un certain pin
//* Parametre d'entree  : (uint8_t) pin 
//* Parametre de sortie : la valeur du capteur au moment de l'appel de la fonction
//******************************************************************************/
uint8_t lireSenseur(uint8_t pin){
can convertisseur = can();
return convertisseur.lecture(pin) >> 2;
}


//******************************************************************************/
//* nom : allumerDelSenseur()
//* description : permet d'allumer les led en fonction des capteurs 
//* Parametre d'entree  : rien
//* Parametre de sortie : rien
//******************************************************************************/
void allumerDelSenseur(){
	if(lireSenseur(PINA0) < ir1){
		PORTC |= 0b00000001;
	}else{
		PORTC &= 0b11111110;
	}
	if(lireSenseur(PINA1) < ir2){
		PORTC |= 0b00000010;
	}else{
		PORTC &= 0b11111101;
	}
	if(lireSenseur(PINA2) < ir3){
		PORTC |= 0b00000100;
	}else{
		PORTC &= 0b11111011;
	}
	if(lireSenseur(PINA3) < ir4){
		PORTC |= 0b00001000;
	}else{
		PORTC &= 0b11110111;
	}
	if(lireSenseur(PINA4) < ir5){
		PORTC |= 0b00010000;
	}else{
		PORTC &= 0b11101111;
	}
}

//******************************************************************************/
//* nom : lireSenseurComplet()
//* description : permet de stocker l'etat de tout les capteurs en un moment precis
//* Parametre d'entree  : rien 
//* Parametre de sortie : un 8 bit qui qui correspont a l'etat des capteurs 
//******************************************************************************/
uint8_t lireSenseurComplet(){
	allumerDelSenseur();
    uint8_t temp = 0b0;
    if (lireSenseur(PINA0) < ir1)
        temp |= 1;
    if (lireSenseur(PINA1) < ir2)
        temp |= 1 << 1;
    if (lireSenseur(PINA2) < ir3)
        temp |= 1 << 2;
    if (lireSenseur(PINA3) < ir4)
        temp |= 1 << 3;
    if (lireSenseur(PINA4) < ir5)
        temp |= 1 << 4;

    return temp;

}

