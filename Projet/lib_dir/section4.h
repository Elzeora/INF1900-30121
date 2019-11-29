#ifndef SECTION4_H
#define SECTION4_H
#define F_CPU 8000000
#include <variable.h>
#include <capteur.h>
#include <pwm.h>
#include <avr/io.h>
#include <son.h>


//pour parcours 4////////////
#define vitesse4Faible 150///
#define vitesse4Normal 155///
#define vitesse4Elever 160///
/////////////////////////////


void parcoursSection4(struct moteur *m);




#endif // SECTION4_H

