#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao = 0;
    float salario, imposto, aumento, novo_salario;
    do {
        printf("Menu de opcoes\n1. Imposto\n2. Novo salario\n3. Classificacao\n4. Finalizar o programa\n\nInsira a opcao desejada:\n");
        scanf("%d", &opcao);
    } while (opcao > 4 || opcao < 1);
    if (opcao == 1) {
        printf("\nInsira o salario para calcular o imposto:\n");
        scanf("%f", &salario);
        if (salario < 500) {
            imposto = 0.05;
        } else if (salario >= 500 && salario <= 850) {
            imposto = 0.1;
        } else {
            imposto = 0.15;
        }
        printf("\nO valor do imposto e de %.2f reais!", salario*imposto);
    }
    if (opcao == 2) {
        printf("\nInsira o salario para calcular o aumento:\n");
        scanf("%f", &salario);
        if (salario < 450) {
            aumento = 100;
        } else if (salario >= 450 && salario < 750) {
            aumento = 75;
        } else if (salario >= 750 && salario <= 1500) {
            aumento = 50;
        } else {
            aumento = 25;
        }
        novo_salario = salario + aumento;
        printf("\nPara o salario de %.2f reais, o valor do aumento e de %.2f reais e o salario final equivale a %.2f reais!", salario, aumento, novo_salario);
    }
    if (opcao == 3) {
        printf("\nInsira o salario para realizar a classificacao:\n");
        scanf("%f", &salario);
        if (salario <= 700) {
            printf("\nSalario mal remunerado!\n");
        } else {
            printf("\nSalario bem remunerado!\n");
        }
    }
}