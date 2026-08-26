#include <iostream>
#include <iomanip>
using namespace std;

class Relogio {
    private:
        int h, m, s;
    public:
        Relogio () { inicializaTudo(1, 1, 1); }
        Relogio (int hora, int min, int seg) { inicializaTudo(hora, min, seg); }
        void setHora(int hora) { h = hora; }
        void setMin(int min) { m = min; }
        void setSeg(int seg) { s = seg; }
        void avancaHorario () {
            s++;
            if (s == 60) {
                s = 0; m++;
                if (m == 60) {
                    m = 0;
                    h++;
                    if (h == 24) h = 0;
                }
            }
        }
        void exibe (int hora, int min, int seg) {
            cout << "Horário inicial: " << setfill('0') << setw(2) << hora << ":" << setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << seg << endl;
            cout << "Novo horário: " << setfill('0') << setw(2) << h << ":" << setfill('0') << setw(2) << m << ":" << setfill('0') << setw(2) << s << endl;
        }
    private:
        void inicializaTudo(int hora, int min, int seg) {
            setHora(hora);
            setMin(min);
            setSeg(seg);
        }
};

int main () {
    int N; cin >> N;
    Relogio r;
    for (int i = 0; i < N; i++) {
        int hora, min, seg;
        cin >> hora >> min >> seg;
        r = Relogio(hora, min, seg);
        r.avancaHorario();
        r.exibe(hora, min, seg);
    }
}