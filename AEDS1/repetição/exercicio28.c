#include <stdio.h>
#include <stdlib.h>

int main () {
    int N, idade, pessoas = 0;
    float perc15 = 0, perc30 = 0, perc45 = 0, perc60 = 0, perc61 = 0;
    printf("Insira quantas idades quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("Insira a idade:\n");
        scanf("%d", &idade);
        pessoas++;
        if (idade <= 15) {
            perc15++;
        } else if (idade <= 30) {
            perc30++;
        } else if (idade <= 45) {
            perc45++;
        } else if (idade <= 60) {
            perc60++;
        } else {
            perc61++;
        }
    }
    printf("\nA porcentagem de pessoas na faixa etaria de ate 15 anos e de %.2f!\n", perc15*100.0/pessoas);
    printf("\nA porcentagem de pessoas na faixa etaria de ate 30 anos e de %.2f!\n", perc30*100.0/pessoas);
    printf("\nA porcentagem de pessoas na faixa etaria de ate 45 anos e de %.2f!\n", perc45*100.0/pessoas);
    printf("\nA porcentagem de pessoas na faixa etaria de ate 60 anos e de %.2f!\n", perc60*100.0/pessoas);
    printf("\nA porcentagem de pessoas na faixa etaria de mais de 60 anos e de %.2f!\n", perc61*100.0/pessoas);
}