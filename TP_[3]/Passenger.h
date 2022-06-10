/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <stdio.h>
#include <stdlib.h>
#include "Passenger.h"
#include "validaciones.h"
#include "LinkedList.h"

#define MAX_PASAJEROS 2000
#define NOMBRE_LEN 50
#define APELLIDO_LEN 50
#define CODIGO_LEN 8

typedef struct
{
	int id;
	char nombre[NOMBRE_LEN];
	char apellido[APELLIDO_LEN];
	float precio;
	int tipoPasajero;
	char codigoVuelo[CODIGO_LEN];
	int estadoVUelo;

}Passenger;

int Passenger_generarIdUnico (void);
void Passenger_setUltimoId (int ultimoId);
int Passenger_getUltimoId(int* id);

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr, char* apellidoStr, char* precioStr, char* codigoVueloStr, char* tipoPasajeroStr, char* estadoVueloStr);
void Passenger_delete(Passenger* this);

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);
int Passenger_TipoPasajeroToInt (char* cadena, int* numero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);
int Passenger_EstadoVueloToInt (char* cadena, int* numero);

int Passenger_print (Passenger* this);

int passenger_orderByID (void* thisOne, void* thisTwo);
int passenger_orderByName (void* thisOne, void* thisTwo);
int passenger_orderByLastName (void* thisOne, void* thisTwo);
int passenger_orderByPrice (void* thisOne, void* thisTwo);
int passenger_orderByFlightCode (void* thisOne, void* thisTwo);
int passenger_orderByTypePassenger (void* thisOne, void* thisTwo);
int passenger_orderByStatusFlight (void* thisOne, void* thisTwo);


#endif /* PASSENGER_H_ */
