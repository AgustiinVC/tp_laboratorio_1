/*
 * OperacionesyResultados.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agostin
 */

#ifndef OPERACIONESYRESULTADOS_H_
#define OPERACIONESYRESULTADOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define PRECIO_BITCOIN 4606954.55
#define DEBITO 10.00
#define CREDITO 25.00

void cargaForzada (int *kilometros,float *precioAero,float *precioLatam);

void validacionCalculo(int kilometros, float precioAero, float precioLatam, float *debitoA,float *creditoA, float *bitcoinA, float *unitarioA, float *debitoL, float *creditoL, float *bitcoinL, float *unitarioL, float *diferenciaPrecio);

void calculoAero (int kilometros,float precioAero,float precioLatam,float **debitoA,float **creditoA, float **bitcoinA, float **unitarioA);
void calculoLatam (int kilometros,float precioAero,float precioLatam,float **debitoL, float **creditoL, float **bitcoinL, float **unitarioL);



void mostrarResultadosAero (float precioAero,float precioLatam,float debitoA,float creditoA, float bitcoinA, float unitarioA);
void mostrarResultadosLatam (float precioLatam,float debitoL, float creditoL, float bitcoinL, float unitarioL);
void mostrarDiferencia (float difereciaPrecio);

#endif /* OPERACIONESYRESULTADOS_H_ */
