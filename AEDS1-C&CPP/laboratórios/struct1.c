#include <stdlib.h>
#include <stdio.h>

typedef struct endereco {
    char *logradouro;
    int numero;
    char *complemento;
} End;

typedef struct aluno {
    char *nome;
    int idade;
    float notas[3];
    End endereco;
} Al;

void preenche (Al *vet, int N) {
    for (int i = 0; i < N; i++) {
        (vet + i)->nome = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (vet + i)->nome);
        scanf("%d", &vet[i].idade);
        for (int j = 0; j < 3; j++) scanf("%f", &vet[i].notas[j]);
        (vet + i)->endereco.logradouro = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (vet + i)->endereco.logradouro);
        scanf("%d", &vet[i].endereco.numero);
        (vet + i)->endereco.complemento = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (vet + i)->endereco.complemento);
    }
}

void exibe (Al *vet, int N) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Nome: %s\n", (vet + i)->nome);
        printf("Idade: %d\n", vet[i].idade);
        printf("Notas: ");
        for (int j = 0; j < 3; j++) printf("%.2f / ", vet[i].notas[j]);
        printf("\nEndereco: ");
        printf("%s, %d, %s\n", (vet + i)->endereco.logradouro, vet[i].endereco.numero, (vet + i)->endereco.complemento);
        printf("\n");
    }
}

Al maisVelho (Al *vet, int N) {
    Al maior = *(vet);
    for (int i = 1; i < N; i++) {
        if((vet + i)->idade > maior.idade) maior = *(vet + i);
    }
    return maior;
}

void alunoVelho (Al velho) {
    printf("Aluno mais velho\n");
    printf("Nome: %s\n", velho.nome);
    printf("Idade: %d anos\n", velho.idade);
    printf("Notas: ");
    for (int i = 0; i < 3; i++) printf("%.2f / ", velho.notas[i]);
    printf("\nEndereco: ");
    printf("%s, %d, %s\n", velho.endereco.logradouro, velho.endereco.numero, velho.endereco.complemento);
    printf("\n");
}

float mediaAlunos (Al *vet, int N) {
    float media = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) media += vet[i].notas[j];
    }
    media /= (N*3);
    return media;
}

int main () {
    int N;
    scanf("%d", &N);
    Al *turma = (Al*)malloc(N*sizeof(Al));
    Al velho;
    preenche(turma, N); exibe(turma, N);
    velho = maisVelho(turma, N);
    alunoVelho(velho);
    for (int i = 0; i < N; i++) {
        free(turma[i].nome);
        free(turma[i].endereco.logradouro);
        free(turma[i].endereco.complemento);
    }
    float media = mediaAlunos(turma, N);
    printf("Media das notas: %.2f\n", media);
    free(turma);
}