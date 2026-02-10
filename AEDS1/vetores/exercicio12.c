#include <stdlib.h>
#include <stdio.h>

int main() {
    int c[5], economico, menor_c;
    char m[5];
    float media;
    for (int cont1 = 0; cont1 < 5; cont1++) {
        printf("Digite a inicial do modelo do %d carro:\n", cont1 + 1);
        scanf(" %c", &m[cont1]);
    }
    for (int cont1 = 0; cont1 < 5; cont1++) {
        media = 0;
        printf("\nDigite o consumo, em quilometros, do carro %d:\n", cont1 + 1);
        scanf("%d", &c[cont1]);
        if (cont1 == 0) {
            economico = cont1;
            menor_c = c[cont1];
        } else {
            if (c[cont1] < menor_c) {
            economico = cont1;
            menor_c = c[cont1];
            }
        }
        media = 1000.0 / c[cont1];
        printf("\nO modelo do carro %c faz %.2f km/litro!\n", m[cont1], media);
    }
    printf("\nO carro mais economico e o modelo %c, fazendo %.2f km/litro!\n", m[economico], 1000.0/menor_c);
}