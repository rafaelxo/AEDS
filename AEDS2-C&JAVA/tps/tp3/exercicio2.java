public class exercicio2 {
    public static String inversao (String str, int i) { // método para realizar a inversao de uma string
        if (i < 0) return ""; // condição de parada da recursão
        else return "" + str.charAt(i) + inversao(str, i - 1); // chamada recursiva para o próximo caractere
    }

    public static void main (String[] args) { // main do programa
        String str = MyIO.readLine(); // declaração e leitura da string
        while (!(str.length() == 3 && str.charAt(0) == 'F' && str.charAt(1) == 'I' && str.charAt(2) == 'M')) { // loop para ler strings e fazer sua inversão
            MyIO.println(inversao(str, str.length() - 1)); // saída da string invertida ao chamar o método
            str = MyIO.readLine(); // leitura da próxima string
        }
    }
}
