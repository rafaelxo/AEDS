#include <stdlib.h>
#include <stdio.h>

void preenche (int *matriz) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) scanf("%d", (matriz + i*5 + j));
    }
}

int somA (int *matriz) {
    int somA = 0;
    for (int j = 0; j < 5; j++) somA += *(matriz + 3*5 + j);
    return somA;
}

int somB (int *matriz) {
    int somB = 0;
    for (int i = 0; i < 5; i++) somB += *(matriz + i*5 + 1);
    return somB;
}

int somC (int *matriz) {
    int somC = 0;
    for (int i = 0; i < 5; i++) somC += *(matriz + i*5 + i);
    return somC;
}

int somD (int *matriz) {
    int somD = 0;
    for (int i = 0; i < 5; i++) somD += *(matriz + i*5 + (4-i));
    return somD;
}

int somE (int *matriz) {
    int somE = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) somE += *(matriz + i*5 + j);
    }
    return somE;
}

int main () {
    int *M = (int*)malloc(5*5*sizeof(int));
    preenche(M);
    printf("%d\n%d\n%d\n%d\n%d\n", somA(M), somB(M), somC(M), somD(M), somE(M));
    free(M);
}