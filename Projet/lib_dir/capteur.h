#ifndef CAPTEUR_H
#define CAPTEUR_H
#define F_CPU 8000000
#include <avr/io.h>
#include <can.h>

#define ir1 140
#define ir2 140
#define ir3 140
#define ir4 140
#define ir5 140

	uint8_t lireSenseur(uint8_t pin);

	void allumerDelSenseur();

	uint8_t lireSenseurComplet ();





#endif // CAPTEUR_H

