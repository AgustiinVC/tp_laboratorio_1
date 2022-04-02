/*
 * TextoValidaciones.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agostin
 */

#ifndef TEXTOVALIDACIONES_H_
#define TEXTOVALIDACIONES_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void menu (int kilometros, float precioAero, float precioLatam);
int getInt (char *mensaje);
float getFloat(char *mensaje);
unsigned int validacionAero (void);
unsigned int validacionSiNo (char *mensaje);
void saltoDeLinea(void);
void alerta (char *mensaje);



#endif /* TEXTOVALIDACIONES_H_ */
