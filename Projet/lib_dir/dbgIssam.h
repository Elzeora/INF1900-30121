/*******************************************************************************
* Titre: INF1900 - tp9 - Debug.h
* Nous permet de faire le debogage
* Date: 19 mars 2019
* Auteurs : Issam Maghni 1960514, Michael Ogbaghebriel 1965104, 
* Nicolas Lauzon 1959682, Lucas Dameron-Monfrais 1963135
*******************************************************************************/

#ifndef DBG_H
#define DBG_H

#include "usartIssam.h"

#ifndef CHUNK
#define CHUNK 128u
#endif

#ifdef DEBUG
/// https://stackoverflow.com/a/8713662/11161541
// THIS IS NOT PART OF C, BUF RATHER A COMPILER-SPECIFIC FEATURE (gcc and clang)
// ERROR: DEFINED IN BOTH LIBRARY AND EXECUTABLE
//void __attribute__((constructor)) initDebugBeforeMain() { initUSART(); }
#define DEBUG_INIT initUSART()
#define DEBUG_PRINT(msg) _printf("(%s:%d) " msg, __FILE__, __LINE__)
#define DEBUG_PRINTF(fmt, ...)                                                 \
	_printf("(%s:%d) " fmt, __FILE__, __LINE__, __VA_ARGS__)
#else
#define DEBUG_INIT
#define DEBUG_PRINT(x)
#define DEBUG_PRINTF(...)
#endif

// Si cette entête est incluse depuis un fichier C++, alors on précise
// au compilateur que ce qui suit doit être interprété comme du C.
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* void _printf(const char *format, ...)                                       */
/*                                                                            */
/*      Genere le texte formatee a l'usart                                    */
/*                                                                            */
/*                                                                            */
/* Parametre d'entree  : *format    -format d'affichage                       */
/*                       ...        -permet d'accepter un nombre indetermine  */
/*                                   de parametres                            */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
void _printf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // DBG_H
