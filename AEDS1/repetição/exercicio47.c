#include <stdio.h>
#include <stdlib.h>

int main() {
    int idade, q_pessoas = 0, q_pessoas50 = 0;
    float altura, m_idade = 0, m_altura = 0, m_altura50 = 0;
    printf("Insira a idade e a altura do individuo:\n");
    scanf("%d%f", &idade, &altura);
    while (idade > 0) {
        q_pessoas++;
        m_idade += idade;
        m_altura += altura;
        if (idade > 50) {
            q_pessoas50++;
            m_altura50 += altura;
        }
        printf("Insira a idade e a altura do individuo:\n");
        scanf("%d%f", &idade, &altura);
    }
    printf("\nA media das idades e das alturas de todos os individuos e de %.2f anos e %.2f metros!\n", m_idade*1.0/q_pessoas, m_altura*1.0/q_pessoas);
    printf("\nA media das alturas das pessoas com mais de 50 anos e de %.2f metros!\n", m_altura50*1.0/q_pessoas50);
}
