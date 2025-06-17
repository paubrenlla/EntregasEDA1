#include "EjerciciosListas.h"

//Funciones auxiliares//
void agregarAlPrincipio(NodoLista*& l, int dato) {
	NodoLista* nuevo = new NodoLista;
	nuevo->dato = dato;
	nuevo->sig = l;
	l = nuevo;
}

void intercambiar(int& n1, int& n2) {
	int temp = n1;
	n1 = n2;
	n2 = temp;
}

void insertarOrdMenorAMayor(NodoLista*& l, int dato) {
	if (!l || l->dato > dato) {
		agregarAlPrincipio(l, dato);
	}
	else {
		NodoLista* aux = l;
		while (aux->sig && aux->sig->dato < dato) {
			aux = aux->sig;
		}
		agregarAlPrincipio(aux->sig, dato);
	}
}

void borrarAlPrinicio(NodoLista*& l) {
	if (!l) {
		return;
	}
	else {
		NodoLista* borro = l;
		l = l->sig;
		delete borro;
		borro = NULL;
	}
}

bool esSec(NodoLista* l, NodoLista* sec) {
	if (!sec)
	{
		return true;
	}
	if (!l)
	{
		return false;
	} if (sec->dato != l->dato)
	{
		return false;
	}
	return esSec(l->sig, sec->sig);
}

void borrarSec(NodoLista*& l, NodoLista* sec) {
	while (sec)
	{
		borrarAlPrinicio(l);
		sec = sec->sig;
	}
}

//*****//*****//*****//*****//*****//*****//*****//

NodoLista* invertirParcial(NodoLista* l) {
	NodoLista* retorno = NULL;
	while (l->sig) {
		agregarAlPrincipio(retorno, l->dato);
		l = l->sig;
	}
	return retorno;
}

void eliminarNesimoDesdeElFinal(NodoLista*& lista, int& n) {
	if (!lista) {
		return;
	}
	else {
		eliminarNesimoDesdeElFinal(lista->sig, n);
		n = n - 1;
		if (n == 0) {
			NodoLista* borrar = lista;
			lista = borrar->sig;
			delete borrar;
			borrar = NULL;
		}
	}
}

NodoLista* listaOrdenadaInsertionSort(NodoLista* l) {
	NodoLista* retorno = NULL;
	NodoLista* aux = l;
	while (aux) {
		insertarOrdMenorAMayor(retorno, aux->dato);
		aux = aux->sig;
	}
	return retorno;
}

void listaOrdenadaSelectionSort(NodoLista*& l) {
	if (!l || !l->sig) {
		return;
	}
	NodoLista* aux = l;
	while (aux) {
		NodoLista* auxSig = aux->sig;
		NodoLista* min = NULL;
		while (auxSig) {
			if (!min && (aux->dato > auxSig->dato)) {
				min = auxSig;
			}
			else if (min && (min->dato > auxSig->dato)) {
				min = auxSig;
			}
			auxSig = auxSig->sig;
		}
		if (min) {
			intercambiar(min->dato, aux->dato);
		}
		aux = aux->sig;
	}
}

NodoLista* intercalarIter(NodoLista* l1, NodoLista* l2) {
	NodoLista* retorno = new NodoLista;
	NodoLista* actual = retorno;

	while (l1 && l2) {
		if (l1->dato < l2->dato) {
			actual->sig = new NodoLista(l1->dato);
			l1 = l1->sig;
		}
		else {
			actual->sig = new NodoLista(l2->dato);
			l2 = l2->sig;
		}
		actual = actual->sig;
	}
	while (l1) {
		actual->sig = new NodoLista(l1->dato);
		l1 = l1->sig;
		actual = actual->sig;
	}
	while (l2) {
		actual->sig = new NodoLista(l2->dato);
		l2 = l2->sig;
		actual = actual->sig;
	}
	borrarAlPrinicio(retorno);
	return retorno;
}

