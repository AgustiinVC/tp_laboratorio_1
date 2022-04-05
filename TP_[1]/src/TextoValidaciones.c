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

//salto de linea para emprolijar y ordenar lo que uno ve
void saltoDeLinea(void)
{
	puts("-------------------------------------------------------");
}

//ingreso de un Entero
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

//Ingreso de un float
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
		printf ("Ingrese una opción válida (%c/%c): ", caracterUno, caracterDos);
		fflush (stdin);
		charIngresado = toupper(getchar());
	}
	return (charIngresado == caracterUno);
}
/*
void ingresoOtroVuelo (char* mensaje, char* vueloUno, char* vueloDos , float* precioVueloUno, float* precioVueloDos)
{
	strcat (mensaje, vueloUno);
	strcat (mensaje, ":");
	printf (mensaje);
	*precioVueloUno = getFloat(mensaje);
	if(validacionCaracteres("\nDesea ingresar otra aerolinea? (S/N) ", 'S', 'N'))
	{
		strcat (mensaje, vueloDos);
		strcat (mensaje, ":");
		*precioVueloDos = getFloat(mensaje);
	}
}*/

void alerta (char *mensaje)
{
	puts (mensaje);
}
