#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float p_final, c_fabrica, p_distribuidor, p_impostos;
    printf("Insira o custo de fabrica do veiculo:\n");
    scanf("%f", &c_fabrica);
    if (c_fabrica <= 12000) {
        p_distribuidor = c_fabrica * 0.05;
        p_impostos = 0;
    } else if (c_fabrica > 12000 && c_fabrica <= 25000) {
        p_distribuidor = c_fabrica * 0.1;
        p_impostos = c_fabrica * 0.15;
    } else {
        p_distribuidor = c_fabrica * 0.15;
        p_impostos = c_fabrica * 0.2;
    }
    p_final = c_fabrica + p_distribuidor + p_impostos;
    printf("\nA porcentagem do distribuidor, dos impostos e o preco final do carro equivale, respectivamente, a:\n%.2f\n%.2f\n%.2f\n", p_distribuidor, p_impostos, p_final);
}
