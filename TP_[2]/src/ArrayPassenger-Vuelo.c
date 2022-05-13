/*
 * ArrayPassenger-Vuelo.c
 *
 *  Created on: 10 may. 2022
 *      Author: Agostin
 */

#include "validaciones.h"
#include "ArrayPassenger-Vuelo.h"

static const char VUELOS_TIPOS [3][10] = {"ACTIVO", "DEMORADO", "CANCELADO"};
static const char PASAJERO_TIPOS [4][30] = {"Primera Clase", "Business", "Premium Economy", "Economy"};


/// @fn int union_altaPassenger(Passenger*, int, Vuelo*, int)
/// @brief
///
/// @param aPassenger
/// @param pas_len
/// @param aVuelo
/// @param vuelo_len
/// @return
int union_altaPassenger (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len)
{
	int rtn = -1;
	Passenger auxMiPasajero;

	if (aPassenger != NULL && aVuelo != NULL && pas_len > 0 && vuelo_len > 0)
	{
		puts ("\n~~ALTA DE PASAJERO~~");
		if (cargaDatosPasajero (&auxMiPasajero) == 0 &&
			addPassenger(aPassenger, pas_len, auxMiPasajero.id, auxMiPasajero.name, auxMiPasajero.lastName, auxMiPasajero.price, auxMiPasajero.typePassenger, auxMiPasajero.FK_flycode) == 0 &&
			addFlight (aVuelo,vuelo_len, auxMiPasajero.FK_flycode) == 0)
		{
			puts ("Carga Cliente y Vuelo.");
			rtn = 0;
		}
		else
		{
			puts("Error en la carga");
		}
	}
	return rtn;
}


/// @fn int union_Modificacion(Passenger*, int, Vuelo*, int)
/// @brief  modificacion de algun campo de los pasajeros. en caso de modificarse el codigo de vuelo se procede a
/// crear un nuevo vuelo con su nuevo estado de vuelo. Si ya esxiste el vuelo se pregunta si se quiere actualizar el estado de vuelo.
/// @param aPassenger array estructura pasajeros
/// @param pas_len cantidad maxima de pasajeros
/// @param aVuelo array estructura vuelo
/// @param vuelo_len cantidad maxima vuelos
/// @return devuelve un 0 si esta OK. un -1 si hay error
int union_Modificacion (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len)
{
	int rtn = -1;
	int idIngresado;
	int indicePasajero;
	int flagAlta = 0;
	Passenger auxiliar;
	if (aPassenger != NULL && aVuelo != NULL && pas_len > 0 && vuelo_len > 0)
	{
		if (union_printStruct(aPassenger, pas_len, aVuelo, vuelo_len) == 0)
		{
			flagAlta = 1;
		}

		if (flagAlta)
		{
			if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n") == 0)
			{
				while (findPassengerById(aPassenger, pas_len, idIngresado) == -1)
				{
					puts("NO EXISTE ID.");
					utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n");
				}
				indicePasajero = findPassengerById(aPassenger, pas_len, idIngresado);
				auxiliar = pas_ModificarUno(aPassenger[indicePasajero]);
				if (compararCadenas(auxiliar.FK_flycode, aPassenger[indicePasajero].FK_flycode, CODIGO) != 3)
				{
					addFlight (aVuelo, vuelo_len, auxiliar.FK_flycode);
				}
				aPassenger[indicePasajero] = auxiliar;
				rtn = 0;
			}
		}
	}
	return rtn;
}


/// @fn int union_printStruct(Passenger*, int, Vuelo*, int)
/// @brief  imprime toda la lista de pasajeros con el estado de vuelo
///si no llega a encontrar pasajeros y vuelos no imprime nada.
/// @param aPassenger array estructura pasajeros
/// @param pas_len cantidad maxima de pasajeros
/// @param aVuelo array estructura vuelo
/// @param vuelo_len cantidad maxima vuelos
/// @return devuelve un 0 si esta OK. un -1 si hay error
int union_printStruct(Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len)
{
	int rtn = -1;
	int flagPrimerPasajero = 0;
	int indiceVuelo;

	if (aPassenger != NULL && aVuelo != NULL && pas_len > 0 && vuelo_len > 0)
	{
		for (int i = 0; i < pas_len; i++)
		{
			if (aPassenger[i].isEmpty == OCUPADO)
			{
				indiceVuelo = findFlightByCode(aVuelo, vuelo_len, aPassenger[i].FK_flycode);
				if (flagPrimerPasajero == 0)
				{
					flagPrimerPasajero = 1;
					puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS\n"
						"--------------------------------------------------------------------------------------"
						"------------------------------------------------------------------------------------------");
					printf("%-6s %-52s %-52s %-12s %-21s %-15s %-s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "  TIPO PASAJERO" ,"CODIGO VUELO", "ESTADO VUELO");
				}

				union_printOne (&aPassenger[i], &aVuelo[indiceVuelo]);
				rtn = 0;
			}
		}
	}

	return rtn;
}

