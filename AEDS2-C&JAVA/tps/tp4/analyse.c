#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool comparar (char a[], char b[]) { // método para comparar duas strings
    if (a == NULL || b == NULL) return false; // se alguma for nula, retorna false
    int i = 0; // inicializa o índice
    while (a[i] != '\0' && b[i] != '\0') { // percorre ambas as strings enquanto não chegar ao final
        if (a[i] != b[i]) return false; // se algum caractere for diferente, retorna false
        i++; // avança o índice
    }
    return (a[i] == '\0' && b[i] == '\0'); // retorna true se ambas chegaram ao final, caso contrário false
}

char* copiar (char *a, char *b) { // método para copiar uma string em outra
    char *str = a; // guarda o início da string a
    while (*b != '\0') { // enquanto não chegar ao final da string b
        *a = *b; // copia o caractere de b para a
        a++; b++; // avança ambos os ponteiros
    }
    *a = '\0'; // finaliza a string a com o caractere nulo
    return str; // retorna o início da string a
}

char *concatenar (char *a, char *b) { // método para concatenar duas strings
    char *str = a; // guarda o início da string a
    while (*a != '\0') a++; // avança até o final da string a
    while (*b != '\0') { // enquanto não chegar ao final da string b
        *a = *b; // copia o caractere de b para a
        a++; b++; // avança ambos os ponteiros
    }
    *a = '\0'; // finaliza a string a com o caractere nulo
    return str; // retorna o início da string a
}

int length (char str[]) { // método para obter o tamanho da string
    int i = 0; // inicializa o índice
    while (str[i] != '\0') i++; // percorre a string até o caractere nulo
    return i; // retorna o tamanho da string
}

void trim (char str[]) { // método para remover espaços em branco do início e fim da string
    if (str == NULL) return; // se a string for nula, retorna

    int i = 0, j = length(str) - 1; // inicializa os índices para o início e fim da string
    while (i <= j && (str[i] == ' ' || str[i] == '\t')) i++; // remove espaços em branco do início
    while (j >= i && (str[j] == ' ' || str[j] == '\t')) j--; // remove espaços em branco do fim

    for (int k = i; k <= j; k++) str[k - i] = str[k]; // desloca os caracteres para o início
    str[j - i + 1] = '\0'; // finaliza a string removendo os espaços em branco do fim
}

