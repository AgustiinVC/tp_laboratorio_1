/*
 * Passenger.c
 *
 *  Created on: 19 may. 2022
 *      Author: Maru
 */
#include "Passenger.h"

static const char PASAJERO_TIPOS [3][15] = {"FirstClass", "ExecutiveClass", "EconomyClass"};
static const char ESTADO_VUELO [4][11] = {"Aterrizado", "En Horario", "En Vuelo", "Demorado"};

static int unicoId = 0;

int Passenger_generarIdUnico (void)
{
	return unicoId++;
}

void Passenger_setUltimoId (int ultimoId)
{
	unicoId = ultimoId;
	printf ("Ultimo ID: %d\n", unicoId);
}

int Passenger_getUltimoId(int* id)
{
	int rtn = -1;
	*id = unicoId;
	rtn = 0;
	return rtn;
}

Passenger* Passenger_new()
{
	Passenger* auxPassenger;
	auxPassenger = (Passenger*) malloc (sizeof (Passenger));
	return auxPassenger;
}

Passenger* Passenger_newParametros(char* idStr,char* nombreStr, char* apellidoStr, char* precioStr, char* codigoVueloStr, char* tipoPasajeroStr, char* estadoVueloStr)
{
	Passenger* auxPassenger;
	auxPassenger = Passenger_new();
	int id = 0;
	float precio;
	int tipoPasajero;
	int estadoVuelo;
	if ( auxPassenger != NULL &&
		getIntFromStr(idStr, &id) == 0 &&
		getFloatFromStr(precioStr, &precio) == 0 &&
		Passenger_TipoPasajeroToInt(tipoPasajeroStr, &tipoPasajero) == 0 &&
		Passenger_EstadoVueloToInt(estadoVueloStr, &estadoVuelo) == 0)
	{
		Passenger_setId(auxPassenger, id);
		Passenger_setNombre(auxPassenger, nombreStr);
		Passenger_setApellido(auxPassenger, apellidoStr);
		Passenger_setPrecio(auxPassenger, precio);
		toUpperCadena(codigoVueloStr);
		Passenger_setCodigoVuelo(auxPassenger, codigoVueloStr);
		Passenger_setTipoPasajero(auxPassenger, tipoPasajero);
		Passenger_setEstadoVuelo(auxPassenger, estadoVuelo);
	}
	return auxPassenger;
}

void Passenger_delete(Passenger* this)
{
	free (this);
}

int Passenger_setId(Passenger* this,int id)
{
	int rtn = -1;

	if (this != NULL && id > 0)
	{
		this -> id = id;
		rtn = 0;
	}
	return rtn;
}

int Passenger_getId(Passenger* this,int* id)
{
	int rtn = -1;

	if (this != NULL)
	{
		*id = this -> id;
		rtn = 0;
	}
	return rtn;
}

int Passenger_setNombre(Passenger* this,char* nombre)
{
	int rtn = -1;

	if (this != NULL && nombre != NULL)
	{
		strcpy (this -> nombre, nombre);
		rtn = 0;
	}
	return rtn;
}

int Passenger_getNombre(Passenger* this,char* nombre)
{
	int rtn = -1;

	if (this != NULL )
	{
		strcpy (nombre, this -> nombre);
		rtn = 0;
	}
	return rtn;
}

int Passenger_setApellido(Passenger* this,char* apellido)
{
	int rtn = -1;

	if (this != NULL && apellido != NULL)
	{
		strcpy (this -> apellido, apellido);
		rtn = 0;
	}
	return rtn;
}

int Passenger_getApellido(Passenger* this,char* apellido)
{
	int rtn = -1;

	if (this != NULL )
	{
		strcpy (apellido, this -> apellido);
		rtn = 0;
	}
	return rtn;
}

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int rtn = -1;

	if (this != NULL && codigoVuelo != NULL)
	{
		strcpy (this -> codigoVuelo, codigoVuelo);
		rtn = 0;
	}
	return rtn;
}

int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int rtn = -1;

	if (this != NULL )
	{
		strcpy (codigoVuelo, this -> codigoVuelo);
		rtn = 0;
	}
	return rtn;
}

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero)
{
	int rtn = -1;

	if (this != NULL && tipoPasajero > 0 && tipoPasajero <= 3)
	{
		this -> tipoPasajero = tipoPasajero;
		rtn = 0;
	}
	return rtn;
}

int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero)
{
	int rtn = -1;

	if (this != NULL)
	{
		*tipoPasajero = this -> tipoPasajero;
		rtn = 0;
	}
	return rtn;
}

int Passenger_TipoPasajeroToInt (char* cadena, int* numero)
{
	int rtn = -1;
	if (cadena != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			if (strcmp(cadena, PASAJERO_TIPOS[i]) == 0)
			{
				*numero = i+1;
				rtn = 0;
				break;
			}
		}
	}
	return rtn;
}

int Passenger_setPrecio(Passenger* this,float precio)
{
	int rtn = -1;

	if (this != NULL && precio > 0)
	{
		this -> precio = precio;
		rtn = 0;
	}
	return rtn;
}

