#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float a, b, raiz;
    scanf("%f%f", &a, &b);
    if (a != 0 && b != 0) {
        raiz = -b/a;
        printf("%.2f", raiz);
    }
}
