#include <stdio.h>
#include <stdlib.h>

int main() {
    int I;
    float A, B, C;
    printf("Insira os valores de A, B e C:\n");
    scanf("%f%f%f", &A, &B, &C);
    printf("\nAgora, insira um valor de 1 a 3 para I, sendo 1 para ordem crescente,"
            "2 para ordem decrescente, e 3 para que o maior numero fique no meio dos numeros inseridos:\n");
    scanf("%d", &I);
    if (I == 1) {
        if (A < B && A < C) {
            if (B < C) {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", A, B, C);
            } else {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", A, C, B);
            }
        } else if (B < A && B < C) {
            if (A < C) {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", B, A, C);
            } else {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", B, C, A);
            }
        } else if (C < A && C < B) {
            if (A < B) {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", C, A, B);
            } else {
                printf("\nA ordem crescente dos numeros e:\n%.2f < %.2f < %.2f\n", C, B, A);
            }
        }
    } else if (I == 2) {
        if (A > B && A > C) {
            if (B > C) {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", A, B, C);
            } else {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", A, C, B);
            }
        } else if (B > A && B > C) {
            if (A > C) {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", B, A, C);
            } else {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", B, C, A);
            }
        } else if (C > A && C > B) {
            if (A > B) {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", C, A, B);
            } else {
                printf("\nA ordem decrescente dos numeros e:\n%.2f > %.2f > %.2f\n", C, B, A);
            }
        }
    } else if (I == 3) {
        if (A > B && A > C) {
            printf("\nA ordem desejada e:\n%.2f < %.2f > %.2f\n", B, A, C);
        } else if (B > A && B > C) {
            printf("\nA ordem desejada e:\n%.2f < %.2f > %.2f\n", A, B, C);
        } else if (C > A && C > B) {
            printf("\nA ordem desejada e:\n%.2f < %.2f > %.2f\n", A, C, B);
        }
    } else if (I !=1 && I!=2 && I!=3) {
        printf("\nValor invalido para I, escolha de 1 a 3!\n");
    }
}
