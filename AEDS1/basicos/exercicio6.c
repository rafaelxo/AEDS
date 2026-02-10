#include <stdio.h>
#include <stdlib.h>

int main()
{
    float salario, salario_novo, gratificacao, imposto;
    printf("Digite o salario atual do funcionario:\n");
    scanf("%f", &salario);
    gratificacao = salario*0.05;
    imposto = salario*0.07;
    salario_novo = salario + gratificacao - imposto;
    printf("\nO novo salario deste funcionario sera de:\n%.2f\n", salario_novo);
}
