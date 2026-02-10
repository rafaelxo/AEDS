#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int x, y, z;
    printf("Insira os tres lados de um triangulo para calssifica-lo:\n");
    scanf("%d%d%d", &x, &y, &z);
    if (!( x < y + z && y < x + z && z < x + y)) {
        printf("\nLados invalidos! O valor de um lado do trinagulo tem que ser menor que a soma dos outros dois!\n");
        return 0;
    }
    if (x == y && y == z) {
        printf("\nEsse e um triangulo equilatero!\n");
    } else if (x == y || x == z || y == z) {
        printf("\nEsse e um triangulo isosceles!\n");
    } else if (x != y && x != z && y != z) {
        printf("\nEsse e um triangulo escaleno!\n");
    }
}
