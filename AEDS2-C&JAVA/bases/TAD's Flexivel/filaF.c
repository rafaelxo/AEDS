#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

Celula *newCelula (int x) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = x;
    nova->prox = NULL;
    return nova;
}

Celula *primeiro, *ultimo;

void Fila () {
    primeiro = newCelula(0);
    ultimo = primeiro;
}

void inserir (int x) {
    ultimo->prox = newCelula(x);
    ultimo = ultimo->prox;
}

int remover () {
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

int somar () {
    int soma = 0;
    for (Celula *i = primeiro->prox; i != NULL; i = i->prox) soma += i->elemento;
    return soma;
}
int somarRec (Celula *i) {
    if (i == NULL) return 0;
    else return i->elemento + somarRec(i->prox);
}

int maior () {
    int maior = primeiro->prox->elemento;
    for (Celula *i = primeiro->prox->prox; i != NULL; i = i->prox) {
        if (i->elemento > maior) maior = i->elemento;
    }
    return maior;
}
int maiorRec (Celula *i) {
    if (i == NULL) return 0;
    else return (i->elemento > maiorRec(i->prox)) ? i->elemento : maiorRec(i->prox);
}

void inverter () {
    Celula *prev = NULL, *next = NULL, *atual = primeiro->prox;
    while (atual != NULL) {
        next = atual->prox;
        atual->prox = prev;
        prev = atual;
        atual = next;
    }
    ultimo = primeiro->prox;
    primeiro->prox = prev;
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
    } else printf("]\n");
}
void mostrarRecInv (Celula *i) {
    if (i != NULL) {
        mostrarRecInv(i->prox);
        printf("%d ", i->elemento);
    } else printf("[ ");
    if (i == primeiro->prox) printf("]\n");
}
