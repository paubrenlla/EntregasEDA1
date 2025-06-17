#include "EjerciciosComienzo.h"

//AUXILIARES//
/*
PRE: 
POS: retorna el macimo comun divisor entre los 2 numeros n y d
*/
int mcd(int n, int d) {
	int temporal = 0;
	while (d != 0) {
		temporal = d;
		d = n % d;
		n = temporal;
	}
	return n;
}

/*
PRE: recibe un char*
POS: retorna el largo del char*
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
* PRE: recibe dos char* cualesquiera
* POS: si el primero es mayor, retorna True, si el primero es menos, retorna False
*/
bool ordenados(char* str1, char* str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 < *str2) {
			return true;
		}
		else if (*str1 > *str2) {
			return false;
		}
		str1++;
		str2++;
	}
	return (*str1 == '\0');
}

/*
* PRE: recibe un char** cualquiera y su largo
* POS: copia el char** y retorna uno nuevo con los mismos valores
*/
char** copiarStrDeStr(char** str, int largo) {
	char** retorno = new char* [largo];
	int largoSubStr = 0;
	for (int i = 0; i < largo; i++) {
		largoSubStr = largoStr(str[i]) + 1;
		retorno[i] = new char[largoSubStr];

		for (int j = 0; j < largoSubStr; j++) {
			retorno[i][j] = str[i][j];
		}
	}

	return retorno;
}

void interambiar(char*& s1, char*& s2) {
	char* temp = s1;
	s1 = s2;
	s2 = temp;
}

//*****//*****//*****//*****//*****//*****//*****//

int suma(int a, int b) {
    return (a+b);
}

void tablaDel(unsigned int tablaDel, unsigned int desde, unsigned int hasta) {
	for (int i = desde; i <= hasta; i++) {
		cout << i << "*" << tablaDel << "=" << tablaDel * i;
		if (i < hasta) {
			cout << ";";
		}
	}
}

void simplificar(int n, int d) {
	int divisor = mcd(n, d);
	if (divisor != 0) {
		cout << (n / divisor) << "/" << (d / divisor) << endl;
	}
}

int ocurrencias123Repetidos(int* vector, int largo) {
	int contadorReps = 0;
	int contadorReturn = 0;
	for (int i = 0; i < largo; i++) {
		//casos para aumentar el contador de repeticiones
		if (vector[i] == 1 && contadorReps == 0) {
			contadorReps = 1;
		}
		if (vector[i] == 2 && contadorReps == 1) {
			contadorReps = 2;
		}
		if (vector[i] == 3 && contadorReps == 2) {
			contadorReps = 0;
			++contadorReturn;
		}
		//casos para resetear el contador de repeticiones
		if (vector[i] == 1 && contadorReps == 2) {
			contadorReps = 0;
		}
		if (vector[i] == 3 && contadorReps == 0) {
			contadorReps = 0;
		}
	}
	return contadorReturn;
}

int maximoNumero(unsigned int n) {
	int numIngresado = 0;
	int mayorNumero = INT_MIN;
	for (int i = 0; i < n; i++){
		cin >> numIngresado;
		if (numIngresado > mayorNumero) {
			mayorNumero = numIngresado;
		}
	}
    return mayorNumero;
}

void ordenarVecInt(int *vec, int largoVec) {
	for (int i = 1; i < largoVec; i++){
		if (vec[i] < vec[i - 1]) {
			bool bandera = 0;
			int trans = vec[i];
			for (int j = i; j >= 1 && bandera == 0; j--){
				if (vec[j] < vec[j - 1]) {
					vec[j] = vec[j - 1];
					vec[j - 1] = trans;
				}
				else {
					bandera = 1;
				}
			}
		}
	}
}

char* invertirCase(char* str){
	int largo = largoStr(str);
	char* invertido = new char[largo + 1];
	invertido[largo] = '\0';
	for (int i = 0; i < largo; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			invertido[i] = (str[i] - 32);
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			invertido[i] = (str[i] + 32);
		}
		else {
			invertido[i] = str[i];
		}
	}
	return invertido;
}

int islas(char** mapa, int col, int fil){
    return 0;
}

unsigned int ocurrenciasSubstring(char **vecStr, int largoVecStr, char *substr)
{
	// IMPLEMENTAR SOLUCION
    return 0;
}

char **ordenarVecStrings(char **vecStr, int largoVecStr){
	char** retorno = copiarStrDeStr(vecStr, largoVecStr);

	for (int i = 0; i < largoVecStr; i++){
		for (int j = i + 1; j < largoVecStr; j++) {
			if (ordenados(retorno[j], retorno[i])){
				interambiar(retorno[i], retorno[j]);
			}
		}
	}
    return retorno;
}

int* intercalarVector(int* v1, int* v2, int l1, int l2){
	if (!l1 && !l2)
	{
		return NULL;
	}
	int largo = l1+l2;
	int* vIntercalado = new int[largo];
	int v1Dir = 0;
	int v2Dir = 0;
	//recorro y asigno a vIntercalado
	for (int vIntDir = 0; vIntDir < l1+l2; vIntDir++) {
		//v1 y v2 en rango
		if (v1Dir < l1 && v2Dir < l2){
			//comparo y combino
			if (v1[v1Dir] <= v2[v2Dir]) {
				vIntercalado[vIntDir] = v1[v1Dir];
				v1Dir++;
			}
			else {
				vIntercalado[vIntDir] = v2[v2Dir];
				v2Dir++;
			}
		}
		//solo v1 en rango
		else if (v1Dir < l1) {
			vIntercalado[vIntDir] = v1[v1Dir];
			v1Dir++;
		}
		//solo v2 en rango
		else{
			vIntercalado[vIntDir] = v2[v2Dir];
			v2Dir++;
		}
	}
	return vIntercalado;
}

bool subconjuntoVector(int* v1, int* v2, int l1, int l2){
	bool encontre = true;
	for (int i = 0; i < l1 && encontre; i++){
		int buscar = v1[i];
		encontre = false;
		for (int j = 0; j < l2 && !encontre; j++){
			if (v1[i] == v2[j]){
				encontre = true;
			}
		}
	}
	if (!encontre){
		return false;
	} else {
		return encontre;
	}
}

char** splitStr(char* str, char separador, int &largoRet)
{
	// IMPLEMENTAR SOLUCION
	//largoRet =...;
	return NULL;
}

void ordenarVecIntMergeSort(int* vector, int largo) 
{
	// IMPLEMENTAR SOLUCION
}
