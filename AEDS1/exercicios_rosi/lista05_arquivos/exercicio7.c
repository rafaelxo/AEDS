#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () {
    FILE *arquivo = fopen("arq7.txt", "w");
    int N, vogais = 0;
    char letra;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf(" %c", &letra);
        fprintf(arquivo, "%c\n", letra);
    }
    fclose(arquivo);
    arquivo = fopen("arq7.txt", "r");
    while (fscanf(arquivo, "%c", &letra) != EOF) {
        letra = toupper(letra);
        if (letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U') vogais++;
    }
    fclose(arquivo);
    printf("%d\n", vogais);
}