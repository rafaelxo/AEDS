#include <stdlib.h>
#include <stdio.h>

int main () {
    int x[8], num, pos;
    printf("Digite os 8 valores do vetor:\n");
    for (int cont1 = 0; cont1 < 8; cont1++) {
        printf("%do valor:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
        pos = cont1;
        while (pos > 0 && x[pos - 1] > num) {
            x[pos] = x[pos - 1];
            pos--;
        }
        x[pos] = num;
    }
    printf("\nVetor em ordem crescente:\n");
    for (int cont1 = 0; cont1 < 8; cont1++) printf("%d ", x[cont1]);
    printf("\nVetor em ordem decrescente:\n");
    for (int cont1 = 7; cont1 >= 0; cont1--) printf("%d ", x[cont1]);
}