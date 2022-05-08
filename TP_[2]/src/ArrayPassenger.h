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

#define TEXT_LEN 51
#define CODIGO 10

struct
{
	int id;
	char name[TEXT_LEN];
	char lastName[TEXT_LEN];
	float price;
	char flycode[CODIGO];
	int typePassenger;
	int statusFlight;
	int isEmpty;

}typedef Passenger;

int initPassengers(Passenger* list, int len);
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
void pas_printOne (Passenger* list, int index);
int sortPassengers(Passenger* list, int len, int order);
int sortPassengersByCode(Passenger* list, int len, int order);
int compararCadenas (char* cadenaUno, char* cadenaDos);
void toLowerCadena (char* cadena);
void menu (void);


#endif /* ARRAYPASSENGER_H_ */
