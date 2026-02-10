#include <stdlib.h>
#include <stdio.h>

int main () {
    int x[10], troca;
    for (int cont1 = 0; cont1 < 10; cont1++ ) {
        printf("Digite o valor para a posicao %d do vetor:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        for (int cont2 = 0; cont2 <= 9; cont2++) {
            if (x[cont2] > x[cont2 + 1]) {
                troca = x[cont2];
                x[cont2] = x[cont2 + 1];
                x[cont2 + 1] = troca;
            }
        }
    }
    printf("\nA ordem crescente do vetor X e:\n");
    for (int cont1 = 0; cont1 < 10; cont1++) printf("%d ", x[cont1]);
    printf("\n\nA ordem decrescente do vetor X e:\n");
    for (int cont1 = 9; cont1 >= 0; cont1--) printf("%d ", x[cont1]);
}