/*
 * TextoValidaciones.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */

#ifndef TEXTOVALIDACIONES_H_
#define TEXTOVALIDACIONES_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/// @fn void menu(int, float, float)
/// @brief el menu que vamos a mostrar para ver las opciones.
///Este muno lo volvemos a ver con las modificaciones de los valores que se vayan ingresando
/// @param kilometros	si tenemos el kilometraje lo podemos ingresar al menu
/// @param precioAero	al igual que en el kilometraje pero con el precio de aerolinea
/// @param precioLatam	Lo mismo que en los dos casos anteriores.
void menu (int kilometros, float precioAero, float precioLatam);

/// @fn int getInt(int*, char*, char*, int)
/// @brief validacion de que ingresamos un numeros flotante mayor a 0
///Si se ingresa un caracter o numero menor a 0 nos tira un error hasta ingresar un valor correcto.
/// @param nroIngresado el puntero donde vamos a guardar el numero ingresado
/// @param mensaje el mensaje que queres que muestre al principio de que queremos pedir
/// @param mensajeError el mensaje de error que queremos que aparezca
/// @param min	el numero minimo a tener en cuenta
/// @return 0 cuando se termina la funcion
int getInt (int * nroIngresado, char *mensaje, char* mensajeError, int min);

/// @fn int getFloat(float*, char*, char*, float)
/// @brief validacion de que ingresamos un numeros entero mayor a 0
///Si se ingresa un caracter o numero menor a 0 nos tira un error hasta ingresar un valor correcto.
/// @param nroIngresado el puntero donde vamos a guardar el numero ingresado
/// @param mensaje el mensaje que queres que muestre al principio de que queremos pedir
/// @param mensajeError el mensaje de error que queremos que aparezca
/// @param min	el numero minimo a tener en cuenta
/// @return 0 cuando se termina la funcion
int getFloat (float * nroIngresado, char *mensaje, char* mensajeError, float min);

/// @fn unsigned int validacionCaracteres(char*, char, char)
/// @brief validamos los caracteres con 2 caracteres en especial que queremos.
///cualquier otro caracter lo toma como error
/// @param mensaje el mensaje que queremos mostrar
/// @param caracterUno el primer caracter que vamos a comparar
/// @param caracterDos el segundo caracter que se va a comparar
/// @return si retorna un 1 es que se ingreso el primer caracter. si retorna un 0 es que se ingreso el segundo caracter.
unsigned int validacionCaracteres (char *mensaje, char caracterUno, char caracterDos);

/// @fn void saltoDeLinea(void)
/// @brief	solo un salto de linea con ---- para emprolijar
///
void saltoDeLinea(void);

#endif /* TEXTOVALIDACIONES_H_ */
