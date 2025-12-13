#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TAM 100

int array[MAX_TAM];
int n = 0;

void inserirIni (int x) {
    if (n >= MAX_TAM) exit(1);
    for (int i = n; i > 0; i--) array[i] = array[i-1];
    array[0] = x;
    n++;
}
void inserirPos (int x, int pos) {
    if (n >= MAX_TAM || pos < 0 || pos > n) exit(1);
    for (int i = n; i > pos; i--) array[i] = array[i-1];
    array[pos] = x;
    n++;
}
void inserirFim (int x) {
    if (n >= MAX_TAM) exit(1);
    array[n++] = x;
}

void inserirOrd (int x) {
    if (n >= MAX_TAM) exit(1);
    int i = n - 1;
    while (i >= 0 && array[i] > x) {
        array[i + 1] = array[i];
        i--;
    }
    array[i + 1] = x;
    n++;
}

int removerIni () {
    if (n == 0) exit(1);
    int resp = array[0];
    n--;
    for (int i = 0; i < n; i++) array[i] = array[i+1];
    return resp;
}
int removerPos (int pos) {
    if (n == 0 || pos < 0 || pos >= n) exit(1);
    int resp = array[pos];
    n--;
    for (int i = pos; i < n; i++) array[i] = array[i+1];
    return resp;
}
int removerFim () {
    if (n == 0) exit(1);
    return array[--n];
}

bool vazia () { return n == 0; }

bool pesquisarElem (int x) {
    for (int i = 0; i < n; i++) {
        if (array[i] == x) return true;
    }
    return false;
}

bool pesquisarPos (int pos) {
    for (int i = 0; i < n; i++) {
        if (array[i] == array[pos]) return true;
    }
    return false;
}

int impPar () {
    int pares = 0, impares = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] % 2 == 0) pares++;
        else impares++;
    }
    int result[2];
    result[0] = pares; result[1] = impares;
    return result;
}

bool palindromo () {
    int i = 0, j = n - 1;
    while (i <= j) {
        if (array[i] != array[j]) return false;
        i++; j--;
    }
    return true;
}

void mostrar () {
    printf("[ ");
    for (int i = 0; i < n; i++) printf("%d ", array[i]);
    printf("]\n");
}
void mostrarRec (int i) {
    if (i == 0) printf("[ ");
    if (i < n) {
        printf("%d ", array[i]);
        mostrarRec(i + 1);
    } else printf("]\n");
}
void mostrarInv () {
    printf("[ ");
    for (int i = n - 1; i >= 0; i--) printf("%d ", array[i]);
    printf("]\n");
}
