public class exercicio3 {
    public static String inversao (String str) { // método para realizar a inversao de uma string
        String nova = ""; // declaração da string invertida como vazia
        for (int i = str.length() - 1; i >= 0; i--) nova += str.charAt(i); // atribuição de cada caracter individualmente à cada posição da nova string
        return nova; // retorno da nova string invertida
    }
    public static void main (String[] args) { // main do programa
        String str = MyIO.readLine(); // declaração e leitura da string
        while (!str.equals("FIM")) { // loop para ler strings e fazer sua inversão
            System.out.println(inversao(str)); // saída da string invertida ao chamar o método
            str = MyIO.readLine(); // leitura da próxima string
        }
    }
}
