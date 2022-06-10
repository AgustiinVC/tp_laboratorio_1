/*
 * validaciones.c
 *
 *  Created on: 5 abr. 2022
 *      Author: Agostin
 */
#include "validaciones.h"

//Verifica si una cadena es un numero
static int myGets ( char * cadena, int l);


/// @fn int validacionDosCaracteres(char*, char, char)
/// @brief
/// compara el caracter que se ingrese con dos caracteres que seteamos
/// @param mensaje que se desea mostrar al usuario con las opciones.
/// @param caracterUno caracter uno a comparar
/// @param caracterDos caracter dos a comparar
/// @return devuelve un 1 si es el primer caracter y un 0 si es el segundo caracter
int validacionDosCaracteres (char* mensaje, char caracterUno, char caracterDos)
{
	char charIngresado;
	int retorno = -1;

	if (mensaje != NULL)
	{
		retorno = 0;
		printf(mensaje);
		charIngresado = toupper(getchar());
		while (charIngresado != caracterUno && charIngresado != caracterDos)
		{
			printf ("Ingrese una opcion valida (%c/%c): ", caracterUno, caracterDos);
			fflush (stdin);
			charIngresado = toupper(getchar());
		}
		if (charIngresado == caracterUno)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/// @fn int validacionCaracter(char*, char)
/// @brief
/// validar un solo caracter para continuar
/// @param mensaje que se muestra al usuario
/// @param caracter que queremos que presione el usuario
/// @return devuelve un 0 si esta ok y un -1 si hay algun error
int validacionCaracter (char *mensaje, char caracter)
{
	char charIngresado;
	int retorno = -1;

	if (mensaje != NULL)
	{
		retorno = 0;
		printf(mensaje);
		fflush (stdin);
		charIngresado = toupper(getchar());
		while (charIngresado != caracter)
		{
			printf ("Caracter incorrecto. Ingrese %c para continuar: ", caracter);
			fflush (stdin);
			charIngresado = toupper(getchar());
		}
	}

	return retorno;
}

/// @fn int compararCadenas(char*, char*, int)
/// @brief
/// comparamos dos cadenas para ver cual es mayor independiente de si son mayusculas o minusculas
/// @param cadenaUno a comparar
/// @param cadenaDos a comparar
/// @param len tamaño maximo de las cadenas
/// @return devuelve un 1 si la cadenaUno es mayor, un 2 si es mayor la cadenaDos y un 0 si ambas son iguales.
int compararCadenas (char* cadenaUno, char* cadenaDos, int len)
{
	int rtn = -1;
	int comparacion;
	char auxCadenaUno [len];
	char auxCadenaDos [len];

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

/// @fn void toLowerCadena(char*)
/// @brief
/// recorre una cadena y en caso de ser mayuscula la pasa a minuscula
/// @param cadena a pasar a minuscula
void toLowerCadena (char* cadena)
{
	for(int i = 0; cadena[i]; i++)
	{
		cadena[i] = tolower(cadena[i]);
	}
}

void toUpperCadena (char* cadena)
{
	for(int i = 0; cadena[i]; i++)
	{
		cadena[i] = toupper(cadena[i]);
	}
}

//-----------------------------------------------------------------------------------------------------

/// @fn int utn_getString(char*, char*, char*, int, int)
/// @brief
/// funcion para pedir al usuario una cadena en general
/// @param charIngresado es donde almacenamos la cadena ingresada en caso de que la verificacion dio OK
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param len tamaño maximo de la cadena
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getString(char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos)
{
	char buffer[len];
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && len > 0 && reintentos > 0)
	{
		while (reintentos > 0)
		{
			reintentos--;
			printf (mensaje);

			if (getString (buffer, sizeof(buffer)) == 1 && strnlen(buffer, sizeof(buffer)) < len && strnlen(buffer, sizeof(buffer)) > 0)
			{
				strncpy(charIngresado , buffer, len );
				rtn = 0;
				break;
			}
			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}

	}
	if (reintentos == 0)
	{
		rtn = 0;
	}
	return rtn;
}

/// @fn int utn_getNombre(char*, char*, char*, int, int)
/// @brief
/// funcion para pedir al usuario un nombre. Solo letras y espacios por si tiene mas de un nombre
/// @param charIngresado es donde almacenamos la cadena ingresada en caso de que la verificacion dio OK
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param len tamaño maximo de la cadena
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getNombre(char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos)
{
	char buffer[len];
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && len > 0 && reintentos > 0)
	{
		while (reintentos > 0)
		{
			reintentos--;
			printf (mensaje);
			if (getNombre (buffer, sizeof(buffer)) == 1 && strnlen(buffer, sizeof(buffer)) < len && strnlen(buffer, sizeof(buffer)) > 0)
			{
				strncpy(charIngresado , buffer, len );
				rtn = 0;
				break;
			}
			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}
	}
	return rtn;
}

/// @fn int utn_getDescripcion(char*, char*, char*, int, int)
/// @brief
/// funcion para pedir al usuario una cadena habiendose pedido una descripcion de algo.
/// @param charIngresado es donde almacenamos la cadena ingresada en caso de que la verificacion dio OK
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param len tamaño maximo de la cadena
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getDescripcion (char* charIngresado, char* mensaje, char* mensajeError, int len, int reintentos)
{
	char buffer[len];
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && len > 0 && reintentos > 0)
	{
		while (reintentos > 0)
		{
			reintentos--;
			printf (mensaje);

			if (getDescripcion (buffer, sizeof(buffer)) == 1 && strnlen(buffer, sizeof(buffer)) < len)
			{
				strncpy (charIngresado, buffer, len );
				rtn = 0;
				break;
			}
			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}
	}
	return rtn;
}

