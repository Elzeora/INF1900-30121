#ifndef SECTION2_H
#define SECTION2_H
#define F_CPU 8000000
#include <variable.h>
#include <capteur.h>
#include <pwm.h>
#include <avr/io.h>

//pour parcours 2
//////////////////////////////////
#define TempsDebutCourbe1 600  ///
#define TempsFinCourbe1 1600   ///
#define TempsDebutCourbe2 3500 ///
#define TempsFinCourbe2 4500   ///
/////////////////////////////////////////////////
#define Delay_Avancer_Pour_Tourner 800        ///
#define Delay_Avancer_Pour_Tourner_Ralenti 900///
/////////////////////////////////////////////////
#define vitesse2Faible 135///
#define vitesse2Normal 150///
#define vitesse2Elever 185///
/////////////////////////////


void parcoursSection2(struct moteur *m);


#endif // SECTION2_H