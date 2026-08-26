#include <stdlib.h>
#include <stdio.h>

typedef struct cliente {
    char *nome;
    char *endereco;
    char *telefone;
} Cl;

int main () {
    Cl clientes[2];
    for (int i = 0; i < 2; i++) {
        clientes[i].nome = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", clientes[i].nome);
        clientes[i].endereco = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", clientes[i].endereco);
        clientes[i].telefone = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", clientes[i].telefone);
    }
    for (int i = 0; i < 2; i ++) printf("%s %s %s\n", clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
    for (int i = 0; i < 2; i++) {
        free(clientes[i].nome);
        free(clientes[i].endereco);
        free(clientes[i].telefone);
    }
}