#include <stdio.h>
#include <stdlib.h>

int somaDivisores (int a, int b, int c) {
    int soma = 0, menor;
    if (b > c) {
        menor = b;
        b = c;
        c = menor;
    }
    for (int cont1 = b; cont1 <= c; cont1++) {
        if (cont1%a == 0) soma += cont1;
    }
    return soma;
}

int main () {
    int a, b, c;
    do {
        printf("Insira, respectivamente, um valor para A (positivo), para B e para C:\n");
        scanf("%d%d%d", &a, &b, &c);
    } while (a <= 0);
    printf("\nA soma dos numeros divisiveis por %d de %d ate %d e %d!\n", a, b, c, somaDivisores(a, b, c));
}
