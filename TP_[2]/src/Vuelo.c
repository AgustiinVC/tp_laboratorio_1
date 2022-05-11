/*
 * Vuelo.c
 *
 *  Created on: 10 may. 2022
 *      Author: Agostin
 */

#include "validaciones.h"
#include "Vuelo.h"

static const char VUELOS_TIPOS [3][10] = {"ACTIVO", "DEMORADO", "CANCELADO"};

static int Vuelo_idUnico = 0;

static int eVue_ObtenerID (void)
{
	return Vuelo_idUnico++;
}

static int flagAltaForzada = 0;

static int eVue_AltaForzada (void)
{
	return flagAltaForzada++;
}


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
			puts ("Vuelo existente!");
			printf ("Estado actual vuelo: %s\n", VUELOS_TIPOS[list[indice].statusFlight-1]);
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
									"\n\t 1 = ACTIVO\n\t 2 = DEMORADO\n\t 3 - CANCELADO\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,3) == 0)
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

int vue_altaForzada (Vuelo* list, int len)
{
	int rtn = -1;
	int indiceLibre;
	int altaRealizada;

	altaRealizada = eVue_AltaForzada();

	if (list != NULL && len > 0 && altaRealizada == 0)
	{
		indiceLibre = vue_indexEmpty (list, len);
		if (indiceLibre != -1)
		{

			list[indiceLibre] = vue_UnElementoForzado (indiceLibre, "ABC123", 1);
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

char flycode[CODIGO];
int statusFlight;


Vuelo vue_UnElementoForzado (int indiceLibre, char* flyCode, int statusFlight)
{
	Vuelo auxLista;
	strncpy(auxLista.flycode, flyCode, CODIGO);
	auxLista.statusFlight = statusFlight;
	return auxLista;
}

