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
    printf("%.0f%% POSITIVOS\n%0.f%% NEGATIVOS\n%0.f%% ZEROS", pos*100.0/N, neg*100.0/N, zero*100.0/N);
}
