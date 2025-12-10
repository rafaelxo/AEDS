#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

Celula *newCelula(int x) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = x;
    nova->prox = NULL;
    return nova;
}

Celula *primeiro, *ultimo;

void Lista () {
    primeiro = newCelula(0);
    ultimo = primeiro;
}

void inserirIni (int x) {
    primeiro->elemento = x;
    Celula *tmp = newCelula(0);
    tmp->prox = primeiro;
    primeiro = tmp;
    tmp = NULL;
}
void inserirPos (int x, int pos) {
    if (pos < 0 || pos > tamanho()) exit(1);
    else if (pos == 0) inserirIni(x);
    else if (pos == tamanho()) inserirFim(x);
    else {
        Celula *i = primeiro;
        for (int j = 0; j < pos; j++) i = i->prox;
        Celula *tmp = newCelula(x);
        tmp->prox = i->prox;
        i->prox = tmp;
        i = tmp = NULL;
    }
}
void inserirFim (int x) {
    ultimo->prox = newCelula(x);
    ultimo = ultimo->prox;
}

int removerIni () {
    if (primeiro == ultimo) exit(1);
    Celula *tmp = primeiro->prox;
    int resp = tmp->elemento;
    primeiro->prox = tmp->prox;
    tmp->prox = NULL;
    free(tmp);
    tmp = NULL;
    if (primeiro->prox == NULL) ultimo = primeiro;
    return resp;
}
int removerPos (int pos) {
    if (primeiro == ultimo || pos < 0 || pos >= tamanho()) exit(1);
    else if (pos == 0) return removerIni();
    else if (pos == tamanho() - 1) return removerFim();
    else {
        Celula *i = primeiro;
        for (int j = 0; j < pos; j++) i = i->prox;
        Celula *tmp = i->prox;
        int resp = tmp->elemento;
        i->prox = tmp->prox;
        tmp->prox = NULL;
        free(tmp);
        i = tmp = NULL;
        return resp;
    }
}
int removerFim () {
    if (primeiro == ultimo) exit(1);
    Celula *i = primeiro;
    while (i->prox != ultimo) i = i->prox;
    int resp = ultimo->elemento;
    ultimo = i;
    free(ultimo->prox);
    i = ultimo->prox = NULL;
    return resp;
}

void inserirOrd (int x) {
    if (primeiro == ultimo || x >= ultimo->elemento) inserirFim(x);
    else if (x <= primeiro->prox->elemento) inserirIni(x);
    else {
        Celula *i = primeiro;
        while (i->prox != NULL && i->prox->elemento < x) i = i->prox;
        Celula *tmp = newCelula(x);
        tmp->prox = i->prox;
        i->prox = tmp;
        if (tmp->prox == NULL) ultimo = tmp;
    }
}

int tamanho () {
    int tamanho = 0;
    for (Celula *i = primeiro->prox; i != NULL; i = i->prox) tamanho++;
    return tamanho;
}

void mostrar () {
    printf("[ ");
    for (Celula *i = primeiro->prox; i != NULL; i = i->prox) printf("%d ", i->elemento);
    printf("]\n");
}
void mostrarRec (Celula *i) {
    if (i == primeiro->prox) printf("[ ");
    if (i != NULL) {
        printf("%d ", i->elemento);
        mostrarRec(i->prox);
    } else printf("]");
}
void mostrarInvRec (Celula *i) {
    if (i != NULL) {
        mostrarInvRec(i->prox);
        printf("%d ", i->elemento);
    } else printf("[ ");
    if (i == primeiro->prox) printf("]");
}
