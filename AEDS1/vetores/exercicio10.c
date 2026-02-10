#include <stdlib.h>
#include <stdio.h>

int main() {
    int N, n_aluno, pontos, aprovados = 0;
    char g[8], r[8];
    for (int cont1 = 0; cont1 < 8; cont1++) {
        printf("Digite o gabarito da questao %d:\n", cont1 + 1);
        scanf(" %c", &g[cont1]);
    }
    printf("\nInsira o numero de alunos na sala:\n");
    scanf("%d", &N);
    for (int cont1 = 0; cont1 < N; cont1++) {
        pontos = 0;
        printf("\nDigite o numero do %d aluno:\n", cont1 + 1);
        scanf("%d", &n_aluno);
        for (int cont2 = 0; cont2 < 8; cont2++) {
            printf("Digite a resposta do aluno %d para a questao %d:\n", n_aluno, cont2 + 1);
            scanf(" %c", &r[cont2]);
            if (r[cont2] == g[cont2]) pontos++;
        }
        printf("\nO aluno %d obteve %d pontos!\n", n_aluno, pontos);
        if (pontos >= 6) {
            printf("Aprovado!\n");
            aprovados++;
        } else printf("Reprovado!\n");
    }
    printf("\nA porcentagem de alunos aprovados foi de %.2f%%\n", (aprovados*100.0)/N);
}