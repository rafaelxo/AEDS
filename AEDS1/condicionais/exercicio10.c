#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int d1, m1, a1, d2, m2, a2;
    printf("Insira a primeira data no formato dd/mm/aaaa:\n");
    scanf("%d/%d/%d", &d1, &m1, &a1);
    printf("\nInsira a segunda data tambem no formato dd/mm/aaaa:\n");
    scanf("%d/%d/%d", &d2, &m2, &a2);
    if (a1 > a2) {
        printf("\nA maior data e:\n%d/%d/%d\n", d1, m1, a1);
    } else if (a2 > a1) {
        printf("\nA maior data e:\n%d/%d/%d\n", d2, m2, a2);
    } else if (m1 > m2) {
        printf("\nA maior data e:\n%d/%d/%d\n", d1, m1, a1);
    } else if (m2 > m1) {
        printf("\nA maior data e:\n%d/%d/%d\n", d2, m2, a2);
    } else if (d1 > d2) {
        printf("\nA maior data e:\n%d/%d/%d\n", d1, m1, a1);
    } else if (d2 > d1) {
        printf("\nA maior data e:\n%d/%d/%d\n", d2, m2, a2);
    } else {
        printf("\nAs datas sao iguais!");
    }
}
