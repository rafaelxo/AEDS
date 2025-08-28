public class exercicio5 {
    public static void ordenar (char[] str) {
        for (int i = 0; i < str.length - 1; i++) {
            for (int j = 0; j < str.length - i - 1; j++) {
                if (str[j] > str[j + 1]) {
                    char temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                }
            }
        }
    }
    public static boolean anagrama (String str1, String str2) {
        if (str1.length() != str2.length()) return false;
        char[] aux1 = new char[str1.length()]; char[] aux2 = new char[str2.length()];
        for (int i = 0; i < str1.length(); i++) {
            aux1[i] = str1.charAt(i);
            aux2[i] = str2.charAt(i);
        }
        ordenar(aux1); ordenar(aux2);
        for (int i = 0; i < aux1.length; i++) {
            if (aux1[i] != aux2[i]) return false;
        }
        return true;
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
