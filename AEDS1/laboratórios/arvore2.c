#include <stdio.h>
#include <stdlib.h>

void arvoreEsqI (int N) {
    if (N == 1) printf("*\n");
    else if (N > 1) {
        for (int cont1 = 1; cont1 <= N; cont1++) printf("* ");
        printf("\n");
    }
    arvoreEsqI(N - 1);
}

int main () {
    int N;
    printf("Insira a quantidade de linhas que deseja imprimir:\n");
    scanf("%d", &N);
    printf("\n");
    arvoreEsqI(N);
}
