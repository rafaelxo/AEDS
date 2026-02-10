#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float salario, c1, c2, i1, i2, novo_saldo;
    printf("Insira o valor do salario depositado e o valor, respectivamente, do primeiro e do segundo cheque emitido:\n");
    scanf("%f%f%f", &salario, &c1, &c2);
    i1 = c1*0.38;
    i2 = c2*0.38;
    novo_saldo = salario - c1 - c2 - i1 - i2;
    printf("\nO valor dos impostos cobrados e o seu novo saldo sao, respectivamente:\n%.2f\n%.2f\n%.2f\n", i1, i2, novo_saldo);
}
