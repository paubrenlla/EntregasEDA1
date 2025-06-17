#include "PilaInt.h"
#include "Definiciones.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	NodoListaInt* ppio;
	unsigned int cantElem;
};


PilaInt crearPilaInt(){
	PilaInt nueva = new _cabezalPilaInt;
	nueva->ppio = NULL;
	nueva->cantElem = 0;
	return nueva;
}

void push(PilaInt& p, int e) {
	NodoListaInt* agregar = new NodoListaInt;
	agregar->dato = e;
	agregar->sig = p->ppio;
	p->ppio = agregar;
	p->cantElem++;
}

int top(PilaInt p) {
	assert(!esVacia(p));
	return p->ppio->dato;
}

void pop(PilaInt& p) {
	assert(!esVacia(p));
	NodoListaInt* borrar = p->ppio;
	p->ppio = p->ppio->sig;
	delete borrar;
	borrar = NULL;
	p->cantElem--;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->cantElem;
}

bool esVacia(PilaInt p) {
	return p->ppio == NULL;
}

PilaInt clon(PilaInt p) {
	PilaInt aux = crearPilaInt();
	NodoListaInt* nodo = p->ppio;
	while (nodo)
	{
		push(aux, nodo->dato);
		nodo = nodo->sig;
	}

	PilaInt retorno = crearPilaInt();
	nodo = aux->ppio;
	while (nodo)
	{
		push(retorno, nodo->dato);
		nodo = nodo->sig;
	}
	destruir(aux);
	return retorno;
}

void destruir(PilaInt& p) {
	while (!esVacia(p))
	{
		pop(p);
	}
	delete p->ppio;
	delete p;
	p = NULL;
}


#endif