#include <stdlib.h>
#include <stdio.h>

void preenche (int *mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) scanf("%d", (mat + i*6 + j));
    }
}

void mostra (int *mat) {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 6; j++) printf("%d ", *(mat + i*6 + j));
    }
}

int *somaAB (int *mat1, int *mat2) {
    int *S = (int*)malloc(4*6*sizeof(int));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) *(S + i*6 + j) = *(mat1 + i*6 + j) + *(mat2 + i*6 + j);
    }
    return S;
}

int *diferencaAB (int *mat1, int *mat2) {
    int *D = (int*)malloc(4*6*sizeof(int));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) *(D + i*6 + j) = *(mat1 + i*6 + j) - *(mat2 + i*6 + j);
    }
    return D;
}

int main () {
    int *A = (int*)malloc(4*6*sizeof(int)); preenche(A);
    int *B = (int*)malloc(4*6*sizeof(int)); preenche(B);
    int *S = somaAB(A, B); mostra(S);
    int *D = diferencaAB(A, B); mostra(D);
    free (A); free(B); free(S); free(D);
}