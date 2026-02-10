#include <stdio.h>
#include <stdlib.h>

int main () {
    int N;
    printf("Insira o numero que deseja calcular a tabuada:\n");
    scanf("%d", &N);
    printf("\nA tabuada do numero %d e:\n", N);
    for (int cont1 = 1; cont1 <= 10; cont1++) {
        printf("\n%d * %d = %d", N, cont1, N*cont1);
    }
}