/// @fn int utn_getDNI(int*, char*, char*, int, int)
/// @brief
/// funcion para pedir al usuario un numero de DNi. Solo los numeros del DNI. Se ingresa una cadena y luego se pasa a entero
/// @param pNumeroIngresado es donde se guarda lo que el usuario ingreso luego de copiarse la cadena y haberse verificado y pasado a int
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param len tamaño maximo de la cadena
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getDNI(int* pNumeroIngresado, char* mensaje, char* mensajeError, int len, int reintentos)
{
	int bufferInt;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && len > 0 && reintentos > 0)
	{
		while (reintentos > 0)
		{
			printf (mensaje);

			if (getDNI (&bufferInt) == 1 && bufferInt > 0 && bufferInt <= len )
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			reintentos--;
			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}

		if (reintentos == 0)
		{
			rtn = -2;
		}
	}
	return rtn;
}

/// @fn int utn_getCodigo(char*, char*, char*, int, int, int)
/// @brief
/// funcion para pedir al usuario un codgio alfanumerico de entre min y max valores
/// @param charIngresado es donde se guarda lo que el usuario ingreso luego de copiarse la cadena y haberse verificado
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param min tamaño maximo del codigo
/// @param max tamaño maximo del codigo
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getCodigo(char* charIngresado, char* mensaje, char* mensajeError, int min, int max, int reintentos)
{
	char buffer[max];
	int rtn = -1;

	if (mensaje != NULL && mensajeError != NULL && min < max && reintentos > 0)
	{
		while (reintentos > 0)
		{
			reintentos--;
			printf (mensaje);
			if (getCodigo (buffer, sizeof(buffer)) == 1 && strlen(buffer)>= min && strlen(buffer) < max)
			{
				strncpy(charIngresado , buffer, max );
				rtn = 0;
				break;
			}

			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}
	}

	return rtn;
}

/// @fn int utn_getInt(int*, char*, char*, int, int, int)
/// @brief
/// funcion para pedir al usuario un numero. se verifica en otra funcion que se ingreso un numero. si esta ok se copia ese numero en la variable que queremos.
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param min tamaño maximo del codigo
/// @param max tamaño maximo del codigo
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getInt(int* pNumeroIngresado, char* mensaje, char* mensajeError, int min, int max, int reintentos)
{
	int bufferInt;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && max > min && reintentos > 0)
	{
		while (reintentos > 0)
		{
			printf (mensaje);

			if (getInt (&bufferInt) == 1 && bufferInt >= min && bufferInt <= max )
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			reintentos--;
			printf (mensajeError);
			printf ("\nTe quedan %d intentos.\n", reintentos);
		}

		if (reintentos == 0)
		{
			rtn = -2;
		}
	}
	return rtn;
}

