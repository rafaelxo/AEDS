#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float s_bruto, s_receber, gratificacao, imposto;
    printf("Insira o salario bruto do funcionario:\n");
    scanf("%f", &s_bruto);
    if (s_bruto <= 350) {
        gratificacao = 100;
    } else if (s_bruto > 350 && s_bruto < 600) {
        gratificacao = 75;
    } else if (s_bruto >= 600 && s_bruto <= 900) {
        gratificacao = 50;
    } else {
        gratificacao = 35;
    }
    imposto = s_bruto * 0.07;
    s_receber = s_bruto + gratificacao - imposto;
    printf("\nO valor a receber desse funcionario e de %.2f reais!\n", s_receber);
}
