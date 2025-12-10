#include <stdio.h>
#include <stdlib.h>

int tamTab = 0;
int tamRes = 0;
int qtd = 0;

int** inicializar (int x, int y) {
    tamTab = x;
    tamRes = y;
    int* tabela = (int*)malloc(x*sizeof(int*));
    for (int i = 0; i < x; i++) tabela[i] = -1;
    int* reserva = (int*)malloc(y*sizeof(int));
    for (int i = 0; i < y; i++) reserva[i] = -1;
    int** resp = (int**)malloc(2*sizeof(int*));
    resp[0] = tabela;
    resp[1] = reserva;
    return resp;
}

int hashar (int x) { return x % tamTab; }

void inserir (int x, int* tabela, int* reserva) {
    if (x != -1) {
        int i = hashar(x);
        if (tabela[i] == -1) tabela[i] = x;
        else if (qtd < tamRes) reserva[qtd++] = x;
        else printf("Capacidade da tabela excedida!\n");
    }
}

int pesquisar (int x, int* tabela, int* reserva) {
    int i = hashar(x);
    if (tabela[i] == x) return i;
    if (tabela[i] != -1) {
        for (int j = 0; j < qtd; j++) {
            if (reserva[j] == x) return tamTab + j;
        }
    }
    return -1;
}

int remover (int x, int* tabela, int* reserva) {
    int i = hashar(x);
    if (tabela[i] == x) {
        tabela[i] = -1;
        return i;
    } else {
        for (int j = 0; j < qtd; j++) {
            if (reserva[j] == x) {
                reserva[j] = -1;
                qtd--;
                return tamTab + j;
            }
        }
    }
    return -1;
}



