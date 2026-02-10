#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap (int *a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void ordenar (int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) menor = j;
        }
        swap(v, i, menor);
    }
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        int ips[1000];
        char lixo[20];
        int count = 0;
        int num;
        while (scanf("%s", lixo) != EOF) {
            if (strcmp(lixo, "0") == 0) break;
            scanf("%d", &num);
            ips[count++] = num;
        }
        ordenar(ips, count);
        for (int i = 0; i < count; i++) printf("Package %03d\n", ips[i]);
        printf("\n");
    }
    return 0;
}
