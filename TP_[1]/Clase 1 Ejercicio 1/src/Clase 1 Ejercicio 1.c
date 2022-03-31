/*
 ============================================================================
 Name        : Clase.c
 Author      : Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	setbuf (stdout,NULL);
	//Pedir dos números al usuario
	//sumarlos y mostrar la suma

	int nroUno;
	int nroDos;
	int resultado;

	printf("Ingrese el primer número: ");
	scanf ("%d", &nroUno);

	printf("Ingrese el segundo número: ");
	scanf ("%d",&nroDos);

	resultado = nroUno + nroDos;
	printf ("El resultado es: %d \n",resultado);


	return EXIT_SUCCESS;
}
