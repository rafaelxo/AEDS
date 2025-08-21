public class exercicio5 {
    public static boolean anagrama (String str1, String str2) {
        
    }
    public static void main (String[] args) {
        String str1 = MyIO.readLine(); String str2 = MyIO.readLine();// declaração e leitura da string
        while (!str1.equals("FIM")) { // loop para ler duas strings e verifiar se essas são anagramas enquanto a string seja diferente de "FIM"
            if (anagrama(str1, str2)) MyIO.println("SIM"); // se forem anagramas, imprime "SIM"
            else MyIO.println("NAO"); // se não, imprime "NAO"
            str1 = MyIO.readLine(); str2 = MyIO.readLine();// leitura das próximas strings
        }
    }
}
