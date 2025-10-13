#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int length (char *s) { // método para obter o tamanho da string
    if (!s) return 0; // se a string for nula, retorna 0

    int i = 0; // inicializa o índice
    while (s[i] != '\0') i++; // percorre a string até o caractere nulo
    return i; // retorna o tamanho da string
}

bool comparar (char *a, char *b) { // método para comparar duas strings
    if (a == NULL || b == NULL) return false; // se alguma for nula, retorna false

    int i = 0; // inicializa o índice
    while (a[i] != '\0' && b[i] != '\0') { // percorre ambas as strings enquanto não chegar ao final
        if (a[i] != b[i]) return false; // se algum caractere for diferente, retorna false
        i++;
    }
    return a[i] == '\0' && b[i] == '\0'; // retorna true se ambas chegaram ao final, caso contrário false
}

char *copiar (char *a, char *b) { // método para copiar uma string em outra
    char *str = a; // guarda o início da string saida

    if (!a) return a; // se saida for nula, retorna saida
    if (!b) { // se entrada for nula, finaliza saida como string vazia
        *a = '\0'; // finaliza a string saida
        return a; // retorna saida
    }

    while (*b != '\0') { // enquanto não chegar ao final da string entrada
        *a = *b; // copia o caractere de entrada para saida
        a++; b++; // avança ambos os ponteiros
    }
    *a = '\0'; // finaliza a string saida com o caractere nulo
    return str; // retorna o início da string saida
}

char *concatenar (char *a, char *b) { // método para concatenar duas strings
    char *str = a; // guarda o início da string a

    if (!a) return a; // se a for nula, retorna a
    while (*a != '\0') a++; // avança até o final da string a
    if (!b) { // se b for nula, finaliza a como string vazia
        *a = '\0';
        return str; // retorna a string a
    }

    while (*b != '\0') { // enquanto não chegar ao final da string b
        *a = *b; // copia o caractere de b para a
        a++; b++; // avança ambos os ponteiros
    }

    *a = '\0';
    return str; // retorna a string a
}

bool espaco (char c) { // método para verificar se um caractere é espaço em branco
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; // verifica os tipos de espaço em branco
}

void trim (char *str) { // método para remover espaços em branco do início e fim da string
    if (str == NULL) return; // se a string for nula, retorna

    int ini = 0, fim = length(str) - 1; // índices para o início e fim da string
    while (ini <= fim && espaco(str[ini])) ini++; // remove espaços em branco do início
    while (fim >= ini && espaco(str[fim])) fim--; // remove espaços em branco do fim
    int k = 0; // índice para a nova posição na string
    for (int t = ini; t <= fim; t++) str[k++] = str[t]; // desloca os caracteres para o início
    str[k] = '\0'; // finaliza a string removendo os espaços em branco do fim
}

void limparAspas (char *str) { // método para remover aspas do início e fim da string
    if (!str) return; // se a string for nula, retorna

    trim(str); // remove espaços em branco do início e fim
    int n = length(str); // obtém o tamanho da string
    if (n >= 2) { // se a string tiver pelo menos 2 caracteres
        char ini = str[0], fim = str[n - 1]; // obtém o primeiro e o último caractere
        if ((ini == '\"' && fim == '\"') || (ini == '\'' && fim == '\'')) { // se ambos forem aspas simples ou duplas
            for (int i = 1; i < n - 1; i++) str[i - 1] = str[i]; // desloca os caracteres para a esquerda
            str[n - 2] = '\0'; // finaliza a string removendo o último caractere
        }
    }
    trim(str); // remove espaços em branco novamente
}

int inteiro (char *str) { // método para converter string em int
    if (!str) return 0; // se a string for nula, retorna 0

    int i = 0, fim = length(str) - 1; // inicializa os índices para percorrer a string
    while (i <= fim && espaco(str[i])) i++; // remove espaços em branco do início
    while (fim >= i && espaco(str[fim])) fim--; // remove espaços em branco do fim

    int num = 0; // inicializa o número
    bool achou = false, negat = false; // flags para indicar se encontrou dígitos e se é negativo
    if (i <= fim && str[i] == '-') { // verifica se o número é negativo
        negat = true; // marca como negativo
        i++;
    }
    for (; i <= fim; i++) { // percorre cada caractere da string
        char c = str[i];
        if (c >= '0' && c <= '9') { // se for um dígito
            num = num * 10 + (c - '0'); // acumula o número
            achou = true; // marca que encontrou um dígito
        }
    }
    return achou ? (negat ? -num : num) : 0; // retorna o número final, considerando o sinal
}

