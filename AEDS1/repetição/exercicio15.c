#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, q_barato = 0, q_normal = 0, q_caro = 0, c_estocagem, s_estocagem = 0;
    float p_unitario, imposto, p_final, m_adicionais = 0, maior_p_final = 0, menor_p_final = 0, t_impostos = 0;
    char refrigeracao, categoria;
    printf("Insira quantos produtos quer calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira o preco unitario do produto, sua necessidade de refrigeracao (S ou N) e sua categoria (A, L ou V):\n");
        scanf("%f %c %c", &p_unitario, &refrigeracao, &categoria);
        if (refrigeracao != 'S' && refrigeracao != 'N') {
            printf("\nTipo de refrigeracao invalido!\n");
            return 0;
        } else if (categoria != 'A' && categoria != 'L' && categoria != 'V') {
            printf("\nCategoria invalida!\n");
            return 0;
        }
        if (p_unitario <= 20) {
            if (categoria == 'A') {
                c_estocagem = 2;
            } else if (categoria == 'L') {
                c_estocagem = 3;
            } else {
                c_estocagem = 4;
            }
        } else if (p_unitario <= 50) {
            if (refrigeracao == 'S') {
                c_estocagem = 6;
            } else {
                c_estocagem = 0;
            }
        } else {
            if (refrigeracao == 'S') {
                if (categoria == 'A') {
                    c_estocagem = 5;
                } else if (categoria == 'L') {
                    c_estocagem = 2;
                } else {
                    c_estocagem = 4;
                }
            } else {
                if (categoria == 'A' || categoria == 'V') {
                    c_estocagem = 0;
                } else {
                    c_estocagem = 1;
                }
            }
        }
        if (categoria == 'A' && refrigeracao == 'S') {
            imposto = p_unitario * 0.04;
        } else {
            imposto = p_unitario * 0.02;
        }
        p_final = p_unitario + c_estocagem + imposto;
        printf("\nO custo de estocagem, o imposto e o preco final equivalem, respectivamente a:\n%d\n%.2f\n%.2f\n", c_estocagem, imposto, p_final);
        if (p_final <= 20) {
            printf("\nProduto barato!\n");
            q_barato++;
        } else if (p_final <= 100) {
            printf("\nProduto normal!\n");
            q_normal++;
        } else {
            printf("\nProduto caro!\n");
            q_caro++;
        }
        m_adicionais += c_estocagem + imposto;
        t_impostos += imposto;
        if (p_final > maior_p_final) {
            maior_p_final = p_final;
        } else if (p_final < menor_p_final) {
             menor_p_final = p_final;
        }
    }
    printf("\nA media dos valores adicionais e o total de impostos equivale, respectivamente, a:\n%.2f e %.2f\n", m_adicionais/(N*1.0), t_impostos);
    printf("\nO maior preco final e o menor sao, respectivamente:\n%.2f e %.2f\n", maior_p_final, menor_p_final);
    printf("\nA quantidade de produtos , respectivamente, sao:\n%d baratos, %d normais e %d caros!\n", q_barato, q_normal, q_caro);
}
