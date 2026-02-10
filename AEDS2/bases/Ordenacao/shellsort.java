public class shellsort {
    public static void insercao (int array[], int n, int gap, int alt) {
        for (int i = (alt + gap); i < n; i += alt) {
            int aux = array[i];
            int j = i - alt;
            while (j >= 0 && array[j] > aux) {
                array[j + alt] = array[j];
                j -= alt;
            }
            array[j + alt] = aux;
        }
    }
    
    public static void shell (int array[], int n) {
        int alt = 1;
        do {
            alt = (alt * 3) + 1;
        } while (alt < n);

        do {
            alt /= 3;
            for (int gap = 0; gap < alt; gap++) insercao(array, n, gap, alt);
        } while (alt > 1);
    }

}
