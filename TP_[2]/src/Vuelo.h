/*
 * Vuelo.h
 *
 *  Created on: 10 may. 2022
 *      Author: Agostin
 */

#ifndef VUELO_H_
#define VUELO_H_

#include <stdio.h>
#include <stdlib.h>

#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

#define ACTIVO 1
#define DEMORADO 2
#define CANCELADO 3

#define CODIGO 10

struct
{
	int id;
	char flycode[CODIGO];
	int statusFlight;
	int isEmpty;

}typedef Vuelo;

int vue_initArray(Vuelo* list, int len);
int vue_indexEmpty (Vuelo* list, int len);
int addFlight (Vuelo* list, int len, char* flycode);
int findFlightByCode(Vuelo* list, int len, char* flycode);
int vue_altaForzada (Vuelo* list, int len);
Vuelo vue_UnElementoForzado (int indiceLibre, char* flyCode, int statusFlight);

#endif /* VUELO_H_ */
