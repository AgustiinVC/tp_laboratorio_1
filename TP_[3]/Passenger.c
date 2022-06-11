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

/// @fn int Passenger_generarIdUnico(void)
/// @brief generamos el id unico para cada pasajero
///
/// @return el id unico
int Passenger_generarIdUnico (void)
{
	return unicoId++;
}

/// @fn void Passenger_setUltimoId(int)
/// @brief seteamos el ultimo id para arrcncar desde cierto numero
///
/// @param ultimoId
void Passenger_setUltimoId (int ultimoId)
{
	unicoId = ultimoId;
}

/// @fn int Passenger_getUltimoId(int*)
/// @brief tomamos el ultimo id
///
/// @param id
/// @return un 0 si esta Ok y un -1 si hay error
int Passenger_getUltimoId(int* id)
{
	int rtn = -1;
	*id = unicoId;
	rtn = 0;
	return rtn;
}

/// @fn Passenger Passenger_new*()
/// @brief generamos el espacio en memoria de la estructura pasajero
///
/// @return el puntero que apunta a donde arranca la estructura pasajero creada
Passenger* Passenger_new()
{
	Passenger* auxPassenger;
	auxPassenger = (Passenger*) malloc (sizeof (Passenger));
	return auxPassenger;
}

/// @fn Passenger Passenger_newParametros*(char*, char*, char*, char*, char*, char*, char*)
/// @brief  tomamos los datos que queremos guardar en una estructura pasajero. dentro tenemos que convertir algunas cadenas en entero y flotante
///
/// @param idStr el ID en cadena
/// @param nombreStr el nombre en cadena
/// @param apellidoStr el apellido del pasajero
/// @param precioStr el precio del pasajero en cadena
/// @param codigoVueloStr el codigo del vuelo en cadena
/// @param tipoPasajeroStr el tipo de pasajero en formato cadena
/// @param estadoVueloStr el estado de vuelo en cadena
/// @return el pasajero con todos los datos seteados.
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

/// @fn void Passenger_delete(Passenger*)
/// @brief borramos el pasajero de la memoria
///
/// @param this
void Passenger_delete(Passenger* this)
{
	free (this);
}

/// @fn int Passenger_setId(Passenger*, int)
/// @brief guardamos el id del pasajero que queremos
///
/// @param this pasajero
/// @param id queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getId(Passenger*, int*)
/// @brief tomamos el id del pasajero
///
/// @param this pasajero
/// @param id donde queremos guardar el id del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_setNombre(Passenger*, char*)
/// @brief guardamos el nombre del pasajero que queremos
///
/// @param this pasajero
/// @param nombre es el que queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getNombre(Passenger*, char*)
/// @brief tomamos el nombre del pasajero
///
/// @param this pasajero
/// @param nombre donde queremos guardar el nombre del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_setApellido(Passenger*, char*)
/// @brief guardamos el apellido del pasajero que queremos
///
/// @param this pasajero
/// @param apellido es el  que queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getApellido(Passenger*, char*)
/// @brief tomamos el apellido del pasajero
///
/// @param this pasajero
/// @param apellido variable donde queremos guardar el apellido  del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_setCodigoVuelo(Passenger*, char*)
/// @brief guardamos el codigo del Vuelo del pasajero que queremos
///
/// @param this pasajero
/// @param codigoVuelo  es el codigo del Vuelo que queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getCodigoVuelo(Passenger*, char*)
/// @brief tomamos el codigo de vuelo del pasajero
///
/// @param this pasajero
/// @param codigoVuelo variable donde queremos guardar el codigo de vuelo  del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_setTipoPasajero(Passenger*, int)
/// @brief guardamos el tipo de Pasajero del pasajero que queremos
///
/// @param this pasajero
/// @param tipoPasajero  es el tipo de Pasajeroque queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getTipoPasajero(Passenger*, int*)
/// @brief tomamos el tipo de pasajero
///
/// @param this pasajero
/// @param tipoPasajero  variable donde queremos guardar el tipo de pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_TipoPasajeroToInt(char*, int*)
/// @brief convertimos una cadena del tipo de pasajero en un entero
///
/// @param cadena del tipo de pasajero
/// @param numero donde guardamos el entero
/// @return un 0 si esta OK y un -1 si hay error
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

/// @fn int Passenger_setPrecio(Passenger*, float)
/// @brief guardamos el precio del pasajero que queremos
///
/// @param this pasajero
/// @param precio  que queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getPrecio(Passenger*, float*)
/// @brief tomamos el precio del pasajero
///
/// @param this pasajero
/// @param precio variable donde queremos guardar el precio  del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_setEstadoVuelo(Passenger*, int)
/// @brief guardamos el estado del vuelo del pasajero que queremos
///
/// @param this pasajero
/// @param estadoVuelo el estado que queremos guardar en el pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_getEstadoVuelo(Passenger*, int*)
/// @brief
/// tomamos el estado de vuelo del pasajero y lo guardamos en una variable
/// @param this pasajero
/// @param estadoVuelo variable externa donde guardamos el estado del pasajero
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_EstadoVueloToInt(char*, int*)
/// @brief convertir el estado de vuelo en un entero
/// comparamos la cadena, cuando encontramos cual es devolvemos el entero que se condice
/// @param cadena cadena del estado del vuelo
/// @param numero donde guardamos el entero del estado de vuelo
/// @return un 0 si esta Ok y un -1 si hay error
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

/// @fn int Passenger_print(Passenger*)
/// @brief impresion de un pasajero
///
/// @param this el pasajero a imprimir
/// @return un 0 si esta OK y un -1 si hay error
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
		printf ("%-6d %-50s %-50s %-14.2f %-12s %-15s %-11s\n",
				auxPassenger->id, auxPassenger->nombre, auxPassenger->apellido, auxPassenger->precio, auxPassenger->codigoVuelo, PASAJERO_TIPOS [(auxPassenger->tipoPasajero)-1], ESTADO_VUELO[(auxPassenger->estadoVUelo)-1]);
		rtn = 0;
	}
	return rtn;
}

/// @fn int passenger_orderByID(void*, void*)
/// @brief  orden segun el ID
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByName(void*, void*)
/// @brief  orden segun el nombre
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByLastName(void*, void*)
/// @brief  orden segun el apellido
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByPrice(void*, void*)
/// @brief  orden segun el precio
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByFlightCode(void*, void*)
/// @brief  orden segun el codigo del vuelo
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByTypePassenger(void*, void*)
/// @brief  orden segun el tipo de pasajero
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

/// @fn int passenger_orderByStatusFlight(void*, void*)
/// @brief  orden segun el estado del vuelo
///
/// @param thisOne un pasajero
/// @param thisTwo otro pasajero
/// @return un 1 si es mayor el primero, -1 si es mayor el segundo y un 0 si son iguales
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

