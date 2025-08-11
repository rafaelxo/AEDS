import java.util.Scanner;

public class exercicio3 {
    public static class Cargo {
        private int codigo;
        private double v_hora;
        public Cargo() { codigo = 1; v_hora = 10; }
        public Cargo(int i, double f) { codigo = i; v_hora = f; }
        public int getCodigo() { return codigo; }
        public double getVHora() { return v_hora; }
    }

    public static class Funcionario {
        private String nome;
        private int cargo, horas_t;
        private char sexo;
        public Funcionario() {
            setNome("nenhum");
            setCargo(1);
            setSexo('M');
            setHorasT(10);
        }
        public Funcionario(String n, int c, char s, int h) {
            setNome(n);
            setCargo(c);
            setSexo(s);
            setHorasT(h);
        }
        public void setNome(String n) {
            try {
                if (n.length() > 2) nome = n;
                else throw new IllegalArgumentException("Nome inválido!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public String getNome() { return nome; }

        public void setCargo(int c) {
            try {
                if (c > 0) cargo = c;
                else throw new IllegalArgumentException("Cargo inválido!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public int getCargo() { return cargo; }
        public void setSexo(char s) {
            s = Character.toUpperCase(s);
            try {
                if (s == 'M' || s == 'F') sexo = s;
                else throw new IllegalArgumentException("Sexo inválido!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public char getSexo() { return sexo; }
        public void setHorasT(int h) {
            try {
                if (h > 0) horas_t = h;
                else throw new IllegalArgumentException("Horas inválidas!");
            } catch (Exception e) { System.out.println(e.getMessage()); }
        }
        public int getHorasT() { return horas_t; }
        public double calcular(Cargo[] c, char s) {
            double salario = horas_t * c[cargo - 1].getVHora();
            if (s == 'F') salario *= 1.2;
            return salario;
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Cargo[] c = new Cargo[3];
        c[0] = new Cargo(1, 10);
        c[1] = new Cargo(2, 20);
        c[2] = new Cargo(3, 30);
        Funcionario f = new Funcionario();
        int cod, horas;
        char sexo;
        String nome;
        System.out.print("Insira o nome do funcionário: ");
        nome = sc.nextLine(); f.setNome(nome);
        System.out.print("Insira o código do funcionário: ");
        cod = sc.nextInt(); f.setCargo(cod);
        System.out.print("Insira o sexo do funcionário (M ou F): ");
        sexo = sc.next().charAt(0); f.setSexo(sexo);
        System.out.print("Insira o número de horas trabalhadas pelo funcionário: ");
        horas = sc.nextInt(); f.setHorasT(horas);
        System.out.print("Salário do funcionário: " + f.calcular(c, sexo) + " reais!");
        System.out.println();
        sc.close();
    }
}