NodoLista* intercalarRec(NodoLista* l1, NodoLista* l2) {
	if (!l1 && !l2) {
		return NULL;
	}

	NodoLista* retorno = new NodoLista;
	retorno->sig = NULL;

	if (!l1) {
		retorno->dato = l2->dato;
		retorno->sig = intercalarRec(l1, l2->sig);
	}
	else if (!l2) {
		retorno->dato = l1->dato;
		retorno->sig = intercalarRec(l1->sig, l2);
	}
	else {
		if (l1->dato < l2->dato) {
			retorno->dato = l1->dato;
			retorno->sig = intercalarRec(l1->sig, l2);
		}
		else {
			retorno->dato = l2->dato;
			retorno->sig = intercalarRec(l1, l2->sig);
		}
	}
	return retorno;
}

NodoLista* insComFin(NodoLista* l, int x)
{
	// IMPLEMENTAR SOLUCION
	return NULL;
}

NodoLista* exor(NodoLista* l1, NodoLista* l2) {
	NodoLista* retorno = NULL;
	NodoLista* aux = retorno;
	while (l1 || l2)
	{
		if (l1)
		{
			if (l2)
			{
				if (l1->dato < l2->dato)
				{
					if (!retorno)
					{
						retorno = new NodoLista(l1->dato);
						aux = retorno;
					}
					else if (aux->dato != l1->dato)
					{
						aux->sig = new NodoLista(l1->dato);
						aux = aux->sig;
					}
					l1 = l1->sig;
				}
				else if (l2->dato < l1->dato)
				{
					if (!retorno)
					{
						retorno = new NodoLista(l2->dato);
						aux = retorno;
					}
					else if (aux->dato != l2->dato)
					{
						aux->sig = new NodoLista(l2->dato);
						aux = aux->sig;
					}
					l2 = l2->sig;
				}
				else {
					int datoRep = l1->dato;
					while (l1 && l1->dato == datoRep)
					{
						l1 = l1->sig;
					}
					while (l2 && l2->dato == datoRep)
					{
						l2 = l2->sig;
					}
				}
			}
			else {
				if (!retorno)
				{
					retorno = new NodoLista(l1->dato);
					aux = retorno;
				}
				else if (aux->dato != l1->dato)
				{
					aux->sig = new NodoLista(l1->dato);
					aux = aux->sig;
				}
				l1 = l1->sig;
			}
		}
		else {
			if (!retorno)
			{
				retorno = new NodoLista(l2->dato);
				aux = retorno;
			}
			else if (aux->dato != l2->dato)
			{
				aux->sig = new NodoLista(l2->dato);
				aux = aux->sig;
			}
			l2 = l2->sig;
		}
	}

	return retorno;
}

void eliminarDuplicadosListaOrdenadaDos(NodoLista*& l) {
	if (!l) {
		return;
	}
	if (!l->sig) {
		return;
	}
	if (l->dato == l->sig->dato) {
		int borrar = l->dato;
		while (l && l->dato == borrar)
		{
			borrarAlPrinicio(l);
		}
		eliminarDuplicadosListaOrdenadaDos(l);
	}
	else {
		eliminarDuplicadosListaOrdenadaDos(l->sig);
	}

}

bool palindromo(NodoLista* l)
{
	// IMPLEMENTAR SOLUCION
	return false;
}

void eliminarSecuencia(NodoLista*& l, NodoLista* secuencia) {
	if (!l || !secuencia)
	{
		return;
	}
	if (l->dato != secuencia->dato)
	{
		eliminarSecuencia(l->sig, secuencia);
	}
	if (esSec(l, secuencia))
	{
		borrarSec(l, secuencia);
		return;
	}
	else
	{
		eliminarSecuencia(l->sig, secuencia);
	}
}

void moverNodo(NodoLista*& lista, unsigned int inicial, unsigned int final)
{
	// IMPLEMENTAR SOLUCION
}
