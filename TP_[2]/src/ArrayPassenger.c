/*
 * ArrayPassenger.c
 *
 *  Created on: 4 may. 2022
 *      Author: Agostin
 */

#include "validaciones.h"
#include "ArrayPassenger.h"

/// Para facilitar en la impresion de los tipos de pasajeros
static const char PASAJERO_TIPOS [4][30] = {"Primera Clase", "Business", "Premium Economy", "Economy"};

/// Inicio de variable ID Pasajero
static int Pasajero_idUnico = 1;

/// @fn int ePas_ObtenerID(void)
/// @brief
///  Generador de ID de cada pasajero. Suma 1 a la variable
/// @return devuelve el id de cada pasajero
static int ePas_ObtenerID (void)
{
	return Pasajero_idUnico++;
}


/// @fn int pas_initArray(Passenger*, int)
/// @brief
/// funcion para iniciar la estructura pasajeros al poner en LIBRE el campo isEmpty
/// @param list es la estructura pasajero
/// @param len es el tamaño de la estructura
/// @return devuelve un 0 si esta OK. Devuelve un -1 si hay algun error.
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

/// @fn int pas_indexEmpty(Passenger*, int)
/// @brief
/// funcion para buscar un indice que este vacio
/// @param list es la estructura pasajero
/// @param len es el tamaño de la estructura
/// @return devuelve el indice que se encuentra libre.. Devuelve un -1 si hay algun error.
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

/// @fn int addPassenger(Passenger*, int, int, char[], char[], float, int, char[])
/// @brief
///
/// @param list es la estructura pasajero
/// @param len es el tamaño de la estructura
/// @param id es el id del pasajero
/// @param name es el nombre del pasajero
/// @param lastName es el apellido del pasajero
/// @param price es el precio del vuelo del pasajero
/// @param typePassenger es el tipo de pasajero
/// @param flycode es el codigo del vuelo
/// @return devuelve un 0 si esta OK. Devuelve un -1 si hay algun error.
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
			strncpy (list[indiceLibre].FK_flycode, flycode, CODIGO);
			list[indiceLibre].id =  id;
			list[indiceLibre].isEmpty = OCUPADO;

			rtn = 0;
		}
	}
	return rtn;
}

