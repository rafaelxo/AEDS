#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoAN {
    int elemento;
    bool cor;
    struct NoAN *esq, *dir;
} NoAN;

NoAN *newNo (int x) {
    NoAN *novo = (NoAN*)malloc(sizeof(NoAN));
    novo->elemento = x;
    novo->cor = false;
    novo->esq = novo->dir = NULL;
    return novo;
}

NoAN *raiz;

void ArvoreAN () {
    raiz = NULL;
}

NoAN* rotacionarDir (NoAN *i) {
    NoAN *noEsq = i->esq;
    NoAN *noEsqDir = noEsq->dir;
    noEsq->dir = i;
    i->esq = noEsqDir;
    return noEsq;
}
NoAN* rotacionarEsq (NoAN *i) {
    NoAN *noDir = i->dir;
    NoAN *noDirEsq = noDir->esq;
    noDir->esq = i;
    i->dir = noDirEsq;
    return noDir;
}
NoAN* rotacionarDirEsq (NoAN *i) {
    i->dir = rotacionarDir(i->dir);
    return rotacionarEsq(i);
}
NoAN* rotacionarEsqDir (NoAN *i) {
    i->esq = rotacionarEsq(i->esq);
    return rotacionarDir(i);
}

void balancear (NoAN *bis, NoAN *avo, NoAN *pai, NoAN *i) {
    if (pai->cor == true) {
        if (pai->elemento > avo->elemento) {
            if (i->elemento > pai->elemento) avo = rotacionarEsq(avo);
            else avo = rotacionarDirEsq(avo);
        } else {
            if (i->elemento < pai->elemento) avo = rotacionarDir(avo);
            else avo = rotacionarEsqDir(avo);
        }
        if (bis == NULL) raiz = avo;
        else if (avo->elemento < bis->elemento) bis->esq = avo;
        else bis->dir = avo;
        avo->cor = false;
        avo->esq->cor = avo->dir->cor = true;
    }
}

void inserirRec (int x, NoAN *bis, NoAN *avo, NoAN *pai, NoAN *i) {
    if (i == NULL) {
        if (x < pai->elemento) i = pai->esq = newNo(x);
        else i = pai->dir = newNo(x);
        if (pai->cor == true) balancear(bis, avo, pai, i);
    } else {
        if (i->esq != NULL && i->dir != NULL && i->esq->cor == true && i->dir->cor == true) {
            i->cor = true;
            i->esq->cor = i->dir->cor = false;
            if (i == raiz) i->cor = false;
            else if (pai->cor == true) balancear(bis, avo, pai, i);
        }
        if (x < i->elemento) inserirRec(x, pai, avo, i, i->esq);
        else if (x > i->elemento) inserirRec(x, pai, avo, i, i->dir);
        else exit(1);
    }
}
void inserir (int x) {
    if (raiz == NULL) raiz = newNo(x);
    else if (raiz->esq == NULL && raiz->dir == NULL) {
        if (x < raiz->elemento) raiz->esq = newNo(x);
        else if (x > raiz->elemento) raiz->dir = newNo(x);
    } else if (raiz->esq == NULL) {
        if (x < raiz->elemento) raiz->esq = newNo(x);
        else if (x < raiz->dir->elemento) {
            raiz->esq = newNo(raiz->elemento);
            raiz->elemento = x;
        } else {
            raiz->esq = newNo(raiz->elemento);
            raiz->elemento = raiz->dir->elemento;
            raiz->dir->elemento = x;
        }
        raiz->esq->cor = raiz->dir->cor = false;
    } else if (raiz->dir == NULL) {
        if (x > raiz->elemento) raiz->dir = newNo(x);
        else if (x > raiz->esq->elemento) {
            raiz->dir = newNo(raiz->elemento);
            raiz->elemento = x;
        } else {
            raiz->dir = newNo(raiz->elemento);
            raiz->elemento = raiz->esq->elemento;
            raiz->esq->elemento = x;
        }
        raiz->esq->cor = raiz->dir->cor = false;
    } else inserirRec(x, NULL, NULL, NULL, raiz);
    raiz->cor = false;
}

bool pesquisarNo (NoAN *i, int x) {
    if (i == NULL) return false;
    else if (x == i->elemento) return true;
    else if (x < i->elemento) return pesquisarNo(i->esq, x);
    else return pesquisarNo(i->dir, x);
}
bool pesquisar (int x) {
    return pesquisarNo(raiz, x);
}

NoAN* removerNo (int x, NoAN *i) {
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

NoAN* maiorEsq (NoAN *i, NoAN *j) {
    if (j->dir == NULL) {
        i->elemento = j->elemento;
        j = j->esq;
    }
    else j->dir = maiorEsq(i, j->dir);
    return j;
}
NoAN* menorDir (NoAN *i, NoAN *j) {
    if (j->esq == NULL) {
        i->elemento = j->elemento;
        j = j->dir;
    }
    else j->esq = menorDir(i, j->esq);
    return j;
}

void caminharCentral (NoAN *i) {
    if (i != NULL) {
        caminharCentral(i->esq);
        printf("%d %s ", i->elemento, (i->cor ? "(P)" : "(B)"));
        caminharCentral(i->dir);
    }
}
void caminharPre (NoAN *i) {
    if (i != NULL) {
        printf("%d %s ", i->elemento, (i->cor ? "(P)" : "(B)"));
        caminharPre(i->esq);
        caminharPre(i->dir);
    }
}
void caminharPos (NoAN *i) {
    if (i != NULL) {
        caminharPos(i->esq);
        caminharPos(i->dir);
        printf("%d %s ", i->elemento, (i->cor ? "(P)" : "(B)"));
    }
}

int getAlturaRec (NoAN *i) {
    if (i == NULL) return 0;
    else {
        int altEsq = getAlturaRec(i->esq);
        int altDir = getAlturaRec(i->dir);
        return (altEsq > altDir ) ? altEsq + 1: altDir + 1;
    }
}

int getMaior () {
    if (raiz == NULL) exit(1);
    NoAN *i;
    for (i = raiz; i->dir != NULL; i = i->dir);
    return i->elemento;
}
int getMenor () {
    if (raiz == NULL) exit(1);
    NoAN *i;
    for (i = raiz; i->esq != NULL; i = i->esq);
    return i->elemento;
}

int somarRec (NoAN *i) {
    if (i == NULL) return 0;
    return i->elemento + somarRec(i->esq) + somarRec(i->dir);
}

bool igual (NoAN *a, NoAN *b) {
    if (a == NULL && b == NULL) return true;
    else if (a == NULL || b == NULL) return false;
    else if (a->elemento != b->elemento) return false;
    else return igual(a->esq, b->esq) && igual(a->dir, b->dir);
}
bool igualArvore (NoAN *outraRaiz) {
    return igual(raiz, outraRaiz);
}
bool espelho (NoAN *a, NoAN *b) {
    if (a == NULL && b == NULL) return true;
    else if (a == NULL || b == NULL) return false;
    else if (a->elemento != b->elemento) return false;
    else return espelho(a->esq, b->dir) && espelho(a->dir, b->esq);
}
bool espelhoArvore (NoAN *outraRaiz) {
    return espelho(raiz, outraRaiz);
}
