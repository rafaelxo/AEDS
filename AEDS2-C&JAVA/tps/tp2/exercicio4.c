#include <stdlib.h>
#include <stdio.h>

int somaDigitos (int n) { // método recursivo para somar cada caracter do número inteiro
    if (n < 10) return n; // condição de parada, retornando o próprio número se for menor que 10
    else return n % 10 + somaDigitos(n / 10); // soma do resto do número dividido por 10 e chamada recursiva do número dividido por 10
}

int main () { // main do programa
    int n; scanf("%d", &n); // declaração e leitura do número
    while (n != -1) { // loop para ler números enquanto o número seja diferente de -1
      printf("%d\n", somaDigitos(n)); // saída do resultado da soma dos caracteres
      scanf("%d", &n); // leitura do próximo número
    }
    return 0;
}
