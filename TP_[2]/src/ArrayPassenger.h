/*
 * ArrayPassenger.h
 *
 *  Created on: 4 may. 2022
 *      Author: Agostin
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

#include <stdio.h>
#include <stdlib.h>

#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

#define ACTIVO 1
#define DEMORADO 2
#define CANCELADO 3


#define TEXT_LEN 51
#define CODIGO 10

struct
{
	int id;
	char name[TEXT_LEN];
	char lastName[TEXT_LEN];
	float price;
	char FK_flycode[CODIGO];
	int typePassenger;
	int isEmpty;

}typedef Passenger;

int pas_initArray(Passenger* list, int len);
int pas_indexEmpty (Passenger* list, int len);
int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[]);
Passenger pas_ModificarUno(Passenger miPasajero);
int pas_Modificacion(Passenger* list, int len);
int cargaDatosPasajero (Passenger* auxList);
int findPassengerById(Passenger* list, int len,int id);
int removePassenger(Passenger* list, int len, int id);
int pas_Baja (Passenger* list, int len);
int pas_Informar (Passenger* list, int len);
int pas_isStrucEmpty (Passenger* list, int len);
int pas_CalculosPasaje (Passenger* list, int len);
int printPassenger(Passenger* list, int length);
void pas_printOne (Passenger* list);
int printActivePassenger(Passenger* list, int length);
int sortPassengers(Passenger* list, int len, int order);
int sortPassengersByCode(Passenger* list, int len, int order);
int altaForzadaPasajeros (Passenger* list, int len);
Passenger pas_UnPasajeroForzado (int indiceLibre, char* name, char* lastname, float price,char* codeFlight,int typePassenger);
void menu (void);


#endif /* ARRAYPASSENGER_H_ */
