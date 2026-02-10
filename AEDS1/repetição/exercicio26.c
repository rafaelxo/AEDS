#include <stdio.h>
#include <stdlib.h>

int main() {
    int n1, n2, n3, n4;
    for (int grupo = 1; grupo <= 5; grupo++) {
        printf("Insira os quatro valores do grupo %d:\n", grupo);
        scanf("%d%d%d%d", &n1, &n2, &n3, &n4);
        printf("\nOrdem lida: %d, %d, %d, %d\n", n1, n2, n3, n4);
        if (n1 > n2) {
            n1 = n1 + n2; n2 = n1 - n2; n1 = n1 - n2; 
        }
        if (n1 > n3) {
            n1 = n1 + n3; n3 = n1 - n3; n1 = n1 - n3; 
        }
        if (n1 > n4) {
            n1 = n1 + n4; n4 = n1 - n4; n1 = n1 - n4;
        }
        if (n2 > n3) {
            n2 = n2 + n3; n3 = n2 - n3; n2 = n2 - n3;
        }
        if (n2 > n4) {
            n2 = n2 + n4; n4 = n2 - n4; n2 = n2 - n4;
        }
        if (n3 > n4) {
            n3 = n3 + n4; n4 = n3 - n4; n3 = n3 - n4;
        }
        printf("\nOrdem crescente: %d, %d, %d, %d\n", n1, n2, n3, n4);
        if (n1 < n2) {
            n1 = n1 + n2; n2 = n1 - n2; n1 = n1 - n2;
        }
        if (n1 < n3) {
            n1 = n1 + n3; n3 = n1 - n3; n1 = n1 - n3;
        }
        if (n1 < n4) {
            n1 = n1 + n4; n4 = n1 - n4; n1 = n1 - n4;
        }
        if (n2 < n3) {
            n2 = n2 + n3; n3 = n2 - n3; n2 = n2 - n3;
        }
        if (n2 < n4) {
            n2 = n2 + n4; n4 = n2 - n4; n2 = n2 - n4;
        }
        if (n3 < n4) {
            n3 = n3 + n4; n4 = n3 - n4; n3 = n3 - n4;
        }
        printf("\nOrdem decrescente: %d, %d, %d, %d\n", n1, n2, n3, n4);
    }
}