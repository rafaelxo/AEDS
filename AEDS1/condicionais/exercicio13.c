#include <stdio.h>
#include <stdlib.h>

int main() {
    float salario, imposto, aumento, n_salario;
    int menu, classificacao;
    printf("Menu de opcoes:\n\n1. Imposto\n2. Novo salario\n3. Classificacao\n\nEscolha a opcao desejada:\n");
    scanf("%d", &menu);
    if (menu < 1 || menu > 3) {
        printf("\nOpcao invalida!\n");
    }
    switch (menu) {
        case 1: printf("\nInsira o salario para calcular o imposto:\n");
                scanf("%f", &salario);
            if (salario < 500) {
                imposto = salario * 0.05;
                printf("\nO imposto sobre seu salario e de 5 porcento e equivale a %.2f reais!\n", imposto);
            } else if (salario < 500 && salario <= 850) {
                imposto = salario * 0.1;
                printf("\nO imposto sobre seu salario e de 10 porcento e equivale a %.2f reais!\n", imposto);
            } else if (salario > 850) {
                imposto = salario * 0.15;
                printf("\nO imposto sobre seu salario e de 15 porcento e equivale a %.2f reais!\n", imposto);
            } break;
        case 2: printf("\nInsira o salario para calcular o aumento:\n");
                scanf("%f", &salario);
            if (salario < 450) {
                n_salario = salario + 100;
                printf("\nVoce recebera um aumento de 100 reais e seu novo salario sera de:\n%.2f\n", n_salario);
            } else if (salario >= 450 && salario <= 750) {
                n_salario = salario + 75;
                printf("\nVoce recebera um aumento de 75 reais e seu novo salario sera de:\n%.2f\n", n_salario);
            } else if (salario > 750 && salario <= 1500) {
                n_salario = salario + 50;
                printf("\nVoce recebera um aumento de 50 reais e seu novo salario sera de:\n%.2f\n", n_salario);
            } else if (salario > 1500) {
                n_salario = salario + 25;
                printf("\nVoce recebera um aumento de 25 reais e seu novo salario sera de:\n%.2f\n", n_salario);
            } break;
        case 3: printf("\nInsira o salario para realizar a classificacao:\n");
                scanf("%f", &salario);
            if (salario <= 750) {
                printf("\nFuncionario mal remunerado!\n");
            } else if (salario > 750) {
                printf("\nFuncionario bem remunerado!\n");
            } break;
        }
    }
