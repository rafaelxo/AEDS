#include <stdio.h>
#include <stdlib.h>

int main () {
    for (int cont1 = 1; cont1 <= 10; cont1++) {
        printf("\nA tabuada de %d e:", cont1);
        for (int cont2 = 1; cont2 <= 10; cont2++) {
            printf("\n%d * %d = %d", cont1, cont2, cont2*cont1);
        }
        printf("\n");
    }
}