/// @fn int utn_getIntRange(int*, char*, char*, int, int)
/// @brief funcion para pedir al usuario un numero.
/// se verifica en otra funcion que se ingreso un numero. si esta ok se copia ese numero en la variable que queremos. No hay cant reintentos en este caso
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param min tamaño maximo del codigo
/// @param max tamaño maximo del codigo
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getIntRange(int *pNumeroIngresado, char *mensaje, char *mensajeError, int min, int max)
{
	int bufferInt;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && max > min)
	{
		while (1)
		{
			printf(mensaje);

			if (getInt (&bufferInt) == 1 && bufferInt >= min && bufferInt <= max)
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			printf(mensajeError);
		}
	}
	return rtn;
}

/// @fn int utn_getIntPositivo(int*, char*, char*)
/// @brief funcion para pedir al usuario un numero.positivo
/// SIn cantidad maxima de reintentos y solo verificamos que sea un numero entero positivo
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getIntPositivo (int* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	int bufferInt;
	int rtn = 0;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getInt(&bufferInt) == 1 && bufferInt > 0)
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			printf (mensajeError);
		}
	}
	return rtn;
}

/// @fn int utn_getIntNegativo(int*, char*, char*)
/// @brief funcion para pedir al usuario un numero negativo
/// SIn cantidad maxima de reintentos y solo verificamos que sea un numero entero negativo
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getIntNegativo(int* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	int bufferInt;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getInt(&bufferInt) == 1 && bufferInt < 0)
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			printf (mensajeError);
		}
	}
	return rtn;
}

/// @fn int utn_getIntAlone(int*, char*, char*)
/// @brief funcion para pedir al usuario un numero cualquiera
/// SIn cantidad maxima de reintentos y solo verificamos que sea un numero entero
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error
int utn_getIntAlone (int* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	int bufferInt;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getInt(&bufferInt) == 1)
			{
				*pNumeroIngresado = bufferInt;
				rtn = 0;
				break;
			}

			puts (mensajeError);
		}
	}
	return rtn;
}

//--------------------------------------------------------------------------------------------------------------

/// @fn int utn_getFloat(float*, char*, char*, float, float, int)
/// @brief
/// funcion para pedir al usuario un numero.flotante se verifica en otra funcion que se ingreso un numero. si esta ok se copia ese numero en la variable que queremos.
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param min tamaño maximo del codigo
/// @param max tamaño maximo del codigo
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getFloat(float* pNumeroIngresado, char* mensaje, char* mensajeError, float min, float max, int reintentos)
{
	float bufferFloat;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && max > min && reintentos > 0)
	{
		while (reintentos > 0)
		{
			printf (mensaje);

			if (getFloat (&bufferFloat) == 1 && bufferFloat >= min && bufferFloat <= max)
			{
				break;
			}

			reintentos--;
			printf (mensajeError);
			printf ("\n Te quedan %d intentos.\n", reintentos);
		}

		if (reintentos == 0)
		{
			rtn = -2;
		}
		else
		{
			*pNumeroIngresado = bufferFloat;
			rtn = 0;
		}
	}
	return rtn;

}

/// @fn int utn_getFloatPositivo(float*, char*, char*)
/// @brief
/// funcion para pedir al usuario un numero.flotante positivo
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getFloatPositivo (float* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	float bufferFloat;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getFloat(&bufferFloat) == 1 && bufferFloat > 0)
			{
				*pNumeroIngresado = bufferFloat;
				rtn = 0;
				break;
			}

			printf (mensajeError);
		}
	}
	return rtn;
}

/// @fn int utn_getFloatAlone(float*, char*, char*)
/// @brief
/// funcion para pedir al usuario un numero. flotante.
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getFloatAlone(float* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	float bufferFloat;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getFloat (&bufferFloat) == 1)
			{
				*pNumeroIngresado = bufferFloat;
				rtn = 0;
				break;
			}


			printf (mensajeError);
		}
	}
	return rtn;
}

//--------------------------------------------------------------------------------------------------------------

/// @fn int utn_getDouble(double*, char*, char*, double, double, int)
/// @brief
/// funcion para pedir al usuario un numero doble
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @param min tamaño maximo del codigo
/// @param max tamaño maximo del codigo
/// @param reintentos cantidad maxima de reintentos
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getDouble(double* pNumeroIngresado, char* mensaje, char* mensajeError, double min, double max, int reintentos)
{
	double bufferDouble;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && max > min && reintentos > 0)
	{
		while (reintentos > 0)
		{
			printf (mensaje);

			if (getDouble (&bufferDouble) == 1 && bufferDouble >= min && bufferDouble <= max)
			{
				break;
			}

			reintentos--;
			printf (mensajeError);
			printf ("\n Te quedan %d intentos.\n", reintentos);
		}

		if (reintentos == 0)
		{
			rtn = -2;
		}
		else
		{
			*pNumeroIngresado = bufferDouble;
			rtn = 0;
		}
	}
	return rtn;

}

