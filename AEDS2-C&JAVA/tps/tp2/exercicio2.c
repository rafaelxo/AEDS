#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool vogais (char str[]) { // método para verificar se a string recebida é formada apenas por vogais
    int i = 0;
    while (str[i] != '\0') { // loop para verificação até que atinja a condição de parada da string
        char c = str[i]; // atribuição de cada caracter para realizar a comparação a cada posição da string
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false; // verificação individual para validar somente letras, retornando falso caso seja símbolo ou número
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') return false; // mais uma verificação para validar se o caracter é diferente de uma vogal, retornando false
        i++;
    }
    return true;
}

bool consoantes (char str[]) { // método para verificar se a string recebida é formada apenas por consoantes
    int i = 0;
    while (str[i] != '\0') { // loop para verificação até que atinja a condição de parada da string
        char c = str[i]; //atribuição de cada caracter para realizar a comparação a cada posição da string
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false; // verificação individual para validar somente letras, retornando falso caso seja símbolo ou número
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return false; // mais uma verificação para validar se o caracter é uma vogal, retornando false
        i++;
    }
    return true; // se não cair no retorno da estrutura condicional, retorna true
}

bool inteiros (char str[]) { // método para verificar se a string recebida é um número inteiro
    int i = 0;
    while (str[i] != '\0') { // loop para verificação até que atinja a condição de parada da string
        if (str[i] < '0' || str[i] > '9') return false; // verificação individual de cada caracter, comparando-o com numeros inteiros e retornando false caso a condição for verdadeira
        i++;
    }
    return true; // se não cair no retorno da estrutura condicional, retorna true
}

bool reais (char str[]) { // método para verificar se a string recebida é um número real
    int i = 0, virgula = 0;
    while (str[i] != '\0') { // loop para verificação até que atinja a condição de parada da string
        if (str[i] == '.') { // verificação individual para validar a vírgula de um número real
            virgula++;
            if (virgula > 1) return false; // se tiver mais de um ponto, retorna false
        }
        else if ((str[i] < '0' || str[i] > '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) return false; // mais uma verificação para validar somente números, retornando falso caso seja símbolo ou letra
        i++;
    }
    if (virgula == 1) return true; // verificação de presença de somente uma vírgula para um número real, retornando verdadeiro
    return false; // se não, retorno falso como padrão
}

int main () { // main do programa
    char str[500]; scanf(" %[^\n]", str); // declração e leitura da string
    while (!(str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0')) { // loop para ler string e verificar seus métodos enquanto a string seja diferente de "FIM"
        bool x1 = vogais(str);
        bool x2 = consoantes(str);
        bool x3 = inteiros(str);
        bool x4 = reais(str); // variáveis booleanas individuais para armazenar cada resposta dos métodos
        printf("%s %s %s %s\n", x1 ? "SIM" : "NAO", x2 ? "SIM" : "NAO", x3 ? "SIM" : "NAO", x4 ? "SIM" : "NAO"); // saída utilizando operador ternário com base no retorno dos métodos (true = SIM, false = NAO)
        scanf(" %[^\n]", str); // leitura da próxima string
    }
    return 0;
}
