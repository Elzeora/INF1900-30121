#ifndef UART_H
#define UART_H

#include <avr/io.h> 
#include <util/delay.h>

//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include <memoire_24.h>


    void initialisationUART ();
    void transmissionUART ( uint8_t donnee );
    void transmettreAffichageUART(char texte[],uint16_t dimensionTab);
    void debugUART(char texte[]);
	uint8_t receptionUART();
   



#endif // UART_H
