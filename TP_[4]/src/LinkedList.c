#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*)malloc (sizeof(LinkedList));
    if (this != NULL)
    {
    	this -> pFirstNode = NULL;
    	this -> size = 0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
    	returnAux = this -> size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	int lenList = ll_len(this);
	if (this != NULL && nodeIndex >= 0 && nodeIndex < lenList)
	{
		pNode = this -> pFirstNode;
		for (int i = 0; i < nodeIndex; i++)
		{
			pNode = pNode -> pNextNode;
		}
	}
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int lenList = ll_len(this);


    if (this != NULL && nodeIndex >= 0 && nodeIndex <= lenList)
    {
    	Node* newNode = (Node*) malloc (sizeof(Node)); //Creo un nuevo Nodo
    	if (newNode != NULL)
    	{
    		if (nodeIndex == 0)
    		{
    			newNode -> pNextNode = this -> pFirstNode; // apunto el nuevo nodo al nodo en el indice 0
    			this -> pFirstNode = newNode; // apunto el primer nodo al nuevo nodo
    		}
    		else
    		{
    			Node* auxNode = getNode(this, nodeIndex - 1); //ultimo nodo
    			newNode -> pNextNode = auxNode -> pNextNode;
    			auxNode -> pNextNode = newNode;  //apunto el anterior ultimo nodo al nuevo ultimo nodo
    		}
    		newNode -> pElement = pElement; // asignamos el elemento al nuevo nodo.
    		this -> size++; //aumento el tama�o
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this); //tama�o de la lista
    	if(addNode(this, lenList, pElement) == 0) //si pude agregar un nodo correctamente
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pAuxNode;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this);
    	if (index >= 0 && index <= lenList) //valido el indice que recibo
    	{
    		pAuxNode = getNode(this, index); //tomo el nodo del indice
			if (pAuxNode != NULL)
			{
				returnAux = pAuxNode -> pElement; // si el indice no esta vacio retorno  el puntero al elemento
			}
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pAuxNode;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this);
		if (index >= 0 && index <= lenList) // valido el indice
		{
			pAuxNode = getNode(this, index); //tomo el nodo que esta en el indice que se necesita
			if (pAuxNode != NULL) // verifico q no sea NULL
			{
				pAuxNode -> pElement = pElement; // seteo el nodo apuntando al nuevo elemento
				returnAux = 0;
			}
		}
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pAuxNode;
    Node* pAuxNodeRemove;
    int lenList = ll_len(this);

    if (this != NULL && index >= 0 && index <= lenList) //valido el indice y que la lista no sea NULL
    {
    	pAuxNode = getNode(this, index); //Tomo el nodo en el indice que quiero borrar
    	if (pAuxNode != NULL)
    	{
    		if (index != 0) //si NO es el nodo inicial
    		{
    			pAuxNode = getNode(this, index - 1); //tomo el nodo anterior al que quiero eleminar
    			pAuxNodeRemove = pAuxNode -> pNextNode; //tomo la direccion donde apunta al siguiente nodo
    			pAuxNode -> pNextNode = pAuxNodeRemove -> pNextNode;
    		}
    		else
    		{
				pAuxNodeRemove = pAuxNode -> pNextNode;
				this -> pFirstNode = pAuxNodeRemove;
    		}
			free (pAuxNodeRemove);
			this -> size--;
			returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this);
    	for (i = 0; i < lenList; i++)
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL && ll_clear(this) == 0)
    {
    	free (this);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int lenList;
    void* auxPElement;
    if (this != NULL)
    {
    	lenList = ll_len(this);
    	if (lenList > 0)
    	{
    		for (i = 0; i < lenList; i++)
			{
    			auxPElement = ll_get(this, i);
				if (auxPElement == pElement)
				{
					returnAux = i;
					break;
				}
			}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this);
    	if (lenList > 0)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int lenList;

    if (this != NULL)
    {
    	lenList = ll_len(this);
    	if (index >= 0 && index <= lenList)
    	{
    		if (addNode(this, index, pElement) == 0)
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int lenList;
    Node* nodeAux = NULL;

    if (this != NULL)
    {
    	lenList = ll_len(this);
    	if (index >= 0 && index < lenList)
    	{
    		nodeAux = getNode(this, index);
    		returnAux = nodeAux -> pElement;
    		ll_remove(this, index);
    	}
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int aux;
    if (this != NULL)
    {
    	aux = ll_indexOf(this, pElement);
    	if (aux >= 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int lenList;
    int i;
    int counter = 0;
    void* pElement = NULL;

    if (this != NULL && this2 != NULL)
    {
    	lenList = ll_len(this2);

    	for (i = 0; i < lenList; i ++)
    	{
    		pElement = ll_get(this2, i);
    		if (ll_contains(this, pElement) == 1)
    		{
    			counter++;
    		}
    		else
    		{
    			break;
    		}
    	}

    	if (lenList == counter)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    int lenList;
    void* pElement;

    if (this != NULL)
    {
    	lenList = ll_len(this);

    	if (from >= 0 && from <= lenList && to >= 0 && to <= lenList && from <= to && lenList > 0)
    	{
    		cloneArray = ll_newLinkedList();
    	}

    	if (cloneArray != NULL)
    	{
    		for (i = from; i <= to; i ++)
    		{
    			pElement = ll_get(this, i);
    			ll_add(cloneArray, pElement);
    		}
    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int lenList;
    if (this != NULL)
    {
    	lenList = ll_len(this);

    	if (lenList > 0)
    	{
    		cloneArray = ll_subList(this, 0, lenList);
    	}
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    int i;
    int flag;
    int lenList;

    void* pElementOne;
    void* pElementTwo;
    void* pElementAux;

    if (this != NULL && pFunc != NULL && (order == 0 || order ==1) )
    {
    	lenList = ll_len(this);
    	if (lenList > 1)
    	{
    		do
    		{
    			flag = 0;
    			for (i = 0; i < lenList -1; i++)
    			{
    				pElementOne = ll_get(this, i);
    				pElementTwo = ll_get(this, i+1);

    				if ( (pFunc(pElementOne, pElementTwo) == -1 && order == 0) || (pFunc(pElementOne, pElementTwo) == 1 && order == 1) )
    				{
    					pElementAux = pElementOne;
    					ll_set(this, i, pElementTwo);
    					ll_set(this, i+1, pElementAux);
    					flag = 1;
    				}
    			}
    		}
    		while (flag == 1);
    		returnAux = 0;
    	}
    }
    return returnAux;
}

