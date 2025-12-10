import java.util.*;

public class pesqbin {
    public static void swap (int array[], int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void ordenar (int array[], int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[esq + (dir - esq) / 2];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++; j--;
            }
        }
        if (esq < j) ordenar(array, esq, j);
        if (i < dir) ordenar(array, i, dir);
    }

    public static void pesquisa (int x, int array[]) {
        if (array.length == 0) {
            System.out.println("Elemento " + x + " não encontrado!");
            return;
        }
        int esq = 0, dir = array.length - 1;
        while (esq <= dir) {
            int meio = esq + (dir - esq) / 2;
            if (array[meio] == x) {
                System.out.println("Elemento " + x + " encontrado na posição " + meio + "!");
                return;
            } else if (x < array[meio]) dir = meio - 1;
            else esq = meio + 1;
        }
        System.out.println("Elemento " + x + " não encontrado!");
    }

    public static void main (String []args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int array[] = new int[n];
        for (int i = 0; i < n; i++) array[i] = sc.nextInt();
        if (n > 1) ordenar(array, 0, n - 1);
        int x = sc.nextInt();
        pesquisa(x, array);
        sc.close();
    }
}
