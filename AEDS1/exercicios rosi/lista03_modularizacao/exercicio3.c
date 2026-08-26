#include <stdlib.h>
#include <stdio.h>

void ordemCrescente (int n1, int n2, int n3) {
    int menor;
    if (n1 > n2) {
        menor = n1;
        n1 = n2;
        n2 = menor;
    }
    if (n1 > n3) {
        menor = n1;
        n1 = n3;
        n3 = menor;
    }
    if (n2 > n3) {
        menor = n2;
        n2 = n3;
        n3 = menor;
    }
    printf("%d %d %d\n", n1, n2, n3);
}

int main () {
    int N, n1, n2, n3;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        scanf("%d%d%d", &n1, &n2, &n3);
        ordemCrescente(n1, n2, n3);
    }
}