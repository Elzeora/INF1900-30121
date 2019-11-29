#define section1_H
#ifdef  section1_H

#include "pwm.h"
#include "variable.h"
#include "capteur.h"
#include <util/delay.h>
#include "son.h"
#include "receptionIR.h"
#define F_CPU 8000000


//pour parcours 4////////////
#define vitesse1Faible 150///
#define vitesse1Normal 160///
#define vitesse1Elever 170///
/////////////////////////////
//variable section 1
enum points{p1 = 1, p2, p3, p4, p5, p6, p7, p8, p9};
///////////////////////////////////////////////////////
const int tournerDroite = 750, tournerGauche = 660;///
//representent le temps necessaire ////////////////////
//pour se rendre a la coordonnee//////////
// a modifier pour calibrer///////////////
const int ligne[3] = {2700,2200,1700}; ///
const int colonne[3] = {2615,2115,1615};///
//////////////////////////////////////////


void parcourirMatrice(struct moteur *m, const int ligne, const int colonne);
void choisirPoint(struct moteur *m,uint8_t valeur);



#endif



