/*
 ============================================================================
 Name        : TP_[1].c
 Author      : Vallario Cores, Agust�n
 Version     :
 Copyright   : Your copyright notice
 Description : TP N�mero 1 - Agencia de Viaje
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "TextoValidaciones.h"
#include "OperacionesyResultados.h"

int main(void) {
	setbuf(stdout,NULL);

	int nroIngresado;
	int  aerolineaElegida;

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
		menu(kilometros, precioAero, precioLatam);  // Menu con opciones

		nroIngresado = getInt ("\nIngrese un numero: "); //Ingreso la opci�n a elegir del menu

		switch (nroIngresado)
		{
			//Case 1 es el ingreso de los kil�metros.
			case 1:
				kilometros = getInt("1. Ingresar Kil�metros: ");
				break;

			//Case 2 es el ingreso del precio de los vuelos.
			case 2:
				//Guardamos en la variable aerolineaElegida un 1 o 0. Si es un 1 sera Aerolineas y si es un 0 ser� Latam.
				aerolineaElegida = validacionCaracteres("\nIngresar el tipo de aerolinea a ingresar (Aerol�neas = A, Latam = L): ", 'A', 'L');
				if (aerolineaElegida)
				{
					//ingresoOtroVuelo ("Ingresar el precio de ", "Aerolineas","Latam", &precioAero, &precioLatam);
					precioAero = getFloat("Ingresar el precio de Aerolineas: ");
					//Le damos la opcion al usuario a ingresar el precio de la otra aerolinea si asi lo prefiere.
					if(validacionCaracteres("\nDesea ingresar otra aerolinea? (S/N) ", 'S', 'N'))
					{
						precioLatam = getFloat("Ingresar el precio de Latam: ");
					}
				}
				else
				{
					precioLatam = getFloat("Ingresar el precio de Latam: ");
					if(validacionCaracteres("\nDesea ingresar otra aerolinea? (S/N) ", 'S', 'N'))
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
			//Informar resultados. Se utiliza una bandera para asegurarme que los calculos ya los realice para asi tener resultados para mostrar
			if (flagCalculo != 0)
			{
				//Si no tengo precio de alguno de los vuelos puedo realizar el calculo del vuelo que si tengo
				if (precioAero !=0)
				{

					mostrarResultados("Aerol�neas" ,precioAero, debitoA, creditoA,  bitcoinA,  unitarioA);
				}
				if (precioLatam != 0)
				{
					mostrarResultados("Latam" ,precioLatam, debitoL,  creditoL,  bitcoinL,  unitarioL);
				}

				//Solo la diferencia se va a mostrar cuando tenga precios de ambos vuelos.
				if (precioAero != 0 && precioLatam != 0)
				{
					mostrarDiferencia (diferenciaPrecio);
				}
				saltoDeLinea();
				nroIngresado = 6;
			}
			else
			{
				//En caso de que no se ingreso datos suficientes salta este mensaje y no se calcula nada
				alerta("Te falta calcular los datos.");
			}
			break;

		case 5:
			//valores forzados y muestro
			saltoDeLinea();
			saltoDeLinea();

			cargaForzada(&kilometros, &precioAero, &precioLatam); //Le asigno los valores de la carga forzada a las variable de km y precios mediante punteros.
			printf ("KMs Ingresados: %d\n", kilometros);
			//Realizo la validacion de los datos que obtengo y el calculo de todos los valores que se necesitan.
			validacionCalculo(kilometros, precioAero, precioLatam, &debitoA, &creditoA, &bitcoinA, &unitarioA, &debitoL, &creditoL, &bitcoinL, &unitarioL, &diferenciaPrecio);

			//Luego de realizado los c�lculos paso a mostrar los resultados obtenidos.
			mostrarResultados("Aerol�neas" ,precioAero, debitoA, creditoA,  bitcoinA,  unitarioA);
			mostrarResultados("Latam" ,precioLatam, debitoL,  creditoL,  bitcoinL,  unitarioL);
			mostrarDiferencia (diferenciaPrecio);
			//Una vez realizado la muestra de la carga forzada, le doy valor 6 a nroIngresado para asi salir del programa,
			nroIngresado = 6;
 			break;

		case 6:
			//mensaje que se muestra al salir del programa
			alerta ("\nGracias por usar este programa. Saludos!");
			break;

		default:
			//Cada vez que se ingrese un n�mero incorrecto salta este mensaje.
			alerta("N�mero Ingresado incorrecto. Ingrese otro.");

		}
		saltoDeLinea();
	}
	while (nroIngresado != 6);

	return EXIT_SUCCESS;
}


