public class exercicio5 {
    public static boolean anagrama ()
    public static void main (String[] args) {
        String str = MyIO.readLine(); // declaração e leitura da string
        while (!str.equals("FIM")) { // loop para ler strings e verifiar se essa é um palíndromo enquanto a string
                                     // seja diferente de "FIM"
            if (anagrama(str)) MyIO.println("SIM"); // se for palíndromo, imprime "SIM"
            else MyIO.println("NAO"); // se não, imprime "NAO"
            str = MyIO.readLine(); // leitura da próxima string
        }
    }
}
