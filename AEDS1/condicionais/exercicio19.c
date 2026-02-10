#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float peso, altura;
    printf("Insira seu peso e sua altura:\n");
    scanf("%f%f", &peso, &altura);
    if (altura < 1.20) {
        if (peso <=60) {
            printf("\nConceito A!\n");
        } else if (peso > 60 && peso <=90) {
            printf("\nConceito D!\n");
        } else if (peso > 90) {
            printf("\nConceito G!\n");
        }
    }
    if (altura > 1.20 && altura <= 1.70) {
        if (peso <=60) {
            printf("\nConceito B!\n");
        } else if (peso > 60 && peso <=90) {
            printf("\nConceito E!\n");
        } else if (peso > 90) {
            printf("\nConceito H!\n");
        }
    }
    if (altura > 1.70) {
        if (peso <=60) {
            printf("\nConceito C!\n");
        } else if (peso > 60 && peso <=90) {
            printf("\nConceito F!\n");
        } else if (peso > 90) {
            printf("\nConceito I!\n");
        }
    }
}
