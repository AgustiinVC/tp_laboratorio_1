/*
 * OperacionesyResultados.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Agustin
 */
#include "OperacionesyResultados.h"
#include "TextoValidaciones.h"

//Por medio de punteros modificamos los valores de las variable de kilómetros y precios de vuelos.
void cargaForzada (int* kilometros,float* precioAero,float* precioLatam)
{
	*kilometros = 7090;
	*precioAero = 162925;
	*precioLatam = 159339;
}


/*Realizamos la validacion y luego el cálculo de todos los datos necesarios.
Si falta ingresar kilómetros o no se ingresa al menos uno de los vuelos no se realizan los calculos respectivos */
void validacionCalculo(int kilometros, float precioAero, float precioLatam, float* debitoA,float* creditoA, float* bitcoinA, float* unitarioA, float* debitoL, float* creditoL, float* bitcoinL, float* unitarioL, float* diferenciaPrecio)
{
	if (kilometros != 0 && precioAero !=0)  //verifico que ingrese kilometros y precio de Aerolinea
	{
		calculoVuelo(kilometros, precioAero, &debitoA, &creditoA, &bitcoinA, &unitarioA);
	}

	if (kilometros != 0 && precioLatam !=0) //verifico que ingrese kilometros y precio de Latam
	{
		calculoVuelo(kilometros,precioLatam, &debitoL, &creditoL, &bitcoinL, &unitarioL);
	}

	if (kilometros == 0) //Si no ingreso kilometros no realizo ningun calculo y aviso por mensaje
	{
		puts ("Todavia no ingresaste los kilometros por lo que no se puede realizar los calculos.");
	}

	if (precioAero == 0 && precioLatam == 0) //Si faltan ambos precios de aerolineas tampoco realizo el cálculo
	{
		puts ("Todavia no ingresaste ningun precio de vuelo por lo que no se puede realizar los calculos.");
	}
	else	//En este caso como tengo ambos precios puedo realizar la diferencia de precios.
	{
		*diferenciaPrecio = precioAero - precioLatam;
	}
}


//Aca se realiza el cálculo del vuelo. Empleo puntero de punteros asi modifico directo en las variables del programa
void calculoVuelo (int kilometros,float precioVuelo,float** debito,float** credito, float** bitcoin, float** unitario)

{
	**debito = precioVuelo * (1 - DEBITO/100);  //Uso una Constante DEBITO asi en caso de queres modificar a futuro ese valor es mas facil modificarlo
	**credito = precioVuelo * (1 + CREDITO/100);
	**bitcoin = precioVuelo / PRECIO_BITCOIN; //El precio del bitcoin lo modifico solo en la constante.
	**unitario = precioVuelo / kilometros;

}


//Muestra de los resultados ya sea para Latam o para Aerolineas.
void mostrarResultados (char* vuelo, float precioVuelo, float debito,float credito, float bitcoin, float unitario)
{
	printf ("\nPrecio %s: $%.2f\n", vuelo, precioVuelo);
	printf ("a)Precio con tarjeta de debito: $%.2f\n", debito);
	printf ("b)Precio con tarjeta de credito: $%.2f\n", credito);
	printf ("c)Precio pagando con bitcoin: %.5f BTC\n", bitcoin);
	printf ("d)Mostrar precio unitario: $%.2f por Km.\n", unitario);

}

//Función para mostrar la diferencia de precios si hay ambos precios de vuelos.
void mostrarDiferencia (float diferenciaPrecio)
{
	printf ("\nLa diferencia de precio es: $%.2f\n", diferenciaPrecio);
	saltoDeLinea();
}

