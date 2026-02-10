#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float n1, n2;
    printf("Insira dois numeros para analisar qual e maior:\n");
    scanf("%f%f", &n1, &n2);
    if (n1 > n2) {
        printf("\nO maior numero e %f!\n", n1);
    } else {
        printf("\nO maior numero e %f!\n", n2);
    }
}
