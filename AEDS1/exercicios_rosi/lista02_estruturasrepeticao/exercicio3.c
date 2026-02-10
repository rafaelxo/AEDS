#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int d39 = 0, d2 = 0, d5 = 0;
    for (int cont1 = 1; cont1 <= 10; cont1++) {
        float num;
        scanf("%f", &num);
        if ((fmod (num, 3) == 0) && (fmod (num, 9) == 0)) {
            d39++;
        } 
        if ((fmod (num, 2) == 0)) {
            d2++;
        }
        if ((fmod (num, 5) == 0)) {
            d5++;
        }
        if (!((fmod (num, 3) == 0) && (fmod (num, 9) == 0) || (fmod (num, 2) == 0) || (fmod (num, 5) == 0))) {
            printf("Numero nao e divisivel pelos valores\n");
        }
    }
    printf("%d Numeros sao divisiveis por 3 e por 9\n%d Numeros sao divisiveis por 2\n%d Numeros sao divisiveis por 5", d39, d2, d5);
}