#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float p_fabrica, per_distribuidor, per_imposto, l_distribuidor, v_imposto, p_final;
    printf("Insira o preco de fabrica do veiculo:\n");
    scanf("%f", &p_fabrica);
    printf("\nInsita o percentual do distribuidor e dos impostos:\n");
    scanf("%f%f", &per_distribuidor, &per_imposto);
    l_distribuidor = p_fabrica*per_distribuidor/100.0;
    v_imposto = p_fabrica*per_imposto/100.0;
    p_final = p_fabrica + l_distribuidor + v_imposto;
    printf("\nO lucro do distribuidor, os impostos a serem pagos e o valor do veiculo sao, respectivamente:\n%.2f\n%.2f\n%.2f\n", l_distribuidor, v_imposto, p_final);
}
