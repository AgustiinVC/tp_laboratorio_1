/*
 * Vuelo.c
 *
 *  Created on: 10 may. 2022
 *      Author: Agostin
 */

#include "validaciones.h"
#include "Vuelo.h"

/// para facilitar la impresion del estado de vuelo
static const char VUELOS_TIPOS [3][10] = {"ACTIVO", "DEMORADO", "CANCELADO"};

static int Vuelo_idUnico = 1;

/// @fn int eVue_ObtenerID(void)
/// @brief
/// empieza por 0 y luego va sumando al valor de id.
/// @return el id unico de un vuelo
static int eVue_ObtenerID (void)
{
	return Vuelo_idUnico++;
}

/// @fn int vue_initArray(Vuelo*, int)
/// @brief
/// inicializar vuelos en LIBRE
/// @param list de la estructura de los vuelo
/// @param len cantidad maxima de vuelos
/// @return devuelve un 0 si esta OK. o un -1 si hay error.
int vue_initArray(Vuelo* list, int len)
{
	int rtn = -1;
	int i;
	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = LIBRE;
			rtn = 0;
		}
	}
	return rtn;
}

/// @fn int vue_indexEmpty(Vuelo*, int)
/// @brief
/// podemos saber si hay un indice libre
/// @param list de la estructura de los vuelo
/// @param len cantidad maxima de vuelos
/// @return devuelve un indice si se encontro algun indice libre. y -1 si no se encontro un indice libre.
int vue_indexEmpty (Vuelo* list, int len)
{
	int rtn = -1;
	int i;
	if (list != NULL && len >= 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].isEmpty == LIBRE)
			{
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}

/// @fn int addFlight(Vuelo*, int, char*)
/// @brief
/// funcion para agregar un vuelo. si hay un vuelo existente con mismo codigo se pregunta si se quiere actualizar el estado de vuelo
/// @param list de la estructura de los vuelo
/// @param len cantidad maxima de vuelos
/// @param flycode el codigo de vuelo ingresado
/// @return se devuelve un 0 si esta ok. un -1 si hay error.
int addFlight (Vuelo* list, int len, char* flycode)
{
	int rtn = -1;
	int indice;
	int respuesta;
	int auxEstadoVuelo;

	if (list != NULL && len > 0 && flycode != NULL)
	{
		indice = findFlightByCode (list, len, flycode);
		if (indice != -1)
		{
			puts ("\n~~Vuelo existente!~~");
			printf ("Codigo de vuelo ingresado: %s \nEstado actual vuelo: %s\n", list[indice].flycode ,VUELOS_TIPOS[list[indice].statusFlight-1]);
			fflush(stdin);
			respuesta  =  validacionDosCaracteres ("¿Desea actualizar el estado del vuelo? (S/N)", 'S', 'N');
			if (respuesta == 1)
			{
				utn_getIntRange(&auxEstadoVuelo, "Actualice el estado del vuelo: "
															"\n\t 1 = ACTIVO\n\t 2 = DEMORADO\n\t 3 - CANCELADO\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,3);
				list[indice].statusFlight = auxEstadoVuelo;
			}
		}
		else
		{
			indice = vue_indexEmpty (list, len);
			if (indice != -1)
			{
				if(utn_getIntRange(&auxEstadoVuelo, "Ingrese el estado del vuelo: "
									"\n\t 1 = ACTIVO\n\t 2 = DEMORADO\n\t 3 - CANCELADO\nIngrese su opcion: ", "Ingrese un estado de vuelo valido\n", 1,3) == 0)
				{
					list[indice].id = eVue_ObtenerID();
					strncpy (list[indice].flycode, flycode, CODIGO);
					list[indice].statusFlight = auxEstadoVuelo;
					list[indice].isEmpty = OCUPADO;
				}
			}
		}
		rtn = 0;
	}
	return rtn;
}

/// @fn int findFlightByCode(Vuelo*, int, char*)
/// @brief
/// buscar el id del vuelo al comparar los codigo de vuelo del array de estructura vuelo
/// @param list de la estructura de los vuelo
/// @param len cantidad maxima de vuelos
/// @param flycode el codigo de vuelo ingresado
/// @return devuelve el indice del codigo de vuelo si se encontro o. un -1 si hay error.
int findFlightByCode(Vuelo* list, int len, char* flycode)
{
	int rtn = -1;
	int i;
	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (compararCadenas (list[i].flycode, flycode, CODIGO) == 3 && list[i].isEmpty == OCUPADO)
			{
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}


/// @fn int vue_altaForzada(Vuelo*, int)
/// @brief
/// alta forzada de vuelos
/// @param list de la estructura de los vuelo
/// @param len cantidad maxima de vuelos
/// @return un 0 si esta OK. un -1 si hay error
int vue_altaForzada (Vuelo* list, int len)
{
	int rtn = -1;
	int indiceLibre;

	if (list != NULL && len > 0)
	{
		indiceLibre = vue_indexEmpty (list, len);
		if (indiceLibre != -1)
		{

			list[indiceLibre] = vue_UnElementoForzado (indiceLibre, "SAS321", 1);
			list[indiceLibre+1] = vue_UnElementoForzado (indiceLibre+1, "CFR234", 1);
			list[indiceLibre+2] = vue_UnElementoForzado (indiceLibre+2, "GHR736", 1);
			list[indiceLibre+3] = vue_UnElementoForzado (indiceLibre+3, "LOL640", 2);
			list[indiceLibre+4] = vue_UnElementoForzado (indiceLibre+4, "ABC123", 1);

			for (int i = indiceLibre; i < indiceLibre + 5; i++)
			{

				list[i].id = eVue_ObtenerID();
				list [i].isEmpty = OCUPADO;
			}
			rtn = 0;
		}
	}

	return rtn;
}

/// @fn Vuelo vue_UnElementoForzado(int, char*, int)
/// @brief
/// carga forzada de los datos de vuelos en una estructura auxiliar
/// @param indiceLibre el indice donde cargar el alta forzada
/// @param flyCode el codigo de vuelo
/// @param statusFlight el estado del vuelo
/// @return devuelve un astructura auxiliar con los datos del vuelo
Vuelo vue_UnElementoForzado (int indiceLibre, char* flyCode, int statusFlight)
{
	Vuelo auxLista;
	strncpy(auxLista.flycode, flyCode, CODIGO);
	auxLista.statusFlight = statusFlight;
	return auxLista;
}

