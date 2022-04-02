/*
 * OperacionesyResultados.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Agostin
 */
#include "OperacionesyResultados.h"

void cargaForzada (int* kilometros,float *precioAero,float *precioLatam)
{
	*kilometros = 7090;
	*precioAero = 162925;
	*precioLatam = 159339;
}

void validacionCalculo(int kilometros, float precioAero, float precioLatam, float* debitoA,float* creditoA, float* bitcoinA, float* unitarioA, float* debitoL, float* creditoL, float* bitcoinL, float* unitarioL, float* diferenciaPrecio)
{
	if (kilometros != 0 && precioAero !=0)
	{
		calculoAero(kilometros, precioAero, precioLatam, &debitoA, &creditoA, &bitcoinA, &unitarioA);
		puts ("Calculo de Aerolineas realizado.");
	}

	if (kilometros != 0 && precioLatam !=0)
	{
		calculoLatam(kilometros, precioAero, precioLatam, &debitoL, &creditoL, &bitcoinL, &unitarioL);
		puts ("Calculo de Latam realizado.");
	}

	if (kilometros == 0)
	{
		puts ("Todavia no ingresaste los kilómetros por lo que no se puede realizar los cálculos.");
	}

	if (precioAero == 0 && precioLatam == 0)
	{
		puts ("Todavia no ingresaste ningun precio de vuelo por lo que no se puede realizar los cálculos.");
	}
	else
	{
		*diferenciaPrecio = precioAero - precioLatam;
	}
}


void calculoAero (int kilometros,float precioAero,float precioLatam,float** debitoA,float** creditoA, float** bitcoinA, float** unitarioA)

{
	**debitoA = precioAero * (1 - DEBITO/100);
	**creditoA = precioAero * (1 + CREDITO/100);
	**bitcoinA = precioAero / PRECIO_BITCOIN;
	**unitarioA = precioAero / kilometros;

}
void calculoLatam (int kilometros,float precioAero,float precioLatam,float** debitoL, float** creditoL, float** bitcoinL, float** unitarioL)
{
	**debitoL = precioLatam * (1 - DEBITO/100);
	**creditoL = precioLatam * (1 + CREDITO/100);
	**bitcoinL = precioLatam / PRECIO_BITCOIN ;
	**unitarioL = precioLatam / kilometros;
}


void mostrarResultadosAero (float precioAero,float precioLatam,float debitoA,float creditoA, float bitcoinA, float unitarioA)
{
	printf ("\nPrecio Aerolíneas: $%.2f\n", precioAero);
	printf ("a)Precio con tarjeta de débito: $%.2f\n", debitoA);
	printf ("b)Precio con tarjeta de crédito: $%.2f\n", creditoA);
	printf ("c)Precio pagando con bitcoin: %.2f BTC\n", bitcoinA);
	printf ("d)Mostrar precio unitario: $%.2f por Km.\n", unitarioA);

}

void mostrarResultadosLatam (float precioLatam,float debitoL, float creditoL, float bitcoinL, float unitarioL)
{
	printf ("\nPrecio Aerolíneas: $%.2f\n", precioLatam);
	printf ("a)Precio con tarjeta de débito: $%.2f\n", debitoL);
	printf ("b)Precio con tarjeta de crédito: $%.2f\n", creditoL);
	printf ("c)Precio pagando con bitcoin: %.2f BTC\n", bitcoinL);
	printf ("d)Mostrar precio unitario: $%.2f por Km.\n", unitarioL);

}

void mostrarDiferencia (float diferenciaPrecio)
{
	printf ("La diferencia de precio es: $%.2f", diferenciaPrecio);
}

