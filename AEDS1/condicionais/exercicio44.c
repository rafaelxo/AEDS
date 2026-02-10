#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float altura, peso;
    char genero;
    printf("Insira sua altura (x.xx) e seu genero (M ou F) para calcular o peso ideal:\n");
    scanf("%f %c", &altura, &genero);
    if (genero == 'M') {
        peso = (72.7 * altura) - 58;
    } else if (genero == 'F') {
        peso = (62.1 * altura) - 44.7;
    }
    printf("\nSeu peso ideal e de %.2f kg!\n", peso);
}
