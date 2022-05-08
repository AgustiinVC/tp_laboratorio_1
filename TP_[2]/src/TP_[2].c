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
#include "ArrayPassenger.h"


#define CANT_PASAJEROS 200

int main(void) {
	setbuf (stdout,NULL);
	int opcion;

	Passenger miPasajero [CANT_PASAJEROS];
	Passenger auxMiPasajero;

	//Inicializo la estructura
	initPassengers(miPasajero, CANT_PASAJEROS);

	do
	{
		menu();
		fflush (stdin);
		utn_getIntPositivo (&opcion ,"\nIngrese una Opcion: ", "Error. Ingrese una opcion correcta.\n");

		switch (opcion)
		{
			case 1: //Alta
				if (cargaDatosPasajero (&auxMiPasajero) == 0 &&
					addPassenger(miPasajero, CANT_PASAJEROS, auxMiPasajero.id, auxMiPasajero.name, auxMiPasajero.lastName, auxMiPasajero.price, auxMiPasajero.typePassenger, auxMiPasajero.flycode) == 0)
				{
					puts ("Carga con exito.");
				}
				else
				{
					puts("Error en la carga");
				}
				break;

			case 2: //Modificar por ID
				if (pas_Modificacion(miPasajero, CANT_PASAJEROS) == 0)
				{
					puts("\n * MODIFICACION DE Pasajero Exitosa");
				}
				else
				{
					puts("\n * MODIFICACION DE Pasajero Cancelada");
				}
				break;

			case 3: //Baja de Pasajero
				if (pas_Baja(miPasajero, CANT_PASAJEROS) == 0)
				{
					puts("\n * BAJA DE Pasajero Exitosa");
				}
				else
				{
					puts("\n * BAJA DE Pasajero Cancelada");
				}
				break;

			case 4:  // Informar
				pas_Informar (miPasajero, CANT_PASAJEROS);
				break;

			case 5: //Alta forzada
				break;

			default:
				puts ("Ingrese una opcion valida");

		}
	}
	while (opcion != 6);

	puts ("Salida");

	return EXIT_SUCCESS;
}
