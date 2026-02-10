#include <stdio.h>
#include <stdlib.h>

int main()
{
    float salario, salario_novo;
    printf("Digite seu salario atual para calcular o aumento:\n");
    scanf("%f", &salario);
    salario_novo = salario*1.25;
    printf("\nSeu novo salario sera:\n%.2f", salario_novo);
    return 0;
}
