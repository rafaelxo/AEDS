#include <stdlib.h>
#include <stdio.h>

int main() {
    int j[24], c[24], op, num, cont1;
    char posicao;
    for (int cont1 = 0; cont1 < 24; cont1++) {
        j[cont1] = 0;
        c[cont1] = 0;
    }
    do {
        printf("\nMenu de opcoes:\n1 - Vender passagem\n2 - Mostrar mapa de conducao\n3 - Encerrar\nInsira a opcao desejada:\n");
        scanf("%d", &op);
        switch (op) {
            case 1:
                for (cont1 = 0; cont1 < 24 && (j[cont1] != 0 && c[cont1] != 0); cont1++);
                if (cont1 == 24) printf("\nOnibus lotado!");
                else {
                    do {
                        printf("\nEscolha a posicao (J - janela ou C - corredor):\n");
                        scanf(" %c", &posicao);
                    } while (posicao != 'J' && posicao != 'C');
                    do {
                        printf("\nEscolha o numero da poltrona (1 a 24):\n");
                        scanf("%d", &num);
                    } while (num < 1 || num > 24);
                    if (posicao == 'J') {
                        if (j[num - 1] == 1) printf("\nPoltrona ocupada!\n");
                        else {
                            j[num - 1] = 1;
                            printf("\nVenda realizada na poltrona %d!\n", num);
                        }
                    } else if (posicao == 'C') {
                        if (c[num - 1] == 1) printf("\nPoltrona ocupada!\n");
                        else {
                            c[num - 1] = 1;
                            printf("\nVenda realizada na poltrona %d!\n", num);
                        }
                    }
                }
                break;
                case 2:
                    printf("\nMapa de conducao do onibus:\nJANELA\t\tCORREDOR\n");
                    for (int cont1 = 0; cont1 < 24; cont1++) {
                        printf("%2d - %d\t\t%2d - %d\n", cont1 + 1, (j[cont1] == 0 ? 0 : 1), cont1 + 1, (c[cont1] == 0 ? 0 : 1));
                    }
                break;
                case 3:
                    printf("\nPrograma finalizado!\n");
                break;
                default:
                    printf("\nOpcao invalida!\n");
        }
    } while (op != 3);
}