float real (char *str) { // método para converter string em float
    if (!str) return 0.0f; // se a string for nula, retorna 0.0

    int i = 0, fim = length(str) - 1; // inicializa os índices para percorrer a string
    while (i <= fim && espaco(str[i])) i++; // remove espaços em branco do início
    while (fim >= i && espaco(str[fim])) fim--; // remove espaços em branco do fim

    float num = 0.0f, div = 1.0f; // inicializa o número e o divisor para a parte decimal
    bool achou = false, negat = false, decimal = false; // flags para indicar se encontrou dígitos, se é negativo e se está na parte decimal
    if (i <= fim && str[i] == '-') { // verifica se o número é negativo
        negat = true; // marca como negativo
        i++;
    }
    for (; i <= fim; i++) { // percorre cada caractere da string
        char c = str[i];
        if (c == '.') decimal = true; // se encontrar um ponto, marca que está na parte decimal
        else if (c >= '0' && c <= '9') { // se for um dígito
            achou = true; // marca que encontrou um dígito
            if (!decimal) num = num * 10.0f + (float)(c - '0'); // se não estiver na parte decimal, acumula o número inteiro
            else { // se estiver na parte decimal
                div *= 10.0f; // aumenta o divisor
                num = num + (float)(c - '0') / div; // acumula a parte decimal
            }
        }
    }
    return achou ? (negat ? -num : num) : 0.0f; // retorna o número final, considerando o sinal
}

int separaCampos (char *str, char campos[][1000], int maxCampos) { // método para separar os campos de uma linha CSV
    int n = 0, x = 0; // n é o contador de campos, x é o índice dentro do campo atual
    bool aspas = false; // flag para indicar se estamos dentro de aspas
    for (int i = 0; str[i] != '\0'; i++) { // percorrer cada caractere da string
        char c = str[i];
        if (c == '\"') aspas = !aspas; // alternar a flag de aspas ao encontrar uma aspa
        else if (c == ',' && !aspas) { // se encontrar uma vírgula fora de aspas, é o fim de um campo
            if (n < maxCampos) { // se não exceder o máximo de campos
                campos[n][x] = '\0'; // finalizar a string do campo atual
                limparAspas(campos[n]); // remover aspas do campo
                n++; x = 0;
            }
        }
        else { // caso contrário, adicionar o caractere ao campo atual
            if (n < maxCampos && x < 999) campos[n][x++] = c; // garantir que não exceda o tamanho do campo
        }
    }

    if (n < maxCampos) { // adicionar o último campo se houver caracteres
        campos[n][x] = '\0'; // finalizar a string do campo atual
        limparAspas(campos[n]); // remover aspas do campo
        n++; x = 0;
    }

    return n; // retornar o número de campos separados
}

int separaArray (char *str, char dest[][50], int max) { // método para separar os elementos de um array representado como string
    int n = 0, x = 0; // n é o contador de elementos, x é o índice dentro do elemento atual
    bool aspas = false; // flag para indicar se estamos dentro de aspas
    for (int i = 0; str[i] != '\0'; i++) { // percorrer cada caractere da string
        char c = str[i];
        if (c == '\"') aspas = !aspas; // alternar a flag de aspas ao encontrar uma aspa
        else if (c == ',' && !aspas) { // se encontrar uma vírgula fora de aspas, é o fim de um elemento
            if (x > 0 && n < max) { // se houver caracteres no elemento atual e não exceder o máximo
                dest[n][x] = '\0'; // finalizar a string do elemento atual
                trim(dest[n]); // remover espaços em branco do início e fim
                limparAspas(dest[n]); // remover aspas do elemento
                n++; x = 0;
            }
            else x = 0; // se não houver caracteres, apenas resetar o índice
        }
        else if (c == '[' || c == ']') { // ignorar colchetes
        } else { // caso contrário, adicionar o caractere ao elemento atual
            if (n < max && x < 49) dest[n][x++] = c; // garantir que não exceda o tamanho do array
        }
    }

    if (x > 0 && n < max) { // adicionar o último elemento se houver caracteres
        dest[n][x] = '\0'; // finalizar a string do elemento atual
        trim(dest[n]); // remover espaços em branco do início e fim
        limparAspas(dest[n]); // remover aspas do elemento
        n++; x = 0;
    }
    return n; // retornar o número de elementos separados
}

