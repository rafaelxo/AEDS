#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, q_sim = 0, q_nao = 0, q_mulheressim = 0;
    float perc_homensnao = 0;
    char sexo, gostou;
    printf("Insira a quantidade de individuos:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira o sexo (M ou F) do entrevistado e se gostou ou nao do produto (S ou N):\n");
        scanf(" %c %c", &sexo, &gostou);
        if (gostou == 'S') {
            q_sim++;
        } else {
            q_nao++;
        }
        if (sexo == 'F' && gostou == 'S') {
            q_mulheressim++;
        }
        if (sexo == 'M' && gostou == 'N') {
            perc_homensnao++;
        }
    }
    printf("\nO numero de pessoas que responderam sim foi de %d!", q_sim);
    printf("\nO numero de pessoas que responderam nao foi de %d!", q_nao);
    printf("\nO numero de mulheres que responderam sim foi de %d!", q_mulheressim);
    printf("\nA porcentagem de homens que responderam nao entre todos os analisados foi de %.2f%%!", perc_homensnao*100.0/N);
}