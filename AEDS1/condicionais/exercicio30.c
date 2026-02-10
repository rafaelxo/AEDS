#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int opcao;
    float n1, n2, n3, media, diferenca, produto, divisao;
    printf("Menu de opcoes:\n\n1. Media\n2. Diferenca\n3. Produto\n4. Divisao\n\nEscolha a opcao desejada:\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 4) {
        printf("\nOpcao invalida!\n");
        return 1;
    }
    printf("\nAgora, insira os dois valores para realizar o calculo desejado:\n");
    scanf("%f%f", &n1, &n2);
    if (n2 == 0) {
        printf("\nO segundo valor nao pode ser igual a 0!\n");
        return 0;
    }
    media = (n1 + n2) / 2.0;
    diferenca = n1 - n2;
    produto = n1 * n2;
    divisao = n1 / (n2 * 1.0);
    switch (opcao) {
        case 1: printf("\nA media dos valores e:\n%.2f\n", media); break;
        case 2: printf("\nA diferenca dos valores e de:\n%.2f\n", diferenca); break;
        case 3: printf("\nO produto dos valores e de:\n%.2f\n", produto); break;
        case 4: printf("\nA divisao dos valores e de:\n%.2f\n", divisao); break;
    default: printf("\nOpcao invalida!\n");
    }
}
