#include <stdio.h>
#include <stdlib.h>

int somaDigitos (int N) {
    if (N == 0) return 0;
    else if (N == 1) return 1;
    else return N%10 + somaDigitos(N/10);
}

int main () {
    int N;
    scanf("%d", &N);
    printf("%d", somaDigitos(N));
}
