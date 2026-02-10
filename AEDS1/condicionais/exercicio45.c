
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int idade;
    printf("Insira a idade do atleta:\n");
    scanf("%d", &idade);
    if (idade >= 5 && idade <= 7) {
        printf("\nAtleta infantil!\n");
    } else if (idade >= 8 && idade <= 10) {
        printf("\nAtleta juvenil!\n");
    } else if (idade >= 11 && idade <= 15) {
        printf("\nAtleta adolescente!\n");
    } else if (idade >= 16 && idade <= 30) {
        printf("\nAtleta adulto!\n");
    } else if (idade > 30) {
        printf("\nAtleta senior!\n");
    } else {
        printf("\nAtleta fora de categoria!\n");
    }
}
