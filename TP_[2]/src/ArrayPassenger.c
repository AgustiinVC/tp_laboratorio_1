/*
 * ArrayPassenger.c
 *
 *  Created on: 4 may. 2022
 *      Author: Agostin
 */

#include "validaciones.h"
#include "ArrayPassenger.h"

static int Pasajero_idUnico = 0;

static int ePas_ObtenerID (void)
{
	return Pasajero_idUnico++;
}

int initPassengers(Passenger* list, int len)
{
	int rtn = -1;
	int i;
	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = LIBRE;
			rtn = 0;
		}
	}
	return rtn;
}

int pas_indexEmpty (Passenger* list, int len)
{
	int rtn = -1;
	int i;
	if (list != NULL && len >= 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].isEmpty == LIBRE)
			{
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}

int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[])
{
	int rtn = -1;
	int indiceLibre;

	if (list != NULL && len > 0 && id >= 0 && name != NULL && lastName != NULL && price > 0 && typePassenger > 0 && flycode != NULL)
	{
		indiceLibre = pas_indexEmpty (list, len);
		if (indiceLibre != -1)
		{
			strncpy (list[indiceLibre].name, name, TEXT_LEN);
			strncpy (list[indiceLibre].lastName, lastName, TEXT_LEN);
			list[indiceLibre].price = price;
			list[indiceLibre].typePassenger = typePassenger;
			strncpy (list[indiceLibre].flycode, flycode, CODIGO);
			list[indiceLibre].id =  id;
			list[indiceLibre].isEmpty = OCUPADO;

			rtn = 0;
		}
	}
	return rtn;
}

