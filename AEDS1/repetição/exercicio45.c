#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, opcao, peso, s_peso = 0;
    float nota, media_a = 0, media_p = 0;
    printf("Menu de opcoes:\n\n1. Media aritmetica\n2. Media ponderada\n3. Sair\n\nInsira a opcao desejada:\n");
    scanf("%d", &opcao);
    do {
        printf("Insira quantas notas deseja calcular:\n");
        scanf("%d", &N);
        if (opcao == 1) {
            media_a = 0;
            for (int cont1 = 1; cont1 <= N; cont1++) {
                printf("\nInsira a %d nota para calcular a media aritmetica:\n", cont1);
                scanf("%f", &nota);
                media_a += nota;
            }
            printf("\nA media aritmetica dessas notas e de %.2f pontos!\n", media_a*1.0/N);
        } else if (opcao == 2) {
            media_p = 0;
            s_peso = 0;
            for (int cont1 = 1; cont1 <= N; cont1++) {
                printf("\nInsira a %d nota e seu respectivo peso para calcular a media ponderada:\n", cont1);
                scanf("%f%d", &nota, &peso);
                media_p += nota*peso;
                s_peso += peso;
            }
            printf("\nA media ponderada dessas notas e de %.2f pontos!\n", media_p*1.0/s_peso);
        } else {
            printf("\nPrograma finalizado!\n");
        }
        printf("\nMenu de opcoes:\n\n1. Media aritmetica\n2. Media ponderada\n3. Sair\n\nInsira a opcao desejada:\n");
        scanf("%d", &opcao);
    } while (opcao < 3);
}
