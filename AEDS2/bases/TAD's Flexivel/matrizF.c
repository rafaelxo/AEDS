#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int elemento;
    struct Celula *esq, *dir, *sup, *inf;
} Celula;

Celula *newCelula(int x) {
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->elemento = x;
    nova->esq = nova->dir = nova->sup = nova->inf = NULL;
    return nova;
}

typedef struct Matriz {
    Celula *inicio;
    int linhas, colunas;
} Matriz;

Matriz *newMatriz (int l, int c) {
    if (l <= 0 || c <= 0) exit(1);
    Matriz *m = (Matriz *)malloc(sizeof(Matriz));
    m->linhas = l;
    m->colunas = c;
    m->inicio = newCelula(0);
    Celula *lin = m->inicio, *col = m->inicio;
    for (int j = 1; j < c; j++) {
        col->dir = newCelula(0);
        col->dir->esq = col;
        col = col->dir;
    }
    for (int i = 1; i < l; i++) {
        lin->inf = newCelula(0);
        lin->inf->sup = lin;
        lin = lin->inf;
        col = lin;
        for (int j = 1; j < c; j++) {
            col->dir = newCelula(0);
            col->dir->esq = col;
            col = col->dir;
            col->sup = col->esq->sup->dir;
            col->sup->inf = col;
        }
    }
    return m;
}

int somaDiagPrinc (Matriz *m) {
    if (m->linhas != m->colunas || m->inicio == NULL) exit(1);
    Celula *i = m->inicio;
    int soma = i->elemento;
    while (i->dir != NULL && i->inf != NULL) {
        i = i->dir->inf;
        soma += i->elemento;
    }
    i = NULL;
    return soma;
}

void circular (Matriz *m) {
    Celula *ini = m->inicio;
    Celula *fim;
    for (fim = ini; fim->inf != NULL; fim = fim->inf);
    while (ini->dir != NULL) {
        fim->inf = ini;
        ini->sup = fim;
        ini = ini->dir;
        fim = fim->dir;
    }
    ini = m->inicio;
    for (fim = ini; fim->dir != NULL; fim = fim->dir);
    while (ini->inf != NULL) {
        fim->dir = ini;
        ini->esq = fim;
        ini = ini->inf;
        fim = fim->inf;
    }
}

void freeMatriz (Matriz *m) {
    if (m == NULL) return;
    Celula *linhaAtual = m->inicio;
    while (linhaAtual != NULL) {
        Celula *proxLinha = linhaAtual->inf;
        Celula *celulaAtual = linhaAtual;
        while (celulaAtual != NULL) {
            Celula *proxCelula = celulaAtual->dir;
            free(celulaAtual);
            celulaAtual = proxCelula;
        }
        linhaAtual = proxLinha;
    }
    free(m);
}

void mostrar (Matriz *m) {
    Celula *tmp = m->inicio;
    for (int i = 0; i < m->linhas && tmp != NULL; i++) {
        printf("[ ");
        Celula *atual = tmp;
        for (int j = 0; j < m->colunas && atual != NULL; j++) {
            printf("%d ", atual->elemento);
            atual = atual->dir;
        }
        printf("]\n");
        tmp = tmp->inf;
    }
}
