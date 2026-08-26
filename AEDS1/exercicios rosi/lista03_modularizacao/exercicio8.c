#include <stdlib.h>
#include <stdio.h>

float conta (int N) {
    float S = 0, num = 2;
    for (int cont1 = 1; cont1 <= N; cont1++) {
        S += num/(cont1+3);
        num += cont1*2 + 1;
    }
    return S;
}

int main () {
    int N;
    scanf("%d", &N);
    printf("%.6f\n", conta(N));
}