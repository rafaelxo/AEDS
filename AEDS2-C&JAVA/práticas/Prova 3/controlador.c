#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Celula {
    int ponto;
    char aviao[20];
    struct Celula* prox;
} Celula;

Celula* newCelula (int x, char str[]) {
    Celula* nova = (Celula*) malloc (sizeof(Celula));
    nova->ponto = x;
    strcpy (nova->aviao, str);
    nova->prox = NULL;
    return nova;
}

typedef struct Fila {
    Celula* primeiro;
    Celula* ultimo;
} Fila;

void inicializar (Fila* f) {
    f->primeiro = f->ultimo = NULL;
}

void inserir (Fila *f, int x, char str[]) {
    Celula *tmp = newCelula (x, str);
    if (f->primeiro == NULL) f->primeiro = f->ultimo = tmp;
    else {
        f->ultimo->prox = tmp;
        f->ultimo = tmp;
    }
}
Celula* remover (Fila *f) {
    if (f->primeiro == f->ultimo) exit(1);
    Celula* tmp = f->primeiro;
    f->primeiro = f->primeiro->prox;
    tmp->prox = NULL;
    return tmp;
}
bool vazia (Fila *f) {
    return (f->primeiro == NULL);
}

int main () {
    Fila entrada; inicializar(&entrada);
    int ponto;
    char aviao[20];
    bool fim = false;
    while (!fim && scanf("%s", aviao) == 1) {
        if (strcmp(aviao, "0") == 0) fim = true;
        else if (aviao[0] == '-' || aviao[0] == '0') ponto = atoi(aviao);
        else inserir(&entrada, ponto, aviao);
    }
    Fila norte, sul, leste, oeste;
    inicializar(&norte); inicializar(&sul); inicializar(&leste); inicializar(&oeste);
    Celula *atual;
    while (!vazia(&entrada)) {
        atual = remover(&entrada);
        switch (atual->ponto) {
            case -1: inserir(&oeste, -1, atual->aviao); break;
            case -2: inserir(&sul, -2, atual->aviao); break;
            case -3: inserir(&norte, -3, atual->aviao); break;
            case -4: inserir(&leste, -4, atual->aviao); break;
        }
        free(atual);
    }
    while (!vazia(&oeste)) {
        atual = remover(&oeste);
        printf("%s ", atual->aviao);
        free(atual);
    }
    while (!vazia(&norte) || !vazia(&sul)) {
        if (!vazia(&norte)) {
            atual = remover(&norte);
            printf("%s ", atual->aviao);
            free(atual);
        }
        if (!vazia(&sul)) {
            atual = remover(&sul);
            printf("%s ", atual->aviao);
            free(atual);
        }
    }
    while (!vazia(&leste)) {
        atual = remover(&leste);
        printf("%s ", atual->aviao);
        free(atual);
    }
    return 0;
}

