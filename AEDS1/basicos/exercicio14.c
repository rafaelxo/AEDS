#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int ano_nascimento, ano_atual, idade_atual, idade_2050;
    printf("Insira o ano atual e seu ano de nascimento:\n");
    scanf("%d%d", &ano_atual, &ano_nascimento);
    idade_atual = ano_atual - ano_nascimento;
    idade_2050 = 2050 - ano_nascimento;
    printf("\nSua idade atual e sua idade no ano de 2050 sao:\n%d\n%d", idade_atual, idade_2050);

}
