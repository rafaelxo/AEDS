#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int cont1 = 1, cod, h_trabalhadas;
    float s_minimo = 450, s_inicial, s_final, v_hora, auxilio;
    char turno, cargo;
    for (cont1 = 1; cont1 <= 10; cont1++) {
        do {
        printf("Insira o codigo (1 a 10), o numero de horas trabalhadas, o turno (M, V ou N) e o cargo (O ou G) do funcionario:\n");
        scanf("%d%d %c %c", &cod, &h_trabalhadas, &turno, &cargo);
        if (turno != 'M' && turno != 'V' && turno != 'N') {
            printf("\nTurno invalido!\n");
        } else if (cargo != 'O' && cargo != 'G')
            printf("\nCargo invalido!\n");
        } while ((turno != 'M' && turno != 'V' && turno != 'N') || (cargo != 'O' && cargo != 'G'));
        if (cargo == 'G') {
            if (turno == 'N') {
                v_hora = s_minimo * 0.18;
            } else {
                v_hora = s_minimo * 0.15;
            }
        } else {
            if (turno == 'N') {
                v_hora = s_minimo * 0.13;
            } else {
                v_hora = s_minimo * 0.1;
            }
        s_inicial = h_trabalhadas * v_hora;
        if (s_inicial <= 300) {
            auxilio = s_inicial * 0.2;
        } else if (s_inicial <= 600) {
            auxilio = s_inicial * 0.15;
        } else {
            auxilio = s_inicial * 0.05;
        }
        s_final = s_inicial + auxilio;
        printf("\nAcerca do funcionario de codigo %d, trabalhando %d horas por mes, este tera o valor de sua hora, seu salario inicial, seu auxilio e seu salario final equivalentes, respectivamente, a:\n%.2f\n%.2f\n%.2f\n%.2f\n\n", cod, h_trabalhadas, v_hora, s_inicial, auxilio, s_final);
    }
}
}
