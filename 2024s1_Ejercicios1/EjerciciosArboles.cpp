#include "EjerciciosArboles.h"

//FUNCIONES AUXILIARES//

bool sumaCamino(NodoAB* r, int suma, int cont) {
	if (!r->der && !r->izq)
	{
		return (cont + r->dato) == suma;
	}
	if (!r->der)
	{
		return sumaCamino(r->izq, suma, cont + r->dato);
	}
	if (!r->izq)
	{
		return sumaCamino(r->der, suma, cont + r->dato);
	}
	return sumaCamino(r->izq, suma, cont + r->dato) || sumaCamino(r->der, suma, cont + r->dato);
}

int maxMin(NodoAB*& r) {
	if (!r->der)
	{
		int dato = r->dato;
		if (!r->izq)
		{
			delete r;
			r = NULL;
		}
		else {
			NodoAB* borro = r;
			r = r->izq;
			delete borro;
			borro = NULL;
		}
		return dato;
	}
	return maxMin(r->der);
}

int maxNum(int a, int b) {
	if (a > b)
	{
		return a;
	}
	else {
		return b;
	}
}

int valorAbsoluto(int numero) {
	if (numero < 0)
	{
		return numero * -1;
	}
	return numero;
}

void buscarSucesor(NodoAB* a, int n, int& x) {
	if (!a)
	{
		return;
	}
	if (a->dato > n) {
		x = a->dato;
		buscarSucesor(a->izq, n, x);
	}
	else {
		buscarSucesor(a->der, n, x);
	}
}

void nodosPorNivel(NodoAB* r, int nivelHasta, int*& arr, int nivelActual) {
	if (r != NULL && nivelActual <= nivelHasta) {
		arr[nivelActual] += 1;
		nodosPorNivel(r->izq, nivelHasta, arr, nivelActual + 1);
		nodosPorNivel(r->der, nivelHasta, arr, nivelActual + 1);
	}
}

//*****//*****//*****//*****//*****//*****//

int altura(NodoAB* raiz) {
	if (!raiz)
	{
		return 0;
	}
	return 1 + maxNum(altura(raiz->izq), altura(raiz->der));
}

bool sonIguales(NodoAB* p, NodoAB* q) {
	if (!p && !q)
	{
		return true;
	}
	if (!p || !q)
	{
		return false;
	}

	return (p->dato == q->dato) && sonIguales(p->izq, q->izq) && sonIguales(p->der, q->der);
}

bool existeCaminoConSuma(NodoAB* raiz, int sum) {
	if (!raiz)
	{
		return sum == 0;
	}

	return sumaCamino(raiz, sum, 0);
}

bool esArbolBalanceado(NodoAB* raiz) {
	if (!raiz)
	{
		return true;
	} if (valorAbsoluto(altura(raiz->izq) - altura(raiz->der)) > 1)
	{
		return false;
	}
	return esArbolBalanceado(raiz->izq) && esArbolBalanceado(raiz->der);
}

NodoLista* enNivel(NodoAB* a, int k) {
	// IMPLEMENTAR SOLUCION
	return NULL;
}

int cantNodosEntreNiveles(NodoAB* a, int desde, int hasta) {
	// IMPLEMENTAR SOLUCION
	return 0;
}

NodoLista* camino(NodoAB* arbol, int x) {
	NodoLista* l = new NodoLista(arbol->dato);
	NodoLista* aux = l;
	while (arbol->dato != x)
	{
		if (arbol->dato > x)
		{
			aux->sig = new NodoLista(arbol->izq->dato);
			aux = aux->sig;
			arbol = arbol->izq;
		}
		if (arbol->dato < x) 
		{
			aux->sig = new NodoLista(arbol->der->dato);
			aux = aux->sig;
			arbol = arbol->der;
		}
	}

	return l;
}

NodoAB* invertirHastak(NodoAB* a, int k) {
	// IMPLEMENTAR SOLUCION
	return NULL;
}

void borrarNodoRaiz(NodoAB*& A) {
	if (!A->der && !A->izq)
	{
		delete A;
		A = NULL;
		return;
	}
	if (!A->der)
	{
		NodoAB* borro = A;
		A = A->izq;
		delete borro;
		return;
	}
	if (!A->izq)
	{
		NodoAB* borro = A;
		A = A->der;
		delete borro;
		return;
	}
	A->dato = maxMin(A->izq);
}

bool sumaABB(NodoAB* a, int n)
{
	// IMPLEMENTAR SOLUCION
	return false;
}

int sucesor(NodoAB* a, int n)
{
	int x = -1;
	buscarSucesor(a, n, x);
	return x;
}

int nivelMasNodos(NodoAB* raiz, int nivelHasta) {
	if (!raiz || nivelHasta == 0)
	{
		return 0;
	}

	int* valores = new int[nivelHasta + 1];
	valores[0] = 0;
	for (int i = 1; i < nivelHasta + 1; i++)
	{
		valores[i] = 0;
	}

	nodosPorNivel(raiz, nivelHasta, valores, 1);
	int nivel = 0;
	int cantidadDeNodos = 0;
	for (int i = 1; i < nivelHasta + 1; i++)
	{
		if (valores[i] > cantidadDeNodos)
		{
			nivel = i;
			cantidadDeNodos = valores[i];
		}
	}

	return nivel;
}

void borrarPares(NodoAB*& a) {
	// IMPLEMENTAR SOLUCION
}

int alturaAG(NodoAG* raiz)
{
	// IMPLEMENTAR SOLUCION
	return 0;
}

int sumaPorNiveles(NodoAG* raiz) {
	// IMPLEMENTAR SOLUCION
	return 0;
}

bool esPrefijo(NodoAG* a, NodoLista* l)
{
	// IMPLEMENTAR SOLUCION
	return false;
}

NodoLista* caminoAG(NodoAG* arbolGeneral, int dato) {
	// IMPLEMENTAR SOLUCION
	return NULL;
}

int nivelConMasNodosAG(NodoAG* arbolGeneral) {
	// IMPLEMENTAR SOLUCION
	return 0;
}
