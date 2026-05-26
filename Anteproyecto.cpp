#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cuenta{
    string usuario;
    string clave;
    double saldo;
};

void menuPrincipal();
void Regitro_De_Usuario();
bool InicioSesión();
void Menu_del_Banco(Cuenta && Usuario_Activo);
void Jugar_Ahorcado(Cuenta && Usuario_Activo);
void Guardar_En_Archivos(CuentaC);
bool Cargar_Usuario(string usuario, string clave, Cuenta && Usuario_Encontrado);

int main(){
    srand(time(0));//Semilla para el juego de ahorcado en aleatorio.
    menuPrincipal();
    return 0;
};

void menuPrincipal(){
    int opcion;
    while(true){
        cout <<"_______BANCO CENTRAL______" << endl;
        cout <<"1. Registrarse: " << endl;
        cout <<"2. Iniciar Sesion: " << endl;
        cout <<"3. Salir: " << endl;
        cout <<"SELECCIONE UNA DE LAS OPCIONES: " << endl;
        cin >> opcion;

        switch(opcion){
            case 1:
            Regitro_De_Usuario();
            break
            case 2:
            if(InicioSesión()){
                cout <<"Sesion Cerrada Correctamente: " << endl;
            }
            break;
            case 3:
            cout << "Gracias por usa el sistema: " << endl;
            return;
            default;
            cout <<"Opciones Invalida: " << endl;
        }
    }
}

//MANEJO DE LOS ARCHIVOS; (REGITRO)
void Regitro_De_Usuario(){
    Cuenta nuevaCuenta;
    cout << "  Registro d Cuenta   " << endl;
    cout << "Ingrese nuevo usuario: " << endl;
    cin >> nuevaCuenta;
    cout <<"Ingrese nueva clave (CLAVE DE 4 DIGITOS): " << endl;
    cin >> nuevaCuenta.clave;

    //Opeardores de asignación;
    nuevaCuenta.saldo = $ 20.0;

    Guardar_En_Archivos(nuevaCuenta);
    cout <<"Te haz regitrado con exito Regalo Inicial : $ 20.0: " << endl;

}

void Guardar_En_Archivos(CuentaC);
ofstream archivo("usuarios.txt, ios:::app");
if(archivo.is_open()){
    archivo <<c.usuario << " " << c.clave << " " << c.saldo << " " << endl;
    archivo.close();
}

bool Cargar_Usuario(string usuario, string clave, Cuenta & Usuario_Encontrado){
    ifstream archivo("usuarios.txt");
    if(!archivo.is_open())return false;

    string u, c;
    double s;
    while(archivo >> u >> c >> s){
        if(u == usuario && c == clave){
            Usuario_Encontrado = u;
            Usuario_Encontrado = c;
            Usuario_Encontrado = s;
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool InicioSesión(){
    string u,c;
    Cuenta Usuario_Activo
    cout <<"______Inicio de Sesion__________" << endl;
    cout << "Usuario: ";
    cin >> u;
    cout << "Clave: ";
    cin >> c;

    if(Cargar_Usuario(u, c, Usuario_Activo)){
        cout <<"Bienvenido/a, " << Usuario_Activo.usuario << "!" << endl;
        Menu_del_Banco(Usuario_Activo),
        return true;
    }
    else{
        cout <<"Usuario o Clave incorrectos (SINTAX ERROR 404)" << endl;
        return false;
    }
}

void Menu_del_Banco(Cuenta &Usuario_Activo){
    int opcion;
    while(true){
        cout << "_______BANCA ELECTRONICA______" << endl;
        cout << "Saldo Actual: $" << Usuario_Activo.saldo << endl;
        cout << "1. Retirar Dinero" << endl;
        cout << "2. Jugar al Ahorcado (Cuesta $5.00, gana $15.00)" << endl;
        cout << "3. Volver al menu principal de la App" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opcion;

        if(opcion == 1){
            double monto;
            cout << "Monto a retirar: ";
            cin >> monto;
            
            if(monto > 0 && monto <= Usuario_Activo.saldo){
                Usuario_Activo.saldo -= monto;
                cout << "Retiro exitoso. Nuevo saldo: $" << Usuario_Activo.saldo << endl;
            } else {
                cout << "Fondos insuficientes o monto invalido." << endl;
            }
        } else if(opcion == 2){
            if(Usuario_Activo.saldo >= $5.00){
                Usuario_Activo.saldo -= $5.00
                Jugar_Ahorcado(Usuario_Activo);
            }else{
                cout << "No tiene saldo suficinete para poder jugar ($5.00). " << endl;
            }    
        } 
        else if(opcion == 3){
            return;
        }        
    }
}
//AQUI HICE ARREGLOS / ARRAYS y Minijuego Del Ahorcado
void Jugar_Ahorcado(Cuenta &Usuario_Activo){
    string palabras[5] = {"banco", "dinero", "ahorro", "credito", "tarjeta"};
    stringPalabraSecreta = palabras[rand() % 5];
    stringPalabraOculta(palabraSecreta.length(),'_');
    const int intentosRestantes = 6;
    char letra;
    bool gano = false;

    cout <<"MINIJUEGO DEL AHORCADO: BANCARIO " << endl;
    cout <<"Adivina la palabra realcionada con finanzas. " << endl;

    //SE OCUPO UN CICLO WHILE,FOR PARA EL JUEGO;
    while(intentosRestatantes > 0 && !gano){
        cout <<"PALABRA. "
        for(int i = 0; i < PalabraOculta.length)
    }

}