/// @fn int utn_getDoubleAlone(double*, char*, char*)
/// @brief
/// funcion para pedir al usuario un numero doble sin maximo reintentos
/// @param pNumeroIngresado donde se va a guardar el numero que ingreso el usuario si todas las verificaciones fueron ok
/// @param mensaje que el usuario ve que debe ingresar
/// @param mensajeError si ingreso algo erroneo
/// @return devuelve un 0 si esta OK o un -1 si hay error y -2 si se acabaron reintentos
int utn_getDoubleAlone(double* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	double bufferDouble;
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL)
	{
		while (1)
		{
			printf (mensaje);

			if (getDouble (&bufferDouble) == 1)
			{
				*pNumeroIngresado = bufferDouble;
				rtn = 0;
				break;
			}

			printf (mensajeError);
		}
	}
	return rtn;
}

//-----------------------------------------------------------------------------------------------------------
//Funciones


/// @fn int getInt(int*)
/// @brief
/// funcion para verificar que si es un entero convertimos la cadena a entero
/// @param pNumeroIngresado donde almacenamos el numero si se verifico que es un numero y es entero
/// @return un 1 si esta OK y un -1 si hay error
int getInt (int* pNumeroIngresado)
{
	char buffer[50];
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esNumerica(buffer) == 1)
	{
		*pNumeroIngresado = atoi (buffer);
		rtn = 1;
	}
	return rtn;
}

/// @fn int getFloat(float*)
/// @brief
/// funcion para verificar que si es un flotante convertimos la cadena a flotante
/// @param pNumeroIngresado donde almacenamos el numero si se verifico que es un numero y es flotante
/// @return un 1 si esta OK y un -1 si hay error
int getFloat (float* pNumeroIngresado)
{
	char buffer[50];
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esFlotante(buffer) == 1)
	{
		*pNumeroIngresado = atof (buffer);
		rtn = 1;
	}
	return rtn;
}

/// @fn int getDouble(double*)
/// @brief
/// funcion para verificar que si es un doble convertimos la cadena a flotante
/// @param pNumeroIngresado donde almacenamos el numero si se verifico que es un numero y es flotante
/// @return un 1 si esta OK y un -1 si hay error
int getDouble (double* pNumeroIngresado)
{
	char buffer[50];
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esFlotante(buffer) == 1)
	{
		*pNumeroIngresado = atof (buffer);
		rtn = 1;
	}
	return rtn;
}

/// @fn int getString(char*, int)
/// @brief
/// funcion para verificar que si es una cadena de caracteres
/// @param pNombreIngresado donde almacenamos la cadena
/// @param len tamaño maximo de la cadena
/// @return un 1 si esta OK y un -1 si hay error
int getString (char* pNombreIngresado, int len)
{
	char buffer[len + 10];
	int rtn = -1;
	if ( pNombreIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pNombreIngresado, buffer, len );
		rtn = 1;
	}
	return rtn;
}


