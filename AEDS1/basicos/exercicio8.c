#include <stdio.h>
#include <stdlib.h>

int main()
{
    float deposito, juros, rendimento, total;
    printf("Insira o valor do deposito realizado e a taxa do juros bancario:\n");
    scanf("%f%f", &deposito, &juros);
    rendimento = deposito*juros/100.0;
    total = deposito + rendimento;
    printf("\nO valor total acumulado com esse deposito sera de:\n%.2f\n", total);
}
