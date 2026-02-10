#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1, periodo, c_falecidas, s_masculino = 0, s_feminino = 0, t_vida, s_24 = 0;
    float p_masculino, p_feminino, p_24;
    char genero;
    printf("Insira o periodo (meses) e o numero de falecimentos nesse intervalo:\n");
    scanf("%d%d", &periodo, &c_falecidas);
    if (c_falecidas == 0) {
        printf("\nNenhuma crianca validada!\n");
        return 0;
    }
    for (cont1 = 1; cont1 <= c_falecidas; cont1++) {
        printf("\nInsira o genero (M ou F) e o tempo de vida (meses) da crianca:\n");
        scanf(" %c%d", &genero, &t_vida);
        if (genero != 'M' && genero != 'F') {
            printf("\nGenero invalido!\n");
            return 0;
        }
        if (genero == 'M') {
            s_masculino += 1;
        } else if (genero == 'F') {
            s_feminino += 1;
        }
        if (t_vida <= 24) {
            s_24 += 1;
        }
    }
    p_masculino = s_masculino*100*1.0/c_falecidas;
    p_feminino = s_feminino*100*1.0/c_falecidas;
    p_24 = s_24*100/c_falecidas;
    printf("\nNo periodo de %d meses:\n", periodo);
    printf("\no percentual de criancas do sexo masculino e feminino falecidas sao, respectivamente:\n%.2f\n%.2f\n", p_masculino, p_feminino);
    printf("\no percentual de criancas falecidas com 24 meses ou menos e:\n%.2f\n", p_24);
}
