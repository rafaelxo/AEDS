#include <stdio.h>
#include <stdbool.h>

bool isFim (char str[]) {
    return (str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0');
}

bool vogaisRec (char str[], int i) { // método para verificar se a string recebida é formada apenas por vogais
    if (str[i] == '\0') return true; // condição de parada da recursão, quando atingiu o fim da string
    char c = str[i]; // atribuição do caractere atual da string a um char para facilitar as comparações
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false; // verificação individual para validar somente letras, retornando falso caso seja símbolo ou número
    if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') return false; // mais uma verificação para validar se o caracter é diferente de uma vogal, retornando false
    else return vogaisRec(str, i + 1); // se não cair em nenhuma condicional, chama a recursão passando a string e o próximo caractere
}

bool vogaisRecBase(char str[]) { // método para fazer a primeira chamada à recursão
    return vogaisRec(str, 0);
}

bool consoantesRec (char str[], int i) { // método para verificar se a string recebida é formada apenas por consoantes
    if (str[i] == '\0') return true; // condição de parada da recursão, quando atingiu o fim da string
    char c = str[i]; // atribuição do caractere atual da string a um char para facilitar as comparações
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false; // verificação individual para validar somente letras, retornando falso caso seja símbolo ou número
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return false; // mais uma verificação para validar se o caracter é uma vogal, retornando false
    else return consoantesRec(str, i + 1); // se não cair em nenhuma condicional, chama a recursão passando a string e o próximo caractere
}

bool consoantesRecBase(char str[]) { // método para fazer a primeira chamada à recursão
    return consoantesRec(str, 0);
}

bool inteirosRec (char str[], int i) { // método para verificar se a string recebida é um número inteiro
    if (str[0] == '\0') return false; // condição para verificar se a string está vazia
    if (str[i] == '\0') return true; // condição de parada da recursão, quando atingiu o fim da string
    if (str[i] < '0' || str[i] > '9') return false; // verificação individual de cada caracter, comparando-o com numeros inteiros e retornando false caso a condição for verdadeira
    else return inteirosRec(str, i + 1); // se não cair no retorno da estrutura condicional, retorna true
}

bool inteirosRecBase(char str[]) { // método para fazer a primeira chamada à recursão
    return inteirosRec(str, 0);
}

bool reaisRec (char str[], int i, int virgula) { // método para verificar se a string recebida é um número real
    if (str[0] == '\0') return false; // condição para verificar se a string está vazia
    if (str[i] == '\0') return (i > 0 && !(str[i - 1] == '.' || str[i - 1] == ',')); // condição de parada da recursão, quando atingiu o fim da string
    char c = str[i]; // atribuição do caractere atual da string a um char para facilitar as comparações
    if (str[i] == '.' || str[i] == ',') {
        if (virgula > 1) return false;
        return reaisRec(str, i + 1, virgula + 1);
    }
    if (c < '0' || c > '9') return false; // mais uma verificação para validar somente números, retornando falso caso seja símbolo ou letra (com exceção do '.' e ',', já verificados anteriormente)
    return reaisRec(str, i + 1, virgula); // retorno true caso não caia em nenhuma das condições de retorno false
}

bool reaisRecBase(char str[]) { // método para fazer a primeira chamada à recursão
    return reaisRec(str, 0, 0);
}

int main() { // main do programa
    char str[500]; scanf(" %[^\n]", str); // declaração e leitura da string
    while (!isFim(str)) { // loop para ler strings e verificar seus métodos enquanto a string seja diferente de "FIM"
        printf("%s ", vogaisRecBase(str) ? "SIM" : "NAO");
        printf("%s ", consoantesRecBase(str) ? "SIM" : "NAO");
        printf("%s ", inteirosRecBase(str) ? "SIM" : "NAO");
        printf("%s\n", reaisRecBase(str) ? "SIM" : "NAO");
        scanf(" %[^\n]", str); // leitura da próxima string
    }
    return 0;
}
