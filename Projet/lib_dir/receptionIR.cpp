#include "receptionIR.h"


//******************************************************************************/
//* nom: recevoirIR
//* description:  permet de recevoir un signal infra rouge selon le protocole Sony SIRC
//* Parametre d'entree  : (bool) interruption un bool qui permet de savoir si le bouton 
//*  		a ete appuyer ou pas
//* Parametre de sortie : la valeur du signal infra rouge
//******************************************************************************/
uint8_t recevoirIR(volatile bool  &interruption) {


 
	DDRC &= ~(1 << DDC5);
	uint8_t positionPremierZero,positionRecherche,message[75], nbDeUnConsecutif=0,commande=0, adresse=0;
	uint16_t code=0;

debut:
	if (interruption){
		return 0;
	}
	//prendre tout le message. exemple pour zero: 10 et un: 110
	for(uint8_t i=0; i<75 ;i++){
		message[i] = !(PINC & (1<<5));
		_delay_us(600);
	}
	//permet de de savoir ou est le premier zero et 
	//de se positionner juste apres 
	for(uint8_t i=0; i < 75;i++){
		if(message[i]){
			positionPremierZero = i;
			positionRecherche = i+1;
		}
	}

	//permet de trouver ou est la sequence de debut 
	//dans le message pour savoir ou est la commande et l'adresse
	do {
		if(message[positionRecherche]){
			nbDeUnConsecutif++;
		}else{
			nbDeUnConsecutif = 0;
		}
		positionRecherche = (positionRecherche + 1) % 75;
	} while(positionRecherche !=positionPremierZero && nbDeUnConsecutif < 4);

	//permet de detecter si le message à bien été lu sans erreur 
	//car si la positionRecherche est = a positionPremierZero
	//alors il a parcourus tout le tableau sans avoir trouve la 
	//sequence de debut. Sinon la a la position suivante il y a encore un 1 alos
	//le message a ete lu avec une erreur 
	if(positionRecherche == positionPremierZero || message[positionRecherche]){
		goto debut;
	}

	for(uint8_t i=0; i < 12;i++){
		if(!message[++positionRecherche % 75]){
			goto debut;
		}
		if(message[++positionRecherche % 75]){
			if(message[++positionRecherche]){
				goto debut;
			}
			code |= 1 << i;
		}
	}

	adresse = code >> 7;
	commande = code & 0b01111111;
	return commande;
}

	