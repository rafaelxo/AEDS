#include <stdlib.h>
#include <stdio.h>

int main() {
    float a, b, troca;
    printf("Insira dois valores quaisquer para inverte-los em A e B:\n");
    scanf("%f%f", &a, &b);
    troca = a;
    a = b;
    b = troca;
    printf("\nOs numeros invertidos sao:\n%.2f\n%.2f\n", a, b);
}
