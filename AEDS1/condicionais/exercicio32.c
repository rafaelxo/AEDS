#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float salario, aumento, n_salario;
    printf("Insira o salario do funcionario:\n");
    scanf("%f", &salario);
    if (salario < 500) {
        aumento = salario * 0.3;
        n_salario = salario + aumento;
        printf("\nO aumento foi de %.2f reais e o novo salario e de %.2f reais!\n", aumento, n_salario);
    } else {
        printf("\nFuncionario inelegivel para aumento, pois o salario ja e maior que 500 reais!\n");
    }
}
