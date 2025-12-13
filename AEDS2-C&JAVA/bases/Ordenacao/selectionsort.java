public class selectionsort {
    public static void swap (int array[], int i, int j) {
        int aux = array[i];
        array[i] = array[j];
        array[j] = aux;
    }

    public static void selection (int array[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int menor = i;
            for (int j = i + 1; j < n; j++) {
                if (array[j] < array[menor]) menor = j;
            }
            swap(array, i, menor);
        }
    }
}
