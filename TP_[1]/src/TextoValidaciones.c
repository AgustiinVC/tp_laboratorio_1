/*
 * TextoValidaciones.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Agostin
 */
#include "TextoValidaciones.h"

void menu (int kilometros, float precioAero, float precioLatam)
{
	if (kilometros == 0)
	{
		puts ("1. Ingresar Kilómetros: (KM = No Ingresado)");
	}
	else
	{
		printf ("1. Ingresar Kilómetros: (KM = %d)\n", kilometros);
	}

	puts ("2. Ingresar Precio de Vuelos: (Aerolíneas = A, Latam = L)");

	if (precioAero == 0)
	{
		puts ("  - Precio Aerolíneas: No Ingresado.");
	}
	else
	{
		printf ("  - Precio Aerolíneas: $%.2f.\n", precioAero);
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

void saltoDeLinea(void)
{
	puts("-------------------------------------------------------");
}


int getInt (char *mensaje)
{
	int nroIngresado;

	printf (mensaje);
	fflush (stdin);
	scanf ("%d", &nroIngresado);
	while (nroIngresado < 1)
	{
		puts ("ingrese un número mayor a 0.");
		fflush (stdin);
		scanf ("%d", &nroIngresado);
	}
	return nroIngresado;
}

float getFloat (char *mensaje)
{
	float nroIngresado;

	printf (mensaje);
	fflush (stdin);
	scanf ("%f", &nroIngresado);
	while (nroIngresado < 1)
	{
		puts ("ingrese un número mayor a 0.");
		fflush (stdin);
		scanf ("%f", &nroIngresado);
	}
	return nroIngresado;
}


unsigned int validacionAero (void)
{
	char charIngresado;
	printf("\nIngresar el tipo de aerolinea a ingresar (Aerolíneas = A, Latam = L): ");
	fflush (stdin);
	charIngresado = toupper(getchar());
	while (charIngresado != 'L' && charIngresado !='A')
	{
		printf ("Ingrese una aerolinea válida: ");
		fflush (stdin);
		charIngresado = toupper(getchar());
	}
	return (charIngresado == 'A');
}

unsigned int validacionSiNo (char *mensaje)
{
	char charIngresado;
	printf(mensaje);
	fflush (stdin);
	charIngresado = toupper(getchar());
	while (charIngresado != 'S' && charIngresado !='N')
	{
		printf ("Ingrese una opción válida (S/N): ");
		fflush (stdin);
		charIngresado = toupper(getchar());
	}
	return (charIngresado == 'S');
}

void alerta (char *mensaje)
{
	puts (mensaje);
}
