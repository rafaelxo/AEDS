#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {
    FILE *arquivo = fopen("arq5.txt", "w");
    char texto1[100], texto2[100];
    FILE *arquivo1 = fopen("arq5E1.txt", "r");
    while (fscanf(arquivo1, " %[^\n]", texto1) != EOF) fprintf(arquivo, "%s\n", texto1);
    fclose(arquivo1);
    FILE *arquivo2 = fopen("arq5E2.txt", "r");
    while (fscanf(arquivo2, " %[^\n]", texto2) != EOF) fprintf(arquivo, "%s\n", texto2);
    fclose(arquivo2);
    fclose(arquivo);
}