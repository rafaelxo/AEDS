#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void geraArquivo () {
    FILE *arq = fopen("vogais.txt", "w");
    char *frase = (char*)malloc(100*sizeof(char));
    printf("Insira uma frase (sair para finalizar):\n");
    scanf(" %[^\n]", frase);
    while (strcmp(frase, "sair") != 0) {
        printf("Tamanho da frase: %d\n", tamanhoTexto(frase));
        fprintf(arq, "%s\n", frase);
        printf("Insira uma frase (sair para finalizar):\n");
        scanf(" %[^\n]", frase);
    }
    fclose(arq);
}

int tamanhoTexto (char *texto) {
    int tam = 0;
    while(*(texto + tam) != '\0') tam++;
    return tam;
}

int contaVogais (char *texto) {
    int vogais = 0;
    for (int i = 0; i < tamanhoTexto(texto); i++) {
        *(texto + i) = tolower(*(texto + i));
        if (*(texto + i) == 'a' || *(texto + i) == 'e' || *(texto + i) == 'i' || *(texto + i) == 'o' || *(texto + i) == 'u') vogais++;
    }
    return vogais;
}

int main () {
    geraArquivo();
    FILE *dados = fopen("vogais.txt", "r");
    char *linha = (char*)malloc(50*sizeof(char));
    while(fscanf(dados, " %[^\n]", linha) != EOF) printf("Na frase \"%s\" tem %d vogais!\n", linha, contaVogais(linha));
    fclose(dados);
    free(linha);
}