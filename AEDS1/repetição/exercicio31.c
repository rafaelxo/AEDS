#include <stdio.h>
#include <stdlib.h>

int main () {
    int N;
    float valor, total_v = 0, total_p = 0, total_g = 0, valor_prestacao = 0;
    char codigo;
    printf("Insira quantas transacoes quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira o valor da transacao e se foi paga a visa (V) ou a prazo (P):\n");
        scanf("%f %c", &valor, &codigo);
        if (codigo == 'V') {
            total_v += valor;
        }
        if (codigo == 'P') {
            total_p += valor;
        }
        total_g = total_v + total_p;
        valor_prestacao = total_p/3.0;
    }
    printf("\nO valor em reais das compras a vista, a prazo e o total das transacoes realizadas e de, respecitvamente:\n%.2f\n%.2f\n%.2f\n", total_v, total_p, total_g);
    printf("\nA soma do valor das prestacoes das compras a prazo e de %.2f reais!\n", valor_prestacao);
}