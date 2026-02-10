#include <stdio.h>
#include <stdlib.h>

int multiplicacao (int N) {
    printf("\nSequencia de %d:\n", N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        for (int cont2 = 1; cont2 <= cont1; cont2++) printf("%d ", cont1*cont2);
        printf("\n");
    }
}

int main() {
   int N;
   do {
        printf("Insira um numero (1 a 9) para realizar a sequencia:\n");
        scanf("%d", &N);
   } while (N <= 1 || N >= 9);
   multiplicacao(N);
}
