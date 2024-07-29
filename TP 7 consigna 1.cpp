#include <iostream>
#include <string>
using namespace std;

int main() {
    string cadena, invertida;
    cout << "ingresa una cadena: ";
    cin >> cadena;
    for (int i = cadena.length() - 1; i >= 0; i--) {
        invertida += cadena[i];
    }
    cout << "cadena invertida: " << invertida << endl;
    return 0;
}

