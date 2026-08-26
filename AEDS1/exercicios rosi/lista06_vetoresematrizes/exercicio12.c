#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void troca (char *a, char *b) {
    char aux = *a;
    *a = *b;
    *b = aux;
}

void permutacao (char *texto, int inicio, int final) {
    if (inicio == final) printf("%s ", texto);
    else {
        for (int i = inicio; i <= final; i++) {
            troca((texto + inicio), (texto + i));
            permutacao(texto, inicio + 1, final);
            troca((texto + inicio), (texto + i));
        }
    }
}

int main () {
    char *texto = (char*)malloc(100*sizeof(char));
    scanf(" %[^\n]", texto);
    int tam = strlen(texto);
    printf("As permutações da string são:\n");
    permutacao(texto, 0, tam - 1);
    printf("\n");
    free(texto);
}