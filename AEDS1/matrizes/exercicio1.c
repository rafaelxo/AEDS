#include <stdlib.h>
#include <stdio.h>

int main () {
    int M[2][2], R[2][2], maior;
    for (int cont1 = 0; cont1 < 2; cont1++) {
        for (int cont2 = 0; cont2 < 2; cont2++) {
            printf("Preencha o elemento da coluna %d da linha %d da matriz 2x2:\n", cont2 + 1, cont1 + 1);
            scanf("%d", &M[cont1][cont2]);
        }
    }
    maior = M[0][0];
    for (int cont1 = 0; cont1 < 2; cont1++) {
        for (int cont2 = 0; cont2 < 2; cont2++) {
            if (M[cont1][cont2] > maior) maior = M[cont1][cont2];
        }
    }
    for (int cont1 = 0; cont1 < 2; cont1++) {
        for (int cont2 = 0; cont2 < 2; cont2++) R[cont1][cont2] = maior * M[cont1][cont2];
    }
    printf("\nO maior elemento da matriz e:\n%d\n", maior);
    printf("\nO resultado da multiplicacao da matriz pelo seu maior elemento e:\n");
    for (int cont1 = 0; cont1 < 2; cont1++) {
        for (int cont2 = 0; cont2 < 2; cont2++) printf("%2d ", R[cont1][cont2]);
        printf("\n");
    }
}