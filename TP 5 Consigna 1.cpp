#include <iostream>
using namespace std;
int main() {
    int numero;
    cout << "Ingrese un numero no negativo entero: ";
    cin >> numero;
    int factor = 1;
    for (int i = 1; i <= numero; ++i) {
        factor *= i; 
    }
	cout << "El factorial de " << numero << " es " << factor << endl;
	return 0;
}

