#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, q_pessoas, canal, q_canal = 0, canal4 = 0, canal5 = 0, canal7 = 0, canal12 = 0, pessoas4 = 0, pessoas5 = 0, pessoas7 = 0, pessoas12 = 0;
    printf("Insira em quantas casas foi feita a pesquisa:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira quantos individuos assistiam e em qual canal estavam:\n");
        scanf("%d%d", &q_pessoas, &canal);
        q_canal++;
        if (canal == 4) {
            pessoas4++;
            canal4++;
        } else if (canal == 5) {
            pessoas5++;
            canal5++;
        } else if (canal == 7) {
            pessoas7++;
            canal7++;
        } else if (canal == 12) {
            pessoas12++;
            canal12++;

        }
    }
    printf("\nO percentual de audiencia do canal 4 e de %.2f%%!\n", canal4*pessoas4*100.0/q_canal);
    printf("\nO percentual de audiencia do canal 5 e de %.2f%%!\n", canal5*pessoas5*100.0/q_canal);
    printf("\nO percentual de audiencia do canal 7 e de %.2f%%!\n", canal7*pessoas7*100.0/q_canal);
    printf("\nO percentual de audiencia do canal 12 e de %.2f%%!\n", canal12*pessoas12*100.0/q_canal);
}