#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int t_servico, gratificacao;
    float sal_base, imposto, sal_liquido;
    printf("Insira o salario base do funcionario e seu tempo de servico em anos:\n");
    scanf("%f%d", &sal_base, &t_servico);
    if (sal_base < 200) {
        imposto = 0;
    } else if (sal_base >= 200 && sal_base <= 450) {
        imposto = sal_base * 0.03;
    } else if (sal_base > 450 && sal_base < 700) {
        imposto = sal_base * 0.08;
    } else if (sal_base >= 700) {
        imposto = sal_base * 0.12;
    }
    printf("\nO valor do imposto e de %.2f reais!\n", imposto);
    if (sal_base > 500) {
        if (t_servico <= 3) {
            gratificacao = 20;
        } else {
            gratificacao = 30;
        }
    } else {
        if (t_servico <= 3) {
            gratificacao = 23;
        } else if (t_servico > 3 && t_servico < 6) {
            gratificacao = 35;
        } else {
            gratificacao = 33;
        }
    }
    printf("\nO valor da sua gratificacao e de %d reais!\n", gratificacao);
    sal_liquido = sal_base - imposto + gratificacao;
    printf("\nO salario liquido desse funcionario e de %.2f reais!\n", sal_liquido);
    if (sal_liquido <= 350) {
        printf("\nA classificacao desse funcionario e A!\n");
    } else if (sal_liquido > 350 && sal_liquido < 600) {
        printf("\nA classificacao desse funcionario e B!\n");
    } else {
        printf("\nA classificacao desse funcionario e C!\n");
    }

}
