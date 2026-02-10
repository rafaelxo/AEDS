#include <stdlib.h>
#include <stdio.h>

int main () {
    int M[10][20], soma[10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) scanf("%d", &M[i][j]);
    }
    printf("Soma das linhas:\n");
    for (int i = 0; i < 10; i++) {
        soma[i] = 0;
        for (int j = 0; j < 20; j++) {
            soma[i] += M[i][j];
            printf("Soma linha %d: %d\n", i + 1, soma);
        }
    }
    printf("\nMatriz multiplicada:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            M[i][j] *= soma[i];
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}