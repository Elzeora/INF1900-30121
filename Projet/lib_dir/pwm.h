#ifndef PWM_H
#define PWM_H

#include <avr/io.h> 

void ajustementPWM (uint8_t puissanceGauche, uint8_t puissanceDroite, uint8_t direction);

void ajustementPWMBetter(uint8_t puissanceGauche, uint8_t puissanceDroite, uint8_t directionGauche, uint8_t directionDroite);
#endif // PWM_H