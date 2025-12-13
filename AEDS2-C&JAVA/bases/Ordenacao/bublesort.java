public class bublesort {
    public static void swap (int array[], int i, int j) {
        int aux = array[i];
        array[i] = array[j];
        array[j] = aux;
    }

    public static void buble (int array[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j] > array[j + 1]) swap(array, j, j + 1);
            }
        }
    }
}
