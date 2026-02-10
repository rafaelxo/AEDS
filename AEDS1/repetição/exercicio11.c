#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1 = 1, N, divisores = 0;
    printf("Insira um numero inteiro e maior que 1:\n");
    scanf("%d", &N);
    if (N <= 1) {
        printf("\nO numero deve ser maior que 1!\n");
        return 0;
    }
    while (cont1 <= N) {
        if ((N%cont1) == 0) {
            divisores += 1;
        }
        cont1++;
    }
    if (divisores > 2) {
        printf("\n%d divisores, numero nao primo!\n", divisores);
    } else {
        printf("\n%d divisores, numero primo!\n", divisores);
    }
}
