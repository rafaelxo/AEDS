#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, idade, f_etaria1 = 0, f_etaria11 = 0, f_etaria21 = 0, f_etaria31 = 0;
    float peso, m_peso1 = 0, m_peso11 = 0, m_peso21 = 0, m_peso31 = 0;
    printf("Insira quantas pessoas quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade e o peso do individuo:\n");
        scanf("%d%f", &idade, &peso);
        if (idade >= 1 && idade <= 10) {
            f_etaria1++;
            m_peso1 += peso;
        } else if (idade <= 20) {
            f_etaria11++;
            m_peso11 += peso;
        } else if (idade <= 30) {
            f_etaria21++;
            m_peso21 += peso;
        } else {
            f_etaria31++;
            m_peso31 += peso;
        }
    }
    printf("\nA media de peso da faixa etaria de 1 a 10 anos e de %.2fkg!\n", m_peso1/f_etaria1*1.0);
    printf("\nA media de peso da faixa etaria de 11 a 20 anos e de %.2fkg!\n", m_peso11/f_etaria11*1.0);
    printf("\nA media de peso da faixa etaria de 21 a 30 anos e de %.2fkg!\n", m_peso21/f_etaria21*1.0);
    printf("\nA media de peso da faixa etaria de maior de 31 anos e de %.2fkg!\n", m_peso31/f_etaria31*1.0);
}