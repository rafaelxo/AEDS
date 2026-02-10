#include <stdio.h>
#include <stdlib.h>

void converteHora(int total_segundos, int *hora, int *min, int *seg) {
    *hora = total_segundos/3600;
    total_segundos = total_segundos%3600;
    *min = total_segundos/60;
    *seg = total_segundos%60;
}

int main() {
   int total_segundos, hora, min, seg;
   scanf("%d", &total_segundos);
   converteHora(total_segundos, &hora, &min, &seg);
   printf("%d:%d:%d", hora, min, seg);
}
