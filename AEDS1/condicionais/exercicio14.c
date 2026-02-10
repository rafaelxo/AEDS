#include <stdio.h>
#include <stdlib.h>

int main() {
    float salario, n_salario, bonificacao, auxilio;
    printf("Insira seu salario para calcular sua bonificacao e seu auxilio:\n");
    scanf("%f", &salario);
    if (salario <= 500) {
        bonificacao = salario * 0.05;
    } else if (salario > 500 && salario <= 1200) {
        bonificacao = salario * 0.12;
    } if (salario < 600) {
        auxilio = 150;
    } else {
        auxilio = 100;
    }
    n_salario = salario + bonificacao + auxilio;
    printf("\nSeu novo salario sera de %.2f reais!\n", n_salario);
}
