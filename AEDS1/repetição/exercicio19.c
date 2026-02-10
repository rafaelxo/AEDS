#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    printf("Digite o valor de m e n:\n");
    scanf("%d%d", &m, &n);
    while (m < n) {
        int soma = 0;
        for (int cont1 = m; cont1 <= n; cont1++) {
            soma += cont1;
        }
        printf("A soma dos inteiros entre de m ate n e de:\n%d\n", soma);
        scanf("%d%d", &m, &n);
    }
}