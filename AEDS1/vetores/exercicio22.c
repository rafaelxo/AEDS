#include <stdlib.h>
#include <stdio.h>

int main() {
    int c[10], op, cod;
    float s[10], valor, soma;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o numero da conta %d e seu respectivo saldo:\n", cont1 + 1);
        scanf("%d%f", &c[cont1], &s[cont1]);
    }
    do {
        printf("\nEscolha uma opcao:\n1 - Efetuar deposito\n2 - Efetuar saque\n3 - Consultar ativo bancario\n4 - Finalizar o programa\nInsira a opcao desejada:\n");
        scanf("%d", &op);
        switch (op) {
            case 1: 
                printf("\nInsira o numero da conta e o valor a ser depositado:\n");
                scanf("%d%f", &cod, &valor);
                int cont1;
                for (cont1 = 0; cont1 < 10; cont1++) {
                    if (c[cont1] == cod) {
                        s[cont1] += valor;
                        printf("\nDeposito efetuado com sucesso!\n");
                    }
                }
                if (cont1 == 10) printf("\nConta nao encontrada!\n");
            break;
            case 2:
                printf("\nInsira o numero da conta e o valor a ser sacado:\n");
                scanf("%d%f", &cod, &valor);
                for (cont1 = 0; cont1 < 10; cont1++) {
                    if (c[cont1] == cod) {
                        if (s[cont1] < valor) printf("\nSaldo insuficiente!\n");
                        else {
                            s[cont1] -= valor;
                            printf("\nSaque efetuado com sucesso!\n");
                        }
                    }
                }
                if (cont1 == 10) printf("\nConta nao encontrada!\n");
            break;
            case 3:
                printf("\nInsira o numero da conta para verificar o extrato:\n");
                scanf("%d", &cod);
                for (cont1 = 0; cont1 < 10; cont1++) {
                    if (c[cont1] == cod) {
                        soma = s[cont1];
                        printf("\nO ativo bancario total e:\n%.2f\n", soma);
                    }
                }
                if (cont1 == 10) printf("\nConta nao encontrada!\n");
            break;
            case 4:
                printf("\nPrograma finalizado!\n");
            break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (op != 4);
}