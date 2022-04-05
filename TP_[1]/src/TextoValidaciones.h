/*
 * TextoValidaciones.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */

#ifndef TEXTOVALIDACIONES_H_
#define TEXTOVALIDACIONES_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void menu (int kilometros, float precioAero, float precioLatam);
int getInt (char *mensaje);
float getFloat(char *mensaje);

unsigned int validacionCaracteres (char *mensaje, char caracterUno, char caracterDos);

void saltoDeLinea(void);
void alerta (char *mensaje);

//void ingresoOtroVuelo (char* mensaje, char* vueloUno, char* vueloDos , float* precioVueloUno, float* precioVueloDos);




#endif /* TEXTOVALIDACIONES_H_ */
