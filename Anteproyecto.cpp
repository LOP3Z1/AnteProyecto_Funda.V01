#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura para almacenar los datos de los usuarios
struct Cuenta {
    string usuario;
    string clave;
    double saldo;
};

// Declaración de funciones (Prototipos)
void menuPrincipal();
void Regitro_De_Usuario();
bool InicioSesion();
void Menu_del_Banco(Cuenta &Usuario_Activo);
void Jugar_Ahorcado(Cuenta &Usuario_Activo);
void Guardar_En_Archivos(const Cuenta &c);
bool Cargar_Usuario(string usuario, string clave, Cuenta &Usuario_Encontrado);
void Actualizar_Saldo_Archivo(const Cuenta &Usuario_Activo);

int main() {
    srand(time(0)); // Semilla para que las palabras del ahorcado sean aleatorias
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;
    while(true) {
        cout << "\n_______BANCO CENTRAL______" << endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Iniciar Sesion" << endl;
        cout << "3. Salir" << endl;
        cout << "SELECCIONE UNA DE LAS OPCIONES: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                Regitro_De_Usuario();
                break;
            case 2:
                if(InicioSesion()) {
                    cout << "Sesion Cerrada Correctamente." << endl;
                }
                break;
            case 3:
                cout << "Gracias por usar el sistema." << endl;
                return;
            default:
                cout << "Opcion Invalida." << endl;
        }
    }
}

void Regitro_De_Usuario() {
    Cuenta nuevaCuenta;
    cout << "\n--- Registro de Cuenta ---" << endl;
    cout << "Ingrese nuevo usuario: ";
    cin >> nuevaCuenta.usuario;
    cout << "Ingrese nueva clave (CLAVE DE 4 DIGITOS): ";
    cin >> nuevaCuenta.clave;
    
    nuevaCuenta.saldo = 20.0; // Se eliminó el signo '$' erróneo
    Guardar_En_Archivos(nuevaCuenta);
    cout << "Te has registrado con exito. Regalo Inicial: $20.0" << endl;
}

void Guardar_En_Archivos(const Cuenta &c) {
    ofstream archivo("usuarios.txt", ios::app); // Corrección de comillas y puntos dobles
    if(archivo.is_open()) {
        archivo << c.usuario << " " << c.clave << " " << c.saldo << endl;
        archivo.close();
    }
}

