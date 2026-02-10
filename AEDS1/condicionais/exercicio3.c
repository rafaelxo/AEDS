#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n1, n2;
    printf("Insira dois numeros para descobrir qual e maior:\n");
    scanf("%f%f", &n1, &n2);
    if (n1 > n2) {
        printf("\nO primeiro numero e maior que o segundo!\n");
    } else if (n2 > n1) {
        printf("\nO segundo numero e maior que o primeiro!\n");
    } else if (n1 == n2) {
        printf("\nOs numeros tem iguais valores!\n");
    }
}
