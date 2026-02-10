#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, idade, opiniao, q_regular = 0, q_otimo = 0;
    float m_idadeO = 0, perc_bom = 0;
    printf("Insira a quantidade de individuos:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira a idade e a opiniao (1 - regular, 2 - bom, 3 - otimo) do espectador:\n");
        scanf("%d%d", &idade, &opiniao);
        if (opiniao == 3) {
            m_idadeO += idade;
            q_otimo++;
        }
        if (opiniao == 1) {
            q_regular++;
        }
        if (opiniao == 2) {
            perc_bom++;
        }
    }
    printf("\nA media das idades das pessoas que responderam otima e de %.2f anos!", m_idadeO*1.0/q_otimo);
    printf("\nA quantidade de pessoas que responderam regular e de %d!", q_regular);
    printf("\nA porcentagem de pessoas que responderam dentre todas as analises e de %.2f%%!", perc_bom*100.0/N);
}