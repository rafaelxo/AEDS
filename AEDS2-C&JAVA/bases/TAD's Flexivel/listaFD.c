#include <stdio.h>
#include <stdlib.h>

typedef struct CelulaDupla {
    int elemento;
    struct CelulaDupla *ant, *prox;
} CelulaDupla;

CelulaDupla *newCelula (int x) {
    CelulaDupla *nova = (CelulaDupla *)malloc(sizeof(CelulaDupla));
    nova->elemento = x;
    nova->ant = nova->prox = NULL;
    return nova;
}

CelulaDupla *primeiro, *ultimo;

void Lista () {
    primeiro = newCelula(0);
    ultimo = primeiro;
}

void inserirIni (int x) {
    primeiro->elemento = x;
    CelulaDupla *tmp = newCelula(0);
    tmp->prox = primeiro;
    primeiro->ant = tmp;
    primeiro = tmp;
    tmp = NULL;
}
void inserirPos (int x, int pos) {
    if (pos < 0 || pos > tamanho()) exit(1);
    else if (pos == 0) inserirIni(x);
    else if (pos == tamanho()) inserirFim(x);
    else {
        CelulaDupla *i = primeiro;
        for (int j = 0; j < pos; j++) i = i->prox;
        CelulaDupla *tmp = newCelula(x);
        tmp->ant = i;
        tmp->prox = i->prox;
        i->prox = tmp->prox->ant = tmp;
        i = tmp = NULL;
    }
}
void inserirFim (int x) {
    ultimo->prox = newCelula(x);
    ultimo->prox->ant = ultimo;
    ultimo = ultimo->prox;
}

int removerIni () {
    if (primeiro == ultimo) exit(1);
    CelulaDupla *tmp = primeiro->prox;
    int resp = tmp->elemento;
    primeiro->prox = tmp->prox;
    if (primeiro->prox != NULL) primeiro->prox->ant = primeiro;
    else ultimo = primeiro;
    tmp->prox = tmp->ant = NULL;
    free(tmp);
    tmp = NULL;
    return resp;
}
int removerPos (int pos) {
    if (primeiro == ultimo || pos < 0 || pos >= tamanho()) exit(1);
    else if (pos == 0) return removerIni();
    else if (pos == tamanho() - 1) return removerFim();
    else {
        CelulaDupla *i = primeiro->prox;
        for (int j = 0; j < pos; j++) i = i->prox;
        int resp = i->elemento;
        i->ant->prox = i->prox;
        i->prox->ant = i->ant;
        i->prox = i->ant = NULL;
        free(i);
        i = NULL;
        return resp;
    }
}
int removerFim () {
    if (primeiro == ultimo) exit(1);
    int resp = ultimo->elemento;
    ultimo = ultimo->ant;
    ultimo->prox->ant = NULL;
    free(ultimo->prox);
    ultimo->prox = NULL;
    return resp;
}

void inserirOrd (int x) {
    if (primeiro == ultimo || x >= ultimo->elemento) inserirFim(x);
    else if (x <= primeiro->prox->elemento) inserirIni(x);
    else {
        CelulaDupla *i = primeiro;
        while (i->prox != NULL && i->prox->elemento < x) i = i->prox;
        CelulaDupla *tmp = newCelula(x);
        tmp->ant = i;
        tmp->prox = i->prox;
        if (i->prox != NULL) i->prox->ant = tmp;
        i->prox = tmp;
        i = tmp = NULL;
    }
}

void inverter () {
    if (primeiro == ultimo) return;
    CelulaDupla *atual = primeiro->prox;
    CelulaDupla *next = NULL;
    while (atual != NULL) {
        next = atual->prox;
        atual->prox = atual->ant;
        atual->ant = next;
        atual = next;
    }
    CelulaDupla *aux = primeiro->prox;
    primeiro->prox = ultimo;
    ultimo = aux;
    if (primeiro->prox != NULL) primeiro->prox->ant = primeiro;
    if (ultimo != NULL) ultimo->prox = NULL;
}

void removerPares () {
    CelulaDupla *i = primeiro->prox;
    while (i != NULL) {
        CelulaDupla *aux = i->prox;
        if (i->elemento % 2 == 0) {
            i->ant->prox = i->prox;
            if (i->prox != NULL) i->prox->ant = i->ant;
            else ultimo = i->ant;
            i->prox = i->ant = NULL;
            free(i);
        }
        i = aux;
    }
}

int tamanho () {
    int tamanho = 0;
    for (CelulaDupla *i = primeiro->prox; i != NULL; i = i->prox) tamanho++;
    return tamanho;
}

void mostrar () {
    printf("[ ");
    for (CelulaDupla *i = primeiro->prox; i != NULL; i = i->prox) printf("%d ", i->elemento);
    printf("]\n");
}
void mostrarRec (CelulaDupla *i) {
    if (i == primeiro->prox) printf("[ ");
    if (i != NULL) {
        printf("%d ", i->elemento);
        mostrarRec(i->prox);
    } else printf("]");
}
void mostrarInvRec (CelulaDupla *i) {
    if (i != NULL) {
        mostrarInvRec(i->prox);
        printf("%d ", i->elemento);
    } else printf("[ ");
    if (i == primeiro->prox) printf("]\n");
}
