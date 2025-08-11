import java.util.Scanner;

public class exercicio1 {
    public class Tipo {
        private int codigo;
        private double percentual;
    public Tipo() { setCodigo(1); }
        public void setCodigo(int num) {
            try {
                if (num == 1) { codigo = 1; percentual = 10; }
                else if (num == 2) { codigo = 2; percentual = 20; }
                else throw new IllegalArgumentException("Código inválido!");
            } catch (Exception e) { System.err.println(e.getMessage()); }
        }
        public int getCodigo() { return codigo; }
        public String formataCod() {
            if (codigo == 1) return "Alimentação";
            else if (codigo == 2) return "Transporte";
            else return "Desconhecido";
        }
        public double getPercentual() { return percentual; }
        public void preenche(Scanner sc) {
            int n;
            System.out.print("Tipo do produto: ");
            n = sc.nextInt(); setCodigo(n);
            System.out.println();
        }
        public void exibe() {
            System.out.println("Tipo do produto: " + formataCod());
            System.out.println("Percentual de imposto: " + getPercentual() + "%");
        }
    }
    public class Produto {
        private String descricao;
        private Tipo tipo = new Tipo();
        private double preco, imposto;
        public Produto() {
            setDescricao("nenhum");
            tipo.setCodigo(1);
            setPreco(1);
            setImposto();
        }
        public Produto(String d, int n, double p) {
            setDescricao(d);
            tipo.setCodigo(n);
            setPreco(p);
            setImposto();
        }
        public void setDescricao(String d) {
            try {
                if (d.length() > 0) descricao = d;
                else throw new IllegalArgumentException("Descrição inválida!");
            } catch (Exception e) { System.err.println(e.getMessage()); }
        }
        public String getDescricao() { return descricao; }
        public void setPreco(double p) {
            try {
                if (p > 0) preco = p;
                else throw new IllegalArgumentException("Preço inválido!");
            } catch (Exception e) { System.err.println(e.getMessage()); }
        }
        public double getPreco() { return preco; }
        public double getImposto() { return imposto; }
        public double getFinal() { return getPreco() + getImposto(); }
        public void preenche(Scanner sc) {
            String txt;
            double val;
            System.out.print("Descrição do produto: ");
            txt = sc.nextLine(); setDescricao(txt);
            System.out.print("Preço do produto: ");
            val = sc.nextDouble(); setPreco(val); setImposto();
            tipo.preenche(sc);
        }
        public void exibe() {
            System.out.println("Descrição: " + getDescricao());
            System.out.println("Preço: " + getPreco() + " reais");
            System.out.println("Imposto: " + getImposto() + " reais");
            tipo.exibe();
        }
        private void setImposto() { imposto = getPreco() * tipo.getPercentual() / 100; }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Produto p = new Produto();
        p.preenche(sc); p.exibe();
        System.out.println("Preço final do produto: " + p.getFinal() + " reais");
    }
}
