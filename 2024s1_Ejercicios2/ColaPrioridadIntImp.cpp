#include "ColaPrioridadInt.h"
#include "Definiciones.h"

#ifdef COLAPRIORIDAD_INT_IMP

//AUXILIARES//
/*
* PRE:
* POS: inserta el elemento
*/
void agregarAlPrincipioColaP(NodoListaIntDobleDato*& l, int e, int prioridad) {
	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato(e, prioridad);
	nuevo->sig = l;
	l = nuevo;
}

/*
* PRE:
* POS: Agrega el elemento e a la lista con sus ocurrencias como segundo dato.
*		La insercion se realiza ordenada.
*/
void insertarOrdenadoColaP(NodoListaIntDobleDato*& l, int e, int prioridad) {
	if (!l || prioridad > l->dato2)
	{
		agregarAlPrincipioColaP(l, e, prioridad);
	}
	else
	{
		insertarOrdenadoColaP(l->sig, e, prioridad);
	}
}

//////////////////////////////////////////

struct _cabezalColaPrioridadInt {
	NodoListaIntDobleDato* cola;
	int cant;
	int size;
};

ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	ColaPrioridadInt nuevo = new _cabezalColaPrioridadInt;
	nuevo->cant = 0;
	nuevo->size = cota;
	nuevo->cola = NULL;
	return nuevo;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	if (!esLlena(c))
	{
		insertarOrdenadoColaP(c->cola, e, p);
		c->cant++;
	}
}

int principio(ColaPrioridadInt c) {
	assert(!esVacia(c));
	return c->cola->dato1;
}

int principioPrioridad(ColaPrioridadInt c) {
	assert(!esVacia(c));
	return c->cola->dato2;
}

void desencolar(ColaPrioridadInt& c) {
	if (!esVacia(c)) {
		NodoListaIntDobleDato* borrar = c->cola;
		c->cola = c->cola->sig;
		c->cant--;

		delete borrar;
		borrar = NULL;
	}
}

bool esVacia(ColaPrioridadInt c) {
	return c->cola == NULL;
}

bool esLlena(ColaPrioridadInt c) {
	return c->cant == c->size;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	if (c == NULL)
	{
		return 0;
	}
	return c->cant;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	ColaPrioridadInt clon = crearColaPrioridadInt(c->size);
	NodoListaIntDobleDato* aux = c->cola;

	while (aux != NULL)
	{
		encolar(clon, aux->dato1, aux->dato2);
		aux = aux->sig;
	}

	return clon;
}

void destruir(ColaPrioridadInt& c) {
	while (!esVacia(c))
	{
		desencolar(c);
	}
	delete c->cola;
	delete c;
	c = NULL;
}

#endif