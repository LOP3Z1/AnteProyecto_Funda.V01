#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. TIPOS DE DATOS (Estructuras globales)
struct Cuenta {
    string usuario;
    string clave;
    double saldo;
};

// Prototipos de funciones
void menuPrincipal();
void registrarUsuario();
bool iniciarSesion();
void menuBanco(Cuenta &usuarioActivo);
void jugarAhorcado(Cuenta &usuarioActivo);
void guardarEnArchivo(Cuenta c);
bool cargarUsuario(string usuario, string clave, Cuenta &usuarioEncontrado);
void actualizarSaldoEnArchivo(Cuenta usuarioModificado); // Nueva función para guardar cambios de saldo

int main() {
    srand(time(0)); // Semilla para el juego aleatorio
    menuPrincipal();
    return 0;
}


void menuPrincipal() {
    int opcion; // TIPO DE DATO entero
    
    // CICLO while para mantener el programa activo
    while (true) {
        cout << "\n=== BANCO CENTRAL & MINIJUEGOS ===" << endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Iniciar Sesion" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // ESTRUCTURA switch para el menú
        switch (opcion) {
            case 1:
                registrarUsuario();
                break;
            case 2:
                if (iniciarSesion()) {
                    cout << "\nSesion cerrada correctamente." << endl;
                }
                break;
            case 3:
                cout << "Gracias por usar el sistema." << endl;
                return;
            default:
                cout << "Opcion invalida." << endl;
        }
    }
}

// MANEJO DE ARCHIVOS: Registro , Creacion de la cuenta y Clave 
void registrarUsuario() {
    Cuenta nuevaCuenta;
    cout << "\n--- REGISTRO DE CUENTA ---" << endl;
    cout << "Ingrese nuevo usuario: ";
    cin >> nuevaCuenta.usuario;
    cout << "Ingrese clave de 4 digitos: ";
    cin >> nuevaCuenta.clave;
    
    // OPERADORES de asignación estándar al registrarse
    nuevaCuenta.saldo = 500.0; // Saldo inicial fijo de regalo

    guardarEnArchivo(nuevaCuenta);
    cout << "Usuario registrado con exito. Regalo inicial: $500.0" << endl;
}

void guardarEnArchivo(Cuenta c) {
    // MANEJO DE ARCHIVOS (Escritura)
    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << c.usuario << " " << c.clave << " " << c.saldo << "\n";
        archivo.close();
    }
}

// MANEJO DE ARCHIVOS: Modificación de saldos en el archivo de texto
void actualizarSaldoEnArchivo(Cuenta usuarioModificado) {
    ifstream archivoLectura("usuarios.txt");
    vector<Cuenta> listaUsuarios;
    string u, c;
    double s;

    // Leer todos los usuarios actuales y guardarlos en memoria temporal (vector)
    if (archivoLectura.is_open()) {
        while (archivoLectura >> u >> c >> s) {
            Cuenta temp;
            temp.usuario = u;
            temp.clave = c;
            if (u == usuarioModificado.usuario) {
                temp.saldo = usuarioModificado.saldo; // Actualiza el saldo del usuario activo
            } else {
                temp.saldo = s;
            }
            listaUsuarios.push_back(temp);
        }
        archivoLectura.close();
    }

    // Reescribir el archivo completo con el saldo actualizado
    ofstream archivoEscritura("usuarios.txt");
    if (archivoEscritura.is_open()) {
        for (int i = 0; i < listaUsuarios.size(); i++) {
            archivoEscritura << listaUsuarios[i].usuario << " " 
                             << listaUsuarios[i].clave << " " 
                             << listaUsuarios[i].saldo << "\n";
        }
        archivoEscritura.close();
    }
}

