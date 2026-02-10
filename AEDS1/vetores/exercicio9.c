#include <stdlib.h>
#include <stdio.h>

int main() {
    int v[12], o[12], d[12], l[12], op1, op2, voo, origem, destino;
    for (int cont1 = 0; cont1 < 12; cont1++) {
        printf("Digite o numero do voo:\n");
        scanf("%d", &v[cont1]);
        printf("Digite o numero de origem:\n");
        scanf("%d", &o[cont1]);
        printf("Digite o numero do destino:\n");
        scanf("%d", &d[cont1]);
        printf("Digite o numero do assento:\n");
        scanf("%d", &l[cont1]);
    }
    do {
        printf("\nMenu de opcoes:\n1 - Consultar\n2 - Reservar\n3 - Finalizar\nInsira a opcao desejada:\n");
        scanf("%d", &op1);
        switch (op1) {
            case 1:
                printf("\nMenu de opcoes:\n1 - Consulta por voo\n2 - Consulta por origem\n3 - Consulta por destino\nInsira a opcao desejada:\n");
                scanf("%d", &op2);
                if (op2 == 1) {
                    printf("\nDigite o numero do voo:\n");
                    scanf("%d", &voo);
                    int cont1 = 0;
                    while (cont1 < 12 && v[cont1] != voo) cont1++;
                    if (cont1 >= 12) printf("\nVoo nao encontrado.\n");
                    else printf("\nNumero do voo: %d\nLocal de origem: %d\nLocal de destino: %d\nLugares disponiveis: %d\n", v[cont1], o[cont1], d[cont1], l[cont1]);
                } else if (op2 == 2) {
                    printf("\nDigite o local de origem:\n");
                    scanf("%d", &origem);
                    int cont1;
                    for (cont1 = 0; cont1 < 12; cont1++) {
                        if (origem == o[cont1]) {
                            printf("\nNumero do voo: %d\nLocal de origem: %d\nLocal de destino: %d\nLugares disponiveis: %d\n", v[cont1], o[cont1], d[cont1], l[cont1]);
                            break;
                        }
                    }
                    if (cont1 == 12) printf("\nNenhum voo encontrado com essa origem.\n");
                } else if (op2 == 3) {
                    printf("\nDigite o local do destino:\n");
                    scanf("%d", &destino);
                    int cont1;
                    for (cont1 = 0; cont1 < 12; cont1++) {
                        if (destino == d[cont1]) {
                            printf("\nNumero do voo: %d\nLocal de origem: %d\nLocal de destino: %d\nLugares disponiveis: %d\n", v[cont1], o[cont1], d[cont1], l[cont1]);
                            break;
                        }
                    }
                    if (cont1 == 12) printf("\nNenhum voo encontrado com esse destino.\n");
                }
                break;
            case 2:
                printf("\nDigite o numero do voo desejado:\n");
                scanf("%d", &voo);
                int cont1 = 0;
                while (cont1 < 12 && v[cont1] != voo) cont1++;
                if (cont1 >= 12) printf("\nVoo nao encontrado.\n");
                else {
                    if (l[cont1] == 0) printf("\nVoo lotado.\n");
                    else {
                        l[cont1]--;
                        printf("\nReserva confirmada! Lugares restantes: %d\n", l[cont1]);
                    }
                }
                break;
            case 3:
                printf("\nPrograma finalizado!\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while (op1 != 3);
}