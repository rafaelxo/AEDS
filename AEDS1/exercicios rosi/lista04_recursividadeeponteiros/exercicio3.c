#include <stdio.h>
#include <stdlib.h>

int divisao (int numerador, int denominador) {
    if (numerador < denominador) return 0;
    else return 1 + divisao (numerador - denominador, denominador);
}

int main () {
    int num, den;
    scanf("%d%d", &num, &den);
    printf("%d", divisao(num, den));
}