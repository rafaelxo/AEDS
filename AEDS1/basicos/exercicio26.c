#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2, subtracao;
    printf("Insira dois numeros para realizar a subtracao:\n");
    scanf("%d%d", &n1, &n2);
    subtracao = n1 - n2;
    printf("\nO resultado da subtracao e:\n%d\n", subtracao);
}
