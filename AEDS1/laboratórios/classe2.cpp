#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
using namespace std;

class Figura {
    private:
        int lados;
        float tamanho;
    public:
        Figura () { setNum(1); setTam(1); }
        Figura (int num, float val) { setNum(num); setTam(val); }
        void setNum (int num) {
            try {
                if (num > 0) lados = num;
                else throw invalid_argument ("Numero de lados invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getNum () { return lados; }
        void setTam (int val) {
            try {
                if (val > 0) tamanho = val;
                else throw invalid_argument ("Tamanho invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getTam () { return tamanho; }
        virtual void exibe () {}
        virtual float calculaArea () {}
        virtual float calculaPerimetro () {}
};

class Quadrado : public Figura {
    public:
        Quadrado () {
            setNum(4); setTam(1);
        }
        Quadrado (float tam) {
            setNum(4); setTam(tam);
        }
        void exibe () { cout << "Quadrado com lados de tamanho " << getTam() << endl; }
        float calculaPerimetro () { return (getNum() * getTam()); }
        float calculaArea () { return (getTam() * getTam()); }
};

class Triangulo : public Figura {
    public:
        Triangulo () {
            setNum(3); setTam(1);
        }
        Triangulo (float tam) {
            setNum(3); setTam(tam);
        }
        void exibe () { cout << "Triangulo com lados de tamanho " << getTam() << endl; }
        float calculaPerimetro () { return (getNum() * getTam()); }
        float calculaArea () { return (pow(getTam(), 2) * sqrt(3) / 4); }
};

void exibeMaior(Quadrado q[10], Triangulo t[10]) {
    int maior = 0, figura = 0, pos = 0;
    for (int i = 0; i < 10; i++) {
        if (q[i].getTam() > maior) {
            maior = q[i].getTam(); figura = 1; pos = i;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (t[i].getTam() > maior) {
            maior = t[i].getTam(); figura = 2; pos = i;
        }
    }
    if (figura == 1) q[pos].exibe();
    else if (figura == 2) t[pos].exibe();
}

void ordena(Quadrado q[10], Triangulo t[10]) {
    Quadrado quad; Triangulo triang;
    int menor, indice;
    for (int i = 0; i < 9; i++) {
        menor = q[i].getTam(); indice = i;
        for (int j = 1; j < 10; j++) {
            if (q[i].getTam() < menor) {
                menor = q[i].getTam(); indice = j;
            }
        }
        quad = q[i]; q[i] = q[indice]; q[indice] = quad;
    }
    for (int i = 0; i < 9; i++) {
        menor = t[i].getTam(); indice = i;
        for (int j = 1; j < 10; j++) {
            if (t[i].getTam() < menor) {
                menor = t[i].getTam(); indice = j;
            }
        }
        triang = t[i]; t[i] = t[indice]; t[indice] = triang;
    }
}

int main () {
    int tam;
    Quadrado q[10]; Triangulo t[10];
    for (int i = 0; i < 10; i++) {
        cout << "Insira o tamanho do quadrado: " << endl;
        cin >> tam; q[i].setTam(tam);
    }
    for (int i = 0; i < 10; i++) {
        cout << "Insira o tamanho do triangulo: " << endl;
        cin >> tam; t[i].setTam(tam);
    }
    for (int i = 0; i < 10; i++) {
        cout << "Quadrado " << (i + 1) << ":" << endl;
        q[i].exibe();
        cout << endl;
        cout << "Area: " << q[i].calculaArea() << endl << "Perimetro: " << q[i].calculaPerimetro() << endl;
    }
    for (int i = 0; i < 10; i++) {
        cout << "Triangulo " << (i + 1) << ":" << endl;
        t[i].exibe();
        cout << endl;
        cout << "Area: " << t[i].calculaArea() << endl << "Perimetro: " << t[i].calculaPerimetro() << endl;
    }
    exibeMaior(q, t); ordena(q, t);
    for (int i = 0; i < 10; i++) q[i].exibe();
    for (int i = 0; i < 10; i++) q[i].exibe();
}
