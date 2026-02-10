#include <stdio.h>
#include <stdlib.h>

int main()
{
    int soma = 0, quantidade = 0, menor_N, maior_N, q_par = 0, q_impar = 0;
    float media_N, m_par = 0, perc_impar;
    long int N;
    printf("Insira os numeros para realizar os calcuos:\n");
    scanf("%ld", &N);
    while (N != 0) {
        if (quantidade == 0) {
            maior_N = N;
            menor_N = N;
        } else {
            if (N > maior_N) {
                maior_N = N;
            }
            else if (N < menor_N) {
                menor_N = N;
            }
        }
        soma += N;
        quantidade++;
        media_N = soma * 1.0 / quantidade;
        if (N % 2 == 0) {
            q_par++;
            m_par += N;
        } else {
            q_impar++;
            perc_impar = q_impar * 100.0 / N;
        }
        scanf("%ld", &N);
    }
    if (quantidade == 0) {
        printf("\nNenhum numero digitado!\n");
    } else {
        printf("\nO valor da soma dos numeros, a quantidade de numeros inseridos e a media desses valores equivalem, respecitvamente, a:\n%d\n%d\n%.2f\n", soma, quantidade, media_N);
        printf("\nO maior valor inserido e %d, e o menor %d!\n", maior_N, menor_N);
        if (q_par == 0)
        {
            printf("\nNenhum numero par inserido!\n");
        }
        else
        {
            printf("\nA quantidade de numeros pares inseridos e a media desses valores equivalem respectivamente, a:\n%d\n%.2f\n", q_par, m_par / q_par);
        }
        printf("\nO percentual de numeros impares inseridos e de %.2f!\n", perc_impar);
    }
}