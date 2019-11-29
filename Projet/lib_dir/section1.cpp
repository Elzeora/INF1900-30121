#include "section1.h"

//******************************************************************************/
//* nom: chosirPoint                                                                                                                                           /
//* description: permet de sélectionner une case dans un tableau selon une valeur
//* Parametre d'entree  : struc moteur et valeur
//* Parametre de sortie : aucun
//******************************************************************************/
void choisirPoint(struct moteur *m, uint8_t valeur){
	switch(valeur){
				case p1:{
					parcourirMatrice(m, ligne[0], colonne[0]);
					break;
				}
				case p2:{
					parcourirMatrice(m,ligne[0], colonne[1]);
					break;
				}
				case p3:{
					parcourirMatrice(m,ligne[0], colonne[2]);
					break;
				}
				case p4:{
					parcourirMatrice(m,ligne[1], colonne[0]);
					break;
				}
				case p5:{
					parcourirMatrice(m,ligne[1], colonne[1]);
					break;
				}
				case p6:{
					parcourirMatrice(m,ligne[1], colonne[2]);
					break;
				}
				case p7:{
					parcourirMatrice(m,ligne[2], colonne[0]);
					break;
				}
				case p8:{
					parcourirMatrice(m,ligne[2], colonne[1]);
					break;
				}
				case p9:{
					parcourirMatrice(m,ligne[2], colonne[2]);
					break;
				}
			}
}

//******************************************************************************/
//* nom: parcourirMatrice                                                                                                                                      /
//* description: permet de realiser le parcours 1, soit aller jusqua un point donne
//* Parametre d'entree  : struc moteur, int ligne et in colonne
//* Parametre de sortie : aucun
//******************************************************************************/
void parcourirMatrice(struct moteur *m, const int ligne, const int colonne){

	//aller tout droit jusqu'a la ligne 
	ajustementPWMBetter(255,255,0,0);
	_delay_ms(50);
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(m->gauche-8, m->droite, 0, 0);
	for (int i = 0; i< ligne; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(500);
					
	//tourner sur place a gauche 90
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(255, 255, 1, 0);
	_delay_ms(100);
	ajustementPWMBetter(m->gauche-8, m->droite, 1, 0);
	for (int i = 0; i< tournerGauche; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(500);

	//aller tout droit jusqua la colonne 
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(m->gauche-8, m->droite, 0, 0);
	for (int i = 0; i< colonne; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(500);

	//tourner de 90 vers la droite pour pointer vers S4 et etre parallele a S3
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(255, 255, 0, 1);
	_delay_ms(100);
	ajustementPWMBetter(m->gauche-8, m->droite, 0, 1);
	for (int i = 0; i< tournerDroite; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(50);

	//attendre 3 secondes et emettre un son grave
	produireSon(45);
	_delay_ms(3000);
	arreterSon();
								
	//tourner de 90 vers la droite (sens horaire)
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(255, 255, 0, 1);
	_delay_ms(100);
	ajustementPWMBetter(m->gauche-8, m->droite, 0, 1);
	for (int i = 0; i< tournerDroite; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(50);

	//attendre 3 secondes et emettre un son grave
	produireSon(45);
	_delay_ms(3000);
	arreterSon();

	//aller tout droit jusqua la "ligne de depart" en utilisant la colonne 
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(m->gauche-compensateur, m->droite, 0, 0);
	for (int i = 0; i< colonne; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(500);

	//tourner sur place a gauche 90
	m->gauche = vitesse1Normal;
	m->droite = vitesse1Normal;
	ajustementPWMBetter(255, 255, 1, 0);
	_delay_ms(100);
	ajustementPWMBetter(m->gauche-8, m->droite, 1, 0);
	for (int i = 0; i< tournerGauche; i++){
		_delay_ms(1);
	}
	ajustementPWMBetter(0, 0, 0, 0);
	_delay_ms(500);


	        //aller tout droit jusqua ce quil revoit la ligne de S3
	uint16_t compteurLOL =0;
	bool lignetrouvee = false;
while(!lignetrouvee){
	     m->gauche = vitesse1Faible;
         m->droite = vitesse1Faible;
         if(compteurLOL < 400){
         	ajustementPWMBetter(m->gauche-8,m->droite,0,0);
         	if(lireSenseurComplet() != capteur0 ){
         		lignetrouvee = true;
         	}
         }
         if(401<compteurLOL && compteurLOL<600){
         	ajustementPWMBetter(m->gauche-8,m->droite,0,1);
         	if(lireSenseurComplet() != capteur0 ){
         		lignetrouvee = true;
         	}
         }
         if(601<compteurLOL && compteurLOL<1000){
         	ajustementPWMBetter(m->gauche-8, m->droite,1,0);
         	if(lireSenseurComplet() != capteur0 ){
         		lignetrouvee = true;
         	}
         }
         if(1001<compteurLOL && compteurLOL<1200){
         	ajustementPWMBetter(m->gauche-8,m->droite,0,1);
         	if(lireSenseurComplet() != capteur0 ){
         		lignetrouvee = true;
         	}
         }
         if(compteurLOL>1201){
         	compteurLOL=0;
         }
         compteurLOL++;
}
        ajustementPWMBetter(0,0,0,0); // arrete et appele la fonction tourner dans le main


}
