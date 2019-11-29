 #include <avr/io.h> 

 #include "librairie.h"

 #define DEBUG // à mettre en commentaire au besoin

#ifdef DEBUG

# define DEBUG_PRINT(x) debugUART(char texte[], uint8_t dimensionTab) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif
