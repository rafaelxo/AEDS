#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float cat1, cat2, hipotenusa;
    printf("Insira o valor dos dois catetos do triangulo para calcualr sua hipotenusa:\n");
    scanf("%f%f", &cat1, &cat2);
    hipotenusa = sqrt(pow(cat1, 2) + pow(cat2, 2));
    printf("\nA hipotenusa desse triangulo equivale a:\n%.2f\n", hipotenusa);
}
