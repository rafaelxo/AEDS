#include <stdio.h>
#include <stdlib.h>

int resto (int numerador, int denominador) {
    if (numerador < denominador) return numerador;
    else return resto (numerador - denominador, denominador);
}

int main () {
    int num, den;
    scanf("%d%d", &num, &den);
    printf("%d", resto(num, den));
}
