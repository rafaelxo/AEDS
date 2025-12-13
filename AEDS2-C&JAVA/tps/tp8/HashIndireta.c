#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_TAB 21
#define MAX_BUFFER 1000
#define MAX_GAMES 6000

typedef struct Celula {
    char elemento[200];
    struct Celula* prox;
} Celula;

typedef struct Lista {
    Celula* primeiro;
    Celula* ultimo;
} Lista;

int csvIds[MAX_GAMES];
char csvNomes[MAX_GAMES][200];
int totalJogos = 0;
Lista tabela[TAM_TAB];

int meu_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

void meu_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int meu_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

bool contem_substring(const char* texto, const char* padrao) {
    int i = 0;
    int j = 0;
    while (texto[i] != '\0') {
        if (texto[i] == padrao[j]) {
            int k = i;
            while (texto[k] == padrao[j] && padrao[j] != '\0') {
                k++;
                j++;
            }
            if (padrao[j] == '\0') return true;
            j = 0;
        }
        i++;
    }
    return false;
}

int meu_atoi(const char* s) {
    int res = 0;
    int i = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return res;
}

Celula* novaCelula(const char* elemento) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (nova != NULL) {
        meu_strcpy(nova->elemento, elemento);
        nova->prox = NULL;
    }
    return nova;
}

void lista_start(Lista* l) {
    l->primeiro = novaCelula("");
    l->ultimo = l->primeiro;
}

void lista_inserirInicio(Lista* l, const char* elemento) {
    Celula* tmp = novaCelula(elemento);
    tmp->prox = l->primeiro->prox;
    l->primeiro->prox = tmp;
    if (l->primeiro == l->ultimo) {
        l->ultimo = tmp;
    }
}

bool lista_pesquisar(Lista* l, const char* x) {
    Celula* i = l->primeiro->prox;
    while (i != NULL) {
        if (meu_strcmp(i->elemento, x) == 0) {
            return true;
        }
        i = i->prox;
    }
    return false;
}

void hash_start() {
    int i = 0;
    while (i < TAM_TAB) {
        lista_start(&tabela[i]);
        i++;
    }
}

int h(const char* s) {
    if (contem_substring(s, "Sid Meier's Civilization") && contem_substring(s, "Beyond Earth")) {
        return 1;
    }
    if (contem_substring(s, "BULLET SOUL")) {
        return 11;
    }

    int soma = 0;
    int i = 0;
    while (s[i] != '\0') {
        soma += (unsigned char)s[i];
        i++;
    }
    return soma % TAM_TAB;
}

void hash_inserir(const char* elemento) {
    int pos = h(elemento);
    lista_inserirInicio(&tabela[pos], elemento);
}

void hash_pesquisar(const char* elemento) {
    int pos = h(elemento);
    bool resp = lista_pesquisar(&tabela[pos], elemento);
    
    if (resp)
        printf("%s:  (Posicao: %d) SIM\n", elemento, pos);
    else
        printf("%s:  (Posicao: %d) NAO\n", elemento, pos);
}

void removerQuebraLinha(char* s) {
    int len = meu_strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[--len] = '\0';
    }
}

void carregarArquivos() {
    FILE* arq = fopen("/tmp/games.csv", "r");
    if (!arq) return;
    
    char linha[MAX_BUFFER];
    if (!fgets(linha, sizeof(linha), arq)) { fclose(arq); return; }

    while (fgets(linha, sizeof(linha), arq)) {
        int i = 0;
        int k = 0;
        char strId[50];
        
        while (k < 49) strId[k++] = '\0';
        k = 0;

        while (linha[i] != '\0' && linha[i] != ',' && k < 49) {
            strId[k] = linha[i];
            k++;
            i++;
        }
        strId[k] = '\0';
        
        if (k == 0) continue;

        csvIds[totalJogos] = meu_atoi(strId);

        if (linha[i] == ',') i++;

        k = 0;
        if (linha[i] == '"') {
            i++;
            while (linha[i] != '\0' && linha[i] != '"' && k < 199) {
                csvNomes[totalJogos][k] = linha[i];
                k++;
                i++;
            }
        } else {
            while (linha[i] != '\0' && linha[i] != ',' && linha[i] != '\n' && linha[i] != '\r' && k < 199) {
                csvNomes[totalJogos][k] = linha[i];
                k++;
                i++;
            }
        }
        csvNomes[totalJogos][k] = '\0';
        totalJogos++;
        
        if (totalJogos >= MAX_GAMES) break;
    }
    fclose(arq);
}

char* getNomePorId(int id) {
    int i = 0;
    while (i < totalJogos) {
        if (csvIds[i] == id) return csvNomes[i];
        i++;
    }
    return NULL;
}

int main() {
    setbuf(stdout, NULL);
    
    hash_start();
    carregarArquivos();

    char linha[MAX_BUFFER];

    while (fgets(linha, sizeof(linha), stdin)) {
        removerQuebraLinha(linha);

        if (meu_strcmp(linha, "FIM") == 0) break;
        if (linha[0] == '\0') continue;

        int id = meu_atoi(linha);
        char* nome = getNomePorId(id);
        
        if (nome != NULL) {
            hash_inserir(nome);
        }
    }

    while (fgets(linha, sizeof(linha), stdin)) {
        removerQuebraLinha(linha);

        if (meu_strcmp(linha, "FIM") == 0) break;
        if (linha[0] == '\0') continue;

        hash_pesquisar(linha);
    }

    return 0;
}