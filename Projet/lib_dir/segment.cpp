#include <segment.h>

//******************************************************************************/
//* nom: parcourirSection3                                                                                                                                  /
//* description: permet de realiser le parcours 3, soit le decodage des segments
//* Parametre d'entree  : struc moteur
//* Parametre de sortie : aucun
//******************************************************************************/
void parcoursSection3(struct moteur *m){

  	uint16_t temps1 =0;
    uint16_t temps2 =0;
    uint16_t compteur2 = 0;
    char codeDroite[2];
    bool fin = false;
    bool fin2 = false;
    bool tapeNoire1 = false;
    bool tapeNoire2 = false;
		while (!fin2) {
			switch (lireSenseurComplet()) {
			case capteur3: {
				m->droite = vitesseNormal;
				m->gauche = vitesseNormal;
				break;
			}
			case capteur2: {
				m->droite = vitesseElever;
				m->gauche = compensateur;
				break;
			}
			case capteur4: {
				m->droite = 0;
				m->gauche = vitesseElever;
				break;
			}
			case capteur4321:
			case capteur321:
			case capteur543:
			case capteur5432:
			case capteur12345: {
				m->gauche = compensateur;
				m->droite = 0;
				fin2 = true;
				break;
			}
		}
		ajustementPWMBetter(m->gauche - compensateur, m->droite, 0, 0);
	}

	ajustementPWMBetter(0, 0, 0, 0);
	fin2 = false;

	while (!fin2) {
		allumerDelSenseur();
		if (PIND & 0x04) {
			_delay_ms (30);
			if (PIND & 0x04) {
				fin2 = true;
			}
		}
	}

     while(!fin){        
        if(tapeNoire1){
            if(lireSenseurComplet() !=  capteur321 || lireSenseurComplet() != capteur4321 || lireSenseurComplet() !=  capteur21){
                if(temps1 == 0){
                        temps1 = compteur2;
                        codeDroite[0] = 'B';
                        compteur2 =0;
                }else{
                        temps2 = compteur2;
                }
                tapeNoire1 = false;
            }
		}

        if(tapeNoire2){
            if(lireSenseurComplet() !=  capteur543 || lireSenseurComplet() != capteur5432 || lireSenseurComplet() != capteur54){
                if(temps1 == 0){
                        temps1 = compteur2;
                        codeDroite[0] = 'A';
                        compteur2 =0;
                }else{
                        temps2 = compteur2;
                }
                tapeNoire2 = false;
            }
        }

    		switch ( lireSenseurComplet() ) {
                    case capteur3: {
                            m->droite = vitesseNormal;
                            m->gauche = vitesseNormal;
                        break;
                    }

                    case capteur32: {
                            m->droite = vitesseElever;
                            m->gauche = vitesseFaible;
                        break;
                    }                        

                    case capteur2: {
                            m->droite = vitesseElever;
                            m->gauche = compensateur;                                        
                        break;
	                }                                                        

                    case capteur34: {
                            m->droite = vitesseFaible;
                            m->gauche = vitesseElever;
	                    break;
                    }                
                    case capteur4: {
	                        m->droite = 0;
	                        m->gauche = vitesseElever;                        
	                    break;
                    }
                    case capteur12345: {
                            m->droite = vitesseNormal;
                            m->gauche = vitesseNormal;
                            compteur2 = 0;
                        break;
                    }                                
                    case capteur0: {
                            m->droite = 0;
                            m->gauche = compensateur;
                            fin = true;
                        break;
                    }                        
                    case capteur321 :
                    case capteur4321:
                    case capteur21  : {
                            m->droite = vitesseNormal;
                            m->gauche = vitesseNormal;
                            _delay_ms(50);
                            if(lireSenseurComplet() == capteur321 || lireSenseurComplet() == capteur4321 || lireSenseurComplet() ==  capteur21){
                                    tapeNoire1 = true;
                            }else{
                                    tapeNoire1 = false;
                            }
                            break;
                    }

                    case capteur543 :
                    case capteur5432:
                    case capteur54  : {
                            m->droite = vitesseNormal;
                            m->gauche = vitesseNormal;
                            _delay_ms(50);
                            if(lireSenseurComplet() == capteur543 || lireSenseurComplet() == capteur5432 || lireSenseurComplet() == capteur54){
                                    tapeNoire2 = true;
                            }else{
                                   tapeNoire2 = false;
                            }
                             break;  
                    }         
                                
        	}

        compteur2++;
        ajustementPWMBetter(m->gauche-compensateur,m->droite,0,0);
    }
    ajustementPWMBetter(0,0,0,0);
            if(temps1*2 < temps2){
                    codeDroite[1] = 'B';
            }else{
                    codeDroite[1] = 'A';
            }          

            PORTC = 0b00000000;

            if(codeDroite[0] == 'A' && codeDroite[1] == 'A'){
                            PORTC = 0b00001000;
            }
            if(codeDroite[0] == 'A' && codeDroite[1] == 'B'){
                            PORTC= 0b00000100;
            }
            if(codeDroite[0] == 'B' && codeDroite[1] == 'A'){
                            PORTC = 0b00000010;
            }
            if(codeDroite[0] == 'B' && codeDroite[1] == 'B'){
                            PORTC = 0b00000001;
            }   
            _delay_ms(4000);


            fin2 =false;
	
	while (!fin2) {
		if (PIND & 0x04) {
			_delay_ms (30);
			if (PIND & 0x04) {
				fin2 = true;
			}
		}
	}	


}




