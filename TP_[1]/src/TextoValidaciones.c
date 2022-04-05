/*
 * TextoValidaciones.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */
#include "TextoValidaciones.h"

//Menu con todas las opciones que se pueden elegir.
void menu (int kilometros, float precioAero, float precioLatam)
{
	if (kilometros == 0)
	{
		puts ("1. Ingresar Kilometros: (KM = No Ingresado)");
	}
	else
	{
		printf ("1. Ingresar Kilometros: (KM = %d)\n", kilometros);
	}

	puts ("2. Ingresar Precio de Vuelos: (Aerolineas = A, Latam = L)");

	if (precioAero == 0)
	{
		puts ("  - Precio Aerolineas: No Ingresado.");
	}
	else
	{
		printf ("  - Precio Aerolineas: $%.2f.\n", precioAero);
	}
	if (precioLatam == 0)
	{
		puts ("  - Precio Latam: No Ingresado.");
	}
	else
	{
		printf ("  - Precio Latam: $%.2f.\n", precioLatam);
	}

	puts ("3. Calcular los costos");
	puts ("4. Informar Resultados");
	puts ("5. Carga forzada de datos");
	puts ("6. Salir");
}

//salto de linea para emprolijar y ordenar lo que uno ve
void saltoDeLinea(void)
{
	puts("-------------------------------------------------------");
}

//ingreso de un Entero
int getInt (int* nroIngresado, char* mensaje, char* mensajeError, int min)
{
	int num;
	while (1)
	{
		printf(mensaje);
		fflush(stdin);
		if (scanf("%d", &num) == 1)
		{
			if (num > min)
			{
				break;
			}

		}
		printf(mensajeError);
	}
	*nroIngresado = num;
	return 0;
}

//Ingreso de un float
int getFloat (float * nroIngresado, char *mensaje, char* mensajeError, float min)
{
	float num;
	while (1)
	{
		printf(mensaje);
		fflush(stdin);
		if (scanf("%f", &num) == 1)
		{
			if (num > min)
			{
				break;
			}

		}
		printf(mensajeError);
	}
	*nroIngresado = num;
	return 0;
}




/* En ValidacionCaracter validamos el tipo de caracter que se ingresa.
 * Si ingresa cualquier otra cosa sigue preguntando hasta que se ingrese los caracteres correctos. Luego devolvemos un 1 o 0 al main.
 * Siendo 1 si es el primer caracter y 0 si es el segundo.*/

unsigned int validacionCaracteres (char *mensaje, char caracterUno, char caracterDos)
{
	char charIngresado;
	printf(mensaje);
	fflush (stdin);
	charIngresado = toupper(getchar());
	while (charIngresado != caracterUno && charIngresado != caracterDos)
	{
		printf ("Ingrese una opcion valida (%c/%c): ", caracterUno, caracterDos);
		fflush (stdin);
		charIngresado = toupper(getchar());
	}
	return (charIngresado == caracterUno);
}

