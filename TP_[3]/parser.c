#include "parser.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int r;
	int rtn = -1;
	int auxId;
	int ultimoId = 0;
	int cantidadPasajeros = 0;
	char bufferId[10];
	char bufferNombre[NOMBRE_LEN];
	char bufferApellido[APELLIDO_LEN];
	char bufferPrecio[256];
	char bufferTipoPasajero [15];
	char bufferCodigoVuelo [CODIGO_LEN];
	char bufferEstadoVuelo [11];
	Passenger* PauxPassenger = NULL;

	if (pFile != NULL && pArrayListPassenger != NULL)
	{
		fscanf (pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero, bufferEstadoVuelo);

		do
		{
			r = fscanf (pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero, bufferEstadoVuelo);
			if (r == 7)
			{
				PauxPassenger = Passenger_newParametros(bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero,bufferEstadoVuelo);
			}

			if (PauxPassenger != NULL && ll_add(pArrayListPassenger, PauxPassenger) == 0 )
			{
				Passenger_getId(PauxPassenger, &auxId);
				if (cantidadPasajeros == 0 || (auxId > ultimoId && ll_len(pArrayListPassenger) < MAX_PASAJEROS))
				{
					Passenger_getId(PauxPassenger, &ultimoId);
				}
				cantidadPasajeros++;
			}
		}
		while (feof(pFile) == 0);
		rtn = 0;
		printf ("Se ingresaron: %d pasajeros y su ultimo id es: %d\n", cantidadPasajeros, ultimoId);
	}
	return rtn;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int rtn = -1;
	int ultimoId;
	int auxId;
	int cantidadPasajeros = 0;

	Passenger* pAuxPassenger;


	if (pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			pAuxPassenger = Passenger_new();
			if (fread(pAuxPassenger, sizeof(Passenger),1,pFile) == 1)
			{

				if (pAuxPassenger != NULL && ll_add(pArrayListPassenger, pAuxPassenger) == 0 && ll_len(pArrayListPassenger) < MAX_PASAJEROS)
				{
					Passenger_getId(pAuxPassenger, &auxId);
					if (cantidadPasajeros == 0 || auxId > ultimoId)
					{
						Passenger_getId(pAuxPassenger, &ultimoId);
					}
					cantidadPasajeros++;
				}
			}
		}
		while (feof(pFile) == 0);
		rtn = 0;
		printf ("Se ingresaron: %d pasajeros.\n", cantidadPasajeros);
	}
	return rtn;
}

/// @fn int parser_PassengerLastIdFromText(FILE*)
/// @brief parseamos el archivo de pasajeros donde tomamos solo el ultimo id para poder tener como referencia
/// parsea el ultimo id que obtenemos del archivo csv
/// @param pFile puntero al archivo donde tenemos los pasajeros y vamos a recorrer viendo el id mas alto
/// @return un 0 si esta Ok y un -1 si hay error
int parser_PassengerLastIdFromText(FILE* pFile)
{
	int r;
	int rtn = -1;
	int ultimoId;
	int auxId;
	int cantidadPasajeros = 0;
	char bufferId[256];
	char bufferNombre[NOMBRE_LEN];
	char bufferApellido[APELLIDO_LEN];
	char bufferPrecio[256];
	char bufferTipoPasajero [15];
	char bufferCodigoVuelo [CODIGO_LEN];
	char bufferEstadoVuelo [11];
	Passenger* PauxPassenger = NULL;

	if (pFile != NULL)
	{
		fscanf (pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero, bufferEstadoVuelo);

		do
		{
			r = fscanf (pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero, bufferEstadoVuelo);
			if (r == 7)
			{
				PauxPassenger = Passenger_newParametros(bufferId, bufferNombre, bufferApellido, bufferPrecio, bufferCodigoVuelo, bufferTipoPasajero,bufferEstadoVuelo);
			}

			if (PauxPassenger != NULL)
			{
				Passenger_getId(PauxPassenger, &auxId);
				if (cantidadPasajeros == 0 || (auxId > ultimoId) )
				{
					Passenger_getId(PauxPassenger, &ultimoId);
				}
				cantidadPasajeros++;
			}
		}
		while (feof(pFile) == 0);
		ultimoId += 1;
		Passenger_setUltimoId (ultimoId);
		rtn = 0;
	}
	return rtn;
}

/// @fn int parser_LastIdFromText(FILE*)
/// @brief
/// parsea el entero del archivo donde guardamos el ultimo id
/// @param pFile puntero al archivo donde tenemos guardado el ultimo id
/// @return un 0 si esta Ok y un -1 si hay error
int parser_LastIdFromText(FILE* pFile)
{
	int rtn = -1;
	int ultimoId;

	if (pFile != NULL)
	{
		do
		{
			if (fscanf (pFile, "%d", &ultimoId) == 1)
			{
				ultimoId += 1;
				Passenger_setUltimoId (ultimoId);
			}
		}
		while (feof(pFile) == 0);
		rtn = 0;
	}
	return rtn;
}
