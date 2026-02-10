import java.util.*;

public class quicksort {
    public static Random ger = new Random();

    public static long tempo () {
        return new Date().getTime();
    }

    public static void gerarArray(int[] arr, int limite) {
        for (int i = 0; i < arr.length; i++) arr[i] = ger.nextInt(limite + 1);
    }

    public static void swap (int[] array, int i, int j) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    public static void QuickSortFirstPivot (int[] array, int left, int right) {
        int i = left, j = right;
        int pivo = array[left];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++; j--;
            }
        }
        if (left < j) QuickSortFirstPivot(array, left, j);
        if (i < right) QuickSortFirstPivot(array, i, right);
    }

    public static void QuickSortLastPivot (int[] array, int left, int right) {
        int i = left, j = right;
        int pivo = array[right];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++; j--;
            }
        }
        if (left < j) QuickSortLastPivot(array, left, j);
        if (i < right) QuickSortLastPivot(array, i, right);
    }

    public static void QuickSortRandomPivot (int[] array, int left, int right) {
        int i = left, j = right;
        int p = left + ger.nextInt(right - left + 1);
        int pivo = array[p];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++; j--;
            }
        }
        if (left < j) QuickSortRandomPivot(array, left, j);
        if (i < right) QuickSortRandomPivot(array, i, right);
    }

    public static int MedianOfThree (int[] array, int left, int right) {
        int meio = (left + right) / 2;
        if (array[left] > array[meio]) swap(array, left, meio);
        if (array[left] > array[right]) swap(array, left, right);
        if (array[meio] > array[right]) swap(array, meio, right);
        return array[meio];
    }

    public static void QuickSortMedianOfThree (int[] array, int left, int right) {
        int i = left, j = right;
        int pivo = MedianOfThree(array, left, right);
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++; j--;
            }
        }
        if (left < j) QuickSortMedianOfThree(array, left, j);
        if (i < right) QuickSortMedianOfThree(array, i, right);
    }

    public static void main (String[] args) {
        int[] array = new int[1000];

        double inicio, fim;

        System.out.println("QUICKSORT COM PIVO NO PRIMEIRO ELEMENTO:");
        //System.out.println("QUICKSORT COM PIVO NO ULTIMO ELEMENTO:");
        //System.out.println("QUICKSORT COM PIVO ALEATORIO:");
        //System.out.println("QUICKSORT COM PIVO DE MEDIANA DE TRES:");
        System.out.println();

        gerarArray(array, 1000);
        System.out.println("Array com 1000 inteiros desordenado:");
        System.out.println("[ X X X X ]");
        System.out.println();
        inicio = tempo();

        QuickSortFirstPivot(array, 0, array.length - 1);
        //QuickSortLastPivot(array, 0, array.length - 1);
        //QuickSortRandomPivot(array, 0, array.length - 1);
        //QuickSortMedianOfThree(array, 0, array.length - 1);

        fim = tempo();

        System.out.println("Array com 1000 inteiros ordenado:");
        System.out.println("[ A A A A ]");
        System.out.println();
        System.out.println("Tempo para ordenar: " + (fim - inicio) + " ms");
    }
}
