#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int elemento;
    struct No *esq, *dir;
} No;

No *newNo (int x) {
    No *novo = (No*)malloc(sizeof(No));
    novo->elemento = x;
    novo->esq = novo->dir = NULL;
    return novo;
}

No *raiz;

void ArvoreBIN () {
    raiz = NULL;
}

No* inserirRefArvore (int x, No *i) {
    if (i == NULL) i = newNo(x);
    else if (x < i->elemento) i->esq = inserirRefArvore(x, i->esq);
    else if (x > i->elemento) i->dir = inserirRefArvore(x, i->dir);
    else exit(1);
    return i;
}
void inserirRef (int x) {
    raiz = inserirRefArvore(x, raiz);
}

void inserirPaiArvore (int x, No *i, No *pai) {
    if (i == NULL) {
        if (x < pai->elemento) pai->esq = newNo(x);
        else pai->dir = newNo(x);
    } else if (x < i->elemento) inserirPaiArvore(x, i->esq, i);
    else if (x > i->elemento) inserirPaiArvore(x, i->dir, i);
    else exit(1);
}
void inserirPai (int x) {
    if (raiz == NULL) raiz = newNo(x);
    else if (x < raiz->elemento) inserirPaiArvore(x, raiz->esq, raiz);
    else if (x > raiz->elemento) inserirPaiArvore(x, raiz->dir, raiz);
    else exit(1);
}

bool pesquisarNo (No *i, int x) {
    if (i == NULL) return false;
    else if (x == i->elemento) return true;
    else if (x < i->elemento) return pesquisarNo(i->esq, x);
    else return pesquisarNo(i->dir, x);
}
bool pesquisar (int x) {
    return pesquisarNo(raiz, x);
}

No* removerNo (int x, No *i) {
    if (i == NULL) exit(1);
    else if (x < i->elemento) i->esq = removerNo(x, i->esq);
    else if (x > i->elemento) i->dir = removerNo(x, i->dir);
    else if (i->dir == NULL) i = i->esq;
    else if (i->esq == NULL) i = i->dir;
    else i->esq = maiorEsq(i, i->esq);
    return i;
}
void remover (int x) {
    raiz = removerNo(x, raiz);
}

No* maiorEsq (No *i, No *j) {
    if (j->dir == NULL) {
        i->elemento = j->elemento;
        j = j->esq;
    }
    else j->dir = maiorEsq(i, j->dir);
    return j;
}
No* menorDir (No *i, No *j) {
    if (j->esq == NULL) {
        i->elemento = j->elemento;
        j = j->dir;
    }
    else j->esq = menorDir(i, j->esq);
    return j;
}

void caminharCentral (No *i) {
    if (i != NULL) {
        caminharCentral(i->esq);
        printf("%d ", i->elemento);
        caminharCentral(i->dir);
    }
}
void caminharPre (No *i) {
    if (i != NULL) {
        printf("%d ", i->elemento);
        caminharPre(i->esq);
        caminharPre(i->dir);
    }
}
void caminharPos (No *i) {
    if (i != NULL) {
        caminharPos(i->esq);
        caminharPos(i->dir);
        printf("%d ", i->elemento);
    }
}

int getAlturaRec (No *i) {
    if (i == NULL) return 0;
    else {
        int altEsq = getAlturaRec(i->esq);
        int altDir = getAlturaRec(i->dir);
        return (altEsq > altDir ) ? altEsq + 1: altDir + 1;
    }
}

int getMaior () {
    if (raiz == NULL) exit(1);
    No *i;
    for (i = raiz; i->dir != NULL; i = i->dir);
    return i->elemento;
}
int getMenor () {
    if (raiz == NULL) exit(1);
    No *i;
    for (i = raiz; i->esq != NULL; i = i->esq);
    return i->elemento;
}

int somarRec (No *i) {
    if (i == NULL) return 0;
    return i->elemento + somarRec(i->esq) + somarRec(i->dir);
}

bool igual (No *a, No *b) {
    if (a == NULL && b == NULL) return true;
    else if (a == NULL || b == NULL) return false;
    else if (a->elemento != b->elemento) return false;
    else return igual(a->esq, b->esq) && igual(a->dir, b->dir);
}
bool igualArvore (No *a, No *b) {
    return igual(a, b);
}
bool espelho (No *a, No *b) {
    if (a == NULL && b == NULL) return true;
    else if (a == NULL || b == NULL) return false;
    else if (a->elemento != b->elemento) return false;
    else return espelho(a->esq, b->dir) && espelho(a->dir, b->esq);
}
bool espelhoArvore (No *a, No *b) {
    return espelho(a, b);
}
