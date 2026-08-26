#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, pos = 0, neg = 0, zero = 0;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        long int num;
        scanf("%ld", &num);
        if (num < 0) {
            neg += 1;
        } else if (num == 0) {
            zero += 1;
        } else {
            pos += 1;
        }
    }
    printf("%d POSITIVOS\n%d NEGATIVOS\n%d ZEROS", pos, neg, zero);
}
