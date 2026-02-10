#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float salario, aumento, n_salario;
    printf("Insira o salario atual do funcionario:\n");
    scanf("%f", &salario);
    if (salario <= 300) {
        aumento = salario * 0.15;
    } else if (salario > 300 && salario < 600) {
        aumento = salario * 0.1;
    } else if (salario >= 600 && salario <= 900) {
        aumento = salario * 0.05;
    } else {
        printf("\nFuncionario inelegivel para aumento, pois o salario ja e maior que 900 reais!\n");
        return 0;
    }
    n_salario = salario + aumento;
    printf("\nO aumento foi de %.2f reais e o novo salario e de %.2f reais!\n", aumento, n_salario);
}
