#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TAM 100

int array[MAX_TAM];
int n = 0;

void inserir (int x) {
    if (n >= MAX_TAM) exit(1);
    array[n++] = x;
}

int remover () {
    if (n == 0) exit(1);
    return array[--n];
}

bool vazia () { return n == 0; }

int topo () {
    if (n == 0) exit(1);
    return array[n - 1];
}

int *impPar () {
    int pares = 0, impares = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] % 2 == 0) pares++;
        else impares++;
    }
    int *resultado = (int*)malloc(2*sizeof(int));
    resultado[0] = pares;
    resultado[1] = impares;
    return resultado;
}

void mostrar () {
    printf("[ ");
    for (int i = n - 1; i >= 0; i--) printf("%d ", array[i]);
    printf("]\n");
}
void mostrarRec (int i) {
    if (i == n) printf("[ ");
    if (i < n) {
        printf("%d ", array[n - 1 - i]);
        mostrarRec(i + 1);
    }
    else printf("]\n");
}
void mostrarInv () {
    printf("[ ");
    for (int i = 0; i < n; i++) printf("%d ", array[i]);
    printf("]\n");
}
