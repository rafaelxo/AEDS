#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;
    float divisao;
    printf("Insira dois numeros para realizar a divisao:\n");
    scanf("%d%d", &n1, &n2);
    divisao = n1/(n2*1.0);
    printf("\nA divisao do primeiro numero pelo segundo e\n%.5f\n", divisao);
}
