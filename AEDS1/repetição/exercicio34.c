#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, idade, q_90kg150cm = 0, q_190cm = 0;
    float altura, peso, m_idade = 0, porc10e30i190cm = 0;
    printf("Insira quantas pessoas quer analisar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade, o peso e a altura do individuo:\n");
        scanf("%d%f%f", &idade, &peso, &altura);
        m_idade += idade;
        if (peso > 90 && altura < 1.5) {
            q_90kg150cm++;
        }
        if (altura > 1.9) {
            q_190cm++;
        }
        if (idade >= 10 && idade <= 30 && altura > 1.9) {
            porc10e30i190cm++;
        }
    }
        printf("\nA media de idade desses individuos e de %.2f anos!\n", m_idade*1.0/N);
        printf("\nA quantidade de pessoas com peso superior a 90kg e altura inferior a 1,50m e de %d!\n", q_90kg150cm);
        printf("\nA porcentagem de pessoas com idade entre 10 e 30 anos entre as pessoas que medem mais de 1,90m e de %.2f%%!\n", porc10e30i190cm*100.0/q_190cm);
}
