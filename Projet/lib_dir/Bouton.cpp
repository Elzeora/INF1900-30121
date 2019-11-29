#include <Bouton.h>

//******************************************************************************/
//* nom : antiRebond()
//* description : un simple anti-rebond pour le bouton poussoir qui nous retourne une valeur bool selon si le bouton a ete presse ou non
//* Parametre d'entree  : aucun
//* Parametre de sortie : true ou false selon si il y vraiment eu un clic ou pas
//******************************************************************************/
bool antiRebond() {
    if (PIND & 0x04){    
        _delay_ms (30);
        if (PIND & 0x04){
            return true;
        }
    }
    return false;
}


//******************************************************************************/
//* nom : initBouton
//* description : Modifie les registres de la carte afin de permetre d'accepter les interruptions du bouton poussoir
//* Parametre d'entree  : aucun
//* Parametre de sortie : aucun
//******************************************************************************/
/*void initBouton ( void ) {
    cli ();
    EIMSK |= (1 << INT0) ; // cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre  les interruptions externes
    EICRA |= (1 << ISC00) ; //sensibilise les interruptions externes aux changements de niveau du bouton-poussoir en ajustant le registre EICRA
    sei ();
}*/
