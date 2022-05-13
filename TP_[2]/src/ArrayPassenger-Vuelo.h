/*
 * ArrayPassenger-Vuelo.h
 *
 *  Created on: 10 may. 2022
 *      Author: Agostin
 */

#ifndef ARRAYPASSENGER_VUELO_H_
#define ARRAYPASSENGER_VUELO_H_

#include "ArrayPassenger.h"
#include "Vuelo.h"

int union_altaPassenger (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len);
int union_Modificacion (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len);

int union_printStruct(Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len);
int union_printActiveStruct(Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len);
void union_printOne (Passenger* aPassenger, Vuelo* aVuelo);

int union_Informar (Passenger* aPassenger, int pas_len, Vuelo* aVuelo, int vuelo_len);


#endif /* ARRAYPASSENGER_VUELO_H_ */
