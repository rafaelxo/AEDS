#include <stdlib.h>
#include <stdio.h>

int fatorial (int cont1) {
    if (cont1 == 1) return 1;
    else return cont1 * fatorial(cont1 - 1);
}

float calculo (int N) {
    float S = 1;
    for (int cont1 = 1; cont1 <= N; cont1++) S += 1.0/fatorial(cont1);
    return S;
}

int main () {
    int N;
    scanf("%d", &N);
    printf("%.6f", calculo(N));
}