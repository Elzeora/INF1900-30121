#ifndef TOURNER_H
#define TOURNER_H
#define F_CPU 8000000
#include <variable.h>
#include <capteur.h>
#include <pwm.h>
#include <avr/io.h>


/////////////////////////////
#define vitesseTFaible 140///
#define vitesseTNormal 150///
#define vitesseTElever 165///
/////////////////////////////


void tourner(struct moteur *m, uint8_t etatInitial, uint8_t &etatPresent);


#endif // VARIABLE_h