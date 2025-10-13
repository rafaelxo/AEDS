import java.util.*;
import java.io.*;

public class exercicio1 {
    public static Scanner sc = new Scanner(System.in); // scanner para leitura de entrada

    public static boolean comparar (String a, String b) { // método para comparar duas strings
        if (a == null || b == null || a.length() != b.length()) return false; // tratamento para strings nulas ou de tamanhos diferentes

        for (int i = 0; i < a.length(); i++) { // loop para comparar caractere por caractere
            if (a.charAt(i) != b.charAt(i)) return false; // se encontrar um caractere diferente, não são iguais
        }

        return true; // se passar por todos os caracteres e não encontrar diferenças, são iguais
    }

    public static class Game { // classe game

        // atributos
        private int id, estimatedOwners, metacriticScore, achievements;
        private String name, releaseDate;
        private float price, userScore;
        private String[] supportedLanguages, publishers, developers, categories, genres, tags;

        // construtor padrão
        public Game() {
            this.id = 0;
            this.name = "";
            this.releaseDate = "";
            this.estimatedOwners = 0;
            this.price = 0;
            this.supportedLanguages = new String[0];
            this.metacriticScore = -1;
            this.userScore = -1.0f;
            this.achievements = 0;
            this.publishers = new String[0];
            this.developers = new String[0];
            this.categories = new String[0];
            this.genres = new String[0];
            this.tags = new String[0];
        }

        // construtor com parâmetros
        public Game(int id, String name, String releaseDate, int estimatedOwners, float price, String[] supportedLanguages, int metacriticScore, float userScore, int achievements, String[] publishers, String[] developers, String[] categories, String[] genres, String[] tags) {
            setId(id);
            setName(name);
            setReleaseDate(releaseDate);
            setEstimatedOwners(estimatedOwners);
            setPrice(price);
            setSupportedLanguages(supportedLanguages);
            setMetacriticScore(metacriticScore);
            setUserScore(userScore);
            setAchievements(achievements);
            setPublishers(publishers);
            setDevelopers(developers);
            setCategories(categories);
            setGenres(genres);
            setTags(tags);
        }

        // getters e setters para cada atributo
        public int getId() { return id; }
        public void setId (int id) { this.id = id; }

        public String getName() { return name; }
        public void setName (String name) { this.name = name; }

        public String getReleaseDate() { return releaseDate; }
        public void setReleaseDate (String releaseDate) { this.releaseDate = releaseDate; }

        public int getEstimatedOwners() { return estimatedOwners; }
        public void setEstimatedOwners (int estimatedOwners) { this.estimatedOwners = estimatedOwners; }

        public float getPrice() { return price; }
        public void setPrice (float price) { this.price = price; }

        public String[] getSupportedLanguages() { return supportedLanguages; }
        public void setSupportedLanguages (String[] supportedLanguages) { this.supportedLanguages = supportedLanguages; }

        public int getMetacriticScore() { return metacriticScore; }
        public void setMetacriticScore (int metacriticScore) {  this.metacriticScore = metacriticScore;  }

        public float getUserScore() { return userScore; }
        public void setUserScore (float userScore) { this.userScore = userScore; }

        public int getAchievements() { return achievements; }
        public void setAchievements (int achievements) { this.achievements = achievements; }

        public String[] getPublishers() { return publishers; }
        public void setPublishers (String[] publishers) { this.publishers = publishers; }

        public String[] getDevelopers() { return developers; }
        public void setDevelopers (String[] developers) { this.developers = developers; }

        public String[] getCategories() { return categories; }
        public void setCategories (String[] categories) { this.categories = categories; }

        public String[] getGenres() { return genres; }
        public void setGenres (String[] genres) { this.genres = genres; }

        public String[] getTags() { return tags; }
        public void setTags(String[] tags) { this.tags = tags; }

        public static String formatarData (String str) { // método para formatar a data
            if (str == null || str.length() == 0) return "01/01/0001"; // retorna data padrão se a string for nula ou muito curta

            String[] meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // array com as abreviações dos meses
            String[] mesesNum = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"}; // array com os números dos meses correspondentes

            String mes = ""; // variável para armazenar o mês
            int i;
            for (i = 0; i < 3 && i < str.length(); i++) mes += str.charAt(i); // extrai os primeiros três caracteres para o mês
            String mesNum = "01"; // variável para armazenar o número do mês, tendo 01 como padrão
            for (int j = 0; j < 12; j++) { // loop para encontrar o número do mês correspondente
                if (comparar(mes, meses[j])) { // se encontrar o mês
                    mesNum = mesesNum[j]; // atribui o número do mês correspondente
                    j = 12; // sai do loop após encontrar o mês
                }
            }

            String dia = ""; // variável para armazenar o dia
            i = 4; // índice para percorrer a string
            while (i < str.length() && str.charAt(i) >= '0' && str.charAt(i) <= '9') { // loop para extrair o dia
                dia += str.charAt(i); // adiciona o caractere ao dia
                i++;
            }
            String diaNum = dia.length() == 1 ? "0" + dia : dia; // formata o dia com dois dígitos, tendo "01" como padrão

            String ano = ""; // variável para armazenar o ano
            i += 2; // pula espaço e vírgula
            while (i < str.length() && str.charAt(i) >= '0' && str.charAt(i) <= '9') { // loop para extrair o ano
                ano += str.charAt(i); // adiciona o caractere ao ano
                i++;
            }
            if (ano.length() != 4) ano = "0001"; // se o ano não tiver 4 dígitos, define como "0001"

            return diaNum + "/" + mesNum + "/" + ano; // retorna a data formatada
        }

