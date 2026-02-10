#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, r;
    printf("Insira um numero inteiro para saber se e impar ou par:\n");
    scanf("%d", &n);
    r = n%2;
    if (r == 0) {
        printf("\nO numero inserido e par!\n");
    } else {
        printf("\nO numero inserido e impar!\n");
    }
}
