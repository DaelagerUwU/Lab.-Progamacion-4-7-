#include <iostream>
#include <unistd.h>
using namespace std;
void mostrarAnimacion() {
    cout << "Cargando";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush(); 
        sleep(1); 
    }
    cout << "\nBienvenido a ATM, Terminal Automatica\n" << endl;
}

int main() {
    mostrarAnimacion();

    int opcion;
    int claveRegistro;
    int claveInicio;
    double saldo = 0.0;

    cout << "Registrar nueva cuenta\n";
    cout << "Ingrese una clave de 4 digitos: ";
    cin >> claveRegistro;

    cout << "Iniciar sesion\n";
    cout << "Ingrese su clave de 4 digitos: ";
    cin >> claveInicio;

    while (claveInicio != claveRegistro) {
        cout << "Clave incorrecta, intente nuevamente: ";
        cin >> claveInicio;
    }

    do {
        cout << "\nMenu principal:" << endl;
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar dinero" << endl;
        cout << "3. Retirar dinero" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Saldo actual: $" << saldo << endl;
        } else if (opcion == 2) {
            double deposito;
            cout << "Ingrese el monto a depositar: $";
            cin >> deposito;
            if (deposito > 0) {
                saldo += deposito;
                cout << "Deposito exitoso." << endl;
            } else {
                cout << "Monto invalido." << endl;
            }
        } else if (opcion == 3) {
            double retiro;
            cout << "Ingrese el monto a retirar: $";
            cin >> retiro;
            if (retiro > 0 && retiro <= saldo) {
                saldo -= retiro;
                cout << "Retiro exitoso." << endl;
            } else {
                cout << "Fondos insuficientes o monto invalido." << endl;
            }
        } else if (opcion == 4) {
            cout << "Gracias por usar el cajero automatico. Adios!" << endl;
        } else {
            cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);

    return 0;
}

