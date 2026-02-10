#include <stdio.h>
#include <stdlib.h>

int main() {
    float n1, n2, n3, n4;
    printf("Insira tres numeros obrigatoriamente em ordem crescente:\n");
    scanf("%f%f%f", &n1, &n2, &n3);
    printf("\nAgora, insira outro valor qualquer diferente dos outros supracitados:\n");
    scanf("%f", &n4);
    if (n4 > n3) {
        printf("\nA ordem decrescente desses numeros e:\n%f<%f<%f<%f", n4, n3, n2, n1);
    } else if (n4 < n3 && n4 > n2) {
        printf("\nA ordem decrescente desses numeros e:\n%f<%f<%f<%f", n3, n4, n2, n1);
    } else if (n4 < n2 && n4 > n1) {
        printf("\nA ordem decrescente desses numeros e:\n%f<%f<%f<%f", n3, n2, n4, n1);
    } else if (n4 < n1) {
        printf("\nA ordem decrescente desses numeros e:\n%f<%f<%f<%f", n3, n2, n1, n4);
    } else {
        printf("\nO valor do quarto numero e invalido!\n");
    }
}
