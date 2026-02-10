#include <stdio.h>
#include <stdlib.h>

int main() {
    int cod, aulas_mensais, homens = 0, mulheres = 0;
    float s_bruto = 0, s_liquido = 0, m_salmasculino = 0, m_salfeminino = 0, m_aulasmasculino = 0, m_aulasfeminino = 0, desconto;
    char sexo;
    printf("Insira o codigo do professor:\n");
    scanf("%d", &cod);
    while (cod != 99999) {
        printf("\nInsira a quantidade de aulas mensais e o sexo do professor (M ou F):\n");
        scanf("%d %c", &aulas_mensais, &sexo);
        s_bruto = aulas_mensais * 30;
        if (sexo == 'M') {
            desconto = 0.1;
            s_liquido = s_bruto - s_bruto * desconto;
            m_salmasculino += s_liquido;
            m_aulasmasculino += aulas_mensais;
            homens++;
        } else {
            desconto = 0.05;
            s_liquido = s_bruto - s_bruto * desconto;
            m_salfeminino += s_liquido;
            m_aulasfeminino += aulas_mensais;
            mulheres++;
        }
        printf("\nO professor de codigo %d recebera um salario bruto de %.2f reais e, descontando %.2f reais, tera um salario liquido de %.2f reais!\n", cod, s_bruto, s_bruto*desconto, s_liquido);
        printf("\nInsira o codigo do professor:\n");
        scanf("%d", &cod);
    }
    if (homens == 0) {
        printf("\nNenhuum professor homem!\n");
    } else {
        m_salmasculino /= homens;
        m_aulasmasculino /= homens;
        printf("\nA media de aulas dadas entre os professores e de %.2f horas!\n", m_aulasmasculino);
        printf("\nA media de salario entre os professores e de %.2f reais!\n", m_salmasculino);
    }
    if (mulheres == 0) {
        printf("\nNenhuma professora mulher!\n");
    } else {
        m_salfeminino /= mulheres;
        m_aulasfeminino /= mulheres;
        printf("\nA media de aulas dadas entre as professoras e de %.2f horas!\n", m_aulasfeminino);
        printf("\nA media de salario entre as professoras e de %.2f reais!\n", m_salfeminino);
    }
}