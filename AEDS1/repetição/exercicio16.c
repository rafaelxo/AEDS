#include <stdio.h>
#include <stdlib.h>

int main() {
    float base, altura, area;
    do {
        printf("Insira o valor da base e da altura do triangulo:\n");
        scanf("%f%f", &base, &altura);
    } while (base <= 0 || altura <= 0);
    area = (base * altura) / 2;
    printf("\nA area do triangulo e de:\n%.2f\n", area);
}