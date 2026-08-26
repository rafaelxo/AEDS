#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    FILE *arquivo = fopen("arq2.txt", "w");
    char texto[100];
    scanf(" %[^\n]", texto);
    fprintf(arquivo, "%s", texto);
    fclose(arquivo);
}