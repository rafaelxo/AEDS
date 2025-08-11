import java.util.Scanner;

public class exercicio5 {
    public abstract class Produto {
        private int codigo;
        private String descricao, validade;
        private double p_compra;
        public Produto() {
            setCodigo(0);
            setDescricao("nenuma");
            setPCompra(0);
            setValidade("00/00/0000");
        }
        public Produto(int c, String d, double pc, String v) {
            setCodigo(c);
            setDescricao(d);
            setPCompra(pc);
            setValidade(v);
        }
        public void setCodigo(int c) {
            try {
                if (c > 0) codigo = c;
                else throw new IllegalArgumentException("Código inválido!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public int getCodigo() { return codigo; }
        public void setDescricao(String d) {
            try {
                if (d.length() > 2) descricao = d;
                else throw new IllegalArgumentException("Descrição inválida!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public String getDescricao() { return descricao; }
        public void setPCompra(double pc) {
            try {
                if (pc > 0) p_compra = pc;
                else throw new IllegalArgumentException("Preço inválido!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public double getPCompra() { return p_compra; }
        public void setValidade(String v) {
            try {
                if (v.length() == 10) validade = v;
                else throw new IllegalArgumentException("Validade inválida!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public String getValidade() { return validade; }
        public abstract double gerarPrecoVenda();
        public void exibe() {
            System.out.println("Código: " + getCodigo());
            System.out.println("Descrição: " + getDescricao());
            System.out.println("Preço de compra: " + getPCompra());
            System.out.println("Preço de venda: " + gerarPrecoVenda());
            System.out.println("Data de validade: " + getValidade());
        }
    }
    public class Medicamento extends Produto {
        public Medicamento() { super(); }
        public Medicamento(int c, String d, double pc, String v) { super(c, d, pc, v); }
        public double gerarPrecoVenda() { return getPCompra() + getPCompra() * 0.4; }
    }
    public class Higiene extends Produto {
        public Higiene() { super(); }
        public Higiene(int c, String d, double pc, String v) { super(c, d, pc, v); }
        public double gerarPrecoVenda() { return getPCompra() + getPCompra() * 0.3; }
    }
}

class Sistema {
    public static void cadastrar(exercicio5.Produto[] p, int n, Scanner sc) {
        for (int i = 0; i < n; i++) {
            boolean valido = false;
            while (!valido) {
                System.out.println("Insira o tipo do produto que deseja cadastrar (1 - Medicamento | 2 - Higiene): ");
                int tipo = sc.nextInt();
                System.out.println("Insira o código do medicamento: ");
                int cod = sc.nextInt();
                System.out.println("Insira a descrição do medicamento: ");
                String desc = sc.next();
                System.out.println("Insira o preço de compra do medicamento: ");
                double p_compra = sc.nextDouble();
                System.out.println("Insira a data de validade do medicamento: ");
                String data = sc.next();
                if (tipo == 1) {
                    p[i] = new exercicio5().new Medicamento(cod, desc, p_compra, data);
                    valido = true;
                } else if (tipo == 2) {
                    p[i] = new exercicio5().new Higiene(cod, desc, p_compra, data);
                    valido = true;
                } else System.out.println("Tipo inválido!");
            }
        }
    }
    public static void exibir(exercicio5.Produto[] p, int n) {
        for (int i = 0; i < n; i++) {
            System.out.println("Produto " + (i + 1) + ":");
            p[i].exibe();
        }
    }
    public static void caro(exercicio5.Produto[] p, int n) {
        double mais = p[0].gerarPrecoVenda();
        int ind = 0;
        for (int i = 1; i < n; i++) {
            if (p[i].gerarPrecoVenda() > mais) {
                mais = p[i].gerarPrecoVenda();
                ind = i;
            }
        }
        System.out.println("Produto mais caro:");
        p[ind].exibe();
    }
    public static void alterar(exercicio5.Produto[] p, int n, Scanner sc) {
        System.out.println("Insira o código do produto que deseja alterar: ");
        int alt = sc.nextInt();
        boolean encontrado = false;
        for (int i = 0; i < n; i++) {
            if (p[i].getCodigo() == alt) {
                System.out.println("Insira o novo código: ");
                int cod = sc.nextInt();
                p[i].setCodigo(cod);
                System.out.println("Insira a nova descrição: ");
                String desc = sc.next();
                p[i].setDescricao(desc);
                System.out.println("Insira o novo preço de compra: ");
                double pc = sc.nextDouble();
                p[i].setPCompra(pc);
                System.out.println("Insira a nova data de validade: ");
                String data = sc.next();
                p[i].setValidade(data);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) System.out.println("Produto com código " + alt + " não encontrado!");
    }
}

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        exercicio5.Produto prod[] = new exercicio5.Produto[n];
        int op;
        do {
            System.out.println("Insira a opção desejada: ");
            System.out.println("1 - Cadastrar produtos");
            System.out.println("2 - Exibir produtos");
            System.out.println("3 - Exibir produto mais caro");
            System.out.println("4 - Alterar produto");
            System.out.println("5 - Sair");
            op = sc.nextInt();
            switch (op) {
                case 1: Sistema.cadastrar(prod, n, sc); break;
                case 2: Sistema.exibir(prod, n); break;
                case 3: Sistema.caro(prod, n); break;
                case 4: Sistema.alterar(prod, n, sc); break;
                case 5: System.out.println("Finalizando..."); break;
                default: System.out.println("Opção inválida!");
            }
        } while (op != 5);
    }
}
