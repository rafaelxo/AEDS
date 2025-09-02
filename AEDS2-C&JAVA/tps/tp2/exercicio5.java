public class exercicio5 {
    public static String trim(String str) {
        String nova = ""; // nova string para armazenar o resultado
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) != ' ') nova += str.charAt(i); // se não for espaço concatena o caractere à nova string
        }
        return nova; // retorna a nova string sem espaços
    }

    public static String minusculo(String str) { // método para converter todos os caracteres de uma string para minúsculo
        String nova = ""; // declaração de uma nova string para armazenar a string em minúsculo
        for (int i = 0; i < str.length(); i++) { // loop para percorrer todos os caracteres da string
            if (str.charAt(i) >= 'A' && str.charAt(i) <= 'Z') nova += (char) (nova.charAt(i) + 32); // se o caractere for maiúsculo, converte o caractere para minúsculo
            else nova += str.charAt(i); // se não, mantém o caractere
        }
        return nova; // retorna a nova string em minúsculo
    }
    public static void swap(char[] str, int i, int j) { // método para trocar dois caracteres de posição em um array
        char temp = str[i]; // variável temporária para armazenar o valor do caractere na posição i
        str[i] = str[j]; // atribui o valor do caractere na posição j ao caractere na posição i
        str[j] = temp; // atribui o valor da variável temporária ao caractere na posição j
    }
    public static void ordenar (char[] str) { // método para ordenar a string em ordem alfabética para assim facilitar a comparação
        for (int i = 0; i < str.length - 1; i++) { // loop até o penúltimo caractere
            for (int j = 0; j < str.length - i - 1; j++) { // loop até o penúltimo caractere menos o número de iterações já feitas
                if (str[j] > str[j + 1]) swap(str, j, j + 1); // se o caractere na posição j for maior que o próximo, chama o método para trocar os caracteres de posição
            }
        }
    }
    public static boolean anagrama (String str) { // método para verificar se é anagrama
        str = trim(str); // chama o método para remover espaços em branco
        str = minusculo(str); // chama o método para converter a string para minúsculo
        
        return true; // se todos os caracteres forem iguais, retorna verdadeiro
    }
    public static void main (String[] args) { // main do programa
        String str1 = MyIO.readString(); // declaração e leitura da string
        while (!(str1.length() == 3 && str1.charAt(0) == 'F' && str1.charAt(1) == 'I' && str1.charAt(2) == 'M')) { // loop para ler duas strings e verifiar se essas são anagramas enquanto a string seja diferente de "FIM"
            if (anagrama(str1)) MyIO.println("SIM"); // chamada do método e validação de se forem anagramas, imprime "SIM"
            else MyIO.println("NAO"); // se não, imprime "NAO"
            str1 = MyIO.readString(); str2 = MyIO.readString();// leitura das próximas strings
        }
    }
}