// MANEJO DE ARCHIVOS: Lectura y Verificación
bool cargarUsuario(string usuario, string clave, Cuenta &usuarioEncontrado) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return false;

    string u, c;
    double s;
    // CICLO while combinado con lectura de archivos
    while (archivo >> u >> c >> s) {
        // CONDICIONAL if con OPERADORES lógicos (&&) y de comparación (==)
        if (u == usuario && c == clave) {
            usuarioEncontrado.usuario = u;
            usuarioEncontrado.clave = c;
            usuarioEncontrado.saldo = s;
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool iniciarSesion() {
    string u, c;
    Cuenta usuarioActivo;
    cout << "\n--- INICIO DE SESION ---" << endl;
    cout << "Usuario: ";
    cin >> u;
    cout << "Clave: ";
    cin >> c;

    if (cargarUsuario(u, c, usuarioActivo)) {
        cout << "\nBienvenido/a, " << usuarioActivo.usuario << "!" << endl;
        menuBanco(usuarioActivo);
        return true;
    } else {
        cout << "Usuario o clave incorrectos." << endl;
        return false;
    }
}

void menuBanco(Cuenta &usuarioActivo) {
    int opcion;
    while (true) {
        cout << "\n--- BANCA ELECTRONICA ---" << endl;
        cout << "Saldo actual: $" << usuarioActivo.saldo << endl;
        cout << "1. Retirar dinero" << endl;
        cout << "2. Depositar dinero" << endl; // NUEVA OPCIÓN AÑADIDA
        cout << "3. Jugar al Ahorcado (Cuesta $50, gana $150)" << endl;
        cout << "4. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            double monto;
            cout << "Monto a retirar: ";
            cin >> monto;
            if (monto > 0 && monto <= usuarioActivo.saldo) {
                usuarioActivo.saldo -= monto;
                actualizarSaldoEnArchivo(usuarioActivo); // Guarda en usuarios.txt
                cout << "Retiro exitoso. Nuevo saldo: $" << usuarioActivo.saldo << endl;
            } else {
                cout << "Fondos insuficientes o monto invalido." << endl;
            }
        } 
        else if (opcion == 2) { // LÓGICA DE LA OPCIÓN DE DEPÓSITO
            double montoDeposito;
            cout << "Ingrese la cantidad de dinero a depositar: $";
            cin >> montoDeposito;
            
            if (montoDeposito > 0) {
                usuarioActivo.saldo += montoDeposito; // Sumar saldo
                actualizarSaldoEnArchivo(usuarioActivo); // Guardar cambio en usuarios.txt permanente
                cout << "Deposito exitoso. Nuevo saldo: $" << usuarioActivo.saldo << endl;
            } else {
                cout << "Monto invalido. El deposito debe ser mayor a 0." << endl;
            }
        }
        else if (opcion == 3) {
            if (usuarioActivo.saldo >= 50.0) {
                usuarioActivo.saldo -= 50.0; // Costo de entrada
                actualizarSaldoEnArchivo(usuarioActivo); // Guardar cobro en usuarios.txt
                jugarAhorcado(usuarioActivo);
            } else {
                cout << "No tienes suficiente saldo para jugar ($50)." << endl;
            }
        } 
        else if (opcion == 4) {
            return;
        }
    }
}

// ARREGLOS / ARRAYS y MINIJUEGO AHORCADO
void jugarAhorcado(Cuenta &usuarioActivo) {
    string palabras[5] = {"banco", "dinero", "ahorro", "credito", "tarjeta"};
    string palabraSecreta = palabras[rand() % 5];
    string palabraOculta(palabraSecreta.length(), '_');
    
    int intentosRestantes = 6;
    char letra;
    bool gano = false;

    cout << "\n=== MINIJUEGO: AHORCADO BANCARIO ===" << endl;
    cout << "Adivina la palabra relacionada con finanzas." << endl;

    while (intentosRestantes > 0 && !gano) {
        cout << "\nPalabra: ";
        for (int i = 0; i < palabraOculta.length(); i++) {
            cout << palabraOculta[i] << " ";
        }
        
        cout << "\nIntentos restantes: " << intentosRestantes << endl;
        cout << "Introduce una letra: ";
        cin >> letra;

        bool acierto = false;
        for (int i = 0; i < palabraSecreta.length(); i++) {
            if (palabraSecreta[i] == letra) {
                palabraOculta[i] = letra;
                acierto = true;
            }
        }

        if (!acierto) {
            intentosRestantes--;
            cout << "Letra incorrecta!" << endl;
        } else {
            cout << "Buen acierto!" << endl;
        }

        if (palabraOculta == palabraSecreta) {
            gano = true;
        }
    }

    if (gano) {
        cout << "\nFelicidades! Ganaste. La palabra era: " << palabraSecreta << endl;
        usuarioActivo.saldo += 150.0;
        actualizarSaldoEnArchivo(usuarioActivo); // Guardar premio en usuarios.txt permanente
        cout << "Se han depositado $150 en tu cuenta!" << endl;
    } else {
        cout << "\nPerdiste! Te quedaste sin intentos. La palabra era: " << palabraSecreta << endl;
    }
}