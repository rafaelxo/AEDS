#include <stdio.h>
#include <stdlib.h>

int main() {
    int razao, termo, termo10;
    printf("Insira, respectivamente, a razao e o primeiro termo da progressao aritmetica para calcular seu decimo valor:\n");
    scanf("%d%d", &razao, &termo);
    termo10 = termo + (9 * razao);
    printf("\nO decimo valor da progressao aritmetica do referido termo a razao de %d equivale a:\n%d\n", razao, termo10);
}
