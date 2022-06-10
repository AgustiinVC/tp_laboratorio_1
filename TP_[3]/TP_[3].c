/*
 ============================================================================
 Name        : TP_[3].c
 Author      : Vallario Cores, Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "controller.h"

int main()
{
	setbuf (stdout,NULL);
    int opcion = 0;
    int flagGuardado = 0;
    LinkedList* listaPasajeros = ll_newLinkedList();

    controller_getLastId();
    // ME QUEDA VER GUARDADO csv
    do
    	{
    		menu();
    		utn_getIntRange (&opcion ,"\nIngrese una Opcion: ", "Error. Ingrese una opcion correcta.\n",1,10);
    		fflush (stdin);
    		switch (opcion)
    		{
    			case 1: //Abrir el csv (abre bien el data)
    				if (flagGuardado == 0) //funca
    				{
    					if (controller_loadFromText("data.csv", listaPasajeros) == 0)
    					{
    						flagGuardado = 1;
    						puts ("\n~~Lectura del archivo CSV correcta~~\n");
    					}
    					else
						{
							puts("\n~~No se pudo leer el archivo CSV~~\n");
						}
    				}
    				else
    				{
    					puts("\n~~Ya se cargo el CSV~~\n");
    				}
    				break;

    			case 2: //Abrir el bin
    				if (flagGuardado == 0)
    				{
    					if (controller_loadFromBinary("data.bin", listaPasajeros) == 0)
    					{
    						flagGuardado = 1;
    						puts ("\n~~Lectura del archivo BIN correcta~~\n");
    					}
    					else
						{
							puts("\n~~No se pudo leer el archivo BIN~~\n");
						}
    				}
    				else
    				{
    					puts("\n~~Ya se cargo el BIN~~\n");
    				}
    				break;

    			case 3: //Alta de Pasajero
    				if (controller_addPassenger(listaPasajeros) == 0)
    				{
    					puts ("\n~~ALTA de pasajero realizada~~\n");
    				}
    				else
    				{
    					puts ("\n~~No se pude realizar el ALTA del pasajero~~\n");
    				}
    				break;

    			case 4:  // Editar Pasajeros
    				if (controller_editPassenger(listaPasajeros) == 0)
    				{
    					puts ("\n~~Se realizo la EDICION con exito~~\n");
    				}
    				else
    				{
    					puts ("\n~~No se pudo realizar la EDICION.~~\n");
    				}
    				break;

    			case 5:  // Baja Pasajeros
					if (controller_removePassenger(listaPasajeros) == 0)
					{
						puts ("\n~~Se ELIMINO el pasajero con exito~~\n");
					}
					else
					{
						puts ("\n~~No se pudo ELIMINAR el pasajero.~~\n");
					}
					break;
    			case 6:  // Listar Pasajeros
					if (controller_ListPassenger(listaPasajeros) == 0)
					{
						puts ("\n~~Se imprimio la lista con exito~~\n");
					}
					else
					{
						puts ("\n~~No se pudo IMPRIMIR.~~\n");
					}
					break;
    			case 7:  // Ordenar Pasajeros
					if (controller_sortPassenger(listaPasajeros) == 0)
					{
						puts ("\n~~Se ORDENO los pasajeros correctamente~~\n");
					}
					else
					{
						puts ("\n~~No se pudo ORDENAR la lista de pasajeros.~~\n");
					}
					break;
				case 8:  // Guardar CSV
					if (controller_saveAsText("data.csv", listaPasajeros) == 0)
					{
						flagGuardado = 0;
						controller_setLastId();
						puts ("\n~~Se realizo el guardado del CSV~~\n");
					}
					else
					{
						puts ("\n~~No se pudo guardar el CSV.~~\n");
					}
					break;
    			case 9:  // Guardar BIN
					if (controller_saveAsBinary("data.bin", listaPasajeros) == 0)
					{
						flagGuardado = 0;
						controller_setLastId();
						puts ("\n~~Se realizo el guardado del BIN~~\n");
					}
					else
					{
						puts ("\n~~No se pudo guardar el BIN.~~\n");
					}
					break;
    			case 10:
    				if (flagGuardado != 0)
    				{
    					opcion = -1;
    					puts ("Guarde antes de salir. Muchas gracias!");
    				}
    				break;
    		}
    	}
    	while (opcion != 10);

    	puts ("Salida");
}
