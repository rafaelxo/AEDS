#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    FILE *arquivo = fopen("arq4.txt", "r");
    int linhas = 0;
    char texto[100];
    while (fscanf(arquivo, " %[^\n]", &texto) != EOF) {
        printf("%s\n", texto);
        linhas++;
    }
    fclose(arquivo);
    printf("%d LINHAS\n", linhas);
}