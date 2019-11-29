#include "UART.h"
#include "string.h"

/******************************************************************************/
//* nom : initialisationUART
//* description :  permet d'ajuster correctement la configuration de l'UART
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
/******************************************************************************/
void initialisationUART () {

// 2400 bauds. Nous vous donnons la valeur des deux
// premier registres pour vous éviter des complications
UBRR0H = 0;
UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0s
    UCSR0A  = 0; //reception
    UCSR0B |= (1 << RXEN0)|(1 << TXEN0); //transmission
    

// Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (1<< UCSZ01)|(1 << UCSZ00);
}
/******************************************************************************/
//* nom : transmettreAffichageUART
//* description : De l'USART vers le PC
//* Parametre d'entree  : char un tableau de char 
//* Parametre de sortie : aucun
/******************************************************************************/
void transmettreAffichageUART(char texte[], uint16_t dimensionTab) {
   // for (uint8_t i = 0; i < dimensionTab; i++ ) {
        for (uint16_t j = 0; j < dimensionTab; j++ )
            transmissionUART(texte[j]);
   // }
    
}
/******************************************************************************/
//* nom : transmissionUART
//* description : De l'USART vers le PC
//* Parametre d'entree  : uint8_t donnee les donnee qu'on souhaite transmetre
//* Parametre de sortie : aucun
/******************************************************************************/
void transmissionUART ( uint8_t donnee ) {
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = donnee;
}

uint8_t receptionUART() {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}


void debugUART(char texte[]){
    initialisationUART();
    transmettreAffichageUART(texte, strlen(texte));
}
