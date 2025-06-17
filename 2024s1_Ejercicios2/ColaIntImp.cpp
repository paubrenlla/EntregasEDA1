#include "ColaInt.h"
#include "Definiciones.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	//saco de ppio
	NodoListaInt* ppio;
	//inserto en ultimo
	NodoListaInt* ultimo;
	int cantidad;
};

ColaInt crearColaInt() {
	ColaInt nueva = new _cabezalColaInt;
	nueva->cantidad = 0;
	nueva->ppio = NULL;
	nueva->ultimo = NULL;
	return nueva;
}

void encolar(ColaInt& c, int e) {
	NodoListaInt* nuevo = new NodoListaInt(e);
	if (c->ppio == NULL)
	{
		c->ppio = nuevo;
	}
	else {
		c->ultimo->sig = nuevo;
	}
	c->ultimo = nuevo;
	c->cantidad++;
}

int principio(ColaInt c) {
	assert(!esVacia(c));
	return c->ppio->dato;
}

void desencolar(ColaInt& c) {
	assert(!esVacia(c));
	NodoListaInt* borrar = c->ppio;
	c->ppio = c->ppio->sig;
	if (c->ppio == NULL)
	{
		c->ultimo = NULL;
	}
	c->cantidad--;

	delete borrar;
	borrar = NULL;
}

bool esVacia(ColaInt c) {
	return c->ppio == NULL;
}

unsigned int cantidadElementos(ColaInt c) {
	return c->cantidad;
}

ColaInt clon(ColaInt c) {
	ColaInt retorno = crearColaInt();
	NodoListaInt* nodo = c->ppio;
	while (nodo)
	{
		encolar(retorno, nodo->dato);
		nodo = nodo->sig;
	}
	return retorno;
}

void destruir(ColaInt& c) {
	while (!esVacia(c))
	{
		desencolar(c);
	}
	delete c->ppio;
	delete c->ultimo;
	delete c;
	c = NULL;
}

#endif