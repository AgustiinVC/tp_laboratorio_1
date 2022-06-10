/*
 * Controller.h
 *
 *  Created on: 6 jun. 2022
 *      Author: Agostin
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "validaciones.h"

int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger);
int controller_getIndexById(LinkedList* pArrayListPassenger, int id);

int controller_changeFlightStatus (LinkedList* pArrayListPassenger, int id);
int controller_checkForFLightCode (LinkedList* pArrayListPassenger, char* codigoVuelo);

int controller_getLastId(void);
int controller_setLastId(void);


#endif /* CONTROLLER_H_ */
