public class exercicio3 {
    public static String inversao (String str) {
        String nova = "";
        for (int i = str.length() - 1; i >= 0; i--) nova += str.charAt(i);
        return nova;
    }
    public static void main (String[] args) {
        String str = MyIO.readLine();
        while (!str.equals("FIM")) {
            System.out.println(inversao(str));
            str = MyIO.readLine();
        }
    }
}
