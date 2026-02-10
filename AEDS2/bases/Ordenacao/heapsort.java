public class heapsort {
    public static void swap (int array[], int i, int j) {
        int aux = array[i];
        array[i] = array[j];
        array[j] = aux;
    }

    public static void construir (int array[], int tam) {
        int i = tam - 1;
        while (i > 0 && array[i] > array[(i - 1) / 2]) {
            swap(array, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    public static void reconstruir (int array[], int tam) {
        int i = 0;
        while (2 * i + 1 < tam) {
            int filho = 2 * i + 1;
            if (filho + 1 < tam && array[filho] < array[filho + 1]) filho++;
            if (array[i] < array[filho]) {
                swap(array, i, filho);
                i = filho;
            } else i = tam;
        }
    }

    public static void heap (int[] array, int n) {
        for (int tam = 2; tam <= n; tam++) construir(array, tam);
        int tam = n;
        while (tam > 1) {
            swap(array, 0, tam - 1);
            tam--;
            reconstruir(array, tam);
        }
    }
}
