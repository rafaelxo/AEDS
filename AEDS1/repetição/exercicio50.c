#include <stdio.h>
#include <stdlib.h>

int main() {
    int cod, investimento;
    float valor, acrescimo, rendimento, t_investido = 0, t_acrescimo = 0, t_rendimento = 0, valor_f = 0;
    printf("Insira o codigo do cliente:\n");
    scanf("%d", &cod);
    while (cod > 0) {
        printf("\nInsira o tipo do investimento (1 - poupanca, 2 - poupanca plus ou 3 - fundos de renda fixa) e o valor investido:\n");
        scanf("%d%f", &investimento, &valor);
        t_investido += valor;
        if (investimento == 1) {
            acrescimo = 0.015;
        } else if (investimento == 2) {
            acrescimo = 0.02;
        } else if (investimento == 3) {
            acrescimo = 0.04;
        } else {
            printf("Tipo de investimento invalido.\n");
        }
        rendimento = valor * acrescimo;
        t_acrescimo += rendimento;
        valor_f = valor + rendimento;
        t_rendimento += valor_f;
        printf("\nO valor do rendimento desse investimento e de %.2f reais!\n", rendimento);
        printf("\nO valor final desse investimento e de %.2f reais!\n", valor_f);
        printf("\nInsira o codigo do cliente:\n");
        scanf("%d", &cod);
    }
    printf("\nO valor total de investimentos e de %.2f reais!\n", t_investido);
    printf("\nO total de rendimentos desses investimentos e de %.2f reais!\n", t_acrescimo);
    printf("\nO total dos valores finais desses investimentos e de %.2f reais!\n", t_rendimento);
}
