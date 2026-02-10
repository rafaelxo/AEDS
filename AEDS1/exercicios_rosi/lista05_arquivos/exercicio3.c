#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    FILE *arquivo = fopen("arq2.txt", "r");
    int caracteres = 0;
    char caracter;
    while (fscanf(arquivo, "%c", &caracter) != EOF) if (caracter == 'a' || caracter == 'A') caracteres++;
    fclose(arquivo);
    printf("%d CARACTERES\n", caracteres);
}