#include <stdio.h>
#include <stdlib.h>

int main() {
    float celsius, fahrenheit;
    printf("Insira a temperatura em graus Celsius:\n");
    scanf("%f", &celsius);
    fahrenheit = (celsius * 9/5) + 32;
    printf("\nEssa temperatura em Celsius equivale a %.1f em Fahrenheit!", fahrenheit);
}