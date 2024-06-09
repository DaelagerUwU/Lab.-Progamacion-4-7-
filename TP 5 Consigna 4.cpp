#include <iostream>
using namespace std;

int main() {
    int cantidadVendedores;
    cout << "Ingrese la cantidad de vendedores: ";
    cin >> cantidadVendedores;

    const int MAX_NOMBRE = 100;
    char nombres[cantidadVendedores][MAX_NOMBRE]; 
    int ventas[cantidadVendedores]; 

    for (int i = 0; i < cantidadVendedores; ++i) {
        cout << "Nombre del vendedor " << i + 1 << ": ";
        cin >> nombres[i];
        cout << "Cantidad de ventas de " << nombres[i] << ": ";
        cin >> ventas[i];
    }

    cout << "Resumen de ventas:" << endl;
    for (int i = 0; i < cantidadVendedores; ++i) {
        cout << nombres[i] << ": " << ventas[i] << " ventas" << endl;
    }

    return 0;
}
