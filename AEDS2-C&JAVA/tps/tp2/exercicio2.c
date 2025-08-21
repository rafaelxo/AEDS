#include <stdlib.h>
#include <stdio.h>

int somaDigitos (int n) {
    if (n < 10) return n;
    else return n % 10 + somaDigitos(n / 10);
}

int main () {
    int n; scanf("%d", &n);
    printf("%d\n", somaDigitos(n));
    return 0;
}
