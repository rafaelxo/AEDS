#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int idade;
    scanf("%d", &idade);
    if (idade >= 5 && idade <= 7) {
        printf("Infantil");
    } else if (idade >= 8 && idade <= 10) {
        printf("Juvenil");
    } else if (idade >= 11 && idade <= 15) {
        printf("Adolescente");
    } else if (idade >= 16 && idade <= 30) {
        printf("Adulto");
    } else if (idade > 30) {
        printf("Senior");
    }
}
