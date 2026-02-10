#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1, N, cod, n_veiculos, n_acidentes, cont_acidentes = 0, s_veiculos = 0, s_acidentes = 0, cidade_M, cidade_m, indice_M, indice_m;
    float m_veiculos, m_acidentes;
    printf("Insira quantas cidades quer calcular:\n");
    scanf("%d", &N);
    for (cont1 = 1; cont1 <= N; cont1++) {
        printf("Insira o codigo da cidade, o numero de veiculos e o numero de acidentes:\n");
        scanf("%d%d%d", &cod, &n_veiculos, &n_acidentes);
        if (cont1 == 1) {
            indice_M = n_acidentes;
            cidade_M = cod;
            indice_m = n_acidentes;
            cidade_m = cod;
        } else {
            if (n_acidentes > indice_M) {
                indice_M = n_acidentes;
                cidade_M = cod;
            } else if (n_acidentes < indice_m) {
                indice_m = n_acidentes;
                cidade_m = cod;
            }
        }
        s_veiculos += n_veiculos;
        if (n_veiculos < 2000) {
            s_acidentes += n_acidentes;
            cont_acidentes += 1;
        }
    }
    printf("\nO maior indice de acidentes e de %d na cidade %d!\n", indice_M, cidade_M);
    printf("\nO menor indice de acidentes e de %d na cidade %d!\n", indice_m, cidade_m);
    m_veiculos = s_veiculos/5.0;
    printf("\nA media de veiculos e de %.2f!\n", m_veiculos);
    if (cont_acidentes == 0) {
        printf("\nNao foi inserida nenhuma cidade com menos de 2000 veiculos!\n");
    } else {
        m_acidentes = s_acidentes*1.0/cont_acidentes;
        printf("\nA media de acidentes e de %.2f!\n", m_acidentes);
    }
}

