#include "MultisetInt.h"
#include "Definiciones.h"

#ifdef MULTISET_INT_IMP

//Auxiliares//
/* 
* PRE: 
* POS: Retorna true si existe el dato e en la lista l
*/
bool perteneceLista(NodoListaIntDobleDato* l, int e) {
	while (l != NULL && l->dato1 != e)
	{
		l = l->sig;
	}
	return l != NULL;
}

/*
* PRE: 
* POS: inserta el elemento
*/
void agregarAlPrincipio(NodoListaIntDobleDato*& l, int e, int ocurrencias) {
	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato(e, ocurrencias);
	nuevo->sig = l;
	l = nuevo;
}

/*
* PRE:
* POS: Agrega el elemento e a la lista con sus ocurrencias como segundo dato.
*		La insercion se realiza ordenada.
*/
void insertarOrdenado(NodoListaIntDobleDato*& l, int e, int ocurrencias) {
	if (!l || l->dato1 > e)
	{
		agregarAlPrincipio(l, e, ocurrencias);
	}
	else if (l->dato1 == e)
	{
		l->dato2 = l->dato2 + ocurrencias;
	}
	else 
	{
		insertarOrdenado(l->sig, e, ocurrencias);
	}
}

/*
* PRE: el elemento e existe en la lista recibida
* POS: Borra una ocurrencia de e en l
*/
void borrarOcurrenciaLista(NodoListaIntDobleDato*& l, int e) {
	if (l->dato1 == e) 
	{
		if (l->dato2 == 1) 
		{
			NodoListaIntDobleDato* borrar = l;
			l = l->sig;
			delete borrar;
			return;
		}
		l->dato2--;
		return;
	}
	borrarOcurrenciaLista(l->sig, e);
}

/*
* PRE: el elemento e existe en la lista recibida
* POS: Borra todas las ocurrencias de e en l y devuelve la cantidad
*/
int borrarElementoLista(NodoListaIntDobleDato*& l, int e) {
	if (l->dato1 == e) {
		NodoListaIntDobleDato* borrar = l;
		int retorno = l->dato2;
		l = l->sig;
		delete borrar;
		return retorno;
	}
	else borrarElementoLista(l->sig, e);
}

/*
* PRE: 
* POS: Borra y destruye la lista de la memoria
*/
void destruirLista(NodoListaIntDobleDato*& l) {
	if (l) {
		destruirLista(l->sig);
		delete l;
		l = NULL;
	}
}

/*
* PRE: 
* POS: retorna el dato mas grande
*/
int maximo(int a, int b) 
{
	if (a > b)
	{
		return a;
	}
	return b;
}

/*
* PRE:
* POS: retorna el dato mas chico
*/
int minimo(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

/*
* PRE:
* POS: hace la resta a - b, si es negativa, retorna 0, de lo contrario su valor
*/
int restaTope(int a, int b)
{
	if (a - b <= 0)
	{
		return 0;
	}
	else a - b;
}

/*
* PRE: el elemento e pertenece a la lista
* POS: si las ocurrencias actuales son mayores a las recibidas, las mantiene, de lo contrario
*		las intercambia.
*/
void elegirMayorCantOcurrencias(NodoListaIntDobleDato* l, int e, int ocurrencia) 
{
	while (l && l->dato1 != e)
	{
		l = l->sig;
	}
	l->dato2 = maximo(l->dato2, ocurrencia);
}

/*
* PRE:
* POS: retorna la cantidad de elementos que tiene la lista (con ocurrencias)
*/
int cantElemLista(NodoListaIntDobleDato* l) 
{
	int cant = 0;
	while (l != NULL)
	{
		cant = cant + l->dato2;
		l = l->sig;
	}
	return cant;
}

/*
* PRE: el elemento e existe en la lista
* POS: retorna la cantidad de ocurrencias de un elemento
*/
int ocurrenciasLista(NodoListaIntDobleDato* l, int e) 
{
	while (l->dato1 != e)
	{
		l = l->sig;
	}
	return l->dato2;
}
///////////////////////////////


struct _cabezalMultisetInt {
	//dato1: dato, dato2: repeticiones
	NodoListaIntDobleDato* lista;
	unsigned int cant;
};

MultisetInt crearMultisetInt() {
	MultisetInt nueva = new _cabezalMultisetInt;
	nueva->cant = 0;
	nueva->lista = NULL;

	return nueva;
}

void agregar(MultisetInt& s, int e, unsigned int ocurrencias){
	if (ocurrencias > 0)
	{
		insertarOrdenado(s->lista, e, ocurrencias);
		s->cant = s->cant + ocurrencias;
	}
}

void borrar(MultisetInt& s, int e) {
	if (pertenece(s, e))
	{
		borrarOcurrenciaLista(s->lista, e);
		s->cant--;
	}
}

bool pertenece(MultisetInt s, int e) {
	return perteneceLista(s->lista, e);
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt retorno = clon(s1);
	NodoListaIntDobleDato* aux = s2->lista;
	
	while (aux != NULL)
	{
		if (!pertenece(retorno, aux->dato1))
		{
			agregar(retorno, aux->dato1, aux->dato2);
		}
		else 
		{
			elegirMayorCantOcurrencias(retorno->lista, aux->dato1, aux->dato2);
		}
		aux = aux->sig;
	}
	retorno->cant = cantElemLista(retorno->lista);
	return retorno;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt retorno = crearMultisetInt();
	MultisetInt clonS1 = clon(s1);

	while (!esVacio(clonS1))
	{
		int e = elemento(clonS1);
		
		int ocurrenciasS1 = borrarElementoLista(clonS1->lista, e);
		clonS1->cant -= ocurrenciasS1;
		
		if (pertenece(s2, e))
		{
			int ocurrenciasS2 = ocurrenciasLista(s2->lista, e);
			int min = minimo(ocurrenciasS2, ocurrenciasS1);
			agregar(retorno, e, min);
		}
	}
	destruir(clonS1);

	return retorno;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt retorno = crearMultisetInt();
	MultisetInt clonS1 = clon(s1);

	while (!esVacio(clonS1))
	{
		int e = elemento(clonS1);

		int ocurrenciasS1 = borrarElementoLista(clonS1->lista, e);
		clonS1->cant -= ocurrenciasS1;

		if (pertenece(s2, e))
		{
			int ocurrenciasS2 = ocurrenciasLista(s2->lista, e);
			int resta = restaTope(ocurrenciasS1, ocurrenciasS2);
			agregar(retorno, e, resta);
		}
		else 
		{
			agregar(retorno, e, ocurrenciasS1);
		}
	}
	destruir(clonS1);

	return retorno;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	return esVacio(diferenciaConjuntos(s1, s2));
}

int elemento(MultisetInt s) {
	assert(!esVacio(s));
	return s->lista->dato1;
}

bool esVacio(MultisetInt s) {
	return s->lista == NULL;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s->cant;
}

void destruir(MultisetInt& s) {
	destruirLista(s->lista);
	delete s->lista;
	delete s;
	s = NULL;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt clon = crearMultisetInt();
	NodoListaIntDobleDato* aux = s->lista;
	while (aux != NULL)
	{
		insertarOrdenado(clon->lista, aux->dato1, aux->dato2); 
		aux = aux->sig;
	}
	clon->cant = s->cant;

	return clon;
}

#endif