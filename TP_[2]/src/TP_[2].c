/*
 ============================================================================
 Name        : TP_[2].c
 Author      : Vallario Cores, Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"
#include "ArrayPassenger-Vuelo.h"


#define CANT_PASAJEROS 2000

int main(void) {
	setbuf (stdout,NULL);
	int opcion;

	Passenger miPasajero [CANT_PASAJEROS];
	Vuelo miVuelo [CANT_PASAJEROS];

	//Inicializo la estructura
	pas_initArray(miPasajero, CANT_PASAJEROS);

	do
	{
		menu();
		utn_getIntRange (&opcion ,"\nIngrese una Opcion: ", "Error. Ingrese una opcion correcta.\n",1,6);
		fflush (stdin);
		switch (opcion)
		{
			case 1: //Alta
				if (union_altaPassenger (miPasajero, CANT_PASAJEROS, miVuelo, CANT_PASAJEROS) == 0)
				{
					puts ("Carga con exito.");
				}
				else
				{
					puts("Error en la carga");
				}
				break;

			case 2: //Modificar por ID
				if (union_Modificacion (miPasajero, CANT_PASAJEROS, miVuelo, CANT_PASAJEROS) == 0)
				{
					puts("\n * MODIFICACION DE Pasajero Exitosa");
				}
				else
				{
					puts("\n * MODIFICACION DE Pasajero Cancelada");
				}
				break;

			case 3: //Baja de Pasajero
				if (union_Baja(miPasajero, CANT_PASAJEROS, miVuelo, CANT_PASAJEROS) == 0)
				{
					puts("\n * BAJA DE Pasajero Exitosa");
				}
				else
				{
					puts("\n * BAJA DE Pasajero Cancelada");
				}
				break;

			case 4:  // Informar
				union_Informar (miPasajero, CANT_PASAJEROS, miVuelo, CANT_PASAJEROS);
				break;

			case 5: //Alta forzada
				if (altaForzadaPasajeros (miPasajero, CANT_PASAJEROS) == 0 &&
					vue_altaForzada(miVuelo, CANT_PASAJEROS) == 0 )
				{
					puts ("\nAlta realizada.");
				}
				else
				{
					puts ("Alta forzada ya cargada.");
				}
				break;
		}
	}
	while (opcion != 6);

	puts ("Salida");

	return EXIT_SUCCESS;
}
