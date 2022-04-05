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
int getInt (int * nroIngresado, char *mensaje, char* mensajeError, int min);
int getFloat (float * nroIngresado, char *mensaje, char* mensajeError, float min);

unsigned int validacionCaracteres (char *mensaje, char caracterUno, char caracterDos);

void saltoDeLinea(void);

//void ingresoOtroVuelo (char* mensaje, char* vueloUno, char* vueloDos , float* precioVueloUno, float* precioVueloDos);




#endif /* TEXTOVALIDACIONES_H_ */
