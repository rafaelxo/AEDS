#include <stdio.h>
#include <stdlib.h>

int fatorial (int cont1) {
    if (cont1 == 1) return 1;
    else return cont1 * fatorial(cont1 - 1);
}

float expressao (int N) {
    float S = 1;
    for (int cont1 = 1; cont1 <= N; cont1++) S += 1.0/fatorial(cont1);
    return S;
}

int main () {
    int N;
    printf("Insira o valor para calcular a expressao:\n");
    scanf("%d", &N);
    printf("\nO valor da expressao e %.2f!\n", expressao(N));
}