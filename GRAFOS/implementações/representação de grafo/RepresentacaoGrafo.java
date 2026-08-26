import java.util.*;
import java.io.*;

public class RepresentacaoGrafo {
    public static Scanner sc = new Scanner(System.in);

    @SuppressWarnings("unchecked")
    public static void main(String[] args) {
        System.out.print("Insira o nome do arquivo: ");
        String nomeArquivo = sc.nextLine();
        System.out.print("Insira o número do vértice alvo: ");
        int verticeAlvo = sc.nextInt();

        List<Integer>[] arestasSaida = null;
        List<Integer>[] arestasEntrada = null;
        int numVertices = 0;
        int numArestas = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha = br.readLine();
            if (linha == null) {
                System.out.println("Arquivo vazio.");
                return;
            }

            StringTokenizer st = new StringTokenizer(linha);
            numVertices = Integer.parseInt(st.nextToken());
            numArestas = Integer.parseInt(st.nextToken());

            arestasSaida = new ArrayList[numVertices + 1];
            arestasEntrada = new ArrayList[numVertices + 1];

            for (int i = 1; i <= numVertices; i++) {
                arestasSaida[i] = new ArrayList<>();
                arestasEntrada[i] = new ArrayList<>();
            }

            for (int i = 0; i < numArestas; i++) {
                linha = br.readLine();
                if (linha == null)
                    break;

                st = new StringTokenizer(linha);
                int origem = Integer.parseInt(st.nextToken());
                int destino = Integer.parseInt(st.nextToken());

                arestasSaida[origem].add(destino);
                arestasEntrada[destino].add(origem);
            }

            System.out.println("Leitura concluída com sucesso!\n");

        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
            return;
        }

        // 3. Processar e imprimir as informações do vértice alvo
        if (verticeAlvo < 1 || verticeAlvo > numVertices) {
            System.out.println("Erro: O vértice informado (" + verticeAlvo
                    + ") não existe no grafo. Os vértices vão de 1 a " + numVertices + ".");
            return;
        }

        List<Integer> sucessores = arestasSaida[verticeAlvo];
        List<Integer> predecessores = arestasEntrada[verticeAlvo];

        Collections.sort(sucessores);
        Collections.sort(predecessores);

        int grauSaida = sucessores.size();
        int grauEntrada = predecessores.size();

        System.out.println("--- Informações do Vértice " + verticeAlvo + " ---");
        System.out.println("Grau de saída: " + grauSaida);
        System.out.println("Grau de entrada: " + grauEntrada);
        System.out.println("Conjunto de sucessores: " + (grauSaida == 0 ? "Nenhum" : sucessores));
        System.out.println("Conjunto de predecessores: " + (grauEntrada == 0 ? "Nenhum" : predecessores));
    }
}
