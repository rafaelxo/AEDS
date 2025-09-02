public class exercicio5 {
    public static String trim (String str) {
        String nova = ""; // declaração de uma nova string para armazenar a string sem espaços
        for (int i = 0; i < str.length(); i++) { // loop para percorrer todos os caracteres da string
            if (str.charAt(i) != ' ') nova += str.charAt(i); // se não for espaço concatena o caractere à nova string
        }
        return nova; // retorna a nova string sem espaços
    }

    public static String minusculo (String str) { // método para converter todos os caracteres de uma string para minúsculo
        String nova = ""; // declaração de uma nova string para armazenar a string em minúsculo
        for (int i = 0; i < str.length(); i++) { // loop para percorrer todos os caracteres da string
            if (str.charAt(i) >= 'A' && str.charAt(i) <= 'Z') nova += (char) (str.charAt(i) + 32); // se o caractere for maiúsculo, converte o caractere para minúsculo
            else nova += str.charAt(i); // se não, mantém o caractere
        }
        return nova; // retorna a nova string em minúsculo
    }

    public static String removerSeparador (String str) {
        String nova = ""; // declaração de uma nova string para armazenar a string sem o separador "-"
        for (int i = 0; i < str.length(); i++) { // loop para percorrer todos os caracteres da string
            if (str.charAt(i) != '-') nova += str.charAt(i); // se o caractere não for "-", concatena o caractere à nova string
        }
        return nova; // retorna a nova string sem o separador "-"
    }
    public static String swap (String str, int i, int j) { // método para trocar dois caracteres de posição em um array
        String nova = ""; // declaração de uma nova string para armazenar a string com os caracteres trocados
        for (int k = 0; k < str.length(); k++) { // loop para percorrer todos os caracteres da string
            if (k == i) nova += str.charAt(j); // se o índice for igual a i, concatena o caractere na posição j
            else if (k == j) nova += str.charAt(i); // se o índice for igual a j, concatena o caractere na posição i
            else nova += str.charAt(k); // se não, mantém o caractere
        }
        return nova; // retorna a nova string com os caracteres trocados
    }
    public static String ordenar (String str) { // método para ordenar a string em ordem alfabética para assim facilitar a comparação
        String nova = str; // declaração de uma nova string para armazenar a string ordenada
        for (int i = 0; i < str.length() - 1; i++) { // loop até o penúltimo caractere
            for (int j = 0; j < str.length() - i - 1; j++) { // loop até o penúltimo caractere menos o número de iterações já feitas
                if (str.charAt(j) > str.charAt(j + 1)) nova = swap(str, j, j + 1); // se o caractere na posição j for maior que o próximo, chama o método para trocar os caracteres de posição
            }
        }
        return nova; // retorna a string ordenada
    }
    public static boolean anagrama (String str) { // método para verificar se é anagrama
        str = trim(str); // chama o método para remover espaços em branco
        str = minusculo(str); // chama o método para converter a string para minúsculo
        str = removerSeparador(str); // chama o método para remover separadores
        if (str.length() % 2 != 0) return false; // se o tamanho da string for ímpar, já retorna falso
        int meio = str.length()/2; // variável que encontra o meio da string
        String str1 = ""; String str2 = ""; // declaração de duas novas strings para armazenar as duas metades da string original
        for (int i = 0; i < meio; i++) str1 += str.charAt(i); // loop para percorrer a primeira metade da string original e concatenar os caracteres na primeira nova string
        for (int i = meio; i < str.length(); i++) str2 += str.charAt(i); // loop para percorrer a segunda metade da string original e concatenar os caracteres na segunda nova string
        str1 = ordenar(str1); str2 = ordenar(str2); // chama o método para ordenar as duas novas strings
        for (int i = 0; i < str1.length(); i++) { // loop para percorrer todos os caracteres da string (que devem ser iguais)
            if (str1.charAt(i) != str2.charAt(i)) return false; // se algum caractere for diferente, retorna falso
        }
        return true; // se todos os caracteres forem iguais, retorna verdadeiro
    }
    public static void main (String[] args) { // main do programa
        String str = MyIO.readString(); // declaração e leitura da string
        while (!(str.length() == 3 && str.charAt(0) == 'F' && str.charAt(1) == 'I' && str.charAt(2) == 'M')) { // loop para ler duas strings e verifiar se essas são anagramas enquanto a string seja diferente de "FIM"
            if (anagrama(str)) MyIO.println("SIM"); // chamada do método e validação de se forem anagramas, imprime "SIM"
            else MyIO.println("NAO"); // se não, imprime "NAO"
            str = MyIO.readString(); // leitura da próxima strings
        }
    }
}
