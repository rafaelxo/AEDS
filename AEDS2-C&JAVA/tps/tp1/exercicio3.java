import java.util.Scanner;

public class exercicio3 {
    public static String ciframento (String str) { // método para o Ciframento de César
        String cod = ""; // declaração da string que armazenará o ciframento
        for (int i = 0; i < str.length(); i++) cod += (char)(str.charAt(i) + 3); // loop para percorrer cada caractere da string, realizando o ciframento ao somar 3 ao respectivo valor ASCII e concatenando ao resultado
        return cod; // retorno do método com a string cifrada
    }
    public static void main (String[] args) { // main do programa
        Scanner sc = new Scanner (System.in);
        String str = sc.nextLine(); // declaração e leitura da string
        while (!str.equals("FIM")) { // loop para ler strings e verifiar se essa é um palíndromo enquanto a string seja diferente de "FIM"
            System.out.println(ciframento(str)); // imprime o resultado do ciframento ao chamar o método
            str = sc.nextLine(); // leitura da próxima string
        }
        sc.close();
    }
}
