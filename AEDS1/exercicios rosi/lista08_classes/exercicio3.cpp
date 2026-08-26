#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Carro {
    private:
        int quantidade, distancia;
    public:
        Carro () { 
            setQuantidade(1);
            setDistancia(1);
         }
        Carro (int quant, int dist) { 
            setQuantidade(quant);
            setDistancia(dist);
        }
        void exibe () {
            cout << "Distância percorrida: " << getDistancia() << endl;
            cout << "Combustível restante: " << getRestante() << endl;
        }
        void setQuantidade(int quant) {
            try {
                if (quant > 0) quantidade = quant;
                else throw invalid_argument ("Quantidade atual do tanque invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setDistancia(int dist) {
            try {
                if (dist > 0) distancia = dist;
                else throw invalid_argument ("Distancia percorrida invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getQuantidade() { return quantidade; }
        int getDistancia() { return distancia; }
        int getRestante() { return round((quantidade - (distancia*1.0/15))); }
};

void exibe (Carro c[2]) {
    for (int i = 0; i < 2; i++) {
        cout << "Carro " << (i + 1) << ":" << endl;
        c[i].exibe();
        cout << endl;
    }
}

int main () {
    Carro c[2];
    int quant[2], dist[2];
    for (int i = 0; i < 2; i++) cin >> quant[i];
    for (int i = 0; i < 2; i++) cin >> dist[i];
    for (int i = 0; i < 2; i++) c[i] = Carro(quant[i], dist[i]);
    exibe(c);
}