typedef struct { // estrutura para armazenar os dados do jogo com seus atributos
    int id, estimatedOwners, metacriticScore, achievements;
    char name[200], releaseDate[30];
    float price, userScore;
    char supportedLanguages[50][50], publishers[50][50], developers[50][50], categories[50][50], genres[50][50], tags[50][50];
} Game;

void inicializar (Game *g) { // método para inicializar os campos do jogo (construtor)
    g->id = 0;
    g->name[0] = '\0';
    g->releaseDate[0] = '\0';
    g->estimatedOwners = 0;
    g->price = 0.0f;
    g->metacriticScore = -1;
    g->userScore = -1.0f;
    g->achievements = 0;
    for (int i = 0; i < 50; i++) {
        g->supportedLanguages[i][0] = '\0';
        g->publishers[i][0] = '\0';
        g->developers[i][0] = '\0';
        g->categories[i][0] = '\0';
        g->genres[i][0] = '\0';
        g->tags[i][0] = '\0';
    }
}

void formatarData (char *src, char dest[]) { // método para formatar a data conforme o enunciado
    dest[0] = '\0'; // inicializa a string de destino como vazia
    if (!src || length(src) == 0) { // se a string de origem for nula ou vazia
        copiar(dest, "01/01/0001"); // copia a data padrão
        return;
    }

    char mes[4] = {0}; // array para armazenar o mês
    int i = 0; // índice para percorrer a string de origem
    for (i = 0; i < 3 && i < length(src); i++) mes[i] = src[i]; // copia os três primeiros caracteres (mês)
    mes[3] = '\0'; // finaliza a string do mês

    char mesNum[3] = "01"; // array para armazenar o número do mês
    if (comparar(mes, "Jan")) copiar(mesNum, "01");
    else if (comparar(mes, "Feb")) copiar(mesNum, "02");
    else if (comparar(mes, "Mar")) copiar(mesNum, "03");
    else if (comparar(mes, "Apr")) copiar(mesNum, "04");
    else if (comparar(mes, "May")) copiar(mesNum, "05");
    else if (comparar(mes, "Jun")) copiar(mesNum, "06");
    else if (comparar(mes, "Jul")) copiar(mesNum, "07");
    else if (comparar(mes, "Aug")) copiar(mesNum, "08");
    else if (comparar(mes, "Sep")) copiar(mesNum, "09");
    else if (comparar(mes, "Oct")) copiar(mesNum, "10");
    else if (comparar(mes, "Nov")) copiar(mesNum, "11");
    else if (comparar(mes, "Dec")) copiar(mesNum, "12"); // comparação do mês e atribuição do número correspondente

    while (i < length(src) && src[i] == ' ') i++; // pula espaços em branco

    char dia[3] = {0}; // array para armazenar o dia
    int pos = 0; // índice para o dia
    while (i < length(src) && src[i] >= '0' && src[i] <= '9' && pos < 2) { // enquanto encontrar dígitos
        dia[pos++] = src[i]; // copia o dígito para o dia
        i++;
    }
    dia[pos] = '\0'; // finaliza a string do dia
    char diaNum[3] = "01"; // array para armazenar o número do dia
    int tam = length(dia); // obtém o tamanho do dia
    if (tam == 0) { // se não houver dia, atribui 01
        diaNum[0] = '0';
        diaNum[1] = '1';
        diaNum[2] = '\0';
    }
    else if (tam == 1) { // se houver um dígito, adiciona o zero à esquerda
        diaNum[0] = '0';
        diaNum[1] = dia[0];
        diaNum[2] = '\0';
    }
    else copiar(diaNum, dia); // caso contrário, copia o dia normalmente

    while (i < length(src) && (src[i] == ' ' || src[i] == ',')) i++; // pula espaços em branco e vírgulas

    char ano[5] = {0}; // array para armazenar o ano
    pos = 0; // índice para o ano
    while (i < length(src) && src[i] >= '0' && src[i] <= '9' && pos < 4) { // enquanto encontrar dígitos
        ano[pos++] = src[i]; // copia o dígito para o ano
        i++;
    }
    ano[pos] = '\0'; // finaliza a string do ano
    if (length(ano) != 4) copiar(ano, "0001"); // se o ano não tiver 4 dígitos, atribui 0001

    dest[0] = '\0'; // inicializa a string de destino como vazia
    concatenar(dest, diaNum);
    concatenar(dest, "/");
    concatenar(dest, mesNum);
    concatenar(dest, "/");
    concatenar(dest, ano); // concatena dia, mês e ano no formato dd/mm/aaaa
}

