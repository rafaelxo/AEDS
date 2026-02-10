#include <stdlib.h>
#include <stdio.h>

void comprimentoTriangulo (float x, float y, float z) {
    if (x < y + z && y < x + z && z < x + y) {
        if (x == y && y == z) {
            printf("TRIANGULO EQUILATERO\n");
        } else if (x == y || y == z || z == x) {
            printf("TRIANGULO ISOSCELES\n");
        } else if (x != y && y != z && z != x) {
            printf("TRIANGULO ESCALENO\n");
        }
    } else {
        printf("NAO TRIANGULO\n");
    }
}

int main () {
    float x, y, z;
    scanf("%f%f%f", &x, &y, &z);
    while (x != -1 && y != -1 && z != -1) {
        comprimentoTriangulo(x, y, z);
        scanf("%f%f%f", &x, &y, &z);
    }
}