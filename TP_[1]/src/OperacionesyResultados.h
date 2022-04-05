/*
 * OperacionesyResultados.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */

#ifndef OPERACIONESYRESULTADOS_H_
#define OPERACIONESYRESULTADOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define PRECIO_BITCOIN 4606954.55
#define DEBITO 10.00
#define CREDITO 25.00

void cargaForzada (int* kilometros,float* precioAero,float* precioLatam);

void validacionCalculo(int kilometros, float precioAero, float precioLatam, float* debitoA,float* creditoA, float* bitcoinA, float* unitarioA, float* debitoL, float* creditoL, float* bitcoinL, float* unitarioL, float* diferenciaPrecio);

void calculoVuelo (int kilometros,float precioVuelo,float** debito,float** credito, float** bitcoin, float** unitario);


void mostrarResultados (char* vuelo, float precioVuelo, float debito,float credito, float bitcoin, float unitario);
void mostrarDiferencia (float difereciaPrecio);

#endif /* OPERACIONESYRESULTADOS_H_ */