        public static String formatarFloat (float n, int casas) { // método para formatar float com 1 ou 2 casas decimais
            if (n == 0.0f || (casas == 1 && n == -1.0f)) return "0.0"; // tratamento especial para 0.0 e -1.0 com 1 casa decimal

            int inteiro = (int) n; // parte inteira do número
            String result = inteiro + "."; // string para armazenar o resultado, começando com a parte inteira e o ponto decimal
            if (casas == 2) { // se for para formatar com 2 casas decimais
                int decimal = (int) ((n - inteiro) * 100 + 0.5f); // parte decimal arredondada
                if (decimal % 10 == 0) result += (decimal / 10); // se o último dígito for 0, adiciona apenas o primeiro dígito
                else if (decimal < 10) result += "0" + decimal; // se for menor que 10, adiciona um 0 antes
                else result += decimal; // caso contrário, adiciona os dois dígitos
            } else { // se for para formatar com 1 casa decimal
                int decimal = (int) ((n - inteiro) * 10 + 0.5f); // parte decimal arredondada
                result += decimal; // adiciona o dígito decimal
            }

            return result; // retorna a string formatada
        }

        public static String juntar (String[] arr) { // método para juntar os elementos
            if (arr == null || arr.length == 0) return "[]"; // se o array for nulo ou vazio, retorna string vazia

            String result = "["; // string para armazenar o resultado
            for (int i = 0; i < arr.length; i++) { // loop para percorrer o array
                result += arr[i]; // adiciona o elemento atual
                if (i < arr.length - 1) result += ", "; // se não for o último elemento, adiciona vírgula e espaço
            }
            result += "]"; // fecha a lista

            return result; // retorna a string resultante
        }

        public String mostrar() { // método para mostrar o game
            String saida = "=> " + getId() + " ## " + getName() + " ## " + formatarData(getReleaseDate()) + " ## " + getEstimatedOwners() + " ## ";
            saida += formatarFloat(getPrice(), 2) + " ## ";
            saida += juntar(getSupportedLanguages()) + " ## ";
            saida += getMetacriticScore() + " ## ";
            saida += formatarFloat(getUserScore(), 1) + " ## ";
            saida += getAchievements() + " ## ";
            saida += juntar(getPublishers()) + " ## ";
            saida += juntar(getDevelopers()) + " ## ";
            saida += juntar(getCategories()) + " ## ";
            saida += juntar(getGenres()) + " ## ";
            saida += juntar(getTags()) + " ##";
            return saida; // retorna a string formatada com todos os atributos
        }
    }

    public static int inteiro (String str) { // método para converter string em inteiro
        if (str == null || str.length() == 0) return 0; // tratamento para string nula ou vazia

        int i = 0, fim = str.length() - 1; // índices para início e fim da string
        while (i <= fim && (str.charAt(i) == ' ' || str.charAt(i) == '\t')) i++; // ignora espaços iniciais
        while (fim >= i && (str.charAt(fim) == ' ' || str.charAt(fim) == '\t')) fim--; // ignora espaços finais

        int num = 0; // variável para o número resultante
        boolean achou = false, negat = false; // flags para marcar se encontrou pelo menos um dígito e se é negativo
        if (i <= fim && str.charAt(i) == '-') { // se o primeiro caractere for '-', marca como negativo
            negat = true; // marca como negativo
            i++;
        }

        for (; i <= fim; i++) { // loop para percorrer os caracteres da string
            char c = str.charAt(i);
            if (c >= '0' && c <= '9') { // se for um dígito
                num = num * 10 + (c - '0'); // constrói o número
                achou = true; // marca que encontrou pelo menos um dígito
            }
        }

        return achou ? (negat ? -num : num) : 0; // retorna o número ou 0 se não encontrou dígitos
    }

