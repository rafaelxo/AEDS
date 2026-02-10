#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, idade, maior_i = 0, menor_i = 0, q_mulheres200 = 0, idade_menor_salario = 0;
    float salario, m_salario = 0, menor_salario = 0;
    char sexo, sexo_menor_salario = '\0';
    printf("Insira quantas pessoas quer analisar:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade, o genero (M ou F) e o salario do individuo:\n");
        scanf("%d %c%f", &idade, &sexo, &salario);
        m_salario += salario;
        maior_i = menor_i = idade;
        menor_salario = salario;
        idade_menor_salario = idade;
        sexo_menor_salario = sexo;
        if (idade > maior_i) {
            maior_i = idade;
        }
        if (idade < menor_i) {
            menor_i = idade;
        }
        if (sexo == 'F' && salario <= 200) {
            q_mulheres200++;
        }
        if (salario < menor_salario) {
            menor_salario = salario;
            idade_menor_salario = idade;
            sexo_menor_salario = sexo;
        }
    }
    printf("\nA media do salario desses individuos e de %.2f reais!\n", m_salario/N);
    printf("\nA maior idade e a menor entre esses individuos e de, respectivamente: %d e %d anos!\n", maior_i, menor_i);
    printf("\nA quantidade de mulheres com salario de ate 200 reais e de %d!\n", q_mulheres200);
    printf("\nA genero e a idade da pessoa que possui o menor salario, equivalente a %.2f reais, e %c e %d anos!\n", menor_salario, sexo_menor_salario, idade_menor_salario);
}