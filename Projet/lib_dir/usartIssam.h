/*******************************************************************************
* Titre: INF1900 - tp9 - usart.h
* Description: Génération de PWM selon un certain taux
* Date: 19 mars 2019
* Auteurs : Issam Maghni 1960514, Michael Ogbaghebriel 1965104, 
* Nicolas Lauzon 1959682, Lucas Dameron-Monfrais 1963135
*******************************************************************************/

#ifndef USART_H
#define USART_H

// Si cette entête est incluse depuis un fichier C++, alors on précise
// au compilateur que ce qui suit doit être interprété comme du C.
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* void initPWM(void)                                                         */
/*                                                                            */
/*      Initialisation                                                        */
/*                                                                            */
/*                                                                            */
/* Parametre d'entree  : aucun                                                */
/*                                                                            */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
void initUSART(void);

/******************************************************************************/
/* void receiveChar(void)                                                     */
/*                                                                            */
/*      Réception d’un charactère                                             */
/*                                                                            */
/*                                                                            */
/* Parametre d'entree  : aucun                                                */
/*                                                                            */
/* Parametre de sortie : char                                                 */
/******************************************************************************/
char receiveChar(void);

/******************************************************************************/
/* void printChar(char data)                                                  */
/*                                                                            */
/*      Affichage d’un charactère                                             */
/*                                                                            */
/*                                                                            */
/* Parametre d'entree  : data  -un caractere                                  */
/*                                                                            */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
void printChar(char data);

/******************************************************************************/
/* void printChars(const char *string)                                        */
/*                                                                            */
/*      Afficher du texte                                                     */
/*                                                                            */
/*                                                                            */
/* Parametre d'entree  : string -pointeur vers des caracteres                 */
/*                                                                            */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
void printChars(const char *string);

#ifdef __cplusplus
}
#endif

#endif // USART_H
