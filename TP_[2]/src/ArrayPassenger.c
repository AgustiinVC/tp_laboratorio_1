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

static int flagAltaForzada = 0;

static int ePas_AltaForzada (void)
{
	return flagAltaForzada++;
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
			list[indiceLibre].statusFlight =  ACTIVO;
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
				if(utn_getString(auxiliar.flycode, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n\n", CODIGO, 3) == 0)
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
		if( utn_getIntAlone (&idIngresado ,"\nIngrese un ID: ", "Error. Ingrese un ID correcto.\n") == 0)
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
		if (utn_getNombre(auxList->name, "Ingrese el nombre del pasajero: ", "Ingrese un nombre valido\n", TEXT_LEN, 3) == 0 &&
			utn_getNombre(auxList->lastName, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n ", TEXT_LEN, 3) == 0 &&
			utn_getFloatPositivo(&auxList->price, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n ") == 0 &&
			utn_getIntRange(&auxList->typePassenger, "Ingrese el tipo del vuelo: "
					"\n\t 1 = Primera Clase\n\t 2 = Business\n\t 3 - Premium Economy\n\t 4 - Economy\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,4) == 0 &&
			utn_getString(auxList->flycode, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n", CODIGO, 3) == 0)
		{
			auxList->id = ePas_ObtenerID();
			auxList->statusFlight = ACTIVO;
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

int pas_Informar (Passenger* list, int len)
{
	int rtn = -1;
	int opcion;
	char respuesta;
	int flagAlta = 0;

	if (pas_isStrucEmpty(list, len) == 0)
	{
		flagAlta = 1;
	}

	if (list != NULL && len > 0 && flagAlta == 1)
	{
		do
		{
			fflush(stdin);
			utn_getIntRange (&opcion ,"\nIngrese la opcion que desea informar:\n "
											"1 - Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.\n "
											"2 - Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio.\n "
											"3 - Listado de los pasajeros por Codigo de vuelo y estados de vuelo ACTIVO\n"
											"Ingrese su opcion: ",
											"Error. Ingrese una opcion correcta\n\n", 1, 3);

			switch (opcion)
			{
				case 1:
					utn_getIntRange (&opcion ,"\nIngrese la opcion que desea informar:\n "
							"1 - Ascendente.\n "
							"2 - Descendente.\n "
							"Ingrese su opcion: ",
							"Error. Ingrese una opcion correcta\n\n", 1, 2);
					if (sortPassengers(list,  len, opcion) == 0)
					{
						printPassenger(list, len);
					}
					break;

				case 2:
					if (pas_CalculosPasaje (list, len) == 0)
					{
						rtn = 0;
					}
					break;

				case 3:
					utn_getIntRange (&opcion ,"\nIngrese la opcion que desea informar:\n "
												"1 - Ascendente.\n "
												"2 - Descendente.\n "
												"Ingrese su opcion: ",
												"Error. Ingrese una opcion correcta\n\n", 1, 2);
					if (sortPassengersByCode(list,  len, opcion) == 0)
					{
						printActivePassenger(list, len);
					}
					break;
			}
			respuesta = validacionDosCaracteres ("¿Desea informar otra opcion? (S/N)", 'S', 'N');
		}
		while (respuesta);
	}
	return rtn;
}


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

		printf ("El total en pasajes es de: $%.4f.\n"
						"El promedio de pasajes es de: $%.4f.\n"
						"La cantidad de pasajes que superan el promedio es: %d\n", totalPrecio, promedioPasaje, cantidadMayorQuePromedio);

	}
	return rtn;
}

int printPassenger(Passenger* list, int length)
{
	int rtn = -1;
	int flagPrimerPasajero = 0;

	if (list != NULL && length > 0)
	{
		for (int i = 0; i < length; i++)
		{
			if (list[i].isEmpty == OCUPADO)
			{
				if (flagPrimerPasajero == 0)
				{
					flagPrimerPasajero = 1;
					puts("\n\t\t\t\t> LISTADO PASAJEROS");
					printf("%-6s %-52s %-52s %-9s %-13s %-s %-s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO", "ESTADO VUELO");
				}

				pas_printOne (list, i);
				rtn = 0;
			}
		}
	}

	return rtn;
}

int printActivePassenger(Passenger* list, int length)
{
	int rtn = -1;
	int flagPrimerPasajero = 0;

	if (list != NULL && length > 0)
	{
		for (int i = 0; i < length; i++)
		{
			if (list[i].isEmpty == OCUPADO && list[i].statusFlight == ACTIVO)
			{
				if (flagPrimerPasajero == 0)
				{
					flagPrimerPasajero = 1;
					puts("\n\t\t\t\t>\t\t\t\t -----LISTADO PASAJEROS-----");
					printf("%-6s %-52s %-52s %-15s %-13s %-20s %-30s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO", "ESTADO VUELO");
				}

				pas_printOne (list, i);
				rtn = 0;
			}
		}
	}

	return rtn;
}

void pas_printOne (Passenger* list, int index)
{
	char typePassenger[TEXT_LEN];
	char flightStatus[TEXT_LEN];
	switch (list[index].typePassenger)
	{
		case 1:
			strncpy(typePassenger, "Primera Clase", TEXT_LEN);
			break;
		case 2:
			strncpy(typePassenger, "Business", TEXT_LEN);
			break;
		case 3:
			strncpy(typePassenger, "Premium Economy", TEXT_LEN);
			break;
		case 4:
			strncpy(typePassenger, "Economy", TEXT_LEN);
			break;

	}
	switch (list[index].statusFlight)
		{
			case 1:
				strncpy(flightStatus, "Activo", TEXT_LEN);
				break;
			case 2:
				strncpy(flightStatus, "Demorado", TEXT_LEN);
				break;
			case 3:
				strncpy(flightStatus, "Cancelado", TEXT_LEN);
				break;
		}

	printf ("%-6d %-52s %-52s %-15.2f %-13s %-20s %-10s\n",
			list[index].id, list[index].name, list[index].lastName, list[index].price, list[index].flycode, typePassenger, flightStatus);
}

int sortPassengers(Passenger* list, int len, int order) //Apellido y tipo de pasajero
{
	int rtn = -1;
	int i;
	int j;
	Passenger auxPasajeros;

	if (list != NULL && len > 0)
	{
		switch (order) {
		case 1: //ascendente (A a Z - Eco a Primera)
			for (i = 1; i < len; i++)
			{
				auxPasajeros = list[i];
				j = i - 1;
				while ( (j >= 0) &&
						( compararCadenas (list[j].lastName, auxPasajeros.lastName) == 1  ||
						 (compararCadenas (auxPasajeros.lastName, list[j].lastName) == 3 && auxPasajeros.typePassenger > list[j].typePassenger) ) )
				{
					list[j + 1] = list[j];
					j--;
				}
				list[j + 1] = auxPasajeros;
			}

			rtn = 0;
			break;
		case 2:
			for (i = 1; i < len; i++)
			{
				auxPasajeros = list[i];
				j = i - 1;
				while ( (j >= 0) &&
						( compararCadenas (list[j].lastName, auxPasajeros.lastName) == 2  ||
						 (compararCadenas (auxPasajeros.lastName, list[j].lastName) == 3 && auxPasajeros.typePassenger < list[j].typePassenger) ) )
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
				while ( (j >= 0) && compararCadenas (list[j].flycode, auxPasajeros.flycode) == 1)
				{
					list[j + 1] = list[j];
					j--;
				}
				list[j + 1] = auxPasajeros;
			}
			rtn = 0;
			break;
		case 2:
			for (i = 1; i < len; i++)
			{
				auxPasajeros = list[i];
				j = i - 1;
				while ( (j >= 0) && compararCadenas (list[j].flycode, auxPasajeros.flycode) == 2)
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

int compararCadenas (char* cadenaUno, char* cadenaDos)
{
	int rtn = -1;
	int comparacion;
	char auxCadenaUno [TEXT_LEN];
	char auxCadenaDos [TEXT_LEN];

	strcpy (auxCadenaUno,cadenaUno);
	strcpy (auxCadenaDos,cadenaDos);
	if (cadenaUno != NULL && cadenaDos != NULL)
	{
		toLowerCadena (auxCadenaUno);
		toLowerCadena (auxCadenaDos);
		comparacion = strcmp (auxCadenaUno,auxCadenaDos);

		if (comparacion > 0)
		{
			rtn = 1;
		}
		else if (comparacion < 0)
		{
			rtn = 2;
		}
		else
		{
			rtn = 3;
		}
	}
	return rtn;
}

void toLowerCadena (char* cadena)
{
	for(int i = 0; cadena[i]; i++)
	{
		cadena[i] = tolower(cadena[i]);
	}
}

int altaForzadaPasajeros (Passenger* list, int len)
{
	int rtn = -1;
	int indiceLibre;
	int altaRealizada;

	altaRealizada = ePas_AltaForzada();
	printf ("%d", altaRealizada);

	if (list != NULL && len > 0 && altaRealizada == 0)
	{
		indiceLibre = pas_indexEmpty (list, len);
		if (indiceLibre != -1)
		{

			list[indiceLibre] = pas_UnPasajeroForzado (indiceLibre, "Agustin", "Vallario", 120000, "ABC123", 1);
			list[indiceLibre+1] = pas_UnPasajeroForzado (indiceLibre, "Rodrigo", "Palacios", 100000, "CFR234", 3);
			list[indiceLibre+2] = pas_UnPasajeroForzado (indiceLibre, "Jimena", "Mendoza", 90054, "GHR736", 1);
			list[indiceLibre+3] = pas_UnPasajeroForzado (indiceLibre, "Pablo", "Vallario", 250000, "LOL640", 2);
			list[indiceLibre+4] = pas_UnPasajeroForzado (indiceLibre, "Rosario", "Fernandez", 58642, "ABC123", 4);

			for (int i = indiceLibre; i < indiceLibre + 5; i++)
			{

				list[i].id = ePas_ObtenerID();
				list [i].statusFlight = ACTIVO;
				list [i].isEmpty = OCUPADO;
			}
			rtn = 0;
		}
	}

	return rtn;
}

Passenger pas_UnPasajeroForzado (int indiceLibre, char* name, char* lastname, float price, char* codeFlight,int typePassenger)
{
	Passenger auxLista;
	strncpy(auxLista.name, name, sizeof(auxLista.name));
	strncpy(auxLista.lastName, lastname, sizeof(auxLista.lastName));
	auxLista.price = price;
	strncpy(auxLista.flycode, codeFlight, sizeof(auxLista.flycode));
	auxLista.typePassenger = typePassenger;

	return auxLista;
}


void menu (void)
{
	puts ("1. Alta de pasajero.");
	puts ("2. Modificar pasajero ID.");
	puts ("3. Baja de pasajero");
	puts ("4. Informar.");
	puts ("5. Alta forzada");
	puts ("6. Salir.");
}
