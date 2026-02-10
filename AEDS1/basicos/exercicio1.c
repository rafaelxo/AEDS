#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2, n3, n4, soma;
    printf("Digite 4 numeros positivos e inteiros para realizar a soma:\n");
    scanf("%d%d%d%d", &n1, &n2, &n3, &n4);
    soma = n1 + n2 + n3 + n4;
    printf("\nA soma desses valores e de:\n%d\n", soma);
    return 0;
}
