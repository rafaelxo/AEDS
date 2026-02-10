#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int h_faltadas, h_extras;
    float h_min;
    printf("Insira a quantidade de horas extras trabalhadas e quantidade de horas faltadas do funcionario:\n");
    scanf("%d%d", &h_extras, &h_faltadas);
    h_min = (h_extras - (h_faltadas * 2 / 3.0)) * 60;
    if (h_min < 600) {
        printf("\nGratificacao de 100 reais!\n");
    } else if (h_min >= 600 && h_min < 1200) {
        printf("\nGratificacao de 200 reais!\n");
    } else if (h_min >= 1200 && h_min < 1800) {
        printf("\nGratificacao de 300 reais!\n");
    } else if (h_min >= 1800 && h_min < 2400) {
        printf("\nGratificacao de 400 reais!\n");
    } else {
        printf("\nGratificacao de 500 reais!\n");
    }
}