/// @fn int union_printActiveStruct(Passenger*, int, Vuelo*, int)
/// @brief  imprime toda la lista de pasajeros con el estado de vuelo tambien con la condicion de que los vuelos esten ACTIVOS
///si no llega a encontrar pasajeros y vuelos no imprime nada.
/// @param aPassenger array estructura pasajeros
/// @param pas_len cantidad maxima de pasajeros
/// @param aVuelo array estructura vuelo
/// @param vuelo_len cantidad maxima vuelos
/// @return devuelve un 0 si esta OK. un -1 si hay error
int union_printActiveStruct(Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len)
{
	int rtn = -1;
	int flagPrimerPasajero = 0;
	int indiceVuelo;

	if (aPassenger != NULL && aVuelo != NULL && pas_len > 0 && vuelo_len > 0)
	{
		for (int i = 0; i < pas_len; i++)
		{
			indiceVuelo = findFlightByCode(aVuelo, vuelo_len, aPassenger[i].FK_flycode);
			if (aPassenger[i].isEmpty == OCUPADO && aVuelo[indiceVuelo].statusFlight == 1)
			{
				if (flagPrimerPasajero == 0)
				{
					flagPrimerPasajero = 1;
					puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS <\n"
											"--------------------------------------------------------------------------------------"
											"------------------------------------------------------------------------------------------");
					printf("%-6s %-52s %-52s %-12s %-21s %-15s %-s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "  TIPO PASAJERO" ,"CODIGO VUELO", "ESTADO VUELO");
				}

				union_printOne (&aPassenger[i], &aVuelo[indiceVuelo]);
				rtn = 0;
			}
		}
	}

	return rtn;
}


/// @fn void union_printOne(Passenger*, Vuelo*)
/// @brief imprime un solo pasajero con datos del vuelo tambien.
///
/// @param aPassenger un pasajero especifico a imprimir
/// @param aVuelo un vuelo especifico a imprimir
void union_printOne (Passenger* aPassenger, Vuelo* aVuelo)
{
		printf ("%-6d %-52s %-52s %-14.2f "
				"%-19s %-15s %-s\n",
				aPassenger->id, aPassenger->name, aPassenger->lastName, aPassenger->price,
				PASAJERO_TIPOS[(aPassenger->typePassenger)-1], aPassenger->FK_flycode, VUELOS_TIPOS[(aVuelo->statusFlight) - 1]);
}

/// @fn int union_Informar(Passenger*, int, Vuelo*, int)
/// @brief
/// funcion de informes. depende la opcion ingresada va a mostrar una lista ordenada segun algun criterio o mostrar promedios y sumas
/// @param aPassenger array estructura pasajeros
/// @param pas_len cantidad maxima de pasajeros
/// @param aVuelo array estructura vuelo
/// @param vuelo_len cantidad maxima vuelos
/// @return devuelve un 0 si esta OK. un -1 si hay error
int union_Informar (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len)
{
	int rtn = -1;
	int opcion;
	char respuesta;
	int flagAlta = 0;

	if (pas_isStrucEmpty(aPassenger, pas_len) == 0)
	{
		flagAlta = 1;
	}

	if (aPassenger != NULL && aVuelo != NULL && pas_len > 0 && vuelo_len > 0 && flagAlta == 1)
	{
		rtn = 0;
		do
		{
			fflush(stdin);
			utn_getIntRange (&opcion ,"\nIngrese la opcion que desea informar:\n"
											"1 - Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.\n"
											"2 - Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio.\n"
											"3 - Listado de los pasajeros por Codigo de vuelo y estados de vuelo ACTIVO\n\n"
											"Ingrese su opcion: ",
											"Error. Ingrese una opcion correcta\n", 1, 3);

			switch (opcion)
			{
				case 1:
					utn_getIntRange (&opcion ,"\nIngrese el orden que desea informar:\n"
							"1 - Descendente (Z a A y Primera Clase a Economy)\n"
							"2 - Ascendente. (A a Z y Economy a Primera Clase)\n\n"
							"Ingrese su opcion: ",
							"Error. Ingrese una opcion correcta\n\n", 1, 2);
					if (sortPassengers(aPassenger,  pas_len, opcion-1) == 0)
					{
						union_printStruct(aPassenger, pas_len, aVuelo, vuelo_len);
					}
					break;

				case 2:
					if (pas_CalculosPasaje (aPassenger, pas_len) == 0)
					{
						puts ("~~Calculo realizado~~");
					}
					break;

				case 3:
					utn_getIntRange (&opcion ,"\nIngrese el orden que desea informar:\n"
												"1 - Descendente (Z a A y vuelos ACTIVOS)\n"
												"2 - Ascendente. (A a Z y vuelos ACTIVOS)\n\n"
												"Ingrese su opcion: ",
												"Error. Ingrese una opcion correcta\n\n", 1, 2);
					if (sortPassengersByCode(aPassenger, pas_len, opcion-1) == 0)
					{
						union_printActiveStruct(aPassenger, pas_len, aVuelo, vuelo_len);
					}
					break;
			}
			respuesta = validacionDosCaracteres ("\n¿Desea informar otra opcion? (S/N)", 'S', 'N');
		}
		while (respuesta);
	}
	puts ("");
	return rtn;
}



