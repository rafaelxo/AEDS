#include <stdlib.h>
#include <stdio.h>

typedef struct loja {
    char *nome;
    char *tel;
    float preco;
} Lj;

int main () {
    Lj lojas[15];
    float media = 0;
    for (int i = 0; i < 15; i++) {
        (lojas + i)->nome = (char*)malloc(100*sizeof(char));
        (lojas + i)->tel = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (lojas + i)->nome);
        scanf(" %[^\n]", (lojas + i)->tel);
        scanf("%f", &lojas[i].preco);
        media += lojas[i].preco;
    }
    media /= 15;
    printf("A média dos precos cadastrados é: %.2f\n", media);
    printf("Lojas com precos abaixo da média:\n");
    for (int i = 0; i < 15; i++) {
        if (lojas[i].preco < media) printf("Nome: %s\nTelefone: %s\n", (lojas + i)->nome, (lojas + i)->tel);
    }
    for (int i = 0; i < 15; i++) {
        free((lojas + i)->nome);
        free((lojas + i)->tel);
    }
}