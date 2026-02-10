#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int a, b, c, delta;
    float x1, x2;
    printf("Insira os valores de A, B e C para calcular a equação:\n");
    scanf("%d%d%d", &a, &b, &c);
    if (a == 0) {
        printf("\nO valor de A nao pode ser 0!\n");
        return 0;
    }
    delta = pow(b, 2) - (4 * a * c);
    printf("\nO delta dessa equacao equivale a:\n%d\n", delta);
    if (delta > 0) {
        x1 = (-b + sqrt(delta))/(2.0 * a);
        x2 = (-b - sqrt(delta))/(2.0 * a);
        printf("\nDevido ao delta ser maior que 0, essa equacao possui duas raizes que equivalem, respectivamente, a:\n%.2f e %.2f\n", x1, x2);
    } else if (delta == 0) {
        x1 = (-b)/(2 * a);
        printf("\nDevido ao delta ser igual a 0, essa equacao possui apenas uma raiz equivalente a:\n%.2f\n", x1);
    } else if (delta < 0) {
        printf("\nEssa equacao nao possui raiz real devido ao delta ser menor que 0!\n");
    }
}
