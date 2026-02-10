#include <stdio.h>
#include <stdlib.h>

int main () {
    int N, idade, q_pessoas = 0, q_50i = 0, q_10e20i = 0, porc_40kg = 0;
    float altura, peso, m_alturas10a20 = 0;
    printf("Insira quantas pessoas quer analisar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade, a altura e o peso da pessoa:\n");
        scanf("%d%f%f", &idade, &altura, &peso);
        q_pessoas++;
        if (idade > 50) {
            q_50i++;
        }
        if (idade >= 10 && idade <= 20) {
            q_10e20i++;
            m_alturas10a20 += altura;
        }
        if (peso < 40) {
            porc_40kg++;
        }
    }
    printf("\nA quantidade de pessoas com idade superior a 50 anos e igual a %d!\n", q_50i);
    printf("\nA media das alturas das pessoas com idade entre 10 e 20 anos e de %.2f!\n", m_alturas10a20/(q_10e20i*1.0));
    printf("\nA porcentagem de pessoas com peso inferior a 40kg entre todas as pessoas analisadas e de %.2f%%!\n", porc_40kg*100.0/q_pessoas);
}
