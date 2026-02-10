#include <stdio.h>
#include <stdlib.h>

int main() {
    int h_trabalhadas, he_trabalhadas;
    float s_minimo, q_receberh, q_receberhe, s_receber, vh_trabalhadas, vhe_trabalhadas;
    printf("Insira quantas horas voce trabalha por mes, seu salario minimo e a quantidade de horas extras trabalhadas:\n");
    scanf("%d %f %d", &h_trabalhadas, &s_minimo, &he_trabalhadas);
    vh_trabalhadas = s_minimo *1/8.0;
    vhe_trabalhadas = s_minimo *1/4.0;
    q_receberh = h_trabalhadas * vh_trabalhadas;
    q_receberhe = he_trabalhadas * vhe_trabalhadas;
    s_receber = q_receberh + q_receberhe;
    printf("\nVoce recebera %.2f reais nesse mes!\n", s_receber);
}
