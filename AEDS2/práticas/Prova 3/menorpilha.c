#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Celula *topo;

void Pilha () { topo = NULL; }

void push (int x) {
    Celula *tmp = newCelula(x);
    tmp->prox = topo;
    topo = tmp;
    tmp = NULL;
}
int pop () {
    if (topo == NULL) exit(1);
    int resp = topo->elemento;
    Celula *tmp = topo;
    topo = topo->prox;
    tmp->prox = NULL;
    free(tmp);
    tmp = NULL;
    return resp;
}

int main () {
    int n;
    scanf("%d", &n);
    Pilha();
    for (int i = 0; i < n; i++) {
        char comando[10];
        scanf("%s", comando);
        if (strcmp(comando, "PUSH") == 0) {
            int valor;
            scanf("%d", &valor);
            push(valor);
        } else if (strcmp(comando, "POP") == 0) {
            if (topo == NULL) printf("EMPTY\n");
            else pop();
        } else if (strcmp(comando, "MIN") == 0) {
            if (topo == NULL) printf("EMPTY\n");
            else {
                Celula *atual = topo;
                int menor = atual->elemento;
                while (atual != NULL) {
                    if (atual->elemento < menor) menor = atual->elemento;
                    atual = atual->prox;
                }
                printf("%d\n", menor);
            }
        }
    }
    return 0;
}
