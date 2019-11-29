#ifndef VARIABLE_H
#define VARIABLE_H
#include <avr/io.h>
#include <util/delay.h>

#define compensateur 10
#define VERT 1
#define ROUGE 2
#define SORTIE 0xFF
#define ENTREE 0x00


//variable pour les capteurs
enum capteur : uint8_t {		//milieu
	capteur3 = 0b00000100,
	//milieu droite
	capteur1    = 0b00000001,
	capteur32   = 0b00000110,
	capteur2    = 0b00000010,
	capteur321  = 0b00000111,
	capteur4321 = 0b00001111,
	capteur21   = 0b00000011,
	capteur234  = 0b00001110,
	//milieu gauche
	capteur5    = 0b00010000,
	capteur34   = 0b00001100,
	capteur4    = 0b00001000,
	capteur543  = 0b00011100,
	capteur5432 = 0b00011110,
	capteur54 	= 0b00011000,
	//full ou pas
	capteur12345 = 0b00011111,
	capteur0 = 0b00000000
};

//variable enum pour les section
enum section : uint8_t {
	section1 = 1,
	section2 = 2,
	section3 = 3,
	section4 = 4
};

//struct pour le moteur
struct moteur {
	uint8_t droite;
	uint8_t gauche;
};


#endif // VARIABLE_h
