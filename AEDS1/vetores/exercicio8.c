#include <stdlib.h>
#include <stdio.h>

int main () {
    int x[5], y[5], r[10], troca;
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("Digite o valor da posicao %d do vetor X:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
        printf("Digite o valor da posicao %d do vetor Y:\n", cont1 + 1);
        scanf("%d", &y[cont1]);
    }
    for (int cont1 = 0; cont1 < 5; cont1++) {
        for (int cont2 = 0; cont2 < 4; cont2++) {
            if (x[cont2] > x[cont2 + 1]) {
                troca = x[cont2];
                x[cont2] = x[cont2 + 1];
                x[cont2 + 1] = troca;
            }
        }
    }
    printf("\nA ordem crescente do vetor X e:\n");
    for (int cont1 = 0; cont1 < 5; cont1++) printf("%d ", x[cont1]);
    for (int cont1 = 0; cont1 < 5; cont1++) {
        for (int cont2 = 0; cont2 < 4; cont2++) {
            if (y[cont2] > y[cont2 + 1]) {
                troca = y[cont2];
                y[cont2] = y[cont2 + 1];
                y[cont2 + 1] = troca;
            }
        }
    }
    printf("\nA ordem crescente do vetor Y e:\n");
    for (int cont1 = 0; cont1 < 5; cont1++) printf("%d ", y[cont1]);
    for (int cont1 = 0; cont1 < 5; cont1++) {
        r[cont1] = x[cont1];
        r[cont1 + 5] = y[cont1];
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        for (int cont2 = 0; cont2 < 9; cont2++) {
            if (r[cont2] > r[cont2 + 1]) {
                troca = r[cont2];
                r[cont2] = r[cont2 + 1];
                r[cont2 + 1] = troca;
            }
        }
    }
    printf("\nA juncao dos vetores X e Y e:\n");
    for (int cont1 = 0; cont1 < 10; cont1++) printf("%d ", r[cont1]);
}