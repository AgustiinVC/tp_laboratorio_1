#include "Controller.h"

static const char PASAJERO_TIPOS [3][15] = {"FirstClass", "ExecutiveClass", "EconomyClass"};
static const char ESTADO_VUELO [4][11] = {"Aterrizado", "En Horario", "En Vuelo", "Demorado"};

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	FILE* pArchivoPasajero;

	if (path != NULL && pArrayListPassenger != NULL)
	{
		pArchivoPasajero = fopen(path, "r");
		if (pArchivoPasajero != NULL)
		{
			if (parser_PassengerFromText(pArchivoPasajero, pArrayListPassenger) == 0)
			{
				rtn = 0;
			}
		}

	}
	fclose (pArchivoPasajero);
    return rtn;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	FILE* pArchivoPasajero;

	if (path != NULL && pArrayListPassenger != NULL)
	{
		pArchivoPasajero = fopen(path, "rb");
		if (pArchivoPasajero != NULL)
		{
			if (parser_PassengerFromBinary(pArchivoPasajero, pArrayListPassenger) == 0)
			{
				rtn = 0;
			}
		}
		else
		{
			rtn = 1;
		}
	}
	fclose (pArchivoPasajero);
    return rtn;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int auxId;
	int auxTipoPasajero;
	int auxEstadoVuelo;
	int estadoVueloExistente;
	float precio;
	char auxNombre[NOMBRE_LEN];
	char auxApellido [APELLIDO_LEN];
	char auxCodigoVuelo[CODIGO_LEN];

	Passenger* pPasajero = Passenger_new();

	if (pArrayListPassenger != NULL)
	{
		if (utn_getNombre(auxNombre, "Ingrese su nombre: ", "Ingrese un nombre valido.", NOMBRE_LEN, 3) == 0 &&
			utn_getNombre(auxApellido, "Ingrese su apellido: ", "Ingrese un apellido valido.", APELLIDO_LEN, 3) == 0 &&
			utn_getFloatPositivo(&precio, "Ingrese el precio: ", "Error ingrese algo valido\n") == 0 &&
			utn_getCodigo(auxCodigoVuelo, "Ingrese el codigo de vuelo: ", "Ingrese un codigo valido", 4, CODIGO_LEN, 3) == 0 &&
			utn_getIntRange(&auxTipoPasajero, "Ingrese el tipo de pasajero: "
					"\n\t 1 = First Class\n\t 2 = Executive Class\n\t 3 - Economy Class\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1, 3) == 0 &&
			utn_getIntRange(&auxEstadoVuelo, "Ingrese el estado del vuelo: "
								"\n\t 1 = Aterrizado\n\t 2 = En Horario\n\t 3 - En Vuelo\n\t 4 - Demorado\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1, 4) == 0)
		{
			auxId = Passenger_generarIdUnico();
			Passenger_setId(pPasajero, auxId);
			Passenger_setNombre(pPasajero, auxNombre);
			Passenger_setApellido(pPasajero, auxApellido);
			Passenger_setPrecio(pPasajero, precio);
			toUpperCadena(auxCodigoVuelo);
			Passenger_setCodigoVuelo(pPasajero, auxCodigoVuelo);
			Passenger_setTipoPasajero(pPasajero, auxTipoPasajero);

			estadoVueloExistente = controller_checkForFLightCode (pArrayListPassenger, auxCodigoVuelo);
			if (estadoVueloExistente != -1)
			{
				printf ("Codigo de Vuelo existente. Estado del vuelo con CODIGO %s: %s\n", auxCodigoVuelo ,ESTADO_VUELO[estadoVueloExistente - 1]);
				printf ("Nuevo ESTADO DE VUELO con CODIGO %s: %s\n", auxCodigoVuelo, ESTADO_VUELO[auxEstadoVuelo-1]);
				if (validacionDosCaracteres("¿Desea actualizar el estado del vuelo? (S/N)", 'S', 'N') == 0)
				{
					auxEstadoVuelo = estadoVueloExistente;
				}
			}
			Passenger_setEstadoVuelo(pPasajero, auxEstadoVuelo);
			if (pPasajero != NULL && ll_add(pArrayListPassenger, pPasajero) == 0)
			{
				Passenger_getId(pPasajero, &auxId);
				controller_changeFlightStatus (pArrayListPassenger, auxId);
				rtn = 0;
			}
		}

	}
    return rtn;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int idBuscado;
	int indice;
	int opcion;

	int auxId;
	int vueloEncontrado;
	int auxEstadoVuelo;

	int respuesta;

	Passenger* pAuxPasajero;

	pAuxPasajero = Passenger_new();

	if (pArrayListPassenger != NULL && ll_len(pArrayListPassenger) > 0)
	{
		utn_getIntPositivo(&idBuscado, "Ingrese el ID a buscar: ", "Ingrese un numero valido.");

		indice = controller_getIndexById(pArrayListPassenger, idBuscado);

		if (indice != -1)
		{
			do
			{
				pAuxPasajero = ll_get(pArrayListPassenger, indice);
				puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS\n"
											"--------------------------------------------------------------------------------------"
											"-------------------------------------------------------------------------------");
									printf("%-6s %-50s %-50s %-14s %-11s %-15s %-11s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO", "ESTADO VUELO");
				Passenger_print(pAuxPasajero);

				fflush(stdin);

				utn_getIntRange (&opcion ,"\nIngrese la opcion a modificar:\n "
											"1 - Nombre\n "
											"2 - Apellido\n "
											"3 - Precio\n "
											"4 - Codigo de Vuelo\n "
											"5 - Tipo de Pasajero\n "
											"6 - Estado del Vuelo\n "
											"7 - Salir\nOpcion: ",
											"Error. Ingrese una opcion correcta\n\n", 1, 7);

				switch (opcion)
				{
					case 1:
						if( utn_getNombre(pAuxPasajero->nombre, "Ingrese el nombre del pasajero: ", "Ingrese un nombre valido\n\n", NOMBRE_LEN, 3) == 0)
						{
							puts ("Carga de nombre correcta\n");
						}
						else
						{
							puts("No se pudo cargar el nombre");
						}
						break;

					case 2:
						if(utn_getNombre(pAuxPasajero->apellido, "Ingrese el apellido del pasajero: ", "Ingrese un apellido valido\n\n", APELLIDO_LEN, 3) == 0)
						{
							puts ("Carga de apellido correcta\n");
						}
						else
						{
							puts("No se pudo cargar el apellido");
						}
						break;

					case 3:
						if(utn_getFloatPositivo(&pAuxPasajero->precio, "Ingrese el precio del vuelo: ", "Ingrese un precio valido\n\n") == 0)
						{
							puts ("Carga de precio correcta\n");
						}
						else
						{
							puts("No se pudo cargar el precio");
						}
						break;
					case 4:

						if(utn_getString(pAuxPasajero->codigoVuelo, "Ingrese el codigo del vuelo: ", "Ingrese un codigo valido\n\n", CODIGO_LEN, 3) == 0)
						{
							vueloEncontrado = controller_checkForFLightCode(pArrayListPassenger, pAuxPasajero->codigoVuelo);
							if (vueloEncontrado != -1)
							{
								Passenger_setEstadoVuelo(pAuxPasajero, vueloEncontrado);
							}
							puts ("Carga de codigo del vuelo correcta\n");
						}
						else
						{
							puts("No se pudo cargar el codigo del vuelo");
						}
						break;

					case 5:
						if(utn_getIntRange(&pAuxPasajero->tipoPasajero, "Ingrese el tipo de pasajero: "
								"\n\t 1 = First Class\n\t 2 = Executive Class\n\t 3 - Economy Class\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1,3) == 0)
						{
							puts ("Carga de tipo del vuelo correcta\n");
						}
						else
						{
							puts("No se pudo cargar el tipo del vuelo");
						}
						break;
					case 6:
						if(utn_getIntRange(&auxEstadoVuelo, "Ingrese el tipo de pasajero: "
								"\n\t 1 = Aterrizado\n\t 2 = En Horario\n\t 3 - En Vuelo\n\t 4 - Demorado\nIngrese su opcion: ", "Ingrese un tipo de vuelo valido\n", 1, 4) == 0)
						{
							Passenger_setEstadoVuelo(pAuxPasajero, auxEstadoVuelo);
							Passenger_getId(pAuxPasajero, &auxId);
							controller_changeFlightStatus(pArrayListPassenger, auxId);
							puts ("Carga de tipo del vuelo correcta\n");
						}
						else
						{
							puts("No se pudo cargar el tipo del vuelo");
						}
						break;
					case 7:
						respuesta = 0;
						break;
				}
				if (opcion != 7)
				{
					respuesta = validacionDosCaracteres ("¿Desea modificar otro campo? (S/N)", 'S', 'N');
				}
			}
			while (respuesta);
			if (ll_set(pArrayListPassenger, indice, pAuxPasajero) == 0)
			{
				rtn = 0;
			}
		}
	}
    return rtn;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int auxId;
	int busquedaId;
	Passenger* pAuxPasajero;

	if (pArrayListPassenger != NULL && ll_len(pArrayListPassenger) > 0)
	{
		if (utn_getIntPositivo(&auxId,"Ingrese el ID del pasajero: ", "Error, ingrese un ID valido") == 0)
		{
			busquedaId = controller_getIndexById(pArrayListPassenger, auxId);
			if (busquedaId != -1)
			{
				pAuxPasajero = ll_get(pArrayListPassenger, busquedaId);
				puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS\n"
															"--------------------------------------------------------------------------------------"
															"-------------------------------------------------------------------------------");
													printf("%-6s %-50s %-50s %-14s %-11s %-15s %-11s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO", "ESTADO VUELO");
				Passenger_print(pAuxPasajero);
				if (validacionDosCaracteres ("¿Seguro quiere eliminar el Pasajero? (S/N): ", 'S', 'N') == 1)
				{
					ll_remove(pArrayListPassenger, busquedaId);
					rtn = 0;
				}
			}
			else
			{
				puts ("Pasajero no encontrado.");
			}
		}
	}
    return rtn;
}

/** \brief Listar pasajeros
 *	imprimir la lista de pasajeros
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int i;
	int lenPasajeros;
	Passenger* pAuxPasajero;

	if (pArrayListPassenger != NULL)
	{
		lenPasajeros = ll_len(pArrayListPassenger);
		if (lenPasajeros > 0 && lenPasajeros < MAX_PASAJEROS)
		{
			puts("\n\t\t\t\t\t\t\t\t> LISTADO PASAJEROS\n"
					"--------------------------------------------------------------------------------------"
					"-------------------------------------------------------------------------------");
			printf("%-6s %-50s %-50s %-14s %-11s %-15s %-11s\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO VUELO", "TIPO PASAJERO", "ESTADO VUELO");
			for (i = 0; i < lenPasajeros; i++)
			{
				pAuxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
				if (pAuxPasajero != NULL)
				{
					if (Passenger_print(pAuxPasajero) == 0)
					{
						rtn = 0;
					}
				}
			}
		}
	}
    return rtn;
}

/** \brief Ordenar pasajeros
 *podemos ordenar por cualquier parametro ya sea ascendente o descendente
 * \param pArrayListPassenger LinkedList* lista con los pasajeros a ordenar
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int opcionTipoOrden;
	int opcionOrden;

	if (pArrayListPassenger != NULL && ll_len(pArrayListPassenger) > 0)
	{
		utn_getIntRange (&opcionTipoOrden ,	"\nIngrese con que parametro ordenar la lista:\n "
											"1 - ID\n "
											"2 - Nombre\n "
											"3 - Apellido\n "
											"4 - Precio\n "
											"5 - Codigo de Vuelo\n "
											"6 - Tipo de Pasajero\n "
											"7 - Estado de Vuelo\nOpcion: ",
											"Error. Ingrese una opcion correcta\n\n", 1, 7);

		utn_getIntRange (&opcionOrden ,	"\nIngrese con que orden desea ordenarlo:\n"
														" 0 - Descendente\n"
														" 1 - Ascendente\nOpcion: ",
														"Error. Ingrese una opcion correcta\n\n", 0, 1);
		puts ("Aguarde unos segundos esto puede demorar...");
		switch (opcionTipoOrden)
		{
			case 1:
				if (ll_sort(pArrayListPassenger, passenger_orderByID, opcionOrden) == 0)
				{
					puts ("Orden por ID realizado");
				}
				break;
			case 2:
				if (ll_sort(pArrayListPassenger, passenger_orderByName, opcionOrden) == 0)
				{
					puts ("Orden por Nombre realizado");
				}
				break;
			case 3:
				if (ll_sort(pArrayListPassenger, passenger_orderByLastName, opcionOrden) == 0)
				{
					puts ("Orden por Apellido realizado");
				}
				break;
			case 4:
				if (ll_sort(pArrayListPassenger, passenger_orderByPrice, opcionOrden) == 0)
				{
					puts ("Orden por Precio realizado");
				}
				break;
			case 5:
				if (ll_sort(pArrayListPassenger, passenger_orderByFlightCode, opcionOrden) == 0)
				{
					puts ("Orden por Codigo de Vuelo realizado");
				}
				break;
			case 6:
				if (ll_sort(pArrayListPassenger, passenger_orderByTypePassenger, opcionOrden) == 0)
				{
					puts ("Orden por Tipo de Pasajero realizado");
				}
				break;
			case 7:
				if (ll_sort(pArrayListPassenger, passenger_orderByStatusFlight, opcionOrden) == 0)
				{
					puts ("Orden por Estado de Vuelo realizado");
				}
				break;
		}
		rtn = 0;
	}
    return rtn;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int lenPasajeros;
	int i;
	Passenger* pAuxPasajero;
	FILE* pArchivoPasajero = NULL;

	int auxId;
	char auxIdStr[8];
	char auxNombre [NOMBRE_LEN];
	char auxApellido [APELLIDO_LEN];
	float auxPrecio;
	char auxPrecioStr[20];
	char auxCodigoVuelo[CODIGO_LEN];
	int auxTipoPasajero;
	int auxEstadoVuelo;

	if (pArrayListPassenger != NULL)
	{
		lenPasajeros = ll_len(pArrayListPassenger);
		pArchivoPasajero = fopen (path, "w");
		pAuxPasajero = Passenger_new();

		if (pArchivoPasajero != NULL && lenPasajeros < MAX_PASAJEROS && lenPasajeros > 0)
		{
			fprintf (pArchivoPasajero, "%s,%s,%s,%s,%s,%s,%s\n", "id", "name", "lastname", "price", "flycode", "typePassenger","statusFlight");
			for (i = 0; i < lenPasajeros; i++)
			{
				pAuxPasajero = ll_get(pArrayListPassenger, i);
				if (pAuxPasajero != NULL)
				{
					Passenger_getId(pAuxPasajero, &auxId);
					sprintf(auxIdStr, "%d",auxId);
					Passenger_getNombre(pAuxPasajero, auxNombre);
					Passenger_getApellido(pAuxPasajero, auxApellido);
					Passenger_getPrecio(pAuxPasajero, &auxPrecio);
					sprintf(auxPrecioStr, "%f",auxPrecio);
					Passenger_getCodigoVuelo(pAuxPasajero, auxCodigoVuelo);
					Passenger_getTipoPasajero(pAuxPasajero, &auxTipoPasajero);
					Passenger_getEstadoVuelo(pAuxPasajero, &auxEstadoVuelo);

					fprintf(pArchivoPasajero, "%s,%s,%s,%s,%s,%s,%s\n", auxIdStr, auxNombre, auxApellido, auxPrecioStr, auxCodigoVuelo, PASAJERO_TIPOS[auxTipoPasajero-1], ESTADO_VUELO[auxEstadoVuelo-1] );
					rtn = 0;
				}
			}
			fclose (pArchivoPasajero);
		}
	}
    return rtn;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char* el nombre del archivo con su extension
 * \param pArrayListPassenger LinkedList*
 * \return int un 0 si esta OK y un -1 si hay error
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int lenPasajeros;
	int i;
	Passenger* pAuxPasajero;
	FILE* pArchivoPasajero = NULL;

	pAuxPasajero = Passenger_new();

	if (pArrayListPassenger != NULL)
	{
		lenPasajeros = ll_len(pArrayListPassenger);
		pArchivoPasajero = fopen (path, "wb");

		if (pArchivoPasajero != NULL && lenPasajeros <= MAX_PASAJEROS && lenPasajeros > 0)
		{
			for (i = 0; i < lenPasajeros; i++)
			{
				pAuxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
				if (pAuxPasajero != NULL)
				{
					fwrite(pAuxPasajero, sizeof(Passenger), 1, pArchivoPasajero);
					rtn = 0;
				}
			}
			fclose (pArchivoPasajero);
		}
	}
    return rtn;
}

/// @fn int controller_getIndexById(LinkedList*, int)
/// @brief obtenemos el indice del id que tomamos
///
/// @param pArrayListPassenger
/// @param id a tener que buscar el indice
/// @return el indice del id a buscar o un -1 si hay error
int controller_getIndexById(LinkedList* pArrayListPassenger, int id)
{
	int rtn = -1;
	int i;
	int auxId;
	int lenLista;
	Passenger* auxPassenger;

	if (pArrayListPassenger != NULL && id > 0)
	{
		lenLista = ll_len(pArrayListPassenger);

		if (lenLista > 0)
		{
			for (i = 0; i < lenLista; i++)
			{
				auxPassenger = ll_get(pArrayListPassenger, i);
				Passenger_getId(auxPassenger, &auxId);
				if (auxPassenger != NULL && auxId == id)
				{
					rtn = i;
					break;
				}
			}
		}
	}
    return rtn;
}

/// @fn int controller_changeFlightStatus(LinkedList*, int)
/// @brief cambiamos el estado de todos los vuelos con el vuelo a comparar
///
/// @param pArrayListPassenger
/// @param id el id del pasajero que vamos a usar como referencia
/// @return un 0 si esta OK y un -1 si hay error
int controller_changeFlightStatus (LinkedList* pArrayListPassenger, int id)
{
	int rtn = -1;
	int i;
	int lenLista;
	int indice;
	int resultado;
	Passenger* auxPassengerToCompare;
	char auxCodigoVuelo [CODIGO_LEN];
	char auxCodigoVueloComparar [CODIGO_LEN];
	int auxEstadoVuelo;

	Passenger* auxPassenger;

	if (pArrayListPassenger != NULL && id > 0)
	{
		lenLista = ll_len(pArrayListPassenger);
		if (lenLista > 0)
		{
			rtn = 0;
			indice = controller_getIndexById(pArrayListPassenger, id);
			auxPassengerToCompare = ll_get(pArrayListPassenger, indice);

			for (i = 0; i < lenLista; i++)
			{
				auxPassenger = ll_get(pArrayListPassenger, i);
				Passenger_getCodigoVuelo(auxPassenger, auxCodigoVuelo);
				Passenger_getCodigoVuelo(auxPassengerToCompare, auxCodigoVueloComparar);
				resultado = strcmp(auxCodigoVuelo, auxCodigoVueloComparar);
				if (resultado == 0 && i != indice)
				{
					Passenger_getEstadoVuelo(auxPassengerToCompare, &auxEstadoVuelo);
					Passenger_setEstadoVuelo(auxPassenger, auxEstadoVuelo);
				}
			}
		}
	}
    return rtn;
}

/// @fn int controller_checkForFLightCode(LinkedList*, char*)
/// @brief
/// verificamos si se ingreso el codigo de vuelo anteriormente revisando la lista de pasajeros. en caso de que si devolvermos en q estado esta el vuelo
/// @param pArrayListPassenger lista de pasajeros
/// @param codigoVuelo codigo de vuelo a comparar
/// @return un 0 si esta OK y un -1 si hay error
int controller_checkForFLightCode (LinkedList* pArrayListPassenger, char* codigoVuelo)
{
	int rtn = -1;
	int i;
	int lenLista;
	int resultado;
	char auxCodigoVuelo [CODIGO_LEN];

	Passenger* auxPassenger;

	if (pArrayListPassenger != NULL && codigoVuelo != NULL)
	{
		lenLista = ll_len(pArrayListPassenger);

		if (lenLista > 0)
		{
			for (i = 0; i < lenLista; i++)
			{
				auxPassenger = ll_get(pArrayListPassenger, i);
				Passenger_getCodigoVuelo(auxPassenger, auxCodigoVuelo);
				resultado = strcmp(auxCodigoVuelo, codigoVuelo);
				if (resultado == 0)
				{
					Passenger_getEstadoVuelo(auxPassenger, &rtn);
					break;
				}
			}
		}
	}
    return rtn;
}

/// @fn int controller_getLastId(void)
/// @brief tomamos el valor entero del archivo donde tenemos guardado el ultimo id
///
/// @return un 0 si esta OK y un -1 si hay error
int controller_getLastId(void)
{
	int rtn = -1;
	FILE* pArchivoPasajero;

	pArchivoPasajero = fopen("unicoId.csv", "r");

	if (parser_LastIdFromText(pArchivoPasajero) == 0)
	{
		rtn = 0;
	}
	else
	{
		fclose (pArchivoPasajero);
		pArchivoPasajero = fopen("data.csv", "r");

		if (parser_PassengerLastIdFromText(pArchivoPasajero) == 0)
		{
			rtn = 0;
		}
		else
		{
			Passenger_setUltimoId (1);
		}
	}
	fclose (pArchivoPasajero);
    return rtn;
}

/// @fn int controller_setLastId()
/// @brief seteamos el ultimo id en un archivo aparte para tenerlo para si damos de alta sin cargar primero los pasajeros
///
/// @return un 0 si esta OK y un -1 si hay error
int controller_setLastId()
{
	int rtn = -1;
	int ultimoId = 0;
	FILE* pArchivoPasajero = NULL;

	pArchivoPasajero = fopen ("unicoId.csv", "w");

	if (pArchivoPasajero != NULL)
	{
		Passenger_getUltimoId(&ultimoId);
		fprintf(pArchivoPasajero, "%d", ultimoId-1);
		rtn = 0;
	}
	fclose (pArchivoPasajero);
    return rtn;
}