void formatarPreco (float preco) { // método para formatar o preço conforme o enunciado
    if (preco == 0.0f) printf("0.0"); // se o preço for 0.0, imprime "0.0"
    else if (preco == (int)preco) printf("%d", (int)preco); // se o preço for um número inteiro, imprime como inteiro
    else if (((int)(preco * 10)) == (preco * 10)) printf("%.1f", preco); // se o preço tiver uma casa decimal, imprime com uma casa decimal
    else printf("%.2f", preco); // caso contrário, imprime com duas casas decimais
}

void processarLinha (char *linha, Game *game) { // método para processar a linha lida do arquivo
    inicializar(game); // inicializar os campos do jogo
    char campos[20][1000]; // array para armazenar os campos separados
    int ncampos = separaCampos(linha, campos, 20); // separar os campos da linha

    if (ncampos > 0) game->id = inteiro(campos[0]); // converter o primeiro campo para inteiro e armazenar no id

    if (ncampos > 1) { // processar o segundo campo para nome
        copiar(game->name, campos[1]); // copiar o segundo campo para o nome
        trim(game->name);
    }

    if (ncampos > 2) { // processar o terceiro campo para data de lançamento
        copiar(game->releaseDate, campos[2]); // copiar o terceiro campo para a data de lançamento
        trim(game->releaseDate);
    }

    if (ncampos > 3) { // processar o quarto campo para estimativa de donos
        char nums[100]; // array para armazenar apenas os dígitos
        int n = 0; // contador de dígitos
        for (int i = 0; campos[3][i] != '\0'; i++) { // percorrer cada caractere do campo
            char c = campos[3][i]; // obter o caractere atual
            if (c >= '0' && c <= '9') { // se for um dígito, armazenar no array de dígitos
                if (n < 99) nums[n++] = c; // evitar overflow
            }
        }
        nums[n] = '\0'; // finalizar a string de dígitos
        game->estimatedOwners = inteiro(nums); // converter a string de dígitos para inteiro e armazenar na estimativa de donos
    }

    if (ncampos > 4) { // processar o quinto campo para preço
        char preco[100]; // array para armazenar o preço
        copiar(preco, campos[4]);
        trim(preco);
        if (comparar(preco, "Free to Play") || length(preco) == 0) game->price = 0.0f; // se for "Free to Play" ou estiver vazio, o preço é 0.0
        else game->price = real(preco); // caso contrário, converter para float e armazenar no preço
    }

    if (ncampos > 5) { // processar o sexto campo para idiomas suportados
        separaArray(campos[5], game->supportedLanguages, 50); // separar os idiomas e armazenar no array
        for (int i = 0; i < 50 && game->supportedLanguages[i][0] != '\0'; i++) limparAspas(game->supportedLanguages[i]); // remover aspas de cada idioma
    }

    if (ncampos > 6) { // processar o sétimo campo para pontuação do Metacritic
        char meta[100]; // array para armazenar a pontuação do Metacritic
        copiar(meta, campos[6]);
        trim(meta);
        if (length(meta) == 0) game->metacriticScore = -1; // se estiver vazio, a pontuação é -1
        else game->metacriticScore = inteiro(meta); // caso contrário, converter para inteiro e armazenar na pontuação do Metacritic
    }

    if (ncampos > 7) { // processar o oitavo campo para pontuação do usuário
        char user[100]; // array para armazenar a pontuação do usuário
        copiar(user, campos[7]);
        trim(user);
        if (length(user) == 0 || comparar(user, "tbd")) game->userScore = -1.0f; // se estiver vazio ou for "tbd", a pontuação é -1.0
        else game->userScore = real(user); // caso contrário, converter para float e armazenar na pontuação do usuário
    }

    if (ncampos > 8) { // processar o nono campo para conquistas
        char ach[100]; // array para armazenar as conquistas
        copiar(ach, campos[8]); // copiar o campo para uma variável temporária
        trim(ach);
        if (length(ach) == 0) game->achievements = 0; // se estiver vazio, as conquistas são 0
        else game->achievements = inteiro(ach); // caso contrário, converter para inteiro e armazenar nas conquistas
    }

    if (ncampos > 9) separaArray(campos[9], game->publishers, 50);
    if (ncampos > 10) separaArray(campos[10], game->developers, 50);
    if (ncampos > 11) separaArray(campos[11], game->categories, 50);
    if (ncampos > 12) separaArray(campos[12], game->genres, 50);
    if (ncampos > 13) separaArray(campos[13], game->tags, 50); // processar os demais campos para editores, desenvolvedores, categorias, gêneros e tags
}

