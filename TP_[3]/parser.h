/*
 * parser.h
 *
 *  Created on: 6 jun. 2022
 *      Author: Agostin
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "validaciones.h"

int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger);
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger);
int parser_PassengerLastIdFromText(FILE* pFile);
int parser_LastIdFromText(FILE* pFile);
#endif /* PARSER_H_ */
