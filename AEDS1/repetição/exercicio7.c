#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1, N, n1, n2, r;
    n1 = 0;
    n2 = 1;
    printf("Insira quantos termos quer calcular na sequencia de Fibonacci:\n");
    scanf("%d", &N);
    printf("\nO valor do primeiro e do segundo numero sao, respectivamente:\n%d e %d\n", n1, n2);
    for (cont1 = 3; cont1 <= N; cont1++) {
        r = n1 + n2;
        printf("\ne o proximo termo equivale a:\n%d\n", r);
        n1 = n2;
        n2 = r;
    }
}
