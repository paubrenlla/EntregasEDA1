#include "ListaOrdInt.h"
#include "Definiciones.h"

#ifdef LISTA_ORD_INT_IMP_2

//Auxiliares//
/* 
* PRE: 
* POS: Agrega de forma ordenada el dato n en el ab a
*/
void agregarABOrdenado(NodoABIntDobleDato*& a, int n) {
	if (!a) 
	{
		a = new NodoABIntDobleDato(n, 1);
		return;
	}
	if (n == a->dato1) 
	{
		a->dato2++;
		return;
	}
	if (n < a->dato1) 
	{
		agregarABOrdenado(a->izq, n);
	}
	else
	{
		agregarABOrdenado(a->der, n);
	}
}

/*
* PRE: recibe un arbol ordenado no vacio
* POS: elimina el maximo elemento mas chico y retorna su valor
*/
NodoABIntDobleDato* borrarMaxMin(NodoABIntDobleDato*& a) {
	if (!a->der)
	{
		NodoABIntDobleDato* dato1 = a;
		if (!a->izq)
		{
			delete a;
			a = NULL;
		}
		else {
			NodoABIntDobleDato* borro = a;
			a = a->izq;
			delete borro;
			borro = NULL;
		}
		return dato1;
	}
	return borrarMaxMin(a->der);
}

/*
* PRE: recibe un arbol ordenado no vacio
* POS: elimina el nodo raiz y mantiene el reto del arbol
*/
void borrarNodoRaiz(NodoABIntDobleDato*& a) {
	if (!a->der && !a->izq)
	{
		delete a;
		a = NULL;
		return;
	}
	if (!a->der)
	{
		NodoABIntDobleDato* borro = a;
		a = a->izq;
		delete borro;
		return;
	}
	if (!a->izq)
	{
		NodoABIntDobleDato* borro = a;
		a = a->der;
		delete borro;
		return;
	}
	NodoABIntDobleDato* nueva = borrarMaxMin(a->izq);
	a->dato1 = nueva->dato1;
	a->dato2 = nueva->dato2;
	delete nueva;
	nueva = NULL;
}

/*
* PRE: recibe un arbol ordenado no vacio
* POS: elimina una ocurrencia del nodo raiz
*/
void borrarOcurrencia(NodoABIntDobleDato*& a) {
	if (a->dato2 > 1)
	{
		a->dato2--;
	}
	else
	{
		borrarNodoRaiz(a);
	}
}

/* 
* PRE: Recibe un arbol no vacio
* POS: Elimina una ocurrencia del valor minimo de a
*/
void borrarMinimoABB(NodoABIntDobleDato*& a) {
	if (a && a->izq)
	{
		borrarMinimoABB(a->izq);
		return;
	}
	if (a && !a->izq)
	{
		borrarOcurrencia(a);
	}
}

/*
* PRE: Recibe un arbol ordenado no vacio
* POS: Elimina una ocurrencia del valor maximo de a
*/
void borrarMaximoABB(NodoABIntDobleDato*& a) {
	if (a && a->der)
	{
		borrarMaximoABB(a->der);
		return;
	}
	if (a && !a->der)
	{
		borrarOcurrencia(a);
	}
}

/*
* PRE: recibe un arbol ordenado no vacio
* POS: Devuelve el valor minimo del arbol
*/
int buscarMinimoABB(NodoABIntDobleDato* a) {
	if (a->izq)
	{
		return buscarMinimoABB(a->izq);
	}
	else
	{
		return a->dato1;
	}
}

/*
* PRE: recibe un arbol ordenado no vacio
* POS: Devuelve el valor maximo del arbol
*/
int buscarMaximoABB(NodoABIntDobleDato* a) {
	if (a->der)
	{
		return buscarMaximoABB(a->der);
	}
	else
	{
		return a->dato1;
	}
}

/*
* PRE: Recibe un arbol ordenado no vacio y un elemento perteneciente al mismo
* POS: Elimina una ocurrencia de e en el arbol
*/
void borrarElemABB(NodoABIntDobleDato*& a, int e) {
	if (a->dato1 == e)
	{
		borrarOcurrencia(a);
		return;
	}
	else if (e < a->dato1)
	{
		borrarElemABB(a->izq, e);
	}
	else if (e > a->dato1)
	{
		borrarElemABB(a->der, e);
	}
}

/*
* PRE: recibe un arbol ordenado
* POS: retorna true si y solo si el elemento e existe en el arbol
*/
bool existeElemAB(NodoABIntDobleDato* a, int e) {
	if (a == NULL)
	{
		return false;
	}
	if (a->dato1 == e)
	{
		return true;
	}
	else if(e > a->dato1) 
	{
		existeElemAB(a->der, e);
	} 
	else if (e < a->dato1)
	{
		existeElemAB(a->izq, e);
	}
}

/*
PRE: 
POS: Retorna una copia de a sin compartir memoria
*/
NodoABIntDobleDato* clonAB(NodoABIntDobleDato* a) {
	if (!a)
	{
		return NULL;
	}
	NodoABIntDobleDato* ret = new NodoABIntDobleDato(a->dato1, a->dato2);
	ret->izq = clonAB(a->izq);
	ret->der = clonAB(a->der);
	return ret;
}

/***//***//***//***//***//***//***//***//***/


struct _cabezalListaOrdInt {
	//dato1: dato, dato2: repeticiones
	NodoABIntDobleDato* arbol;
	unsigned int cant;
};

ListaOrdInt crearListaOrdInt() {
	ListaOrdInt nueva = new _cabezalListaOrdInt;
	nueva->cant = 0;
	nueva->arbol = NULL;

	return nueva;
}

void agregar(ListaOrdInt& l, int e) {
	agregarABOrdenado(l->arbol, e);
	l->cant++;
}

void borrarMinimo(ListaOrdInt& l) {
	if (!esVacia(l))
	{
		borrarMinimoABB(l->arbol);
		l->cant--;
	}
	
}

void borrarMaximo(ListaOrdInt& l) {
	if (!esVacia(l))
	{
		borrarMaximoABB(l->arbol);
		l->cant--;
	}
}

void borrar(ListaOrdInt& l, int e) {
	if (existe(l, e))
	{
		borrarElemABB(l->arbol, e);
		l->cant--;
	}
}

int minimo(ListaOrdInt l) {
	assert(!esVacia(l));
	return buscarMinimoABB(l->arbol);
}

int maximo(ListaOrdInt l) {
	assert(!esVacia(l));
	return buscarMaximoABB(l->arbol);
}

bool existe(ListaOrdInt l, int e) {
	return existeElemAB(l->arbol, e);
}

bool esVacia(ListaOrdInt l) {
	return l->arbol == NULL;
}

unsigned int cantidadElementos(ListaOrdInt l) {
	return l->cant;
}

ListaOrdInt clon(ListaOrdInt l) {
	ListaOrdInt clon = crearListaOrdInt();
	clon->arbol = clonAB(l->arbol);
	clon->cant = l->cant;

	return clon;
}

void destruir(ListaOrdInt& l) {
	while (!esVacia(l))
	{
		borrarNodoRaiz(l->arbol);
	}
	delete l;
	l = NULL;
}



#endif