#include "TablaIntString.h"

#ifdef TABLA_INT_STRING_IMP

const double DELTA = 0.6;

struct NodoListaIntString {
	int dominio;
	const char* elemento;
	NodoListaIntString* sig;
	NodoListaIntString() : dominio(0), elemento(NULL), sig(NULL) {}
	NodoListaIntString(int d, const char* e) : dominio(d), elemento(e), sig(NULL) {}
	NodoListaIntString(int d, const char* e, NodoListaIntString* sig) : dominio(d), elemento(e), sig(sig) {}
};

//Auxiliares
/*
* PRE: recibe los buckets de un diccionario y un elemento
* POS: le aplica la funcion de hash y retorna el valor
*/
int getIndice(int celdas, int e)
{
	int eAbs = e;
	if (e < 0)
	{
		eAbs = e * -1;
	}
	return eAbs % celdas;
}

/*
* PRE: 
* POS: 
*/
void borrarDeLista(NodoListaIntString*& l, int d) {
	if (l != NULL) {
		if (l->dominio == d) {
			NodoListaIntString* aux = l;
			l = l->sig;
			delete aux;
		}
		else borrarDeLista(l->sig, d);
	}
}

/* 
PRE: 
POS: Borra y destruye la lista de la memoria
*/
void destruirLista(NodoListaIntString*& l) {
	if (l) 
	{
		destruirLista(l->sig);
		delete l;
		l = NULL;
	}
}

/*
PRE: recibe un char*
POS: retorna su largo
*/
int largoStr(char* str) {
	unsigned int largo = 0;
	while (*str != '\0') {
		largo++;
		str++;
	}
	return largo;
}

/*
* PRE:
* POS: retorna un string igual al recibido y sin modificarlo ni compartir memoria
*/
char* clonString(char* str) {
	if (str == NULL)
	{
		return NULL;
	}

	int largoSubStr = largoStr(str) + 1;
	char* retorno = new char[largoSubStr];

	for (int i = 0; i < largoSubStr; i++) {
		retorno[i] = str[i];
	}
}

/* 
PRE: 
POS: Retorna una copia de l sin compartir memoria
*/
NodoListaIntString* clonListaString(NodoListaIntString* l) {
	if (!l)
	{
		return NULL;
	}

	const char* c = (const char*) clonString((char*) l->elemento);
	NodoListaIntString* clon = new NodoListaIntString(l->dominio, c);
	clon->sig = clonListaString(l->sig);
	
	return clon;
}

/////////////////////////////////////

struct _cabezalTablaIntString {
	NodoListaIntString** tabla;
	int celdas;
	int cant;
};

TablaIntString crearTablaIntString(unsigned int esperados) {
	TablaIntString nuevo = new _cabezalTablaIntString;
	nuevo->cant = 0;
	nuevo->celdas = esperados / DELTA;
	nuevo->tabla = new NodoListaIntString* [nuevo->celdas];

	for (int i = 0; i < nuevo->celdas; i++)
	{
		nuevo->tabla[i] = NULL;
	}

	return nuevo;
}


void agregar(TablaIntString& t, int d, const char* r) {
	int index = getIndice(t->celdas, d);

	NodoListaIntString* aux = t->tabla[index];

	while (aux && aux->dominio != d)
	{
		aux = aux->sig;
	}
	if (!aux) 
	{
		NodoListaIntString* nuevo = new NodoListaIntString(d, r, t->tabla[index]);
		t->tabla[index] = nuevo;
		t->cant++;
	}
	else aux->elemento = r;
}

bool estaDefinida(TablaIntString t, int d) {
	int index = getIndice(t->celdas, d);

	NodoListaIntString* aux = t->tabla[index];
	while (aux != NULL && aux->dominio != d)
	{
		aux = aux->sig;
	}
	return aux != NULL;
}

const char* recuperar(TablaIntString t, int d) {
	assert(estaDefinida(t, d));

	int index = getIndice(t->celdas, d);

	NodoListaIntString* aux = t->tabla[index];
	while (aux->dominio != d)
	{
		aux = aux->sig;
	}
	return (const char*) aux->elemento;
}

void borrar(TablaIntString& t, int d) {
	if (estaDefinida(t, d)) {
		int index = getIndice(t->celdas, d);
		borrarDeLista(t->tabla[index], d);
		t->cant--;
	}
}

int elemento(TablaIntString t) {
	assert (!esVacia(t));

	int contador = 0;

	while (contador < t->celdas && !t->tabla[contador])
	{
		contador++;
	}
	if (contador < t->celdas)
	{
		return t->tabla[contador]->dominio;
	}
}

bool esVacia(TablaIntString t) {
	return t->cant == 0;
}

unsigned int cantidadElementos(TablaIntString t) {
	return t->cant;
}

void destruir(TablaIntString& t) {
	if (!esVacia(t)) {
		for (int i = 0; i < t->celdas; i++)
		{
			destruirLista(t->tabla[i]);
		}
		delete[] t->tabla;
		delete t;
		t = NULL;
	}
}

TablaIntString clon(TablaIntString t) {
	TablaIntString clon = crearTablaIntString(t->celdas);
	for (int i = 0; i < t->celdas; i++)
	{
		clon->tabla[i] = clonListaString(t->tabla[i]);
	}
	clon->cant = t->cant;
	return clon;
}

#endif