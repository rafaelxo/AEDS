#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TAM 100

int array[MAX_TAM];
int primeiro = 0, ultimo = 0;

void inserir (int x) {
    if ((ultimo + 1) % MAX_TAM == primeiro) exit(1);
    array[ultimo] = x;
    ultimo = (ultimo + 1) % MAX_TAM;
}

int remover () {
    if (primeiro == ultimo) exit(1);
    int resp = array[primeiro];
    primeiro = (primeiro + 1) % MAX_TAM;
    return resp;
}

bool vazia () { return primeiro == ultimo; }

int tamanho () {
    if (ultimo >= primeiro) return ultimo - primeiro;
    else return ultimo - primeiro + MAX_TAM;
}

bool pesquisar (int x) {
    for (int i = primeiro; i != ultimo; i = (i + 1) % MAX_TAM) {
        if (array[i] == x) return true;
    }
    return false;
}

bool palindromo () {
    int ini = primeiro, fim = (ultimo - 1 + MAX_TAM) % MAX_TAM;
    int i = 0;
    while (i < tamanho() / 2) {
        if (array[ini] != array[fim]) return false;
        ini = (ini + 1) % MAX_TAM;
        fim = (fim - 1 + MAX_TAM) % MAX_TAM;
        i++;
    }
    return true;
}

void mostrar () {
    printf("[ ");
    for (int i = primeiro; i != ultimo; i = (i + 1) % MAX_TAM) printf("%d ", array[i]);
    printf("]\n");
}
void mostrarRec (int i) {
    if (i == primeiro) printf("[ ");
    if (i != ultimo) {
        printf("%d ", array[i]);
        mostrarRec((i + 1) % MAX_TAM);
    } else printf("]\n");
}
void mostrarInvertido () {
    if (primeiro == ultimo) exit(1);
    printf("[ ");
    int quant = tamanho() % MAX_TAM;
    for (int i = quant - 1; i >= 0; i--) {
        int j = (primeiro + i) % MAX_TAM;
        printf("%d ", array[j]);
    }
    printf("]\n");
}
