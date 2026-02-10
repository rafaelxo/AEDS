import java.util.*;

public class listelefonica {
    public static Scanner sc = new Scanner(System.in);

    public static void ordenar (String[] telefones) {
        for (int i = 1; i < telefones.length; i++) {
            String aux = telefones[i];
            int j = i - 1;
            while (j >= 0 && telefones[j].compareTo(aux) > 0) {
                telefones[j + 1] = telefones[j];
                j = j - 1;
            }
            telefones[j + 1] = aux;
        }
    }

    public static void main(String[] args) {
        while (sc.hasNext()) {
            int n = sc.nextInt();
            sc.nextLine();
            String[] telefones = new String[n];
            for (int i = 0; i < n; i++) telefones[i] = sc.nextLine();
            int cont = 0;
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < telefones[i].length() && j < telefones[i + 1].length(); j++) {
                    if (telefones[i].charAt(j) == telefones[i + 1].charAt(j)) cont++;
                    else break;
                }
            }
            System.out.println(cont);
        }
    }
}
