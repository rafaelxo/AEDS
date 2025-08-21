#include <stdlib.h>
#include <stdio.h>

int length (char str[]) { // método para calcular o tamanho da string
    int i = 0; // contador para o tamanho da string
    while (str[i] != '\0') i++; // incrementa o contador até encontrar o fim da string
    return i; //retorno do tamanho da string
}

int palindromoBase (char str[]) { // método base para o recursivo
    return palindromoReal(str, 0, length(str) - 1); // chama o método recursivo com os índices inicial e final da string
}

int palindromoReal (char str[], int i, int j) { // método para verificar se a string é um palíndromo
    int resp = 0; //declaração do retorno inteiro do método
    if (i >= j) resp = 1;
    else if (str[i] != str[j]) resp = 0;
    else resp = palindromoReal(str, i + 1, j - 1); // chama o método recursivo com os índices incrementados e decrementados
    return resp; // retorno do método (1 para sim, 0 para não)
}

int main () { // main do programa
    char str[500]; scanf(" %[^\n]", str); //declaração e leitura da string
    while (!(str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0')) { // loop para ler string e verificar se essa é um palíndromo enquanto a string seja diferente de "FIM"
        if (palindromoBase(str) == 1) printf("SIM\n"); // se for palíndromo, imprime "SIM"
        else printf("NAO\n"); // se não, imprime "NAO"
        scanf(" %[^\n]", str); // leitura da próxima string
    }
    return 0;
}
