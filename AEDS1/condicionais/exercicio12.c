#include <stdio.h>
#include <stdlib.h>

int main() {
    int cargo;
    float salario, aumento, n_salario;
    printf("Insira o cargo do funcionario (1 a 5):\n");
    scanf("%d", &cargo);
    if (cargo < 1 || cargo > 5) {
        printf("\nCargo invalido!\n");
    }
    printf("\nAgora, insira o salario desse funcionario:\n");
    scanf("%f", &salario);
    switch (cargo) {
        case 1: aumento = salario * 0.5;
                n_salario = salario + aumento;
                printf("\nPara escrituario, havera um aumento de %.2f reais e o novo salario sera de %.2f reais!\n", aumento, n_salario); break;
        case 2: aumento = salario * 0.35;
                n_salario = salario + aumento;
                printf("\nPara secretario, havera um aumento de %.2f reais e o novo salario sera de %.2f reais!\n", aumento, n_salario); break;
        case 3: aumento = salario * 0.2;
                n_salario = salario + aumento;
                printf("\nPara caixa, havera um aumento de %.2f reais e o novo salario sera de %.2f reais!\n", aumento, n_salario); break;
        case 4: aumento = salario * 0.1;
                n_salario = salario + aumento;
                printf("\nPara gerente, havera um aumento de %.2f reais e o novo salario sera de %.2f reais!\n", aumento, n_salario); break;
        case 5: n_salario = salario;
                printf("\nPara diretor, nao havera aumento e o novo salario mantera como %.2f reais!\n", n_salario); break;
        }
    }
