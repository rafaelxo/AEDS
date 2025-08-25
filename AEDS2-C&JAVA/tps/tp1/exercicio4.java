import java.util.Random;

public class exercicio4 {
    public static String alteracao (String str) { // método para realizar a alteração de caracteres
        Random rand = new Random(); rand.setSeed(4); // predefine 4 como a seed do gerador para padronizar o resultado
        char c1 = (char)(rand.nextInt(26) + 'a'); char c2 = (char)(rand.nextInt(26) + 'a'); // gera dois caracteres aleatórios entre 'a' e 'z'
        String nova = ""; // declaração da string que armazenará a nova string com os caracteres alterados
        for (int i = 0; i < str.length(); i++) { // loop para percorrer cada caractere da string
            if (str.charAt(i) == c1) nova += c2; // se o caractere for igual ao primeiro gerado, substitui por c2
            else nova += str.charAt(i); // se não, mantém o caractere original
        }
        return nova; // retorno do método com a string alterada
    }
    public static void main (String[] args) { // main do programa
        String str = MyIO.readLine(); // declaração e leitura da string
        while (!str.equals("FIM")) { // loop para ler strings e realizar a alteração enquanto a string seja diferente de "FIM"
            System.out.println(alteracao(str)); // imprime o resultado da alteração ao chamar o método
            str = MyIO.readLine(); // leitura da próxima string
        }
    }
}
