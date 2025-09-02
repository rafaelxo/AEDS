public class exercicio5 {
    public static void ordenar (char[] str) { // método para ordenar a string em ordem alfabética para assim facilitar a comparação
        for (int i = 0; i < str.length - 1; i++) { // loop até o penúltimo caractere
            for (int j = 0; j < str.length - i - 1; j++) { // loop até o penúltimo caractere menos o número de iterações já feitas
                if (str[j] > str[j + 1]) { // se o caractere atual for maior que o próximo, troca os dois
                    char temp = str[j]; // variável temporária para armazenar o valor do caractere atual
                    str[j] = str[j + 1]; // atribui o valor do próximo caractere ao atual
                    str[j + 1] = temp; // atribui o valor da variável temporária ao próximo caractere
                }
            }
        }
    }
    public static boolean anagrama (String str1, String str2) { // método para verificar se duas strings são anagramas
        if (str1.length() != str2.length()) return false; // se o tamanho das strings for diferente, retorna falso
        char[] aux1 = new char[str1.length()]; char[] aux2 = new char[str2.length()]; // declara dois arrays de caracteres para armazenar as strings
        for (int i = 0; i < str1.length(); i++) { // loop para copiar os caracteres das strings para os arrays
            aux1[i] = str1.charAt(i); // copia o caractere da string 1 para o array 1
            aux2[i] = str2.charAt(i); // copia o caractere da string 2 para o array 2
        }
        ordenar(aux1); ordenar(aux2); // chama o método para ordenar os arrays
        for (int i = 0; i < aux1.length; i++) { // loop para comparar os arrays ordenados até o tamanho do array 1
            if (aux1[i] != aux2[i]) return false; // se algum caractere for diferente, retorna falso
        }
        return true; // se todos os caracteres forem iguais, retorna verdadeiro
    }
    public static void main (String[] args) { // main do programa
        String str1 = MyIO.readLine(); String str2 = MyIO.readLine();// declaração e leitura da string
        while (!(str1.length() == 3 && str1.charAt(0) == 'F' && str1.charAt(1) == 'I' && str1.charAt(2) == 'M')) { // loop para ler duas strings e verifiar se essas são anagramas enquanto a string seja diferente de "FIM"
            if (anagrama(str1, str2)) MyIO.println("SIM"); // chamada do método e validação de se forem anagramas, imprime "SIM"
            else MyIO.println("NAO"); // se não, imprime "NAO"
            str1 = MyIO.readLine(); str2 = MyIO.readLine();// leitura das próximas strings
        }
    }
}
