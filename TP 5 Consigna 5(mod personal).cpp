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
    cout << "Registro exitoso. Ahora puede iniciar sesión.\n";
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
        cout << "2. Cambiar contraseña" << endl;
        cout << "3. Atrás" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese el nuevo nombre de usuario: ";
            cin >> nombreUsuario;
        } else if (opcion == 2) {
            int claveAnterior;
            cout << "Ingrese la contraseña anterior: ";
            cin >> claveAnterior;
            if (claveAnterior == clave) {
                cout << "Ingrese la nueva contraseña: ";
                cin >> clave;
                cout << "Contraseña cambiada con éxito." << endl;
            } else {
                cout << "Contraseña anterior incorrecta." << endl;
            }
        } else if (opcion == 3) {
            cout << "Volviendo al menú principal." << endl;
        } else {
            cout << "Opción no válida. Intente nuevamente." << endl;
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
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Saldo actual: $" << saldo << endl;
        } else if (opcion == 2) {
            double deposito;
            cout << "Ingrese el monto a depositar: $";
            cin >> deposito;
            if (deposito > 0) {
                saldo += deposito;
                cout << "Depósito exitoso." << endl;
            } else {
                cout << "Monto inválido." << endl;
            }
        } else if (opcion == 3) {
            double retiro;
            cout << "Ingrese el monto a retirar: $";
            cin >> retiro;
            if (retiro > 0 && retiro <= saldo) {
                saldo -= retiro;
                cout << "Retiro exitoso." << endl;
            } else {
                cout << "Fondos insuficientes o monto inválido." << endl;
            }
        } else if (opcion == 4) {
            mostrarPerfil(nombreUsuario, clave);
        } else if (opcion == 5) {
            cout << "Gracias por usar el cajero automático. ¡Hasta luego!" << endl;
            return;
        } else {
            cout << "Opción no válida. Intente nuevamente." << endl;
        }
    } while (true);
}

int main() {
    ofstream archivoUsuarios("usuarios.txt", ios::app); // Abre el archivo en modo de añadir datos
    ifstream archivoSesiones("sesiones.txt");

    // Mostrar animación y bienvenida
    mostrarAnimacion();

    // Variables para almacenar la entrada del usuario
    int opcion;
    string nombreUsuario;
    int clave;
    double saldo;

    // Solicitar al usuario que inicie sesión o se registre
    cout << "¿Desea iniciar sesión (1) o registrarse (2)? ";
    cin >> opcion;

    if (opcion == 2) {
        registrarUsuario(archivoUsuarios);
    } else if (opcion == 1) {
        cout << "Ingrese su nombre de usuario: ";
        cin >> nombreUsuario;
        cout << "Ingrese su contraseña: ";
        cin >> clave;
        if (!iniciarSesion(archivoSesiones, nombreUsuario, clave, saldo)) {
            cout << "Usuario o contraseña incorrectos. Saliendo del programa." << endl;
            return 1;
        }
    } else {
        cout << "Opción no válida. Saliendo del programa." << endl;
        return 1;
    }

    archivoSesiones.close();

    // Mostrar menú principal
    mostrarMenuPrincipal(saldo, nombreUsuario, clave);

    // Actualizar archivo de sesiones con el nuevo saldo
    ofstream archivoSesionesActualizado("sesiones.txt");
    archivoSesionesActualizado << nombreUsuario << " " << clave << " " << saldo << endl;
    archivoSesionesActualizado.close();

    return 0;
}

