#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <ctime>
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

void registrarUsuario(ofstream& archivo) {
    string nombreUsuario;
    int clave;
    double saldo;
    cout << "Ingrese un nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese una clave de 4 digitos: ";
    cin >> clave;
    cout << "Ingrese el saldo inicial: $";
    cin >> saldo;
    archivo << nombreUsuario << " " << clave << " " << saldo << endl;
    cout << "Registro exitoso. Ahora puede iniciar sesi�n.\n";
}

bool iniciarSesion(ifstream& archivo, string nombreUsuario, int clave, double& saldo) {
    string usuario;
    int claveArchivo;
    double saldoArchivo;
    while (archivo >> usuario >> claveArchivo >> saldoArchivo) {
        if (usuario == nombreUsuario && claveArchivo == clave) {
            saldo = saldoArchivo;
            return true;
        }
    }
    return false;
}

void mostrarPerfil(string nombreUsuario, int& clave) {
    int opcion;
    do {
        cout << "\nPerfil de usuario: " << nombreUsuario << endl;
        cout << "1. Cambiar nombre de usuario" << endl;
        cout << "2. Cambiar contrase�a" << endl;
        cout << "3. Atr�s" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese el nuevo nombre de usuario: ";
            cin >> nombreUsuario;
        } else if (opcion == 2) {
            int claveAnterior;
            cout << "Ingrese la contrase�a anterior: ";
            cin >> claveAnterior;
            if (claveAnterior == clave) {
                cout << "Ingrese la nueva contrase�a: ";
                cin >> clave;
                cout << "Contrase�a cambiada con �xito." << endl;
            } else {
                cout << "Contrase�a anterior incorrecta." << endl;
            }
        } else if (opcion == 3) {
            cout << "Volviendo al men� principal." << endl;
        } else {
            cout << "Opci�n no v�lida. Intente nuevamente." << endl;
        }
    } while (opcion != 3);
}

void mostrarMenuPrincipal(double& saldo, string nombreUsuario, int clave) {
    int opcion;
    do {
        cout << "\nMenu principal:" << endl;
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar dinero" << endl;
        cout << "3. Retirar dinero" << endl;
        cout << "4. Perfil" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Saldo actual: $" << saldo << endl;
        } else if (opcion == 2) {
            double deposito;
            cout << "Ingrese el monto a depositar: $";
            cin >> deposito;
            if (deposito > 0) {
                saldo += deposito;
                cout << "Dep�sito exitoso." << endl;
            } else {
                cout << "Monto inv�lido." << endl;
            }
        } else if (opcion == 3) {
            double retiro;
            cout << "Ingrese el monto a retirar: $";
            cin >> retiro;
            if (retiro > 0 && retiro <= saldo) {
                saldo -= retiro;
                cout << "Retiro exitoso." << endl;
            } else {
                cout << "Fondos insuficientes o monto inv�lido." << endl;
            }
        } else if (opcion == 4) {
            mostrarPerfil(nombreUsuario, clave);
        } else if (opcion == 5) {
            cout << "Gracias por usar el cajero autom�tico. �Hasta luego!" << endl;
            return;
        } else {
            cout << "Opci�n no v�lida. Intente nuevamente." << endl;
        }
    } while (true);
}

int main() {
    ofstream archivoUsuarios("usuarios.txt", ios::app); // Abre el archivo en modo de a�adir datos
    ifstream archivoSesiones("sesiones.txt");

    // Mostrar animaci�n y bienvenida
    mostrarAnimacion();

    // Variables para almacenar la entrada del usuario
    int opcion;
    string nombreUsuario;
    int clave;
    double saldo;

    // Solicitar al usuario que inicie sesi�n o se registre
    cout << "�Desea iniciar sesi�n (1) o registrarse (2)? ";
    cin >> opcion;

    if (opcion == 2) {
        registrarUsuario(archivoUsuarios);
    } else if (opcion == 1) {
        cout << "Ingrese su nombre de usuario: ";
        cin >> nombreUsuario;
        cout << "Ingrese su contrase�a: ";
        cin >> clave;
        if (!iniciarSesion(archivoSesiones, nombreUsuario, clave, saldo)) {
            cout << "Usuario o contrase�a incorrectos. Saliendo del programa." << endl;
            return 1;
        }
    } else {
        cout << "Opci�n no v�lida. Saliendo del programa." << endl;
        return 1;
    }

    archivoSesiones.close();

    // Mostrar men� principal
    mostrarMenuPrincipal(saldo, nombreUsuario, clave);

    // Actualizar archivo de sesiones con el nuevo saldo
    ofstream archivoSesionesActualizado("sesiones.txt");
    archivoSesionesActualizado << nombreUsuario << " " << clave << " " << saldo << endl;
    archivoSesionesActualizado.close();

    return 0;
}

