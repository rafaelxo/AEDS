#include <stdio.h>
#include <stdlib.h>

int tam = 0;

int* inicializar (int x) {
    tam = x;
    int* tabela = (int*)malloc(x*sizeof(int*));
    for (int i = 0; i < x; i++) tabela[i] = -1;
    return tabela;
}

int hashar (int x) { return x % tam; }
int rehashar (int x) { return ++x % tam; }

void inserir (int x, int* tabela) {
    if (x != -1) {
        int i = hashar(x);
        if (tabela[i] == -1) tabela[i] = x;
        else if (tabela[i] != x) {
            int j = rehashar(x);
            if (tabela[j] == -1) tabela[j] = x;
        }
        else printf("Erro!\n");
    }
}

int pesquisar (int x, int* tabela) {
    int i = hashar(x);
    if (tabela[i] == x) return i;
    if (tabela[i] != -1) {
        int j = rehashar(x);
        if (tabela[j] == x) return j;
    }
    return -1;
}

int remover (int x, int* tabela, int* reserva) {
    int i = hashar(x);
    if (tabela[i] == x) {
        tabela[i] = -1;
        return i;
    } else {
        int j = rehashar(x);
        if (tabela[j] == x) {
            tabela[j] = -1;
            return j;
        }
    }
    return -1;
}



