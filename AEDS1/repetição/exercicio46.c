#include <stdio.h>
#include <stdlib.h>

int main() {
    int voto, q_votos = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, nulo = 0, branco = 0;
    float perc_nulo, perc_branco;
    printf("Insira o voto do eleitor (0 para finalizar):\n");
    scanf("%d", &voto);
    while (voto > 0) {
        q_votos++;
        if (voto == 1) {
            c1++;
        } else if (voto == 2) {
            c2++;
        } else if (voto == 3) {
            c3++;
        } else if (voto == 4) {
            c4++;
        } else if (voto == 5) {
            nulo++;
            perc_nulo++;
        } else if (voto == 6) {
            branco++;
            perc_branco++;
        }
        printf("\nInsira o voto do eleitor (0 para finalizar):\n");
        scanf("%d", &voto);
    }
    printf("\nO candidato 1 obteve %d votos!\n", c1);
    printf("\nO candidato 2 obteve %d votos!\n", c2);
    printf("\nO candidato 3 obteve %d votos!\n", c3);
    printf("\nO candidato 4 obteve %d votos!\n", c4);
    printf("\nO total de votos nulos foi de %d votos!\n", nulo);
    printf("\nO total de votos brancos foi de %d votos!\n", branco);
    printf("\nO percentual de votos nulos foi de %.2f%%!\n", perc_nulo*100.0/q_votos);
    printf("\nO percentual de votos brancos foi de %.2f%%!\n", perc_branco*100.0/q_votos);
}
