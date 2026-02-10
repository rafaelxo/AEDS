#include <stdio.h>
#include <stdlib.h>

int main() {
    int q_kwt, q_consumidores = 0, tipo;
    float s_minimo, v_kwt, v_final, acrescimo, faturamento = 0;
    printf("Insira o valor do salario minimo e a quantidade de kilowatts:\n");
    scanf("%f%d", &s_minimo, &q_kwt);
    v_kwt = s_minimo/8;
    while (q_kwt != 0) {
        printf("\nInsira o tipo do consumidor (1 - residencial, 2 - comercial, 3 - industrial):\n");
        scanf("%d", &tipo);
        if (tipo == 1) {
            acrescimo = 0.05;
        } else if (tipo == 2) {
            acrescimo = 0.1;
        } else {
            acrescimo = 0.15;
        }
        v_final = q_kwt * v_kwt + (q_kwt*v_kwt*acrescimo);
        faturamento += v_final;
        if (v_final >= 500 && v_final <= 1000) {
            q_consumidores++;
        }
        printf("\nO gasto do consumidor e de %.2f reais, com um acresimo de %.2f reais, o valor total da conta e de %.2f reais!\n", q_kwt*v_kwt, q_kwt*v_kwt*acrescimo, v_final);
        printf("\nInsira a quantidade de kilowatts:\n");
        scanf("%d", &q_kwt);
    }
    printf("\nO faturamento da empresa e de %.2f reais, e o numero de clientes que pagam entre 500 e 1000 reais e de %d!", faturamento, q_consumidores);
}
