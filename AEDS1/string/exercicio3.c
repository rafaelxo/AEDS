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

int contaConsoantes (char *texto) {
    int cons = 0;
    for (int i = 0; i < tamanhoTexto(texto); i++) {
        *(texto + i) = tolower(*(texto + i));
        if (*(texto + i) >= 'a' && *(texto + i) <= 'z') cons++;
    }
    return (cons - contaVogais(texto));
}

int contaPalavras (char *texto) {
    char palavras = 0;
    char *token = strtok(texto, " ,.!?-;*/");
    while (token) {
        palavras++;
        token = strtok(NULL, " ,.!?-;*/");
    }
    return palavras;
}

int main () {
    geraArquivo();
    FILE *dados = fopen("vogais.txt", "r");
    char *linha = (char*)malloc(100*sizeof(char));
    char copia[100];
    while(fscanf(dados, " %[^\n]", linha) != EOF) {
        strcpy(copia, linha);
        printf("Na frase \"%s\" tem %d caracteres, %d vogais, %d consoantes e %d palavras!\n", linha, tamanhoTexto(linha), contaVogais(linha), contaConsoantes(linha), contaPalavras(copia));
    }
    fclose(dados);
    free(linha);
}