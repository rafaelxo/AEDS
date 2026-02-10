#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, idade;
    float m_idade = 0;
    printf("Insira a quantidade de idades que deseja calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade do aluno:\n");
        scanf("%d", &idade);
        m_idade += idade;
    }
    printf("\nA media das idades dos alunos dessa sala e de %.2f anos!\n", m_idade*1.0/N);
}
