#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int investimento;
    float valor, rendimento, saldo;
    printf("Menu de opcoes:\n\n1. Poupanca\n2. Fundos de renda fixa\n\nEscolha o tipo de investimento:\n");
    scanf("%d", &investimento);
    if (investimento < 1 || investimento > 2) {
        printf("\nOpcao invalida!\n");
        return 0;
    }
    printf("\nInsira o valor correspondente desse investimento:\n");
    scanf("%f", &valor);
    switch (investimento) {
        case 1: rendimento = valor * 0.03; break;
        case 2: rendimento = valor * 0.04; break;
    default: printf("\nOpcao invalida!\n");
    }
    saldo = valor + rendimento;
    printf("\nO rendimento foi de %.2f reais e o novo saldo e de %.2f reais!\n", rendimento, saldo);
}