    public static float real (String str) { // método para converter string em float
        if (str == null || str.length() == 0) return 0; // tratamento para string nula ou vazia

        int i = 0, fim = str.length() - 1; // índices para início e fim da string
        while (i <= fim && (str.charAt(i) == ' ' || str.charAt(i) == '\t')) i++; // Ignora espaços iniciais
        while (fim >= i && (str.charAt(fim) == ' ' || str.charAt(fim) == '\t')) fim--; // Ignora espaços finais

        float num = 0, div = 1; // variáveis para o número e divisor decimal
        boolean achou = false, negat = false, decimal = false; // flags para controle de parte decimal, se encontrou dígitos e se é negativo
        if (i <= fim && str.charAt(i) == '-') { // se o primeiro caractere for '-', marca como negativo
            negat = true; // marca como negativo
            i++;
        }

        for (; i <= fim; i++) { // loop para percorrer os caracteres da string
            char c = str.charAt(i);
            if (c == '.') decimal = true; // se encontrar um ponto, ativa a flag de parte decimal
            else if (c >= '0' && c <= '9') { // se for um dígito
                achou = true; // marca que encontrou pelo menos um dígito
                if (!decimal) num = num * 10 + (c - '0'); // se não for parte decimal, constrói a parte inteira
                else {
                    div *= 10; // aumenta o divisor decimal
                    num = num + (c - '0') / div; // parte decimal
                }
            }
        }

        return achou ? (negat ? -num : num) : 0; // retorna o número ou 0 se não encontrou dígitos
    }

    public static void trim (String[] array, int n) { // método para remover espaços em branco do início e fim dos elementos de um array
        for (int i = 0; i < n; i++) { // loop para percorrer os primeiros n elementos do array
            if (array[i] == null) array[i] = ""; // tratamento para elementos nulos

            int ini = 0, fim = array[i].length() - 1; // índices para início e fim do elemento
            while (ini <= fim && (array[i].charAt(ini) == ' '|| array[i].charAt(ini) == '\t')) ini++; // move o índice inicial para o primeiro caractere não branco
            while (fim >= ini && (array[i].charAt(fim) == ' '|| array[i].charAt(fim) == '\t')) fim--; // move o índice final para o último caractere não branco

            String novo = ""; // variável para armazenar o novo elemento sem espaços em branco
            for (int j = ini; j <= fim; j++) novo += array[i].charAt(j); // constrói o novo elemento
            array[i] = novo; // atribui o novo elemento ao array
        }
    }

    public static int separaArray (String str, String[] array) { // método para separar os elementos de um array representado como string
        if (str == null || str.length() == 0) return 0; // tratamento para string nula ou vazia

        boolean eArray = str.length() > 0 && str.charAt(0) == '['; // verifica se a string representa um array
        int n = 0; // contador de elementos
        String campo = ""; // variável temporária para armazenar o elemento atual
        boolean aspas = false; // variável para controle de aspas

        for (int i = 0; i < str.length(); i++) { // loop para percorrer os caracteres da string
            char c = str.charAt(i);
            if (eArray && c == '\'') aspas = !aspas; // alterna o estado de aspas
            else if ((c == ',' || c == ';') && !aspas) { // se encontrar uma vírgula ou ponto e vírgula fora de aspas, finaliza o elemento
                if (eArray || (i + 1 >= str.length() || str.charAt(i + 1) != ' ')) { // se for um array ou não houver espaço após a vírgula
                    if (campo.length() > 0) array[n++] = campo; // armazena o elemento no array se não estiver vazio
                    campo = ""; // reseta a variável temporária
                } else campo += c; // adiciona o caractere ao elemento atual
            } else if (c != '[' && c != ']' && c != '"') campo += c; // adiciona o caractere ao elemento atual, ignorando colchetes e aspas
            else if (c == '\'' && !eArray) campo += c; // adiciona aspas simples se não for um array
        }

        if (campo.length() > 0) array[n++] = campo; // armazena o último elemento se não estiver vazio
        trim(array, n); // remove espaços em branco dos elementos do array

        return n; // retorna a quantidade de elementos separados
    }

    public static String limparAspas (String str) { // método para remover aspas iniciais e finais de uma string
        if (str == null || str.length() == 0) return ""; // tratamento para string nula ou vazia

        int ini = 0, fim = str.length() - 1; // índices para início e fim da string
        while (ini <= fim && (str.charAt(ini) == ' ' || str.charAt(ini) == '\t')) ini++; // ignora espaços iniciais
        while (fim >= ini && (str.charAt(fim) == ' ' || str.charAt(fim) == '\t')) fim--; // ignora espaços finais

        if (fim >= ini + 1 && str.charAt(ini) == '"' && str.charAt(fim) == '"') { // verifica se há aspas nas extremidades
            ini++; fim--; // ajusta os índices para ignorar as aspas
        }

        String result = ""; // variável para armazenar a nova string sem aspas
        for (int i = ini; i <= fim; i++) result += str.charAt(i); // constrói a nova string

        return result; // retorna a string sem aspas
    }

