#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    float fat, E = 1;
    printf("Insira um numero para realizar o calculo:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        fat = 1;
        for (int cont2 = 1; cont2 <= cont1; cont2++) {
            fat *= cont2;
        }
        E += 1.0/fat;
    }
    printf("\nO valor da formula para o numero %d e:\n%f\n", N, E);
}
