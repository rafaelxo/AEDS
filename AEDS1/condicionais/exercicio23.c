#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int h_trabalhadas, gratificacao;
    float s_minimo, coeficiente, s_bruto, imposto, s_liquido, auxilio;
    char turno, cargo;
    printf("Insira o salario minimo, o turno (M, V ou N), o cargo (O ou G) e o numero de horas trabalhadas pelo funcionario:\n");
    scanf("%f %c %c %d", &s_minimo, &turno, &cargo, &h_trabalhadas);
    switch (turno) {
        case 'M': coeficiente = s_minimo * 0.1; break;
        case 'V': coeficiente = s_minimo * 0.15; break;
        case 'N': coeficiente = s_minimo * 0.12; break;
    default: coeficiente = 0; break;
    }
    printf("\nO valor do coeficiente equivale a %.2f reais!\n", coeficiente);
    s_bruto = h_trabalhadas * coeficiente;
    printf("\nO valor do salario bruto equivale a %.2f reais!\n", s_bruto);
    if (cargo == 'O') {
        if (s_bruto >= 300) {
            imposto = s_bruto * 0.05;
        } else {
            imposto = s_bruto * 0.03;
        }
    }
    if (cargo == 'G') {
        if (s_bruto >= 400) {
            imposto = s_bruto * 0.06;
        } else {
            imposto = s_bruto * 0.04;
        }
    }
    printf("\nO valor do imposto e de %.2f reais!\n", imposto);
    if (turno == 'N' && h_trabalhadas > 80) {
        gratificacao = 50;
    } else {
        gratificacao = 30;
    }
    printf("\nA gratificacao equivale a %d reais!\n", gratificacao);
    if (cargo == 'O' || coeficiente <= 25) {
        auxilio = s_bruto * 1/3.0;
    } else {
        auxilio = s_bruto * 1/2.0;
    }
    printf("\nO valor do auxilio e de %.2f reais!\n", auxilio);
    s_liquido = s_bruto - imposto + gratificacao + auxilio;
    printf("\nO valor do salario liquido desse funcionario e de %.2f reais!\n", s_liquido);
    if (s_liquido < 350) {
        printf("\nFuncionario mal remunerado!\n");
    } else if (s_liquido >= 350 && s_liquido <= 600) {
        printf("\nFuncionario normalmente remunerado!\n");
    } else {
        printf("\nFuncionario bem remunerado!\n");
    }
}
