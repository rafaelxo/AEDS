#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float salario, aumento, n_salario;
    printf("Insira o salario atual do funcionario:\n");
    scanf("%f", &salario);
    if (salario <= 300) {
        aumento = salario * 0.5;
    } else if (salario > 300 && salario <= 500) {
        aumento = salario * 0.4;
    } else if (salario > 500 && salario <= 700) {
        aumento = salario * 0.3;
    } else if (salario > 700 && salario <= 800) {
        aumento = salario * 0.2;
    } else if (salario > 800 && salario <= 1000) {
        aumento = salario * 0.1;
    } else {
        aumento = salario * 0.05;
    }
    n_salario = salario + aumento;
    printf("\nO aumento foi de %.2f reais e o novo salario e de %.2f reais!\n", aumento, n_salario);
}
