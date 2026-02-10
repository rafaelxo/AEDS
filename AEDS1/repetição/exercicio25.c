#include <stdio.h>
#include <stdlib.h>

int main() {
    int pais;
    float p_unitario, imposto, v_transporte, v_seguro, p_final, t_impostos = 0;
    char transporte, perigo;
    printf("Insira o preco unitario do produto:\n");
    scanf("%f", &p_unitario);
    while (p_unitario > 0) {
        printf("\nInsira o pais de origem do produto (1 - EUA, 2 - Mexico, 3 - outros), seu meio de transporte (T, F ou A) e sua periculosidade (S ou N):\n");
        scanf("%d %c %c", &pais, &transporte, &perigo);
        if (p_unitario <= 100) {
            imposto = 0.05;
        } else {
            imposto = 0.1;
        }
        if (perigo == 'S') {
            if (pais == 1) {
                v_transporte = 50;
            } else if (pais == 2) {
                v_transporte = 21;
            } else {
                v_transporte = 24;
            }
        } else {
            if (pais == 1) {
                v_transporte = 12;
            } else if (pais == 2) {
                v_transporte = 21;
            } else {
                v_transporte = 60;
            }
        }
        if (pais == 2 || transporte == 'A') {
            v_seguro = p_unitario*1.0/2;
        } else {
            v_seguro = 0;
        }
        p_final = p_unitario + p_unitario*imposto + v_transporte + v_seguro;
        t_impostos += p_unitario*imposto;
        printf("\nO valor do imposto, do transporte, do seguro e o preco final do produto equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n%.2f\n", p_unitario*imposto, v_transporte, v_seguro, p_final);
        scanf("%f", &p_unitario);
    }
    printf("\nO valor total dos impostos e de %.2f reais!\n", t_impostos);
}