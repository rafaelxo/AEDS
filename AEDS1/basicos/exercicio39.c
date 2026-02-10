#include <stdio.h>
#include <stdlib.h>

int main() {
    int a_nascimento, a_atual, i_anos, i_meses, i_dias, i_semanas;
    printf("Digite seu ano de nascimento e o ano atual:\n");
    scanf("%d%d", &a_nascimento, &a_atual);
    i_anos = a_atual - a_nascimento;
    i_meses = i_anos * 12;
    i_dias = i_meses * 30;
    i_semanas = i_dias / 7;
    printf("\nVoce tem %d anos, %d meses, %d dias e %d semanas de vida!\n", i_anos, i_meses, i_dias, i_semanas);
}