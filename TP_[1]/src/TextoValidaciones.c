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
		puts ("1. Ingresar Kil�metros: (KM = No Ingresado)");
	}
	else
	{
		printf ("1. Ingresar Kil�metros: (KM = %d)\n", kilometros);
	}

	puts ("2. Ingresar Precio de Vuelos: (Aerol�neas = A, Latam = L)");

	if (precioAero == 0)
	{
		puts ("  - Precio Aerol�neas: No Ingresado.");
	}
	else
	{
		printf ("  - Precio Aerol�neas: $%.2f.\n", precioAero);
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
		puts ("ingrese un n�mero mayor a 0.");
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
		puts ("ingrese un n�mero mayor a 0.");
		fflush (stdin);
		scanf ("%f", &nroIngresado);
	}
	return nroIngresado;
}


unsigned int validacionAero (void)
{
	char charIngresado;
	printf("\nIngresar el tipo de aerolinea a ingresar (Aerol�neas = A, Latam = L): ");
	fflush (stdin);
	charIngresado = toupper(getchar());
	while (charIngresado != 'L' && charIngresado !='A')
	{
		printf ("Ingrese una aerolinea v�lida: ");
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
		printf ("Ingrese una opci�n v�lida (S/N): ");
		fflush (stdin);
		charIngresado = toupper(getchar());
	}
	return (charIngresado == 'S');
}

void alerta (char *mensaje)
{
	puts (mensaje);
}