Passenger pas_ModificarUno(Passenger miPasajero)
{
	int opcion;
	int respuesta;
	Passenger auxiliar = miPasajero;
	do
	{
		fflush(stdin);
		utn_getIntRange (&opcion ,"\nIngrese la opcion a modificar:\n 1 - Nombre\n 2 - Apellido\n 3 - Precio\n 4 - Tipo de Pasajero\n 5 - Codigo de Vuelo\nOpcion: "
				, "Error. Ingrese una opcion correcta\n\n", 1, 5);

		switch (opcion)
		{
			case 1:
				if( utn_getNombre(auxiliar.name, "Ingrese el nombre del pasajero: ", "Ingrese un nombre valido\n\n", TEXT_LEN, 3))
				{
					puts ("Carga de nombre correcta\n");
				}
				else
				{
					puts("No se pudo cargar el nombre");
				}
			break;

			case 2:
				if(utn_getNombre(auxiliar.lastName, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n\n", TEXT_LEN, 3))
				{
					puts ("Carga de apellido correcta\n");
				}
				else
				{
					puts("No se pudo cargar el apellido");
				}
			break;

			case 3:
				if(utn_getFloatPositivo(&auxiliar.price, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n\n"))
				{
					puts ("Carga de precio correcta\n");
				}
				else
				{
					puts("No se pudo cargar el precio");
				}
			break;

			case 4:
				if(utn_getIntRange(&auxiliar.typePassenger, "Ingrese el tipo del vuelo (1 = A 2 = B): ", "Ingrese un tipo de vuelo valido\n\n", 1,2))
				{
					puts ("Carga de tipo del vuelo correcta\n");
				}
				else
				{
					puts("No se pudo cargar el tipo del vuelo");
				}
			break;

			case 5:
				if(utn_getString(auxiliar.flycode, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n\n", CODIGO, 3))
				{
					puts ("Carga de codigo del vuelo correcta\n");
				}
				else
				{
					puts("No se pudo cargar el codigo del vuelo");
				}
			break;
		}


		respuesta = validacionDosCaracteres ("¿Desea modificar otro campo? (S/N)", 'S', 'N');
	}
	while (respuesta);

	return auxiliar;
}

int pas_Modificacion(Passenger* list, int len)
{
	int rtn = -1;
	int idIngresado;
	int index;
	int flagAlta = 0;
	Passenger auxiliar;

	if (printPassenger(list, len) == 0)
	{
		flagAlta = 1;
	}

	if (flagAlta) {
		if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n"))
		{
			while (findPassengerById(list, len, idIngresado) == -1)
			{
				puts("NO EXISTE ID.");
				utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n");
			}
			index = findPassengerById(list, len, idIngresado);
			auxiliar = pas_ModificarUno(list[index]);
			list[index] = auxiliar;
			rtn = 0;
		}
	}
	return rtn;
}

int cargaDatosPasajero (Passenger* auxList)
{
	int rtn = -1;
	if (auxList != NULL)
	{
		if (utn_getNombre(auxList->name, "Ingrese el nombre del pasajero: ", "Ingrese un nombre valido\n", TEXT_LEN, 3) &&
			utn_getNombre(auxList->lastName, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n ", TEXT_LEN, 3) &&
			utn_getFloatPositivo(&auxList->price, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n ") &&
			utn_getIntRange(&auxList->typePassenger, "Ingrese el tipo del vuelo (1 = A 2 = B): ", "Ingrese un tipo de vuelo valido (1 = A 2 = B)\n", 1,2) &&
			utn_getString(auxList->flycode, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n", CODIGO, 3) )
		{
			auxList->id = ePas_ObtenerID();
			puts ("Cliente cargado");
			rtn = 0;
		}
	}

	return rtn;
}

int findPassengerById(Passenger* list, int len,int id)
{
	int rtn = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].id == id && list[i].isEmpty == OCUPADO)
			{
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}

int removePassenger(Passenger* list, int len, int id)
{
	int rtn = -1;

	if (list != NULL && len >= 0 && id < len && id >= 0 && list[id].isEmpty == OCUPADO)
	{
		list[id].isEmpty = BAJA;
		rtn = 0;
	}
	return rtn;
}

int pas_Baja (Passenger* list, int len)
{
	int rtn = -1;
	int idIngresado;
	int index;
	int flagAlta = 0;

	if (printPassenger(list, len) == 0)
	{
		flagAlta = 1;
	}

	if (flagAlta)
	{
		if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un numero.\n"))
		{
			while (findPassengerById(list, len, idIngresado) == -1)
			{
				puts("NO EXISTE ID.");
				utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un numero.\n");
			}

			index = findPassengerById(list, len, idIngresado);
			if (validacionDosCaracteres ("¿Esta seguro de querer borrar el pasajero? (S/N)", 'S', 'N'))
			{
				if (removePassenger(list, len, index) == 0)
				{
					rtn = 0;
				}
			}
		}
	}

	return rtn;
}

int sortPassengers(Passenger* list, int len, int order)
 {
	int rtn = -1;
	int i;
	int j;
	Passenger aux;

	/** EJEMPLO DE SORT CON ID DE Gen
	 MODIFICAR "CRITERIO DE ORDENAMIENTO" PARA OTROS CASOS DE ORDENAMIENTO
	 CASE -1 -> MENOR A MAYOR (ASCENDENTE)
	 CASE  1 -> MAYOR A MENOR (DESCENDENTE)

	 UTILIZAR strcmp(...) PARA COMPARAR CADENAS
	 */

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (list != NULL && len > 0)
	{
		switch (order) {
		case 1:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (list[i].isEmpty == OCUPADO && list[j].isEmpty == OCUPADO) {
						//CRITERIO DE ORDENAMIENTO
						if (list[i].id > list[j].id) {
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = list[i];
							list[i] = list[j];
							list[j] = aux;
						}
					}
				}
			}
			rtn = 1;
			break;
		case 0:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (list[i].isEmpty == OCUPADO && list[j].isEmpty == OCUPADO) {
						//CRITERIO DE ORDENAMIENTO
						if (list[i].id < list[j].id) {
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = list[i];
							list[i] = list[j];
							list[j] = aux;
						}
					}
				}
			}
			rtn = 0;
			break;
		default:
			//CRITERIO DE ORDENAMIENTO MAL INGRESADO
			rtn = 1;
			break;
		}
	}
	return rtn;
}

int printPassenger(Passenger* list, int length)
{
	int rtn = -1;

	if (list != NULL && length > 0)
	{
		puts("\n\t> LISTADO PASAJEROS");
		printf("ID\tNOMBRE\tAPELLIDO\tPRECIO\tCODIGO VUELO\tTIPO PASAJERO\n"); //AGREGAR TITULOS DE COLUMNA (QUITAR DE VER QUE NO ES NECESARIO)
		for (int i = 0; i < length; i++)
		{
			if (list[i].isEmpty == OCUPADO)
			{
				pas_printOne (list, i);
				rtn = 0;
			}
		}

	}

	return rtn;
}

void pas_printOne (Passenger* list, int index)
{
	printf("%d\t", list[index].id);
	printf("%s\t", list[index].name);
	printf("%s\t", list[index].lastName);
	printf("%.2f\t", list[index].price);
	printf("%s\t", list[index].flycode);
	printf("%d\t", list[index].typePassenger);
}

int sortPassengersByCode(Passenger* list, int len, int order)
{
	int rtn = -1;
	int i;
	int j;
	Passenger aux;

	/** EJEMPLO DE SORT CON ID DE Gen
	 MODIFICAR "CRITERIO DE ORDENAMIENTO" PARA OTROS CASOS DE ORDENAMIENTO
	 CASE -1 -> MENOR A MAYOR (ASCENDENTE)
	 CASE  1 -> MAYOR A MENOR (DESCENDENTE)

	 UTILIZAR strcmp(...) PARA COMPARAR CADENAS
	 */

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (list != NULL && len > 0)
	{
		switch (order) {
		case 1:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (list[i].isEmpty == OCUPADO && list[j].isEmpty == OCUPADO) {
						//CRITERIO DE ORDENAMIENTO
						if (list[i].id > list[j].id) {
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = list[i];
							list[i] = list[j];
							list[j] = aux;
						}
					}
				}
			}
			rtn = 1;
			break;
		case 0:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (list[i].isEmpty == OCUPADO && list[j].isEmpty == OCUPADO) {
						//CRITERIO DE ORDENAMIENTO
						if (list[i].id < list[j].id) {
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = list[i];
							list[i] = list[j];
							list[j] = aux;
						}
					}
				}
			}
			rtn = 0;
			break;
		default:
			//CRITERIO DE ORDENAMIENTO MAL INGRESADO
			rtn = 1;
			break;
		}
	}
	return rtn;
}

void menu (void)
{
	puts ("1. Alta de pasajero.");
	puts ("2. Modificar pasajero ID.");
	puts ("3. Baja de pasajero");
	puts ("4. Ordenar pasajeros por apellido y tipo de pasajero.");
	puts ("5. Ordenar pasajeros por codigo de vuelo");
	puts ("6. Imprimir pasajeros");
	puts ("7. Salir.");
}
