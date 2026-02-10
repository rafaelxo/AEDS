#include <stdio.h>
#include <stdlib.h>

int main()
{
    float salario, percentual, aumento, salario_novo;
    printf("Digite seu salario atual e o percentual de aumento:\n");
    scanf("%f%f", &salario, &percentual);
    aumento = salario*percentual/100.0;
    salario_novo = salario + aumento;
    printf("\nO aumento e seu novo salario seriam:\n%.2f\n%.2f\n", aumento, salario_novo);
    return 0;
}
