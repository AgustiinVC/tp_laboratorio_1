/*
 ============================================================================
 Name        : Clase.c
 Author      : Agust�n
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	setbuf (stdout,NULL);
	//Pedir dos n�meros al usuario
	//sumarlos y mostrar la suma

	int nroUno;
	int nroDos;
	int resultado;

	printf("Ingrese el primer n�mero: ");
	scanf ("%d", &nroUno);

	printf("Ingrese el segundo n�mero: ");
	scanf ("%d",&nroDos);

	resultado = nroUno + nroDos;
	printf ("El resultado es: %d \n",resultado);


	return EXIT_SUCCESS;
}
