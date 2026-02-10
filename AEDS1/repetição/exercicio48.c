#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao, meses_trabalho;
    float salario, aumento;
    printf("Menu de opcoes:\n\n1. Novo salario\n2. Ferias\n3. Decimo terceiro\n4. Sair\n\nInsira a opcao desejada:\n");
    scanf("%d", &opcao);
    do {
        if (opcao == 1) {
            printf("\nInsira o salario do funcionario:\n");
            scanf("%f", &salario);
            if (salario <= 210) {
                aumento = 0.15;
            } else if (salario <= 600) {
                aumento = 0.1;
            } else {
                aumento = 0.05;
            }
            printf("\nO novo salario desse funcionario e de %.2f reais!\n", salario + salario*aumento);
        } else if (opcao == 2) {
            printf("\nInsira o salario do funcionario:\n");
            scanf("%f", &salario);
            printf("\nAs ferias desse funcionario custarao %.2f reais!\n", salario + (salario/3.0));
        } if (opcao == 3) {
            printf("\nInsira o salario do funcionario e a quantidade de meses trabalhados na empresa:\n");
            scanf("%f%d", &salario, &meses_trabalho);
            printf("\nO valor do decimo terceiro desse funcionario e de %.2f reais!\n", salario*(meses_trabalho*1.0/12));
        } else {
            printf("\nPrograma finalizado!\n");
        }
        printf("\nMenu de opcoes:\n\n1. Novo salario\n2. Ferias\n3. Decimo terceiro\n4. Sair\n\nInsira a opcao desejada:\n");
        scanf("%d", &opcao);
    } while (opcao < 4);
}
