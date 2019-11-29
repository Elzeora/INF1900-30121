#include "son.h"



//******************************************************************************/
//* nom: produireSon                                                                                                                          /
//* description: permet produre du son
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void produireSon(uint8_t note)
{

    TCCR2A |= (1 << COM2A0) | (1 << WGM21);
    TCCR2B |= (1 << CS22);
   
    double frequenceNote = tabFrequences[note - 45];
    OCR2A = 8000000 * (1 / frequenceNote) / 2 / 256; //Le pwm sort dans la pin 3 du port B
}


//******************************************************************************/
//* nom: arreterSon                                                                                                                                   /
//* description: permet d,arreter le son
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
void arreterSon()
{
	TCCR2A &= (0 << COM2A0);
}
