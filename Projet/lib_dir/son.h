#ifndef SON_H
#define SON_H
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


const double tabFrequences[] =
    {110.0, 116.5409404, 123.4708253, 130.8127827, 130.5913155, 146.832384, 155.5634919, 164.8137785, 174.6141157,
     184.9972114, 195.997718, 207.6523488, 220.0, 233.0818808, 246.9416506, 261.6255653, 277.182631, 293.6647679, 311.1269837,
     329.6275569, 349.2282314, 369.9944227, 391.995436, 415.3046976, 440.0, 466.1637615, 493.8833013, 523.2511306, 554.365262,
     587.3295358, 622.2539674, 659.2551138, 69.4564629, 739.9888454, 783.990872, 830.6093952, 880.0};



void produireSon(uint8_t note);
void arreterSon();


#endif // SON_H 