#include <stdlib.h>
#include <stdio.h>

int main() {
    int razao, termo, termo5;
    printf("Insira a razao e o termo da progressao geometrica para calcular seu quinto valor:\n");
    scanf("%d%d", &razao, &termo);
    termo5 = termo * (razao * razao * razao * razao);
    printf("\nO quinto valor da progressao geometrica do termo referido a razao de %d equivale a:\n%d\n", razao, termo5);
}
