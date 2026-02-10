#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1 = 1, N, n_operario = 0, p_fabricadas, n_maior, s_minimo = 450, t_pecas = 0, n_feminino = 0, n_masculino = 0, s_masculino = 0, s_feminino = 0, c;
    float m_pecasmasculino = 0, m_pecasfeminino = 0, t_folha = 0, s_individual, s_maior;
    char genero;
    printf("Insira quantos funcionarios deseja realizar os calculos:\n");
    scanf("%d", &N);
    while (cont1 <= N) {
        printf("\nInsira o numero do operario, seu genero (M ou F) e o numero de pecas fabricadas no mes pelo funcionario:\n");
        scanf("%d %c%d", &n_operario, &genero, &p_fabricadas);
        if (genero != 'M' && genero != 'F') {
            printf("\nGenero invalido!\n");
            return 0;
        }
        if (p_fabricadas <= 30) {
            s_individual = s_minimo;
            c = 1;
        } else if (p_fabricadas <= 50) {
            s_individual = s_minimo + ((p_fabricadas - 30) * s_minimo * 0.03);
            c = 2;
        } else {
            s_individual = s_minimo + ((p_fabricadas - 30) * s_minimo * 0.05);
            c = 3;
        }
        if (genero == 'M') {
            printf("\nO operario de numero %d recebe %.2f reais e se enquadra na classe %d!\n", n_operario, s_individual, c);
            s_masculino += p_fabricadas;
            n_masculino++;
        } else if (genero == 'F') {
            printf("\nA operaria de numero %d recebe %.2f reais e se enquadra na classe %d!\n", n_operario, s_individual, c);
            s_feminino += p_fabricadas;
            n_feminino++;;
        }
        t_folha += s_individual;
        t_pecas += p_fabricadas;
        if (cont1 == 1 || s_individual > s_maior) {
            s_maior = s_individual;
            n_maior = n_operario;
        }
        cont1++;
    }
    printf("\nO total da folha de pagamento e o total de pecas fabricadas nesse mes e de:\n%.2f\n%d\n", t_folha, t_pecas);
    if (n_masculino == 0) {
        printf("\nNenhum operario homem!\n");
    } else {
        m_pecasmasculino = s_masculino*1.0/n_masculino;
        printf("\nA media de pecas fabricadas por homens e igual a:\n%.2f\n", m_pecasmasculino);
    }
    if (n_feminino == 0) {
        printf("\nNenhuma operaria mulher!\n");
    } else {
        m_pecasfeminino = s_feminino*1.0/n_feminino;
        printf("\nA media de pecas fabricadas por mulheres e igual a:\n%.2f\n", m_pecasfeminino);
    }
    printf("\nO numero do(a) operario(a) de maior salario (%.2f reais) e:\n%d\n", s_maior, n_maior);
}
