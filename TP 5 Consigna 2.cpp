#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Ingrese un número entero positivo: ";
    cin >> n;

    for (int fila = 0; fila <= n; ++fila) {
        for (int columna = 0; columna <= n; ++columna) {
            if (fila + columna <= n) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    return 0;
}

