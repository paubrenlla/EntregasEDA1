#include "Ejercicios.h"

//AUXILIARES//
/*
* PRE: puntero a un ABB de tipo NodoABInt y una ListaOrdInt por parametro
* POS: agrega todos los elementos del arbol a la lista
*/
void Enlistar(NodoABInt* a, ListaOrdInt& l) 
{
	if (!a)
	{
		return;
	}
	agregar(l, a->dato);
	Enlistar(a->der, l);
	Enlistar(a->izq, l);
}

/*
* PRE: recibe dos PilaInt
* POS: mueve todos los elementos de la segunda pila a la primera, vaciandola
*/
void fusionarPilas(PilaInt& p1, PilaInt& p2) {
	while (!esVacia(p2))
	{
		int dato1 = top(p2);
		pop(p2);
		push(p1, dato1);
	}
}

/* 
PRE: 
POS: Retorna la cantidad de elementos con prioridad p en c
*/
int cantPrio(ColaPrioridadInt c, int p) {
	ColaPrioridadInt aux = clon(c);

	while (principioPrioridad(aux) > p)
	{
		desencolar(aux);
	}

	return cantidadElementos(aux);
}

/////////////////////////////////////////////////////////

ListaOrdInt Enlistar(NodoABInt* a)
{
	ListaOrdInt l = crearListaOrdInt();
	Enlistar(a, l);
	return l;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	ListaOrdInt l = clon(l1);
	ListaOrdInt copial2 = clon(l2);

	while (!esVacia(copial2))
	{
		agregar(l, minimo(copial2));
		borrarMinimo(copial2);
	}

	destruir(copial2);
	copial2 = NULL;

	return l;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	if (esVacia(p1) || esVacia(p2))
	{
		return esVacia(p1);
	}

	PilaInt p1Clon = clon(p1);

	PilaInt p2Clon = clon(p2);
	PilaInt p2Aux = crearPilaInt();

	while (!esVacia(p1Clon) && !esVacia(p2Clon))
	{
		int datoP1 = top(p1Clon);
		int datoP2 = top(p2Clon);

		if (datoP1 == datoP2)
		{
			pop(p1Clon);
			pop(p2Clon);
		}
		else 
		{
			bool salir = false;
			while (!esVacia(p2Clon) && !salir)
			{
				datoP2 = top(p2Clon);
				if (datoP1 == datoP2)
				{
					salir = true;
					pop(p1Clon);
					pop(p2Clon);
					fusionarPilas(p2Clon, p2Aux);
				}
				else 
				{
					pop(p2Clon);
					push(p2Aux, datoP2);
				}				
			}
			if (!salir)
			{
				return false;
			}
		}

	}
	bool retorno = esVacia(p1Clon);
	destruir(p1Clon);
	destruir(p2Clon);
	destruir(p2Aux);

	return retorno;
}

ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	ListaOrdInt retorno = crearListaOrdInt();
	MultisetInt clonM = clon(m);

	while (!esVacio(clonM))
	{
		int e = elemento(clonM);
		borrar(clonM, e);
		if (pertenece(clonM, e))
		{
			while (pertenece(clonM, e))
			{
				borrar(clonM, e);
			}
			agregar(retorno, e);
		}
	}

	destruir(clonM);
	return retorno;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt retorno = unionConjuntos(diferenciaConjuntos(m1, m2), diferenciaConjuntos(m2, m1));
	return retorno;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	if (!esVacia(c)) {
		ColaPrioridadInt copia = clon(c);

		int p = principioPrioridad(copia);

		while (!esVacia(copia))
		{
			p = principioPrioridad(copia);
			desencolar(copia);
		}
		destruir(copia);

		int largo = cantPrio(c, p);

		ColaPrioridadInt retorno = crearColaPrioridadInt(largo);

		ColaPrioridadInt aux = clon(c);
		
		while (p < principioPrioridad(aux)) desencolar(aux);
		
		while (!esVacia(aux)) {
			encolar(retorno, principio(aux), principioPrioridad(aux));
			desencolar(aux);
		}
		destruir(aux);

		return retorno;
	}
	return crearColaPrioridadInt(0);
}