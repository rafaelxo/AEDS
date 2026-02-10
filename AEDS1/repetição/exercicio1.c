#include <stdio.h>
#include <stdlib.h>

int main() {
    int ano_i = 2005, ano_a;
    float s_inicial = 1000, s_novo, percentual = 0.015, aumento;
    printf("Insira o ano a se calcular o salario do funcionario:\n");
    scanf("%d", &ano_a);
    aumento = s_inicial * percentual;
    s_novo = s_inicial + aumento;
    for (ano_i = 2007; ano_i <= ano_a; ano_i++) {
        percentual *= 2;
        aumento = s_novo * percentual;
        s_novo += aumento;
    }
    if (ano_a == 2005) {
        printf("\nNo ano de %d, o salario desse funcionario e de R$%.2f com um aumento de R$0.00!\n", ano_a, s_inicial);
    } else {
    printf("\nNo ano de %d, o salario desse funcionario e de R$%.2f com um aumento de R$%.2f!\n", ano_a, s_novo, aumento);
    }
}
