/*
 * validaciones.h
 *
 *  Created on: 5 abr. 2022
 *      Author: Agostin
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int validacionDosCaracteres (char* mensaje, char caracterUno, char caracterDos);
int validacionCaracter (char *mensaje, char caracter);

int utn_getString(char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos);
int utn_getNombre(char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos);
int utn_getDescripcion (char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos);
int utn_getDNI(char* pNumeroIngresado, char* mensaje, char* mensajeError, int len, int reintentos);

//Para Entero
int utn_getInt(int* pNumeroIngresado, char* mensaje, char* mensajeError, int min, int max, int reintentos);
int utn_getIntRange (int* pNumeroIngresado, char* mensaje, char* mensajeError, int min, int max);
int utn_getIntPositivo (int* pNumeroIngresado, char* mensaje, char* mensajeError);
int utn_getIntNegativo(int* pNumeroIngresado, char* mensaje, char* mensajeError);
int utn_getIntAlone (int* pNumeroIngresado, char* mensaje, char* mensajeError);

//Para Float
int utn_getFloat(float* pNumeroIngresado, char* mensaje, char* mensajeError, float min, float max, int reintentos);
int utn_getFloatPositivo (float* pNumeroIngresado, char* mensaje, char* mensajeError);
int utn_getFloatAlone(float* pNumeroIngresado, char* mensaje, char* mensajeError);

//Para double
int utn_getDouble(double* pNumeroIngresado, char* mensaje, char* mensajeError, double min, double max, int reintentos);
int utn_getDoubleAlone(double* pNumeroIngresado, char* mensaje, char* mensajeError);



void saltoDeLinea (void);
void presionarEnter (void);

#endif /* VALIDACIONES_H_ */
