#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float n1, n2, n3;
    printf("Insira dois numeros para analisar qual e maior:\n");
    scanf("%f%f%f", &n1, &n2, &n3);
    if (n1 > n2 && n1 > n3) {
        printf("\nO maior numero e %f!\n", n1);
    } else if (n2 > n1 && n2 > n3) {
        printf("\nO maior numero e %f!\n", n2);
    } else if (n3 > n1 && n3> n2) {
        printf("\nO maior numero e %f!\n", n3);
    }
}
