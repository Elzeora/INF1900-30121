#ifndef SEGEMENT_H
#define SEGEMENT_H
#define F_CPU 8000000
#include <variable.h>
#include <capteur.h>
#include <pwm.h>
#include <avr/io.h>


//pour parcours 4////////////
#define vitesseFaible 150 ///
#define vitesseNormal 155 ///
#define vitesseElever 160 ///
/////////////////////////////


void parcoursSection3(struct moteur *m);




#endif // SECTION3_H