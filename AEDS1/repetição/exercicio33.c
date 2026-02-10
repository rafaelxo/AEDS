#include <stdio.h>
#include <stdlib.h>

int main () {
    int N, idade, q_50i60kg = 0, q_ruivosNazul = 0, q_altura150 = 0;
    float altura, peso, m_idade150 = 0, porc_azul = 0;
    char olhos, cabelos;
    printf("Insira quantas pessoas quer analisar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade, o peso, a altura, a cor dos olhos (A, P, V ou C) e a cor dos cabelos (P, C, L ou R) do individuo:\n");
        scanf("%d%f%f %c %c", &idade, &peso, &altura, &olhos, &cabelos);
        if (idade > 50 && peso < 60) {
            q_50i60kg++;
        }
        if (altura < 1.50) {
            q_altura150++;
            m_idade150 += idade;
        }
        if (olhos == 'A') {
            porc_azul++;
        }
        if (cabelos == 'R' && olhos != 'A') {
            q_ruivosNazul++;
        }
    }
    printf("\nA quantidade de pessoas com idade superior a 50 anos e peso inferior a 60kg e de %d!\n", q_50i60kg);
    printf("\nA media das idades das pessoas com altura inferior a 1.50m e de %.2f!\n", m_idade150*1.0/q_altura150);
    printf("\nA porcentagem de pessoas com olhos azuis entre todas as pessoas analisadas e de %.2f%%\n", porc_azul*100.0/N);
    printf("\nA quantidade de pessoas ruivas que nao possuem olhos azuis e de %d!\n", q_ruivosNazul);
}