void mostrar (Game *g) { // método para mostrar os dados do jogo para cada atributo e suas devidas formatações
    char data[11];
    formatarData(g->releaseDate, data);

    printf("=> %d ## %s ## %s ## %d ## ", g->id, g->name, data, g->estimatedOwners); // imprimir id, nome, data formatada e estimativa de donos
    formatarPreco(g->price); // imprimir o preço formatado
    printf(" ## [");

    for (int i = 0; i < 50 && g->supportedLanguages[i][0] != '\0'; i++) { // imprimir os idiomas suportados
        if (i > 0) printf(", ");
        printf("%s", g->supportedLanguages[i]);
    }

    printf("] ## %d ## %.1f ## %d ## [", g->metacriticScore, g->userScore, g->achievements); // imprimir pontuação do Metacritic, pontuação do usuário e conquistas

    for (int i = 0; i < 50 && g->publishers[i][0] != '\0'; i++) { // imprimir os editores
        if (i > 0) printf(", ");
        printf("%s", g->publishers[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && g->developers[i][0] != '\0'; i++) { // imprimir os desenvolvedores
        if (i > 0) printf(", ");
        printf("%s", g->developers[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && g->categories[i][0] != '\0'; i++) { // imprimir as categorias
        if (i > 0) printf(", ");
        printf("%s", g->categories[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && g->genres[i][0] != '\0'; i++) { // imprimir os gêneros
        if (i > 0) printf(", ");
        printf("%s", g->genres[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && g->tags[i][0] != '\0'; i++) { // imprimir as tags
        if (i > 0) printf(", ");
        printf("%s", g->tags[i]);
    }
    printf("] ##\n");
}

int main() { // main do programa
    char entrada[10]; // declaração e leitura da entrada
    while (!comparar(entrada, "FIM")) { // enquanto a entrada não for "FIM"
        int id = inteiro(entrada); // converte a entrada para inteiro
        FILE *arq = fopen("/tmp/games.csv", "r"); // abertura do arquivo para leitura

        char linha[2000]; // buffer para ler cada linha do arquivo
        fgets(linha, sizeof(linha), arq); // ler a primeira linha (cabeçalho) e ignorar

        bool encontrado = false;
        while (!encontrado && fgets(linha, sizeof(linha), arq) != NULL) { // ler cada linha do arquivo
            int len = length(linha); // obter o tamanho da linha lida
            if (len > 0 && linha[len - 1] == '\n') linha[len - 1] = '\0'; // remove o caractere de nova linha, se presente

            int i = 0; // índice para percorrer a linha
            char idGame[10]; // buffer para armazenar o id como string
            int ib = 0; // índice para idGame
            while (linha[i] != '\0' && linha[i] != ',' && ib < 9) idGame[ib++] = linha[i++]; // extrair o id
            idGame[ib] = '\0'; // finalizar a string do id
            int idEntrada = inteiro(idGame); // converter o id para inteiro

            if (idEntrada == id) { // se o id da linha for igual ao código procurado
                Game g; // criar uma variável do tipo Game
                processarLinha(linha, &g); // processar a linha e preencher os dados do jogo
                mostrar(&g); // mostrar os dados do jogo
                encontrado = true; // marcar como encontrado e sair do loop
            }
        }

        fclose(arq);
        scanf("%s", entrada); // lê a próxima entrada
    }

    return 0;
}
