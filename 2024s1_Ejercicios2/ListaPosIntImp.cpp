#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int* datos;
	unsigned int sizeArr;
	unsigned int cantElem;
};

ListaPosInt crearListaPosInt()
{
	ListaPosInt nueva = new _cabezalListaPosInt;

	int n = 10;

	nueva->datos = new int [n];
	for (int i = 0; i < n; i++)
	{
		nueva->datos[i] = 0;
	}

	nueva->sizeArr = n;

	nueva->cantElem = 0;
	return nueva;
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
	if (l->cantElem == l->sizeArr) //caso de agrandar
	{
		int* nuevoArr = new int[l->cantElem * 2];
		//cargo los datos que tengo
		for (int i = 0; i < l->cantElem; i++)
		{
			nuevoArr[i] = l->datos[i];
		}
		//cargo el resto en 0
		for (int i = l->cantElem; i < l->sizeArr * 2; i++)
		{
			nuevoArr[i] = 0;
		}
		delete[] l->datos;
		//actualizo los datos de la lista

		l->datos = nuevoArr;
		l->sizeArr = l->sizeArr * 2;
	}
	if (pos >= l->cantElem)
	{
		l->datos[l->cantElem] = e;
	}
	else {
		for (int i = l->cantElem; i > pos; i--)
		{
			l->datos[i] = l->datos[i - 1];
		}
		l->datos[pos] = e;
	}
	l->cantElem++;
}

void borrar(ListaPosInt& l, unsigned int pos)
{
	if (l->cantElem == 0 || pos > l->cantElem)
	{
		return;
	}

	for (int i = pos; i < l->sizeArr - 1; i++)
	{
		l->datos[i] = l->datos[i + 1];
	}
	l->datos[l->cantElem] = 0;
	l->cantElem--;
}

int elemento(ListaPosInt l, unsigned int pos)
{
	assert(0 <= pos || pos > l->cantElem);
	return l->datos[pos];
}

bool esVacia(ListaPosInt l)
{
	return l->cantElem == 0;
}

unsigned int cantidadElementos(ListaPosInt l)
{
	return l->cantElem;
}

ListaPosInt clon(ListaPosInt l)
{
	ListaPosInt retorno = new _cabezalListaPosInt;
	retorno->cantElem = l->cantElem;
	retorno->sizeArr = l->sizeArr;
	retorno->datos = new int[l->sizeArr];

	for (int i = 0; i < l->sizeArr; i++)
	{
		retorno->datos[i] = l->datos[i];
	}

	return retorno;
}

void destruir(ListaPosInt& l)
{
	delete[] l->datos;
	l->datos = NULL;
	delete l;
	l = NULL;
}


#endif