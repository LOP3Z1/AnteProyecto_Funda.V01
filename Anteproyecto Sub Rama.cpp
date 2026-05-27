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

int main() {
    srand(time(0)); // Semilla para el juego aleatorio
    menuPrincipal();
    return 0;
}


void menuPrincipal() {
    int opcion; // TIPO DE DATO entero
    
    // CICLO while para mantener el programa activo
    while (true) {
        cout << "=== BANCO CENTRAL & MINIJUEGOS ===" << endl;
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
    
    // OPERADORES de asignación
    nuevaCuenta.saldo = 500.0; // Saldo inicial de regalo

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
    cin >> c;https://github.com/LOP3Z1/AnteProyecto_Funda.V01.githttps://github.com/LOP3Z1/AnteProyecto_Funda.V01.git

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
        cout << "2. Jugar al Ahorcado (Cuesta $50, gana $150)" << endl;
        cout << "3. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            double monto;
            cout << "Monto a retirar: ";
            cin >> monto;
            // CONDICIONAL if y OPERADORES de comparación
            if (monto > 0 && monto <= usuarioActivo.saldo) {
                // OPERADORES aritméticos (-=)
                usuarioActivo.saldo -= monto;
                cout << "Retiro exitoso. Nuevo saldo: $" << usuarioActivo.saldo << endl;
            } else {
                cout << "Fondos insuficientes o monto invalido." << endl;
            }
        } 
        else if (opcion == 2) {
            if (usuarioActivo.saldo >= 50.0) {
                usuarioActivo.saldo -= 50.0; // Costo de entrada
                jugarAhorcado(usuarioActivo);
            } else {
                cout << "No tienes suficiente saldo para jugar ($50)." << endl;
            }
        } 
        else if (opcion == 3) {
            return;
        }
    }
}

// ARREGLOS / ARRAYS y MINIJUEGO AHORCADO
void jugarAhorcado(Cuenta &usuarioActivo) {
    // ARREGLO / ARRAY de strings para las palabras secretas
    string palabras[5] = {"banco", "dinero", "ahorro", "credito", "tarjeta"};
    
    // Seleccionar palabra aleatoria usando índices del arreglo
    string palabraSecreta = palabras[rand() % 5];
    
    // ARREGLO / ARRAY dinámico (vector) para rastrear las letras adivinadas
    string palabraOculta(palabraSecreta.length(), '_');
    
    int intentosRestantes = 6;
    char letra;
    bool gano = false;

    cout << "\n=== MINIJUEGO: AHORCADO BANCARIO ===" << endl;
    cout << "Adivina la palabra relacionada con finanzas." << endl;

    // CICLO while principal del juego
    while (intentosRestantes > 0 && !gano) {
        cout << "\nPalabra: ";
        // CICLO for para mostrar el progreso de la palabra
        for (int i = 0; i < palabraOculta.length(); i++) {
            cout << palabraOculta[i] << " ";
        }
        
        cout << "\nIntentos restantes: " << intentosRestantes << endl;
        cout << "Introduce una letra: ";
        cin >> letra;

        bool acierto = false;
        // CICLO for para verificar si la letra está en la palabra
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

        // Verificar si completó la palabra
        if (palabraOculta == palabraSecreta) {
            gano = true;
        }
    }

    // CONDICIONAL if para el resultado del juego y asignación de premios
    if (gano) {
        cout << "\nFelicidades! Ganaste. La palabra era: " << palabraSecreta << endl;
        usuarioActivo.saldo += 150.0; // OPERADOR aritmético de suma
        cout << "Se han depositado $150 en tu cuenta!" << endl;
    } else {
        cout << "\nPerdiste! Te quedaste sin intentos. La palabra era: " << palabraSecreta << endl;
    }
}