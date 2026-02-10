#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Veiculo {
    private:
        int numRodas;
        float consumo, tanque, capacidade;
    public:
        Veiculo() { inicializa(4, 1, 0, 50); }
        Veiculo(int n, float num, float val, float tam) { inicializa(n, num, val, tam); }
        void setRodas(int n) {
            try {
                if (n > 1 && n%2 == 0) numRodas = n;
                else throw invalid_argument ("Numero de rodas invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getRodas() { return numRodas; }
        void setConsumo(float num) {
            try {
                if (num > 0) consumo = num;
                else throw invalid_argument ("Consumo invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getConsumo() { return consumo; }
        void setTanque(float val) {
            try {
                if (val > 0 && val <= getCapacidade()) tanque = val;
                else throw invalid_argument ("Litragem invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getTanque() { return tanque; }
        void setCapacidade(float tam) {
            try {
                if (tam > 0) capacidade = tam;
                else throw invalid_argument ("Capacidade invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getCapacidade() { return capacidade; }
        void abastece(float litros) {
            if (litros + getTanque() <= getCapacidade()) setTanque(getTanque() + litros);
        }
        void preenche() {
            int n;
            float val;
            cout << "Numero de rodas: ";
            cin >> n; setRodas(n);
            cout << "Consumo: ";
            cin >> val; setConsumo(val);
            cout << "Litragem atual: ";
            cin >> val; setTanque(val);
            cout << "Capacidade total: ";
            cin >> val; setCapacidade(val);
        }
        void exibe() {
            cout << "Numero de rodas: " << getRodas() << endl << "Consumo: " << getConsumo() << " km/l" << endl << "Litragem atual: " << getTanque() << " litros" << endl << "Capacidade total: " << getCapacidade() << " litros" << endl;
        }
    private:
        void inicializa(int n, float num, float val, float tam) {
            setRodas(n);
            setConsumo(num);
            setTanque(val);
            setCapacidade(tam);
        }
};

class Motocicleta : public Veiculo {
    public:
        Motocicleta() { setRodas(2); }
        Motocicleta(float consumo, float tanque, float maxComb) {
            setRodas(2);
            setConsumo(consumo);
            setTanque(tanque);
            setCapacidade(maxComb);
        }
};

class Caminhao : public Veiculo {
    private:
        float cargaAtual, capacCarroceria;
    public:
        Caminhao() {
            setCarga(1);
            setCarroceria(10);
        }
        Caminhao(float consumo, float tanque, float maxComb, float carga, float maxCarga) {
            setRodas(4);
            setConsumo(consumo);
            setTanque(tanque);
            setCapacidade(maxComb);
            setCarga(carga);
            setCarroceria(maxCarga);
        }
        void setCarga(float num) {
            try {
                if (num > 0) cargaAtual = num;
                else throw invalid_argument ("Carga atual invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getCarga() { return cargaAtual; }
        void setCarroceria(float val) {
            try {
                if (val > 0) capacCarroceria = val;
                else throw invalid_argument ("Carroceria maxima invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getCarroceria() { return capacCarroceria; }
        void carrega(float nova) {
            if (nova + getCarga() <= getCarroceria()) setCarga(nova + getCarga());
        }
        void preenche() {
            float val;
            Veiculo :: preenche();
            cout << "Carga atual: ";
            cin >> val; setCarga(val);
            cout << "Capacidade maxima: ";
            cin >> val; setCarroceria(val);
        }
        void exibe() {
            Veiculo :: exibe();
            cout << "Carga atual: " << getCarga() << " kg" << endl << "Capacidade maxima: " << getCapacidade() << " kg" << endl;
        }
};

int main () {
    float val;
    Motocicleta m; Caminhao c;
    cout << "Motocicleta" << endl; m.preenche();
    cout << "Quantos litros deseja abastecer? ";
    cin >> val; m.abastece(val);
    cout << "Motocicleta" << endl; m.exibe();
    cout << "Caminhao" << endl; c.preenche();
    cout << "Quantos litros deseja abastecer? ";
    cin >> val; c.abastece(val);
    cout << "Quantos kg deseja carregar? ";
    cin >> val; c.carrega(val);
    cout << "Caminhao" << endl; c.exibe();
}