void limparAspas (char str[]) { // método para remover aspas do início e fim da string
    if (str == NULL) return; // se a string for nula, retorna

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

typedef struct { // estrutura para armazenar os dados do jogo
    // atributos
    int id, estimatedOwners, metacriticScore, achievements;
    char name[200], releaseDate[30];
    float price, userScore;
    char supportedLanguages[50][50], publishers[50][50], developers[50][50], categories[50][50], genres[50][50], tags[50][50];
} Game;

void inicializar (Game *game) { // método para inicializar os campos do jogo (construtor)
    game->id = 0;
    game->name[0] = '\0';
    game->releaseDate[0] = '\0';
    game->estimatedOwners = 0;
    game->price = 0.0f;
    game->metacriticScore = -1;
    game->userScore = -1.0f;
    game->achievements = 0;
    for (int i = 0; i < 50; i++) {
        copiar(game->supportedLanguages[i], "");
        copiar(game->publishers[i], "");
        copiar(game->developers[i], "");
        copiar(game->categories[i], "");
        copiar(game->genres[i], "");
        copiar(game->tags[i], "");
    }
}

void formatarData (char *str, char dest[]) { // método para formatar a data no formato dd/mm/aaaa
    dest[0] = '\0'; // inicializa a string de destino como vazia
    if (str == NULL || length(str) == 0) { // se a string de entrada for nula ou vazia
        copiar(dest, "01/01/0001"); // copia a data padrão
        return; // retorna
    }

    char mes[4]; // array para armazenar o mês
    int i = 0; // índice para percorrer a string de entrada
    for (i = 0; i < 3; i++) mes[i] = str[i]; // copia os três primeiros caracteres (mês)
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

    while (i < length(str) && str[i] == ' ') i++; // pula espaços em branco

    char dia[3] = ""; // array para armazenar o dia
    int pos = 0; // índice para o dia
    while (i < length(str) && str[i] >= '0' && str[i] <= '9') { // enquanto encontrar dígitos
        dia[pos++] = str[i]; // copia o dígito para o dia
        i++; // avança o índice
    }
    dia[pos] = '\0'; // finaliza a string do dia
    char diaNum[3]; // array para armazenar o número do dia
    int tam = length(dia); // obtém o tamanho do dia
    if (length(dia) == 0) diaNum[0] = '0', diaNum[1] = '1', diaNum[2] = '\0'; // se não houver dia, atribui 01
    else if (tam == 1) diaNum[0] = '0', diaNum[1] = dia[0], diaNum[2] = '\0'; // se o dia tiver 1 dígito, adiciona um zero à esquerda
    else copiar(diaNum, dia); // caso contrário, copia o dia normalmente

    while(i < length(str) && (str[i] == ' ' || str[i] == ',')) i++; // pula espaços em branco e vírgulas

    char ano[5] = ""; // array para armazenar o ano
    pos = 0; // índice para o ano
    while (i < length(str) && str[i] >= '0' && str[i] <= '9') { // enquanto encontrar dígitos
        ano[pos++] = str[i]; // copia o dígito para o ano
        i++; // avança o índice
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

void formatarPreco (float preco) {
    if (preco == 0.0f) printf("0.0");
    else if (preco == (int)preco) printf("%d", (int)preco);
    else if (((int)(preco * 10)) == (preco * 10)) printf("%.1f", preco);
    else printf("%.2f", preco);
}

void mostrar (Game *games) { // método para mostrar os dados do jogo
    char dataFormatada[11];
    formatarData(games->releaseDate, dataFormatada);

    printf("=> %d ## %s ## %s ## %d ## ", games->id, games->name, dataFormatada, games->estimatedOwners); formatarPreco(games->price);
    printf(" ## [");

    for (int i = 0; i < 50 && games->supportedLanguages[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->supportedLanguages[i]);
    }

    printf("] ## %d ## %.1f ## %d ## [", games->metacriticScore, games->userScore, games->achievements);

    for (int i = 0; i < 50 && games->publishers[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->publishers[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && games->developers[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->developers[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && games->categories[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->categories[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && games->genres[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->genres[i]);
    }
    printf("] ## [");

    for (int i = 0; i < 50 && games->tags[i][0] != '\0'; i++) {
        if (i > 0) printf(", ");
        printf("%s", games->tags[i]);
    }
    printf("] ##\n"); // formatação da saída conforme o enunciado
}

int inteiro (char str[]) { // método para converter string em inteiro
    if (length(str) == 0) return 0; // se a string estiver vazia, retorna 0

    int i = 0, fim = length(str) - 1; // inicializa os índices para percorrer a string
    while (i <= fim && (str[i] == ' ' || str[i] == '\t')) i++; // remove espaços em branco do início
    while (fim >= i && (str[fim] == ' ' || str[fim] == '\t')) fim--; // remove espaços em branco do fim

    int num = 0; // inicializa o número
    bool achou = false, negat = false; // flags para indicar se encontrou dígitos e se é negativo
    if (i <= fim && str[i] == '-') { // verifica se o número é negativo
        negat = true; // marca como negativo
        i++; // avança o índice
    }

    for (; i <= fim; i++) { // percorre cada caractere da string
        char c = str[i]; // obtém o caractere atual
        if (c >= '0' && c <= '9') { // se for um dígito
            num = num * 10 + (c - '0'); // acumula o número
            achou = true; // marca que encontrou um dígito
        }
    }

    return achou ? (negat ? -num : num) : 0; // retorna o número final, considerando o sinal
}

float real (char str[]) { // método para converter string em float
    if(length(str) == 0) return 0.0; // se a string estiver vazia, retorna 0.0

    int i = 0, fim = length(str) - 1; // inicializa os índices para percorrer a string
    while (i <= fim && (str[i] == ' ' || str[i] == '\t')) i++; // remove espaços em branco do início
    while (fim >= i && (str[fim] == ' ' || str[fim] == '\t')) fim--; // remove espaços em branco do fim

    float num = 0, div = 1; // inicializa o número e o divisor para a parte decimal
    bool achou = false, negat = false, decimal = false; // flags para indicar se encontrou dígitos, se é negativo e se está na parte decimal
    if (i <= fim && str[i] == '-') { // verifica se o número é negativo
        negat = true; // marca como negativo
        i++; // avança o índice
    }

    for (; i <= fim; i++) { // percorre cada caractere da string
        char c = str[i]; // obtém o caractere atual
        if (c == '.') decimal = true; // se encontrar um ponto, marca que está na parte decimal
        else if (c >= '0' && c <= '9') { // se for um dígito
            achou = true; // marca que encontrou um dígito
            if (!decimal) num = num * 10 + (c - '0'); // se não estiver na parte decimal, acumula o número inteiro
            else { // se estiver na parte decimal
                div *= 10; // aumenta o divisor
                num = num + (float)(c - '0') / div; // acumula a parte decimal
            }
        }
    }

    return achou ? (negat ? -num : num) : 0.0; // retorna o número final, considerando o sinal
}

int separaCampos (char str[], char campos[][1000]) { // método para separar os campos de uma linha CSV
    int n = 0, x = 0; // n é o contador de campos, x é o índice dentro do campo atual
    bool aspas = false; // flag para indicar se estamos dentro de aspas
    for (int i = 0; str[i] != '\0'; i++) { // percorrer cada caractere da string
        char c = str[i]; // obter o caractere atual
        if (c == '\"') aspas = !aspas; // alternar a flag de aspas ao encontrar uma aspa
        else if (c == ',' && !aspas) { // se encontrar uma vírgula fora de aspas, é o fim de um campo
            campos[n][x] = '\0'; // finalizar a string do campo atual
            limparAspas(campos[n]); // remover aspas do campo
            n++; x = 0; // incrementar o contador de campos e resetar o índice
        } else campos[n][x++] = c; // caso contrário, adicionar o caractere ao campo atual
    }

    campos[n][x] = '\0'; // finalizar a string do último campo
    limparAspas(campos[n]); // remover aspas do último campo

    return n + 1; // retornar o número de campos separados
}

int separaArray (char str[], char dest[][50], int max) { // método para separar os elementos de um array representado como string
    int n = 0, x = 0; // n é o contador de elementos, x é o índice dentro do elemento atual
    bool aspas = false; // flag para indicar se estamos dentro de aspas
    for (int i = 0; str[i] != '\0'; i++) { // percorrer cada caractere da string
        char c = str[i]; // obter o caractere atual
        if (c == '\"') aspas = !aspas; // alternar a flag de aspas ao encontrar uma aspa
        else if (c == ',' && !aspas) { // se encontrar uma vírgula fora de aspas, é o fim de um elemento
            if (x > 0 && n < max) { // se houver caracteres no elemento atual e não exceder o máximo
                dest[n][x] = '\0'; // finalizar a string do elemento atual
                trim(dest[n]); // remover espaços em branco
                n++; x = 0; // incrementar o contador de elementos e resetar o índice
            } else x = 0; // se não houver caracteres, apenas resetar o índice
        } else if (c == '[' || c == ']') { // ignorar colchetes
        } else { // caso contrário, adicionar o caractere ao elemento atual
            if (n < max && x < 49) dest[n][x++] = c; // garantir que não exceda o tamanho do array
        }
    }

    if (x > 0 && n < max) { // adicionar o último elemento se houver caracteres
        dest[n][x] = '\0'; // finalizar a string do elemento atual
        trim(dest[n]); // remover espaços em branco
        n++; // incrementar o contador de elementos
    }

    return n; // retornar o número de elementos separados
}

void processar (char str[], Game *game) { // método para processar a linha lida do arquivo
    inicializar(game); // inicializar os campos do jogo
    char campos[20][1000]; // array para armazenar os campos separados
    int ncampos = separaCampos(str, campos); // separar os campos da linha

    if (ncampos > 0) game->id = inteiro(campos[0]); // converter o primeiro campo para inteiro e armazenar no id
    if (ncampos > 1) { // processar o segundo campo para nome
        copiar(game->name, campos[1]); // copiar o segundo campo para o nome
        trim(game->name); // remover espaços em branco
    }
    if (ncampos > 2) { // processar o terceiro campo para data de lançamento
        copiar(game->releaseDate, campos[2]); // copiar o terceiro campo para a data de lançamento
        trim(game->releaseDate); // remover espaços em branco
    }
    if (ncampos > 3) { // processar o quarto campo para estimativa de donos
        char nums[100]; // array para armazenar apenas os dígitos
        int n = 0; // contador de dígitos
        for (int i = 0; campos[3][i] != '\0'; i++) { // percorrer cada caractere do campo
            char c = campos[3][i]; // obter o caractere atual
            if (c >= '0' && c <= '9') nums[n++] = c; // se for um dígito, armazenar no array de dígitos
        }
        nums[n] = '\0'; // finalizar a string de dígitos
        game->estimatedOwners = inteiro(nums); // converter a string de dígitos para inteiro e armazenar na estimativa de donos
    }
    if (ncampos > 4) { // processar o quinto campo para preço
        char preco[100]; copiar(preco, campos[4]); // copiar o campo para uma variável temporária
        trim(preco); // remover espaços em branco
        if (comparar(preco, "Free to Play")) game->price = 0.0f; // se for "Free to Play", o preço é 0.0
        else if (length(preco) == 0) game->price = 0.0f; // se estiver vazio, o preço é 0.0
        else game->price = real(preco); // caso contrário, converter para float e armazenar no preço
    }
    if (ncampos > 5) { // processar o sexto campo para idiomas suportados
        separaArray(campos[5], game->supportedLanguages, 50); // separar os idiomas e armazenar no array
        for (int i = 0; i < 50 && game->supportedLanguages[i][0] != '\0'; i++) limparAspas(game->supportedLanguages[i]); // remover aspas de cada idioma
    }
    if (ncampos > 6) { // processar o sétimo campo para pontuação do Metacritic
        char meta[100]; copiar(meta, campos[6]); // copiar o campo para uma variável temporária
        trim(meta); // remover espaços em branco
        if (length(meta) == 0) game->metacriticScore = -1; // se estiver vazio, a pontuação é -1
        else game->metacriticScore = inteiro(meta); // caso contrário, converter para inteiro e armazenar na pontuação do Metacritic
    }
    if (ncampos > 7) { // processar o oitavo campo para pontuação do usuário
        char user[100]; copiar(user, campos[7]); // copiar o campo para uma variável temporária
        trim(user); // remover espaços em branco
        if (length(user) == 0 || comparar(user, "tbd")) game->userScore = -1.0f; // se estiver vazio ou for "tbd", a pontuação é -1.0
        else game->userScore = real(user); // caso contrário, converter para float e armazenar na pontuação do usuário
    }
    if (ncampos > 8) { // processar o nono campo para conquistas
        char ach[100]; copiar(ach, campos[8]); // copiar o campo para uma variável temporária
        trim(ach); // remover espaços em branco
        if (length(ach) == 0) game->achievements = 0; // se estiver vazio, as conquistas são 0
        else game->achievements = inteiro(ach); // caso contrário, converter para inteiro e armazenar nas conquistas
    }
    if (ncampos > 9) separaArray(campos[9], game->publishers, 50); // processar o décimo campo para editores
    if (ncampos > 10) separaArray(campos[10], game->developers, 50); // processar o décimo primeiro campo para desenvolvedores
    if (ncampos > 11) separaArray(campos[11], game->categories, 50); // processar o décimo segundo campo para categorias
    if (ncampos > 12) separaArray(campos[12], game->genres, 50); // processar o décimo terceiro campo para gêneros
    if (ncampos > 13) separaArray(campos[13], game->tags, 50); // processar o décimo quarto campo para tags
}

int main () { // main do programa
    FILE *arq = fopen("/tmp/games.csv", "r"); // abertura do arquivo para leitura
    Game *games = malloc(1851 * sizeof(Game)); int qtd = 0; // alocacao dinamica do array de jogos

    char linha[2000]; // declaracao da variavel para ler as linhas do arquivo
    fgets(linha, sizeof(linha), arq); // ler a primeira linha (cabeçalho) e ignorar
    while (fgets(linha, sizeof(linha), arq) != NULL) { // ler cada linha do arquivo
        int len = length(linha); // obter o tamanho da linha lida
        if (len > 0 && linha[len - 1] == '\n') linha[len - 1] = '\0'; // remover o caractere de nova linha, se presente
        processar(linha, games + qtd); // processar a linha e armazenar os dados no array de jogos
        qtd++; // incrementar a quantidade de jogos lidos
    }
    fclose(arq); // fechar o arquivo após a leitura

    char entrada[20]; scanf("%s", entrada); // declaracao e leitura da entrada padrao
    while (!comparar(entrada, "FIM")) { // enquanto a entrada for diferente de "FIM"
        int cod = inteiro(entrada); // converter a entrada para inteiro
        for (int i = 0; i < qtd; i++) { // procurar o jogo com o id correspondente
            if (games[i].id == cod) mostrar(games + i); // se encontrado, mostrar os dados do jogo
        }
        scanf("%s", entrada); // ler a próxima entrada
    }

    free(games); // liberar a memoria alocada para o array de jogos
    return 0;
}
