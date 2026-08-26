#include <stdlib.h>
#include <stdio.h>

void preenche (int *matriz) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) scanf("%d", (matriz + i*10 + j));
    }
}

void linha2PRA8 (int *matriz) {
    for (int i = 0; i < 10; i++) {
        int aux = *(matriz + 1*10 + i);
        *(matriz + 1*10 + i) = *(matriz + 7*10 + i);
        *(matriz + 7*10 + i) = aux;
    }
}

void coluna4PRA10 (int *matriz) {
    for (int i = 0; i < 10; i++) {
        int aux = *(matriz + i*10 + 3);
        *(matriz + i*10 + 3) = *(matriz + i*10 + 9);
        *(matriz + i*10 + 9) = aux;
    }
}

void diagonalPrimRRASec (int *matriz) {
    for (int i = 0; i < 10; i++) {
        int aux = *(matriz + i*10 + i);
        *(matriz + i*10 + i) = *(matriz + i*10 + (9 - i));
        *(matriz + i*10 + (9 - i)) = aux;
    }
}

void linha5PRAcoluna10 (int *matriz) {
    for (int i = 0; i < 10; i++) {
        int aux = *(matriz + 4*10 + i);
        *(matriz + 4*10 + i) = *(matriz + i*10 + 9);
        *(matriz + i*10 + 9) = aux;
    }
}

void exibeMatriz (int *matriz) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) printf("%d ", *(matriz + i*10 + j));
    }
}

int main () {
    int *mat = (int*)malloc(10*10*sizeof(int));
    preenche(mat); linha2PRA8(mat); coluna4PRA10(mat); diagonalPrimRRASec(mat); linha5PRAcoluna10(mat);
    exibeMatriz(mat);
    free(mat);
}