    public static int separaCampos (String str, String[] campos) { // método para separar os campos da linha CSV
        if (str == null || str.length() == 0) return 0; // tratamento para string nula ou vazia

        int n = 0; // contador de campos
        String campo = ""; // variável temporária para armazenar o campo atual
        boolean aspas = false; // variável para controle de aspas

        for (int i = 0; i < str.length(); i++) { // loop para percorrer os caracteres da string
            char c = str.charAt(i);
            if (c == '"') aspas = !aspas; // alterna o estado de aspas
            else if (c == ',' && !aspas) { // se encontrar uma vírgula fora de aspas, finaliza o campo
                campos[n++] = limparAspas(campo); // armazena o campo no array, removendo aspas
                campo = ""; // reseta a variável temporária
            } else campo += c; // adiciona o caractere ao campo atual
        }
        campos[n++] = limparAspas(campo); // armazena o último campo

        return n; // retorna a quantidade de campos separados
    }

    public static String[] processarLista (String campo) { // método para processar uma lista de campos
        String[] tmp = new String[100]; // array temporário para armazenar os campos separados
        int qtd = separaArray(campo == null ? "" : campo, tmp); // separa os campos e obtém a quantidade
        String[] result = new String[qtd]; // array final com o tamanho exato
        for (int i = 0; i < qtd; i++) result[i] = tmp[i]; // copia os campos para o array final

        return result; // retorna o array final
    }

    public static void processar (String str, Game game) { // método para processar a linha e preencher o objeto Game
        String[] campos = new String[15]; // array para armazenar os campos separados
        separaCampos(str, campos); // separa os campos da linha

        game.setId(inteiro(campos[0] == null ? "" : campos[0])); // setagem do identificador único
        game.setName(campos[1] == null ? "" : campos[1]); // setagem do nome
        game.setReleaseDate(campos[2] == null ? "" : campos[2]); // setagem da data de lançamento
        game.setEstimatedOwners(inteiro(campos[3] == null ? "" : campos[3])); // setagem da estimativa de compradores

        // setagem do preço
        if (comparar(campos[4] == null ? "" : campos[4], "Free to Play")) game.setPrice(0.0f); // tratamento especial para "Free to Play"
        else game.setPrice(real(campos[4] == null ? "" : campos[4]));

        game.setSupportedLanguages(processarLista(campos[5])); // setagem dos idiomas suportados

        // setagem da nota atribuída pelo Metacritic
        String campoMeta = campos[6] == null ? "" : campos[6];
        if (campoMeta.length() == 0) game.setMetacriticScore(-1); // tratamento para campo vazio
        else game.setMetacriticScore(inteiro(campoMeta));

        // setagem da nota atribuída pelos usuários
        String campoUser = campos[7] == null ? "" : campos[7];
        if (campoUser.length() == 0 || comparar(campoUser, "tbd")) game.setUserScore(-1.0f); // tratamento para "tbd"
        else game.setUserScore(real(campos[7] == null ? "" : campos[7]));

        game.setAchievements(inteiro(campos[8] == null ? "" : campos[8])); // setagem de conquistas disponíveis
        game.setPublishers(processarLista(campos[9])); // setagem dos responsáveis pela publicação
        game.setDevelopers(processarLista(campos[10])); // setagem dos responsáveis pelo desenvolvimento
        game.setCategories(processarLista(campos[11])); // setagem das categorias associadas
        game.setGenres(processarLista(campos[12])); // setagem dos gêneros
        game.setTags(processarLista(campos[13])); // setagem das tags
    }

    public static void main(String[] args) { // main do programa
        File arq = new File("/tmp/games.csv"); // abertura do arquivo
        Game[] games = new Game[1851]; int qtd = 0; // inicialização do array de games e contador

        try {
            Scanner leitor = new Scanner(arq, "UTF-8"); // leitura do arquivo
            leitor.nextLine(); // pula a primeira linha (cabeçalho)
            while (leitor.hasNextLine()) { // loop para ler linhas enquanto existirem
                String linha = leitor.nextLine(); // declaração e leitura da linha
                games[qtd] = new Game(); // cria um novo objeto Game
                processar(linha, games[qtd]); // processa a linha e preenche o objeto Game
                qtd++; // incrementa o contador de games
            }
            leitor.close();
        } catch (FileNotFoundException e) { System.err.println(e.getMessage()); }

        String str = sc.nextLine(); // declaração e leitura dos id's como string
        while (!comparar(str, "FIM")) { // loop para processar até a entrada "FIM"
            int cod = inteiro(str); // converte a string para inteiro
            for (int i = 0; i < qtd; i++) { // loop para buscar o game com o id correspondente
                if (games[i].getId() == cod) System.out.println(games[i].mostrar()); // se encontrar, imprime os detalhes do game
            }
            str = sc.nextLine(); // lê a próxima entrada
        }
    }
}
