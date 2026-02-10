#include <stdio.h>
#include <stdlib.h>

int main() {
    float s_minimo, s_receber, v_hora, s_mensal, v_dependentes, v_horaextra, s_bruto, s_liquido, imposto;
    int h_trabalhadas, n_dependentes, he_trabalhadas, gratificacao;
    printf("Insira o valor do salario minimo:\n");
    scanf("%f", &s_minimo);
    printf("\nAgora, insira a quantidade de horas trabalhas, a quantidade de horas extras e o numero de dependentes:\n");
    scanf("%d%d%d", &h_trabalhadas, &he_trabalhadas, &n_dependentes);
    v_hora = s_minimo/5.0;
    s_mensal = h_trabalhadas * v_hora;
    v_dependentes = n_dependentes * 32;
    v_horaextra = he_trabalhadas * (v_hora + (v_hora * 0.5));
    s_bruto = s_mensal + v_dependentes + v_horaextra;
    if (s_bruto < 200) {
        imposto = 0;
    } else if (s_bruto >= 200 && s_bruto <= 500) {
        imposto = s_bruto * 0.1;
    } else if (s_bruto > 500) {
        imposto = s_bruto * 0.2;
    }
    s_liquido = s_bruto - imposto;
    if (s_liquido <= 350) {
        gratificacao = 100;
    } else if (s_liquido > 350) {
        gratificacao = 50;
    }
    s_receber = s_liquido + gratificacao;
    printf("\nO salario a receber e de %.2f reais!\n", s_receber);
}
