#include <stdio.h>
#include <stdlib.h>

void arvoreComp (int N1, int N2) {
    if (N1 == 1) {
        for (int cont1 = 1; cont1 < N2; cont1++) printf(" ");
        printf("*\n");
    } else if (N1 > 1) {
        arvoreComp(N1 - 1, N2);
        for (int cont1 = 1; cont1 <= N2 - N1; cont1++) printf(" ");
        for (int cont1 = 1; cont1 <= 2 * N1 - 1; cont1++) printf("*");
        printf("\n");
    }
}

int main () {
    int N;
    printf("Insira a quantidade de linhas que deseja imprimir:\n");
    scanf("%d", &N);
    printf("\n");
    arvoreComp(N, N);
}
