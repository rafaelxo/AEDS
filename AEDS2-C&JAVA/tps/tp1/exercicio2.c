#include <stdlib.h>
#include <stdio.h>

int palindromo (char str[]) { // método para verificar se a string é um palíndromo
    int resp = 0; //declaração do retorno inteiro do método
    if (str[0] == '\0')

    return resp; // retorno do método
}

int main () { // main do programa
    char str[100]; scanf(" %[^\n]", str); //declaração e leitura da string
    while (!(str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0')) { // loop para ler string e verificar se essa é um palíndromo enquanto a string seja diferente de "FIM"
        if (palindromo(str) == 1) printf("SIM\n"); // se for palíndromo, imprime "SIM"
        else printf("NAO\n"); // se não, imprime "NAO"
        scanf(" %[^\n]", str); // leitura da próxima string
    }
    return 0;
}
