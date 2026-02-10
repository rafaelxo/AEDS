#include <stdio.h>
#include <stdlib.h>

int main () {
    int vendas = 120, despesa = 200, m_vendas = 0;
    float p_ingresso = 5.0, lucro, m_preco = 0, m_lucro = 0;
    while (p_ingresso > 1) {
        lucro = p_ingresso*vendas - despesa;
        if (lucro > m_lucro) {
            m_lucro = lucro;
            m_preco = p_ingresso;
            m_vendas = vendas;
        }
        printf("\nA um preco de %.2f reais, o lucro sera igual a %.2f reais, vendendo %d ingressos!\n", p_ingresso, lucro, vendas);
        p_ingresso -= 0.5;
        vendas += 26;
    }
    printf("\nO melhor preco e a quantidade de vendas para obter o maior lucro de %.2f reais, e de, respectivamente:\n%.2f reais e %d ingressos!\n", m_lucro, m_preco, m_vendas);
}