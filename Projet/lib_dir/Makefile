########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   		EQUIPE 30-121				 #####
#####           INF1900 - 2018               #####
#####                                        #####
#####Inspire de Simon Barrette & Jerome Collin ###
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++


#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers a compiler, separes par
# un espace. exemple: 'tp1.c tp2.cpp':
PRJSRC= $(wildcard *.cpp)

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

#compilateur utilise
CC=avr-gcc

#pour produire une librairie statique
AR=avr-ar

#les options c (pour créer l'archive), 
#r (pour insérer les fichiers membres) et 
#s (pour produire en plus l'index des fichiers objets) 
ARFLAGS=-crs

#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f


# Flags pour le compilateur en C
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -DF_CPU=8000000 #pour utiliser les delay dans la librairie

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

#Nom des cibles par defaut
TRG=libStatique.a

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS= $(PRJSRC:.cpp=.o)
	

####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean 

all: $(TRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) $@ $^

# Production des fichiers object
# De C a objet	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<



# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

test:
	@echo "PRJSRC = $(PRJSRC)"
	@echo "OBJDEPS = $(OBJDEPS)"

debug: CCFLAGS += -DDEBUG -g
debug: all