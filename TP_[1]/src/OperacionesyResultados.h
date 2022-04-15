/*
 * OperacionesyResultados.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */

#ifndef OPERACIONESYRESULTADOS_H_
#define OPERACIONESYRESULTADOS_H_

#define PRECIO_BITCOIN 4439362.82
#define DEBITO 10.00
#define CREDITO 25.00

/// @fn void cargaForzada(int*, float*, float*)
/// @brief carga forzada de datos y lueeo muestra del mismmo para chequear el correcto
/// funcionamiento del programa
/// @param kilometros parametro forzado de kilometros
/// @param precioAero parametro forzado del precio Aerolineas
/// @param precioLatam parametro forzado del precio Latinoamerica
void cargaForzada (int* kilometros,float* precioAero,float* precioLatam);


/// @fn int validacionCalculo(int, float, float, float*, float*, float*, float*, float*, float*, float*, float*, float*)
/// @brief aca realizamos la validacion y luego el calculo de los distintos precios para cada caso (debito, credito, bitcoin, unitario)
/// A su vez usamos la funcion que se encuentra abajo para una vez validado que tenemos todos los datos necesarios poder hacer los calculos.
/// @param kilometros
/// @param precioAero
/// @param precioLatam
/// @param debitoA
/// @param creditoA
/// @param bitcoinA
/// @param unitarioA
/// @param debitoL
/// @param creditoL
/// @param bitcoinL
/// @param unitarioL
/// @param diferenciaPrecio
/// @return 0 cuando no se puede realizar el calculo por falta de kilometros y 1 cuando puedo realizar cualquier de los calculos
int validacionCalculo(int kilometros, float precioAero, float precioLatam, float* debitoA,float* creditoA, float* bitcoinA, float* unitarioA, float* debitoL, float* creditoL, float* bitcoinL, float* unitarioL, float* diferenciaPrecio);


/// @fn void calculoVuelo(int, float, float**, float**, float**, float**)
/// @brief en esta funcion calculamos con los valores ingresados de kilometros y precio del vuelo.
///
/// @param kilometros el kilometraje ingresado
/// @param precioVuelo el precio del vuelo
/// @param debito puntero apuntando a puntero que nos dirige al valor de precio por debito para ingresarlo ahi
/// @param credito puntero a puntero para indicarnos la direccion del valor a modificar
/// @param bitcoin lo mismo que lo anterior pero del bitcoin
/// @param unitario	lo mismo pero para el precio en unitario
void calculoVuelo (int kilometros,float precioVuelo,float** debito,float** credito, float** bitcoin, float** unitario);


/// @fn void mostrarResultados(char*, float, float, float, float, float)
/// @brief  Impresion de los resultados obtenidos en los calculos
///
/// @param vuelo nombre del vuelo (Aerolineas o Latam)
/// @param precioVuelo	el precio del vuelo
/// @param debito el precio por debito
/// @param credito el precio por credito
/// @param bitcoin el precio en bitcoin del vuelo
/// @param unitario	precio por kilometro
void mostrarResultados (char* vuelo, float precioVuelo, float debito,float credito, float bitcoin, float unitario);


/// @fn void mostrarDiferencia(float)
/// @brief Imprimimos la diferencia de precio
///
/// @param difereciaPrecio	valor de la diferencia entre ambos vuelos
void mostrarDiferencia (float difereciaPrecio);

#endif /* OPERACIONESYRESULTADOS_H_ */
