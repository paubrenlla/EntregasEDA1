#include "DiccionarioInt.h"
#include "Definiciones.h"

#ifdef DICCIONARIO_INT_IMP

const double DELTA = 0.6;

struct _cabezalDiccionarioInt {
	NodoListaInt** hash;
	unsigned int buckets;
	unsigned int cantElem;
};

//Auxiliares
/*
* PRE: recibe los buckets de un diccionario y un elemento
* POS: le aplica la funcion de hash y retorna el valor
*/
int getIndex(int buckets, int e) 
{
	int eAbs = e;
	if (e < 0)
	{
		eAbs = e * -1;
	}
	return eAbs % buckets;
}

/*
* PRE: recibe una cantidad de buckets
* POS: crea un diccionario con la cantidad de buckets recibidas
*/
DiccionarioInt crearDiccionarioBucket(unsigned int buckets) {
	DiccionarioInt nuevo = new _cabezalDiccionarioInt;
	nuevo->cantElem = 0;
	nuevo->buckets = buckets;
	nuevo->hash = new NodoListaInt* [buckets];

	for (int i = 0; i < buckets; i++)
	{
		nuevo->hash[i] = NULL;
	}

	return nuevo;
}

/*
* PRE: 
* POS: agrega un elemento al principio de una lista
*/
void agregarPrincipio(NodoListaInt*& l, int dato1) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = dato1;
	nuevo->sig = l;
	l = nuevo;
}

/*
* PRE: recibe una lista y un dato que agregarle al final, y un puntero al ultimo elemento
*		de la lista.
* POS: agrega un elemento al final de una lista de forma optimizada y actualiza el puntero
*		al utlimo elemento.
*/
void agregarFin(NodoListaInt*& l, int dato1, NodoListaInt*& fin) {
	if (!l) {
		agregarPrincipio(l, dato1);
		fin = l;
	}
	else {
		agregarPrincipio(fin->sig, dato1);
		fin = fin->sig;
	}
}

/*
* PRE: 
* POS: devuelve una nueva lista igual a la recibida, pero sin compartir memoria
*/
NodoListaInt* clonLista(NodoListaInt* l) 
{
	NodoListaInt* clon = NULL;
	NodoListaInt* fin = NULL;
	while (l != NULL)
	{
		agregarFin(clon, l->dato, fin);
		l = l->sig;
	}

	return clon;
}

/*
* PRE: recibe una lista cualquiera y un elemento que pertenece a ella
* POS: elimina el elemento de la lista
*/
void borrarElemento(NodoListaInt*& l, int elem) {
	if (l->dato == elem) 
	{
		NodoListaInt* borro = l;
		l = l->sig;
		delete borro;
		borro = NULL;
		return;
	}
	borrarElemento(l->sig, elem);
}
//

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
	DiccionarioInt nuevo = new _cabezalDiccionarioInt;
	nuevo->buckets = (int)(esperados / DELTA);
	nuevo->cantElem = 0;
	nuevo->hash = new NodoListaInt* [nuevo->buckets];

	for (int i = 0; i < nuevo->buckets; i++)
	{
		nuevo->hash[i] = NULL;
	}
	
	return nuevo;
}

void agregar(DiccionarioInt& d, int e) {
	if (!pertenece(d, e)) {
		int index = getIndex(d->buckets, e);
		agregarPrincipio(d->hash[index], e);
		d->cantElem++;
	}
}

void borrar(DiccionarioInt& d, int e) {
	if (pertenece(d, e))
	{
		int index = getIndex(d->buckets, e);
		//Si bien hacemos un while, el orden promedio es 1, ya que
		//no deberia haber mas de un elemento por celda en el caso promedio.
		borrarElemento(d->hash[index], e);

		d->cantElem--;
	}
}

bool pertenece(DiccionarioInt d, int e) {
	int index = getIndex(d->buckets, e);
	NodoListaInt* aux = d->hash[index];

	while (aux != NULL)
	{
		if (aux->dato == e)
		{
			return true;
		}
		aux = aux->sig;
	}
	
	return false;
}

int elemento(DiccionarioInt d) {
	assert(!esVacio(d));
	for (int i = 0; i < d->buckets; i++)
	{
		if (d->hash[i] != NULL)
		{
			return d->hash[i]->dato;
		}
	}
}

bool esVacio(DiccionarioInt d) {
	return d->cantElem == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {
	return d->cantElem;
}

DiccionarioInt clon(DiccionarioInt d) {
	DiccionarioInt clon = crearDiccionarioBucket(d->buckets);
	
	for (int i = 0; i < clon->buckets; i++)
	{
		clon->hash[i] = clonLista(d->hash[i]);
	}
	clon->cantElem = d->cantElem;

	return clon;
}

void destruir(DiccionarioInt& d) {
	while (!esVacio(d))
	{
		borrar(d, elemento(d));
	}
	delete[] d->hash;
	delete d;
	d = NULL;
}


#endif