#include <stdio.h>
#include <stdlib.h>

int main() {
    float salario, comissao, v_vendas, salario_final;
    printf("Digite o salario do vendedor e o total de vendas feitas em reais:\n");
    scanf("%f%f", &salario, &v_vendas);
    comissao = v_vendas * 0.04;
    salario_final = salario + comissao;
    printf("\nO salario final do vendedor e:\n%.2f\n", salario_final);
}