bool Cargar_Usuario(string usuario, string clave, Cuenta &Usuario_Encontrado) {
    ifstream archivo("usuarios.txt");
    if(!archivo.is_open()) return false;

    string u, c;
    double s;
    while(archivo >> u >> c >> s) {
        if(u == usuario && c == clave) {
            // Asignación correcta a los campos de la estructura
            Usuario_Encontrado.usuario = u;
            Usuario_Encontrado.clave = c;
            Usuario_Encontrado.saldo = s;
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool InicioSesion() {
    string u, c;
    Cuenta Usuario_Activo;
    cout << "\n______Inicio de Sesion__________" << endl;
    cout << "Usuario: ";
    cin >> u;
    cout << "Clave: ";
    cin >> c;

    if(Cargar_Usuario(u, c, Usuario_Activo)) {
        cout << "Bienvenido/a, " << Usuario_Activo.usuario << "!" << endl;
        Menu_del_Banco(Usuario_Activo);
        return true;
    } else {
        cout << "Usuario o Clave incorrectos (SINTAX ERROR 404)" << endl;
        return false;
    }
}

void Menu_del_Banco(Cuenta &Usuario_Activo) {
    int opcion;
    while(true) {
        cout << "\n_______BANCA ELECTRONICA______" << endl;
        cout << "Saldo Actual: $" << Usuario_Activo.saldo << endl;
        cout << "1. Retirar Dinero" << endl;
        cout << "2. Jugar al Ahorcado (Cuesta $5.00, gana $15.00)" << endl;
        cout << "3. Volver al menu principal de la App" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opcion;

        if(opcion == 1) {
            double monto;
            cout << "Monto a retirar: ";
            cin >> monto;
            if(monto > 0 && monto <= Usuario_Activo.saldo) {
                Usuario_Activo.saldo -= monto;
                Actualizar_Saldo_Archivo(Usuario_Activo); // Guarda el nuevo saldo en el archivo txt
                cout << "Retiro exitoso. Nuevo saldo: $" << Usuario_Activo.saldo << endl;
            } else {
                cout << "Fondos insuficientes o monto invalido." << endl;
            }
        } 
        else if(opcion == 2) {
            if(Usuario_Activo.saldo >= 5.00) {
                Usuario_Activo.saldo -= 5.00;
                Actualizar_Saldo_Archivo(Usuario_Activo);
                Jugar_Ahorcado(Usuario_Activo);
            } else {
                cout << "No tiene saldo suficiente para poder jugar ($5.00)." << endl;
            }
        } 
        else if(opcion == 3) {
            return;
        }
    }
}

void Jugar_Ahorcado(Cuenta &Usuario_Activo) {
    string palabras[5] = {"banco", "dinero", "ahorro", "credito", "tarjeta"};
    string palabraSecreta = palabras[rand() % 5];
    string palabraOculta(palabraSecreta.length(), '_');
    int intentosRestantes = 6;
    char letra;
    bool gano = false;

    cout << "\n--- MINIJUEGO DEL AHORCADO: BANCARIO ---" << endl;
    cout << "Adivina la palabra relacionada con finanzas." << endl;

    while(intentosRestantes > 0 && !gano) {
        cout << "\nPalabra: ";
        for(char c : palabraOculta) {
            cout << c << " ";
        }
        cout << "\nIntentos restantes: " << intentosRestantes << endl;
        cout << "Introduce una letra: ";
        cin >> letra;

        bool acierto = false;
        for(size_t i = 0; i < palabraSecreta.length(); i++) {
            if(palabraSecreta[i] == letra) {
                palabraOculta[i] = letra;
                acierto = true;
            }
        }

        if(!acierto) {
            intentosRestantes--;
            cout << "Letra incorrecta!" << endl;
        }


        if(palabraOculta == palabraSecreta) {
            gano = true;
        }
    }

    if(gano) {
        Usuario_Activo.saldo += 15.00; // Premio por ganar
        Actualizar_Saldo_Archivo(Usuario_Activo);
        cout << "\n¡Felicidades! Ganaste. La palabra era: " << palabraSecreta << endl;
        cout << "Se han sumado $15.00 a tu cuenta. Nuevo Saldo: $" << Usuario_Activo.saldo << endl;
    } else {
        cout << "\nPerdiste. La palabra secreta era: " << palabraSecreta << endl;

    //SE OCUPO UN CICLO WHILE,FOR PARA EL JUEGO;
    while(intentosRestatantes > 0 && !gano){
        cout <<"PALABRA. "
        for(int i = 0; i < PalabraOculta.length)
        cout <<"Palabra: ";

        for(int i = 0; i < PalabraOculta.length(); i++){
            cout << PalabraOculta[i] << " ";
        }

        cout <<"Intentos restantes: " << intentosRestantes << endl;
        cout <<"Introduce una letra: ";
        cin >> int letra;

        bool acierto = false;
        for(int i = 0; i < palabraSecreta.length(); i++){
            if(palabraSecreta[i] == letra){
                PalabraOculta[i] == letra;
                acierto = true;
            }
        }

        if(!acierto){
            intentosRestantes--;
            cout << "Letra Incorrecta!. " << endl;
        }
        else{
            cout << "Bien has acertado!. " << endl;
        } 

        if(PalabraOculta == palabraSecreta){
            gano = true;
        }

    }

    if(gano){
        cout << "Felicidades! Haz Ganado. La Palabra era: " << palabraSecreta << endl;
        Usuario_Activo.saldo += $15.00;
        cout <<"Se han depositado tus $15.00 en tu cuenta Bancaria!. " << endl;
    }
    else{
        cout << "Perdistes! Te quedastes sin mas intetos. La palabara era: " << palabraSecreta << endl;

    }
}

 copilot/vscode-mpm78q1g-3784
// Función auxiliar para que los saldos actualizados se guarden de verdad en el archivo .txt
void Actualizar_Saldo_Archivo(const Cuenta &Usuario_Activo) {
    ifstream archivoLectura("usuarios.txt");
    vector<Cuenta> cuentas;
    Cuenta temporal;

    if(archivoLectura.is_open()) {
        while(archivoLectura >> temporal.usuario >> temporal.clave >> temporal.saldo) {
            if(temporal.usuario == Usuario_Activo.usuario) {
                temporal.saldo = Usuario_Activo.saldo;
            }
            cuentas.push_back(temporal);
        }
        archivoLectura.close();
    }

    ofstream archivoEscritura("usuarios.txt");
    if(archivoEscritura.is_open()) {
        for(const auto &c : cuentas) {
            archivoEscritura << c.usuario << " " << c.clave << " " << c.saldo << endl;
        }
        archivoEscritura.close();
    }

}
