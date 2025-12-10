import java.util.*;

public class hashlista {
    public static Scanner sc = new Scanner (System.in);

    static class Carro {
        public String placa, modelo, tipo, chassi;
        void ler (String linha) {
            String[] partes = linha.split(",");
            placa = partes[0];
            modelo = partes[1];
            tipo = partes[2];
            chassi = partes[3];
        }
        void imprimir () {
            System.out.println("[" + placa + "] [" + modelo + "] [" + tipo + "] [" + chassi + "]");
        }
    }

    static class Celula {
        public Carro elemento;
        public Celula prox;
        public Celula (Carro x) {
            elemento = x;
            prox = null;
        }
    }

    static class Lista {
        private Celula primeiro;
        private Celula ultimo;
        public Lista () {
            primeiro = new Celula (new Carro());
            ultimo = primeiro;
        }
        public void inserir (Carro x) {
            ultimo.prox = new Celula (x);
            ultimo = ultimo.prox;
        }
    }

    static class Tabela {
        private Lista[] tabela;
        private int tamanho;
        public Tabela (int n) {
            tabela = new Lista[n];
            for (int i = 0; i < n; i++) tabela[i] = new Lista();
            tamanho = n;
        }
        public int hash (String str) {
            int total = 0;
            for (int i = 0; i < str.length(); i++) total += (int)str.charAt(i);
            return total % tamanho;
        }
        public void inserir (Carro x) {
            int pos = hash(x.placa);
            tabela[pos].inserir(x);
        }
        public Carro pesquisar (String placa) {
            int pos = hash(placa);
            Celula i = tabela[pos].primeiro.prox;
            while (i != null) {
                if (i.elemento.placa.equals(placa)) return i.elemento;
                i = i.prox;
            }
            return null;
        }
    }

    public static void main (String[] args) {
        int n = sc.nextInt();
        sc.nextLine();
        Tabela carros = new Tabela(n);
        String dados = sc.nextLine();
        while (!dados.equals("FIM")) {
            Carro c = new Carro();
            c.ler(dados);
            carros.inserir(c);
            dados = sc.nextLine();
        }
        String consulta = sc.nextLine();
        while (!consulta.equals("FIM_CONSULTA")) {
            Carro encontrado = carros.pesquisar(consulta);
            if (encontrado != null) encontrado.imprimir();
            else System.out.println("VEICULO NAO CADASTRADO");
            consulta = sc.nextLine();
        }
    }
}
