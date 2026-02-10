#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float salario, aumento, n_salario;
    printf("Insira o salario do funcionario:\n");
    scanf("%f", &salario);
    if (salario <= 300) {
        aumento = salario * 0.35;
    } else {
        aumento = salario * 0.15;
    }
    n_salario = salario + aumento;
    printf("\nO aumento foi de %.2f reais e o salario reajustado equivale a %.2f reais!\n", aumento, n_salario);
}