/// @fn Passenger pas_ModificarUno(Passenger)
/// @brief
/// funcion para modificar un pasajero en especifico ya sea cualquiera de sus campos
/// @param miPasajero es la estructura que se piensa modificar
/// @return devuelve una estructura con los valores que se quisieron modificar
Passenger pas_ModificarUno(Passenger miPasajero)
{
	int opcion;
	int respuesta;
	Passenger auxiliar = miPasajero;
	do
	{
		fflush(stdin);
		utn_getIntRange (&opcion ,"\nIngrese la opcion a modificar:\n "
									"1 - Nombre\n "
									"2 - Apellido\n "
									"3 - Precio\n "
									"4 - Tipo de Pasajero\n "
									"5 - Codigo de Vuelo\nOpcion: ",
									"Error. Ingrese una opcion correcta\n\n", 1, 5);

		switch (opcion)
		{
			case 1:
				if( utn_getNombre(auxiliar.name, "Ingrese el nombre del pasajero: ", "Ingrese un nombre valido\n\n", TEXT_LEN, 3) == 0)
				{
					puts ("Carga de nombre correcta\n");
				}
				else
				{
					puts("No se pudo cargar el nombre");
				}
				break;

			case 2:
				if(utn_getNombre(auxiliar.lastName, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n\n", TEXT_LEN, 3) == 0)
				{
					puts ("Carga de apellido correcta\n");
				}
				else
				{
					puts("No se pudo cargar el apellido");
				}
				break;

			case 3:
				if(utn_getFloatPositivo(&auxiliar.price, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n\n") == 0)
				{
					puts ("Carga de precio correcta\n");
				}
				else
				{
					puts("No se pudo cargar el precio");
				}
				break;

			case 4:
				if(utn_getIntRange(&auxiliar.typePassenger, "Ingrese el tipo del vuelo: "
						"\n\t 1 = Primera Clase\n\t 2 = Business\n\t 3 - Premium Economy\n\t 4 - Economy\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,4) == 0)
				{
					puts ("Carga de tipo del vuelo correcta\n");
				}
				else
				{
					puts("No se pudo cargar el tipo del vuelo");
				}
				break;

			case 5:
				if(utn_getString(auxiliar.FK_flycode, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n\n", CODIGO, 3) == 0)
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

/// @fn int pas_Modificacion(Passenger*, int)
/// @brief modificacion de un pasajero. se imprime la lista de pasajeros. si hay pasajeros se pone en 1 un flag de alta.
/// se pide que se ingrese alguno de los id mostrados y si se encuentra se modifica dicho id
/// @param list es la estructura pasajero
/// @param len es el tamaño de la estructura
/// @return devuelve un 0 si esta OK. un -1 si hay algun error
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
		if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n") == 0)
		{
			while (findPassengerById(list, len, idIngresado) == -1)
			{
				puts("NO EXISTE ID.");
				utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n\n");
			}
			index = findPassengerById(list, len, idIngresado);
			auxiliar = pas_ModificarUno(list[index]);
			list[index] = auxiliar;
			rtn = 0;
		}
	}
	return rtn;
}

/// @fn int cargaDatosPasajero(Passenger*)
/// @brief
/// carga de datos en un pasajero auxiliar para luego ser cargada en la estructura de pasajeros
/// @param auxList un pasajero auxiliar
/// @return devuelve un 0 si esta OK. un -1 si hay algun error
int cargaDatosPasajero (Passenger* auxList)
{
	int rtn = -1;
	if (auxList != NULL)
	{
		if (utn_getNombre(auxList->name, "\nIngrese el nombre del pasajero: ", "Ingrese un nombre valido\n", TEXT_LEN, 3) == 0 &&
			utn_getNombre(auxList->lastName, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n ", TEXT_LEN, 3) == 0 &&
			utn_getFloatPositivo(&auxList->price, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n") == 0 &&
			utn_getIntRange(&auxList->typePassenger, "Ingrese el tipo del vuelo: "
					"\n\t 1 = Primera Clase\n\t 2 = Business\n\t 3 - Premium Economy\n\t 4 - Economy\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,4) == 0 &&
			utn_getCodigo(auxList->FK_flycode, "Ingrese el codigo del vuelo (Alfanumerico min: 4 caracteres): ", "Ingrese un codigo valido\n", 4, CODIGO, 3) == 0)
		{
			auxList->id = ePas_ObtenerID();
			rtn = 0;
		}
	}

	return rtn;
}


/// @fn int findPassengerById(Passenger*, int, int)
/// @brief
/// busca el id en todos los pasajeros dados de alta.
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @param id del pasajero a buscar
/// @return devuelve el indice del ID buscado si se encontro y no esta dado de baja. un -1 si hay algun error
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


/// @fn int removePassenger(Passenger*, int, int)
/// @brief
/// funcion para dar de baja a un pasajero que se haya dado de alta.
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @param id del pasajero a dar de baja
/// @return devuelve un 0 si esta OK. Un -1 si hay algun error
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

/// @fn int pas_Baja(Passenger*, int)
/// @brief funcion para dar de baja un pasajero. se imprime la lista de pasajeros si hay dados de alta. Luego se pide ingresar
/// un id que se quiere dar de baja. si se ingreso un id que se encuentra dado de alta, se preocede a dar de baja en la funcion removePassenger.
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @return devuelve un 0 si esta OK. Un -1 si hay algun error
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
		if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un numero.\n") == 0)
		{
			while (findPassengerById(list, len, idIngresado) == -1)
			{
				puts("NO EXISTE ID.");
				utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un numero.\n");
			}

			index = findPassengerById(list, len, idIngresado);
			if (validacionDosCaracteres ("¿Esta seguro de querer borrar el pasajero? (S/N)", 'S', 'N') == 1)
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

/// @fn int pas_isStrucEmpty(Passenger*, int)
/// @brief
/// funcion para saber si hay pasajeros dados de alta.
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @return devuelve un 0 si la estructura no esta vacia. un -1 si esta vacia
int pas_isStrucEmpty (Passenger* list, int len)
{
	int rtn = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == OCUPADO)
			{
				rtn = 0;
			}
		}
	}
	return rtn;
}

/// @fn int pas_CalculosPasaje(Passenger*, int)
/// @brief
/// funcion para los calculos de promedio, totales y si alguno supero el promedio.
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @return devuelve un 0 si esta OK. un -1 si hay algun error
int pas_CalculosPasaje (Passenger* list, int len)
{
	int rtn = -1;
	float totalPrecio = 0;
	float promedioPasaje;
	int cantidadPasaje = 0;
	int cantidadMayorQuePromedio = 0;

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == OCUPADO)
			{
				cantidadPasaje++;
				totalPrecio += list[i].price;
				rtn = 0;
			}
		}

		promedioPasaje = totalPrecio / cantidadPasaje;

		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == OCUPADO && list[i].price > promedioPasaje)
			{
				cantidadMayorQuePromedio++;
			}
		}
		printf ("---------------------------\n"
				"El total en pasajes es de: $%.4f.\n"
				"El promedio de pasajes es de: $%.4f.\n"
				"La cantidad de pasajes que superan el promedio es: %d\n"
				"---------------------------\n", totalPrecio, promedioPasaje, cantidadMayorQuePromedio);

	}
	return rtn;
}


/// @fn int printPassenger(Passenger*, int)
/// @brief
/// funcion para imprimir los pasajeros dados de alta
/// @param list es la estructura pasajero
/// @param length es la cantidad maxima de pasajeros
/// @return devuelve un 0 si esta ok. un -1 si hay un error.
int printPassenger(Passenger* list, int length)
{
	int rtn = -1;
	int flagPrimerPasajero = 0;

	if (list != NULL && length > 0)
	{
		sortPassengersByID(list, length);
		for (int i = 0; i < length; i++)
		{
			if (list[i].isEmpty == OCUPADO)
			{
				if (flagPrimerPasajero == 0)
				{
					flagPrimerPasajero = 1;
					puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS\n"
							"--------------------------------------------------------------------------------------"
							"-------------------------------------------------------------------------------");
					printf("%-6s %-52s %-52s %-14s %-19s %-15s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO");
				}

				pas_printOne (&list[i]);
				rtn = 0;
			}
		}
	}

	return rtn;
}

/// @fn void pas_printOne(Passenger*)
/// @brief
/// impresion de un solo pasajero
/// @param list es el pasajero que se va a imprimir
void pas_printOne (Passenger* list)
{
	printf ("%-6d %-52s %-52s %-14.2f %-19s %-15s\n",
		list->id, list->name, list->lastName, list->price, list->FK_flycode, PASAJERO_TIPOS [(list->typePassenger)-1]);
}

/// @fn int sortPassengersByID(Passenger*, int)
/// @brief
/// funcion para ordenar los pasajeros por ID menor a mayor
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @return devuelve un 0 si esta OK. un -1 si hay error
int sortPassengersByID(Passenger* list, int len)
{
	int rtn = -1;
	int i;
	int j;
	Passenger auxPasajeros;

	if (list != NULL && len > 0)
	{
				for (i = 1; i < len; i++)
				{
					auxPasajeros = list[i];
					j = i - 1;
					while ( (j >= 0) && (auxPasajeros.id < list[j].id) )
					{
						list[j + 1] = list[j];
						j--;
					}
					list[j + 1] = auxPasajeros;
				}

				rtn = 0;
	}
	return rtn;
}


/// @fn int sortPassengers(Passenger*, int, int)
/// @brief
/// funcion para ordenar los pasajeros por Apellido y si hay mismo apellido por tipo de pasajero
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @param order como se va a ordenar la lista. 1 Ascendente y 0 Descendente
/// @return devuelve un 0 si esta OK. un -1 si hay error
int sortPassengers(Passenger* list, int len, int order) //Apellido y tipo de pasajero
{
	int rtn = -1;
	int i;
	int j;
	Passenger auxPasajeros;

	if (list != NULL && len > 0)
	{
		switch (order)
		{
			case 1: //ascendente (A a Z - Eco a Primera)
				for (i = 1; i < len; i++)
				{
					auxPasajeros = list[i];
					j = i - 1;
					while ( (j >= 0) &&
							( compararCadenas (list[j].lastName, auxPasajeros.lastName, TEXT_LEN) == 1  ||
							 (compararCadenas (auxPasajeros.lastName, list[j].lastName, TEXT_LEN) == 3 && auxPasajeros.typePassenger > list[j].typePassenger) ) )
					{
						list[j + 1] = list[j];
						j--;
					}
					list[j + 1] = auxPasajeros;
				}

				rtn = 0;
				break;
			case 0:
				for (i = 1; i < len; i++)
				{
					auxPasajeros = list[i];
					j = i - 1;
					while ( (j >= 0) &&
							( compararCadenas (list[j].lastName, auxPasajeros.lastName, TEXT_LEN) == 2  ||
							 (compararCadenas (auxPasajeros.lastName, list[j].lastName, TEXT_LEN) == 3 && auxPasajeros.typePassenger < list[j].typePassenger) ) )
					{
						list[j + 1] = list[j];
						j--;
					}
					list[j + 1] = auxPasajeros;
				}

				rtn = 0;
				break;
		}
	}
	return rtn;
}

/// @fn int sortPassengersByCode(Passenger*, int, int)
/// @brief
/// funcion para ordenar los pasajeros por Codigo de vuelo
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @param order como se va a ordenar la lista. 1 Ascendente y 0 Descendente
/// @return devuelve un 0 si esta OK. un -1 si hay error
int sortPassengersByCode(Passenger* list, int len, int order)
{
	int rtn = -1;
	int i;
	int j;
	Passenger auxPasajeros;

	if (list != NULL && len > 0)
	{
		switch (order) {
		case 1:
			for (i = 1; i < len; i++)
			{
				auxPasajeros = list[i];
				j = i - 1;
				while ( (j >= 0) && compararCadenas (list[j].FK_flycode, auxPasajeros.FK_flycode, TEXT_LEN) == 1)
				{
					list[j + 1] = list[j];
					j--;
				}
				list[j + 1] = auxPasajeros;
			}
			rtn = 0;
			break;
		case 0:
			for (i = 1; i < len; i++)
			{
				auxPasajeros = list[i];
				j = i - 1;
				while ( (j >= 0) && compararCadenas (list[j].FK_flycode, auxPasajeros.FK_flycode, TEXT_LEN) == 2)
				{
					list[j + 1] = list[j];
					j--;
				}
				list[j + 1] = auxPasajeros;
			}
			rtn = 0;
			break;
		}
	}
	return rtn;
}

/// @fn int altaForzadaPasajeros(Passenger*, int)
/// @brief
/// alta forzada de pasajeros
/// @param list es la estructura pasajero
/// @param len es la cantidad maxima de pasajeros
/// @return devuelve un 0 si esta OK. un -1 si hay error
int altaForzadaPasajeros (Passenger* list, int len)
{
	int rtn = -1;
	int indiceLibre;

	if (list != NULL && len > 0)
	{
		indiceLibre = pas_indexEmpty (list, len);
		if (indiceLibre != -1)
		{
			list[indiceLibre] = pas_UnPasajeroForzado (indiceLibre, "Agustin", "Vallario", 100, "ABC123", 1);
			list[indiceLibre+1] = pas_UnPasajeroForzado (indiceLibre+1, "Rodrigo", "Palacios", 100, "CFR234", 3);
			list[indiceLibre+2] = pas_UnPasajeroForzado (indiceLibre+2, "Jimena", "Mendoza", 100, "GHR736", 1);
			list[indiceLibre+3] = pas_UnPasajeroForzado (indiceLibre+3, "Pablo", "Vallario", 101, "LOL640", 2);
			list[indiceLibre+4] = pas_UnPasajeroForzado (indiceLibre+4, "Rosario", "Fernandez", 99, "ABC123", 4);

			for (int i = indiceLibre; i < indiceLibre + 5; i++)
			{

				list[i].id = ePas_ObtenerID();
				list [i].isEmpty = OCUPADO;
			}
			rtn = 0;
		}
	}

	return rtn;
}

/// @fn Passenger pas_UnPasajeroForzado(int, char*, char*, float, char*, int)
/// @brief
/// funcion para cargar un pasajero en especifico
/// @param indiceLibre el indice libre del pasajero
/// @param name el nombre del pasajero
/// @param lastname el apellido
/// @param price el precio del vuelo
/// @param codeFlight el codigo de vuelo
/// @param typePassenger tipo de pasajero
/// @return una estructura pasajero auxiliar
Passenger pas_UnPasajeroForzado (int indiceLibre, char* name, char* lastname, float price, char* codeFlight,int typePassenger)
{
	Passenger auxLista;
	strncpy(auxLista.name, name, sizeof(auxLista.name));
	strncpy(auxLista.lastName, lastname, sizeof(auxLista.lastName));
	auxLista.price = price;
	strncpy(auxLista.FK_flycode, codeFlight, sizeof(auxLista.FK_flycode));
	auxLista.typePassenger = typePassenger;

	return auxLista;
}
