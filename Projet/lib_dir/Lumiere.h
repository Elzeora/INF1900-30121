#ifndef LUMIERE_H
#define LUMIERE_H

#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>

enum Couleur { Vert, Rouge, Ambre, Off };



void allumerLumiere(Couleur couleur);
void clignoterLumiere(Couleur couleur);

#endif // LUMIERE_H 
