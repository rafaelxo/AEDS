#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2, n3, multiplicacao;
    printf("Insira 3 numeros que serao multiplicados:\n");
    scanf("%d%d%d", &n1, &n2, &n3);
    multiplicacao = n1*n2*n3;
    printf("\nA multiplicacao desses numeros equivale a:\n%d\n", multiplicacao);
    return 0;
}
