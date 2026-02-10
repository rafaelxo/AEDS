#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int h_trabalhadas;
    float s_minimo, s_bruto, v_hora, s_liquido, impostos;
    printf("Insira quantas horas voce trabalha por mes e seu salario minimo:\n");
    scanf("%d%f", &h_trabalhadas, &s_minimo);
    v_hora = s_minimo/2.0;
    s_bruto = v_hora*h_trabalhadas;
    impostos = s_bruto*0.03;
    s_liquido = s_bruto - impostos;
    printf("\nO valor por hora, seu salario bruto, o valor do imposto a ser pago e seu salario liquido sao, respectivamente:\n%.2f\n%.2f\n%.2f\n%.2f\n", v_hora, s_bruto, impostos, s_liquido);
}
