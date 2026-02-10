#include <stdio.h>
#include <stdlib.h>

int main() {
    float n1, n2, n3;
    printf("Insira tres numeros para coloca-los em ordem crescente:\n");
    scanf("%f%f%f", &n1, &n2, &n3);
    if (n1 < n2 && n1 < n3) {
       if(n2 < n3) {
        printf("\nA ordem crescente e:\n%f<%f<%f", n1, n2, n3);
       } else {
        printf("\nA ordem crescente e:\n%f<%f<%f", n1, n3, n2);
       }
    } else if (n2 < n1 && n2 < n3) {
        if (n1 < n3){
            printf("\nA ordem crescente e:\n%f<%f<%f", n2, n1, n3);
        } else {
            printf("\nA ordem crescente e:\n%f<%f<%f", n2, n3, n1);
        }
    } else if (n3 < n1 && n3 < n2) {
        if (n1 < n2) {
            printf("\nA ordem crescente e:\n%f<%f<%f", n3, n1, n2);
        } else {
            printf("\nA ordem crescente e:\n%f<%f<%f", n3, n2, n1);
        }
    }
}
