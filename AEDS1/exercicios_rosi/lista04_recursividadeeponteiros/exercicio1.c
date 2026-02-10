#include <stdio.h>
#include <stdlib.h>

int digitos (int N) {
    if (N <= 9) return 1;
    else return 1 + digitos (N/10);
}

int main () {
    int N;
    scanf("%d", &N);
    printf("%d", digitos(N));
}