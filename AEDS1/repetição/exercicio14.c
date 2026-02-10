#include <stdio.h>
#include <stdlib.h>

int main() {
    int q_parcelas = 1;
    float v_inicial, juros = 0, v_juros, v_parcelas, v_total;
    printf("Insira o valor inicial da divida:\n");
    scanf("%f", &v_inicial);
    v_total = v_inicial;
    v_parcelas = v_inicial;
    printf("\nO valor total da divida, dos juros, das parcelas e sua quantidade equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n%d\n", v_total, v_juros, v_parcelas, q_parcelas);
    juros += 10;
    q_parcelas += 2;
    v_juros = v_inicial * juros*1.0/100;
    v_total = v_inicial + v_juros;
    v_parcelas = v_total/(q_parcelas*1.0);
    printf("\nO valor total da divida, dos juros, das parcelas e sua quantidade equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n%d\n", v_total, v_juros, v_parcelas, q_parcelas);
    for (int cont1 = 1; cont1 <= 3; cont1++) {
        juros += 5;
        q_parcelas += 3;
        v_juros = v_inicial * juros*1.0/100;
        v_total = v_inicial + v_juros;
        v_parcelas = v_total/(q_parcelas*1.0);
        printf("\nO valor total da divida, dos juros, das parcelas e sua quantidade equivalem, respectivamente, a:\n%.2f\n%.2f\n%.2f\n%d\n", v_total, v_juros, v_parcelas, q_parcelas);
    }
}
