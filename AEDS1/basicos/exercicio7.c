#include <stdio.h>
#include <stdlib.h>

int main()
{
    float salario, salario_novo, imposto;
    printf("Digite o salario atual do funcionario:\n");
    scanf("%f", &salario);
    imposto = salario*0.1;
    salario_novo = salario + 50 - imposto;
    printf("\nO novo salario deste funcionario sera de:\n%.2f\n", salario_novo);
}
