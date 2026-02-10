public class quicksort {
    public static void swap (int array[], int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void quick (int array[], int esq, int dir) {
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
        if (esq < j) quick(array, esq, j);
        if (i < dir) quick(array, i, dir);
    }
}