/// @fn int getNombre(char*, int)
/// @brief
/// funcion para verificar que si es una cadena de solo letras y espacio si son 2 o mas nombres. Funciona para Apellidos
/// @param pNombreIngresado donde almacenamos la cadena si verificamos que son solo letras y espacios
/// @param len tamaño maximo de la cadena
/// @return un 1 si esta OK y un -1 si hay error
int getNombre (char* pNombreIngresado, int len)
{
	char buffer[len + 10];
	int rtn = -1;

	if ( pNombreIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esNombre(buffer, sizeof (buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pNombreIngresado, buffer, len);
		rtn = 1;
	}
	return rtn;
}

/// @fn int getDescripcion(char*, int)
/// @brief
/// funcion para verificar que si es una cadena de solo caracteres validos en una descripcion.
/// @param pCadena donde almacenamos la cadena si verificamos ok que es una cadena de caracteres para una descripcion.
/// @param len tamaño maximo de la cadena
/// @return un 1 si esta OK y un -1 si hay error
int getDescripcion (char* pCadena, int len)
{
	char buffer[len + 10];
	int rtn = -1;
	if ( pCadena != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esDescripcion(buffer, sizeof(buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pCadena, buffer, len);
		rtn = 1;
	}
	return rtn;
}

/// @fn int getCodigo(char*, int)
/// @brief
/// funcion para verificar que si es una cadena alfanumerica.
/// @param pCadena donde almacenamos la cadena si verificamos que son solo letras y numeros
/// @param len tamaño maximo de la cadena
/// @return un 1 si esta OK y un -1 si hay error
int getCodigo (char* pCadena, int len)
{
	char buffer[len+ 10];
	int rtn = -1;
	if ( pCadena != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esCodigo(buffer, sizeof(buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer)) < len)
	{
		strncpy (pCadena, buffer, len);
		rtn = 1;
	}
	return rtn;
}


/// @fn int getDNI(int*)
/// @brief
/// funcion para verificar que si es un entero convertimos la cadena a entero
/// @param pNumeroIngresado donde almacenamos el numero si se verifico que es un numero y es entero
/// @return un 1 si esta OK y un -1 si hay error
int getDNI (int* pNumeroIngresado)
{
	char buffer[50];
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esNumerica(buffer) == 1)
	{
		*pNumeroIngresado = atoi (buffer);
		rtn = 1;
	}
	return rtn;
}

int getIntFromStr (char* cadena, int* pNumeroIngresado)
{
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 cadena != NULL &&
		 esNumerica(cadena) == 1)
	{
		*pNumeroIngresado = atoi (cadena);
		rtn = 0;
	}
	return rtn;
}

int getFloatFromStr (char* cadena, float* pNumeroIngresado)
{
	int rtn = -1;
	if ( pNumeroIngresado != NULL &&
		 cadena != NULL &&
		 esFlotante(cadena) == 1)
	{
		*pNumeroIngresado = atof (cadena);
		rtn = 0;
	}
	return rtn;
}

/// @fn int esNumerica(char*)
/// @brief  se arrance asumiendo que la cadena esta ok y si encontramos algo que no verifica nuestra condicion salimos de la comprobacion e indicamos el error
/// funcion para comprobar que una cadena es entera comparando todos los caracteres de la cadena
/// @param cadenaPosiblesNumeros cadena a comprobar
/// @return 1 si esta OK y un 0 si hay error
int esNumerica ( char * cadenaPosiblesNumeros)
{
	int i = 0;
	int retorno = 1;
	if (cadenaPosiblesNumeros != NULL && strlen (cadenaPosiblesNumeros) > 0)
	{
		while (cadenaPosiblesNumeros[i] != '\0' )
		{
			if( i==0 && (cadenaPosiblesNumeros[i] == '+' || cadenaPosiblesNumeros[i] == '-') )
			{
				i++;
			}
			if (cadenaPosiblesNumeros[i] < '0' || cadenaPosiblesNumeros[i] > '9' )
			{
				retorno = 0;
				break ;
			}
			i++;
		}
	}
	return retorno;
}

