/*
 * validaciones.c
 *
 *  Created on: 5 abr. 2022
 *      Author: Agostin
 */
#include "validaciones.h"

//Verifica si una cadena es un numero
static int getInt (int* pNumeroIngresado);
static int getFloat (float* pNumeroIngresado);
static int getDouble (double* pNumeroIngresado);
static int getString (char* pNombreIngresado, int len);
static int getNombre (char* pNombreIngresado, int len);
static int getDescripcion (char* pCadena, int len);
static int getDNI (char* pCadena, int len);

static int esNumerica ( char * cadenaPosiblesNumeros);
static int esFlotante ( char * cadenaPosiblesNumeros);
static int esNombre ( char * cadena, int len);
static int esDescripcion ( char * cadena, int len);

static int myGets ( char * cadena, int l);

int validacionDosCaracteres (char* mensaje, char caracterUno, char caracterDos)
{
	char charIngresado;
	int retorno = -1;

	if (mensaje != NULL)
	{
		retorno = 0;
		printf(mensaje);
		fflush (stdin);
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


//-----------------------------------------------------------------------------------------------------
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

			if (getString (buffer, sizeof(buffer)) == 1 && strnlen(buffer, sizeof(buffer)) < len)
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
			if (getNombre (buffer, sizeof(buffer)) == 1 && strnlen(buffer, sizeof(buffer)) < len)
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

int utn_getDNI(char* pNumeroIngresado, char* mensaje, char* mensajeError, int len, int reintentos)
{
	char bufferDNI [len];
	int rtn = -1;
	if (mensaje != NULL && mensajeError != NULL && len > 0 && reintentos > 0)
	{
		while (reintentos > 0)
		{
			reintentos--;
			printf (mensaje);

			if ( getDNI (bufferDNI, sizeof(bufferDNI)) == 1 && strnlen(bufferDNI, sizeof(bufferDNI)) < len)
			{
				strncpy (pNumeroIngresado, bufferDNI, len );
				rtn = 0;
				break;
			}

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
//Funciones estaticas

static int getInt (int* pNumeroIngresado)
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

static int getFloat (float* pNumeroIngresado)
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

static int getDouble (double* pNumeroIngresado)
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

static int getString (char* pNombreIngresado, int len)
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
static int getNombre (char* pNombreIngresado, int len)
{
	char buffer[len + 10];
	int rtn = -1;

	if ( pNombreIngresado != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esNombre(buffer, sizeof (buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pNombreIngresado, buffer, len );
		rtn = 1;
	}
	return rtn;
}

static int getDescripcion (char* pCadena, int len)
{
	char buffer[len + 10];
	int rtn = -1;
	if ( pCadena != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esDescripcion(buffer, sizeof(buffer)) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pCadena, buffer, strnlen(buffer,sizeof(buffer) ) );
		rtn = 1;
	}
	return rtn;
}

static int getDNI (char* pCadena, int len)
{
	char buffer[len + 10];
	int rtn = -1;
	if ( pCadena != NULL &&
		 myGets(buffer, sizeof (buffer)) == 1 &&
		 esNumerica(buffer) == 1 &&
		 strnlen(buffer,sizeof(buffer) ) < len )
	{
		strncpy (pCadena, buffer, strnlen(buffer,sizeof(buffer) ) );
		rtn = 1;
	}
	return rtn;
}


static int esNumerica ( char * cadenaPosiblesNumeros)
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

static int esFlotante(char *cadenaPosiblesNumeros)
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
				} else {
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

static int esNombre ( char * cadena, int len)
{
	int rtn = 1;
	int i = 0;

	if (cadena != NULL && len > 0)
	{
		while (cadena[i] != '\0' && i < len)
		{
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

static int esDescripcion ( char * cadena, int len)
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
static int myGets(char *cadena, int len)
 {
	int rtn = -1;
	fflush(stdin);
	if ( cadena != NULL && len > 0 && fgets(cadena, len, stdin) == cadena)
	{
		fflush(stdin);
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

void saltoDeLinea (void)
{
	puts ("------------------------------");
}

void presionarEnter (void)
{
  printf ( "Presiona ENTER para continuar..." );
  fflush (stdin);
  getchar();
}
