#include <pwm.h>


//******************************************************************************/
//* nom: ajutementPWM                                                                                                                                            /
//* description: ajuste la puissance du PWM des roues ou la puissance est
//*              un pourcentage de 255 ex(255*0.5  pour un pwm a 50%)
//* Parametre d'entree  : puissanceDroite et puissanceGauche
//* Parametre de sortie : aucun
//******************************************************************************/

void ajustementPWM(uint8_t puissanceGauche, uint8_t puissanceDroite, uint8_t direction){

    DDRD = 0xFF;

    const uint8_t TOP = 0xFF;

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)

    OCR1A = (TOP * puissanceDroite) / 100;
    OCR1B = (TOP * puissanceGauche) / 100;

    if (direction == 1){
        PORTD |= 1 << 6;
        PORTD |= 1 << 7;
    }else{
        PORTD &= 0 << 6;
        PORTD &= 0 << 7;
    }

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A = (1 << WGM10 | 1 << COM1A1 | 1 << COM1B1); // WGM10 Permet de rentrer dans le mode PWM 8-bit phase correcte, COM1A1 ET COM1B1 permet l'activation de OC1A et OC1B
    TCCR1B = (1 << CS11); //Prescaler qui permet de diviser l'horloge par 8
    TCCR1C = 0;

}

//******************************************************************************/
//* nom: ajutementPWMBetter                                                                                                                                            /
//* description: ajuste la puissance du PWM des roues selon 0 a 255 et permet de choisir la 
//*        direction de chaque roue
//* Parametre d'entree  : puissanceDroite et puissanceGauche
//* Parametre de sortie : aucun
//******************************************************************************/
void ajustementPWMBetter(uint8_t puissanceGauche, uint8_t puissanceDroite, uint8_t directionGauche, uint8_t directionDroite){

    DDRB = 0xFF;

    //const uint8_t TOP = 0xFF;
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)

    OCR0A = puissanceGauche;//sort du portB3
    OCR0B = puissanceDroite;//sort du portB4

    //la direction des moteurs
    if (directionGauche) {  //le bit directionnel du moteur gauche sort de portb2
        PORTB |= 1 << 2;
    }else{
        PORTB &= ~(1 << 2);
    }
    if(directionDroite){    //le bit directionnel du moteur gauche sort de portb5
        PORTB |= 1 << 5;
    }else{
        PORTB &= ~(1 << 5);
    }

    // WGM00 Permet de rentrer dans le mode PWM 8-bit phase correcte, COM1A1  permet l'activation de OC1A 
    TCCR0A = 1 << WGM00 | 1 << COM0A1 | 1 << COM0B1; 
    //Prescaler qui permet de diviser l'horloge par 8
    TCCR0B = (1 << CS01); 

}

