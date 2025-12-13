#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Aluno {
    char nome[100];
    char regiao;
    int distancia;
} Aluno;

bool prioridade (Aluno *a1, Aluno *a2) {
    if (a1->distancia != a2->distancia) return a1->distancia < a2->distancia;
    if (a1->regiao != a2->regiao) return a1->regiao < a2->regiao;
    return strcmp(a1->nome, a2->nome) < 0;
}

void ordenarAlunos (Aluno *alunos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (prioridade(&alunos[j], &alunos[i])) {
                Aluno temp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = temp;
            }
        }
    }
}

int main () {
    int q;
    while (scanf("%d", &q) != EOF) {
        Aluno *alunos = (Aluno*)malloc(q*sizeof(Aluno));
        for (int i = 0; i < q; i++) scanf("%s %c %d", alunos[i].nome, &alunos[i].regiao, &alunos[i].distancia);
        ordenarAlunos(alunos, q);
        for (int i = 0; i < q; i++) printf("%s\n", alunos[i].nome);
        free(alunos);
    }
    return 0;
}
