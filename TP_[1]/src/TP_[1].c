/*
 ============================================================================
 Name        : TP_[1].c
 Author      : Vallario Cores, Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : TP Número 1 - Agencia de Viaje
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "TextoValidaciones.h"
#include "OperacionesyResultados.h"

int main(void) {
	setbuf(stdout,NULL);

	int nroIngresado;
	char aerolineaElegida;

	int kilometros = 0;
	float precioAero = 0;
	float precioLatam = 0;
	int flagCalculo = 0;

	float debitoA;
	float creditoA;
	float bitcoinA;
	float unitarioA;

	float debitoL;
	float creditoL;
	float bitcoinL;
	float unitarioL;

	float diferenciaPrecio;

	do
	{
		menu(kilometros, precioAero, precioLatam);
		nroIngresado = getInt ("\nIngrese un numero: ");
		switch (nroIngresado) {
		case 1:
			kilometros = getInt("1. Ingresar Kilómetros: ");
			break;

		case 2:
			aerolineaElegida = validacionAero();
			if (aerolineaElegida)
			{
				precioAero = getFloat("Ingresar el precio de Aerolineas: ");
				if(validacionSiNo("\nDesea ingresar otra aerolinea? (S/N) "))
				{
					precioLatam = getFloat("Ingresar el precio de Latam: ");
				}
			}
			else
			{
				precioLatam = getFloat("Ingresar el precio de Latam: ");
				if(validacionSiNo("\nDesea ingresar otra aerolinea? (S/N) "))
				{
					precioAero = getFloat("Ingresar el precio de Aerolineas: ");
				}
			}
			break;

		case 3:
			//calcular los costos. validar tener un vuelo
			validacionCalculo(kilometros, precioAero, precioLatam, &debitoA, &creditoA, &bitcoinA, &unitarioA, &debitoL, &creditoL, &bitcoinL, &unitarioL, &diferenciaPrecio);
			flagCalculo ++;
			break;

		case 4:
			//Informar resultados
			if (flagCalculo != 0)
			{
				if (precioAero !=0)
				{
					mostrarResultadosAero ( precioAero, precioLatam, debitoA, creditoA,  bitcoinA,  unitarioA);
				}
				if (precioLatam != 0)
				{
					mostrarResultadosLatam ( precioLatam, debitoL,  creditoL,  bitcoinL,  unitarioL);
				}
				if (precioAero != 0 && precioLatam != 0)
				{
					mostrarDiferencia (diferenciaPrecio);
				}
				saltoDeLinea();
				nroIngresado = 6;
			}
			else
			{
				alerta("Te falta calcular los datos.");
			}
			break;

		case 5:
			//valores forzados y muestro
			saltoDeLinea();
			cargaForzada(&kilometros, &precioAero, &precioLatam);
			printf ("KMs Ingresados: %d\n", kilometros);
			validacionCalculo(kilometros, precioAero, precioLatam, &debitoA, &creditoA, &bitcoinA, &unitarioA, &debitoL, &creditoL, &bitcoinL, &unitarioL, &diferenciaPrecio);
			mostrarResultadosAero ( precioAero, precioLatam, debitoA, creditoA,  bitcoinA,  unitarioA);
			mostrarResultadosLatam ( precioLatam, debitoL,  creditoL,  bitcoinL,  unitarioL);
			printf ("La diferencia de precio es: $%.2f\n", diferenciaPrecio);
			saltoDeLinea();
			nroIngresado = 6;
			break;

		case 6:
			alerta ("\nGracias por usar este programa. Saludos!");
			break;

		default:
			puts ("Número Ingresado incorrecto. Ingrese otro.");

		}
		saltoDeLinea();
	}
	while (nroIngresado != 6);

	return EXIT_SUCCESS;
}