/// @fn int esFlotante(char*)
/// @brief  se arrance asumiendo que la cadena esta ok y si encontramos algo que no verifica nuestra condicion salimos de la comprobacion e indicamos el error
/// funcion para comprobar que una cadena es flotante comparando todos los caracteres de la cadena
/// @param cadenaPosiblesNumeros cadena a comprobar
/// @return 1 si esta OK y un 0 si hay error
int esFlotante(char *cadenaPosiblesNumeros)
{
	int i = 0;
	int flagPunto = 0;
	int retorno = 1;

	if (cadenaPosiblesNumeros != NULL && strlen(cadenaPosiblesNumeros) > 0)
	{
		while (cadenaPosiblesNumeros[i] != '\0')
		{
			if( i==0 && (cadenaPosiblesNumeros[i] == '+' || cadenaPosiblesNumeros[i] == '-') )
			{
				i++;
			}
			if (cadenaPosiblesNumeros[i] < '0'
					|| cadenaPosiblesNumeros[i] > '9')
			{
				if (cadenaPosiblesNumeros[i] == '.' && flagPunto == 0)
				{
					flagPunto++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

/// @fn int esNombre(char*, int)
/// @brief  se arrance asumiendo que la cadena esta ok y si encontramos algo que no verifica nuestra condicion salimos de la comprobacion e indicamos el error
/// funcion para comprobar que una cadena son solo letras o espacios
/// @param cadena  a comprobar
/// @param len tamaño maximo de la cadena
/// @return 1 si esta OK y un 0 si hay error
int esNombre ( char * cadena, int len)
{
	int rtn = 1;
	int i = 0;

	if (cadena != NULL && len > 0)
	{
		while (cadena[i] != '\0' && i < len)
		{
			if (cadena[i] == ' ' && i != 0)
			{
				i++;
			}
			if ( (cadena[i] < 'A' || cadena[i] > 'Z') &&
				 (cadena[i] < 'a' || cadena[i] > 'z') )
			{

					rtn = -1;
					break;
			}
			i++;
		}
	}
	return rtn;
}

/// @fn int esCodigo(char*, int)
/// @brief  se arrance asumiendo que la cadena esta ok y si encontramos algo que no verifica nuestra condicion salimos de la comprobacion e indicamos el error
/// funcion para comprobar que una cadena son solo letras y numeros
/// @param cadena  a comprobar
/// @param len tamaño maximo de la cadena
/// @return 1 si esta OK y un 0 si hay error
int esCodigo ( char * cadena, int len)
{
	int rtn = 1;
	int i = 0;

	if (cadena != NULL && len > 0)
	{
		while (cadena[i] != '\0' && i < len)
		{
			if(cadena[i] < '0' || (cadena[i] > '9' &&
			   cadena[i] < 'A') || (cadena[i] > 'Z' &&
			   cadena[i] < 'a') || cadena[i] > 'z' )
			{
					rtn = -1;
					break;
			}
			i++;
		}
	}
	return rtn;
}

/// @fn int esDescripcion(char*, int)
/// @brief  se arrance asumiendo que la cadena esta ok y si encontramos algo que no verifica nuestra condicion salimos de la comprobacion e indicamos el error
/// funcion para comprobar que una cadena son solo letras, numeros, punto, coma y espacio
/// @param cadena  a comprobar
/// @param len tamaño maximo de la cadena
/// @return 1 si esta OK y un 0 si hay error
int esDescripcion ( char * cadena, int len)
{
	int rtn = 1;
	int i = 0;

	if (cadena != NULL && len > 0)
	{
		while (cadena[i] != '\0' && i < len)
		{
			if ( (cadena[i] < 'A' || cadena[i] > 'Z') &&
				 (cadena[i] < 'a' || cadena[i] > 'z') &&
				 (cadena[i] < '0' || cadena[i] > '9') &&
				  cadena[i] != ' ' &&
				  cadena[i] != '.' &&
				  cadena[i] != ',' )
			{
					rtn = -1;
					break;
			}
			i++;
		}
	}
	return rtn;
}


//Reemplaza el scanf

/// @fn int myGets(char*, int)
/// @brief
/// funcino que reemplaza al scanf ya sea para numeros, letras o lo que queramos. Luego con otra condicion vemos que es lo que contiene la cadena
/// @param cadena donde guardamos lo que ingresamos
/// @param len tamaño maximo de la cadena
/// @return un 1 si esta OK y un -1 si hay error
static int myGets(char *cadena, int len)
 {
	int rtn = -1;
	fflush(stdin);
	if ( cadena != NULL && len > 0 && fgets(cadena, len, stdin) == cadena)
	{

		if (cadena[strlen(cadena) - 1] == '\n')
		{
			cadena[strlen(cadena) - 1] = '\0';
		}
		rtn = 1;
	}
	return rtn;
}


//------------------------------------------------------------------------------------------------------------
//Mejoras de Visualizacion

/// @fn void saltoDeLinea(void)
/// @brief
/// un salto de linea con - para emprolijar la experiencia del usuario
void saltoDeLinea (void)
{
	puts ("------------------------------");
}

/// @fn void presionarEnter(void)
/// @brief
/// funcion que pide al usuario que toque enter para continuar
void presionarEnter (void)
{
  printf ( "Presiona ENTER para continuar..." );
  fflush (stdin);
  getchar();
}

/// funicon de un menu generico
void menu (void)
{	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts ("--Trabajo Practico N°3--\n");
	puts ("1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).");
	puts ("2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).");
	puts ("3. Alta de pasajero");
	puts ("4. Modificar datos de pasajero");
	puts ("5. Baja de pasajero");
	puts ("6. Listar pasajeros");
	puts ("7. Ordenar pasajeros");
	puts ("8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).");
	puts ("9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).");
	puts ("10. Salir");
	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~");
}

