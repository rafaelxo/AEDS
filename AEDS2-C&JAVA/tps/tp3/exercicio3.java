import java.util.*;

public class exercicio3 {
    public static Scanner sc = new Scanner (System.in);
    public static int somaDigitos(String str, int i) { // método recursivo para somar cada caracter do número inteiro
        if (i >= str.length()) return 0; // condição de parada como '\0' qando a string acabar, retornando 0
        else return (str.charAt(i) - '0') + somaDigitos(str, i + 1); // soma o caracter convertido para inteiro e chama o método // recursivo com o índice incrementado
    }

    public static void main (String[] args) {
        String num = sc.nextLine(); // declaração e leitura do número como string
        while (!(num.length() == 3 && num.charAt(0) == 'F' && num.charAt(1) == 'I' && num.charAt(2) == 'M')) { // loop para ler números como string enquanto a string seja diferente de "FIM"
            System.out.println(somaDigitos(num, 0)); // saída do resultado da soma dos caracteres
            num = sc.nextLine(); // leitura do próximo número como string
        }
    }
}