int Passenger_getPrecio(Passenger* this,float* precio)
{
	int rtn = -1;

	if (this != NULL)
	{
		*precio = this -> precio;
		rtn = 0;
	}
	return rtn;
}

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo)
{
	int rtn = -1;

	if (this != NULL && estadoVuelo > 0 && estadoVuelo <= 4)
	{
		this -> estadoVUelo = estadoVuelo;
		rtn = 0;
	}
	return rtn;
}

int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo)
{
	int rtn = -1;

	if (this != NULL)
	{
		*estadoVuelo = this -> estadoVUelo;
		rtn = 0;
	}
	return rtn;
}

int Passenger_EstadoVueloToInt (char* cadena, int* numero)
{
	int rtn = -1;
	if (cadena != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if (strcmp(cadena, ESTADO_VUELO[i]) == 0)
			{
				*numero = i+1;
				rtn = 0;
				break;
			}
		}
	}
	return rtn;
}

int Passenger_print (Passenger* this)
{
	int rtn = -1;
	Passenger* auxPassenger;
	auxPassenger = Passenger_new();

	if (this != NULL &&
		Passenger_getId(this, &auxPassenger->id) == 0 &&
		Passenger_getNombre(this, auxPassenger->nombre) == 0 &&
		Passenger_getApellido(this, auxPassenger->apellido) == 0 &&
		Passenger_getPrecio(this, &auxPassenger->precio) == 0 &&
		Passenger_getCodigoVuelo(this, auxPassenger->codigoVuelo) == 0 &&
		Passenger_getTipoPasajero(this, &auxPassenger->tipoPasajero) == 0 &&
		Passenger_getEstadoVuelo(this, &auxPassenger->estadoVUelo) == 0)
	{
		printf ("%-6d %-50s %-50s %-14.2f %-14s %-14s %-11s\n",
				auxPassenger->id, auxPassenger->nombre, auxPassenger->apellido, auxPassenger->precio, auxPassenger->codigoVuelo, PASAJERO_TIPOS [(auxPassenger->tipoPasajero)-1], ESTADO_VUELO[(auxPassenger->estadoVUelo)-1]);
		rtn = 0;
	}
	return rtn;
}

int passenger_orderByID (void* thisOne, void* thisTwo)
{
	int rtn;
	if ( ((Passenger*)thisOne) -> id > ((Passenger*)thisTwo) -> id )
	{
		rtn = 1;
	}
	else if ( ((Passenger*)thisOne) -> id < ((Passenger*)thisTwo) -> id )
	{
		rtn = -1;
	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

int passenger_orderByName (void* thisOne, void* thisTwo)
{
	int rtn;
	int resultado;
	resultado = compararCadenas(((Passenger*)thisOne) -> nombre, ((Passenger*)thisTwo) -> nombre, NOMBRE_LEN);
	switch (resultado)
	{
		case 1:
			rtn = 1;
			break;
		case 2:
			rtn = -1;
			break;
		case 0:
			rtn = 0;
			break;
	}
	return rtn;
}

int passenger_orderByLastName (void* thisOne, void* thisTwo)
{
	int rtn;
	int resultado;
	resultado = compararCadenas(((Passenger*)thisOne) -> apellido, ((Passenger*)thisTwo) -> apellido, APELLIDO_LEN);
	switch (resultado)
	{
		case 1:
			rtn = 1;
			break;
		case 2:
			rtn = -1;
			break;
		case 0:
			rtn = 0;
			break;
	}
	return rtn;
}

int passenger_orderByPrice (void* thisOne, void* thisTwo)
{
	int rtn;
	if ( ((Passenger*)thisOne) -> precio > ((Passenger*)thisTwo) -> precio )
	{
		rtn = 1;
	}
	else if ( ((Passenger*)thisOne) -> precio < ((Passenger*)thisTwo) -> precio )
	{
		rtn = -1;
	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

int passenger_orderByFlightCode (void* thisOne, void* thisTwo)
{
	int rtn;
	int resultado;
	resultado = compararCadenas(((Passenger*)thisOne) -> codigoVuelo, ((Passenger*)thisTwo) -> codigoVuelo, APELLIDO_LEN);
	switch (resultado)
	{
		case 1:
			rtn = 1;
			break;
		case 2:
			rtn = -1;
			break;
		case 0:
			rtn = 0;
			break;
	}
	return rtn;
}

int passenger_orderByTypePassenger (void* thisOne, void* thisTwo)
{
	int rtn;
	if ( ((Passenger*)thisOne) -> tipoPasajero > ((Passenger*)thisTwo) -> tipoPasajero )
	{
		rtn = 1;
	}
	else if ( ((Passenger*)thisOne) -> tipoPasajero < ((Passenger*)thisTwo) -> tipoPasajero )
	{
		rtn = -1;
	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

int passenger_orderByStatusFlight (void* thisOne, void* thisTwo)
{
	int rtn;
	if ( ((Passenger*)thisOne) -> estadoVUelo > ((Passenger*)thisTwo) -> estadoVUelo )
	{
		rtn = 1;
	}
	else if ( ((Passenger*)thisOne) -> estadoVUelo < ((Passenger*)thisTwo) -> estadoVUelo )
	{
		rtn = -1;
	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

