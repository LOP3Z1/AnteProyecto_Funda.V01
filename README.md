# AnteProyecto_Funda.V01

Creación del anteproyecto de fundamentos.

```mermaid
graph TD
    %% Estilos Generales Optimizados Alto Contraste y Colores Llamativos
    classDef inicio fill:#2ecc71,stroke:#27ae60,stroke-width:3px,color:#fff,font-weight:bold;
    classDef proceso fill:#1f618d,stroke:#1a5276,stroke-width:2px,color:#fff,font-weight:bold;
    classDef decision fill:#f4d03f,stroke:#d4ac0d,stroke-width:2px,color:#1b2631,font-weight:bold;

    %% Flujo Principal
    Start([Inicio: main]) --> MenuP[Mostrar Menu Principal]

    %% Menu Principal
    MenuP --> OpcionP{¿Que opcion elige?}
    OpcionP -->|1. Registrarse| Reg[registrarUsuario]
    OpcionP -->|2. Iniciar Sesion| Login[iniciarSesion]
    OpcionP -->|3. Salir| Exit([Fin del Programa])

    %% Registro con Monto Fijo
    Reg --> RegInput[Pedir Usuario y Clave]
    RegInput --> SetDefault[Asignar Regalo Fijo $500]
    SetDefault --> RegSave[Guardar en usuarios.txt]
    RegSave --> MenuP

    %% Login
    Login --> LogInput[Pedir Credenciales]
    LogInput --> LogCheck{¿Existe en usuarios.txt?}
    LogCheck -->|No| LogFail[Mostrar Error] --> MenuP
    LogCheck -->|Si| BankMenu[Mostrar Menu Banco]

    %% Menu de Banco (4 Opciones Actualizadas)
    BankMenu --> OpcionB{¿Que opcion elige?}

    %% 1. Retiro
    OpcionB -->|1. Retirar| Retiro[Pedir Monto a Retirar]
    Retiro --> CheckSaldo{¿Monto <= Saldo?}
    CheckSaldo -->|Si| DoRetiro[Restar saldo y actualizar archivo] --> BankMenu
    CheckSaldo -->|No| ErrorSaldo[Mostrar error] --> BankMenu

    %% 2. Deposito (Nueva Rama del Flujograma)
    OpcionB -->|2. Depositar| Deposito[Pedir Monto a Depositar]
    Deposito --> CheckDep{¿Monto > 0?}
    CheckDep -->|Si| DoDeposito[Sumar saldo y actualizar archivo] --> BankMenu
    CheckDep -->|No| ErrorDep[Mostrar error] --> BankMenu

    %% 3. Ahorcado
    OpcionB -->|3. Jugar Ahorcado| CheckCosto{¿Saldo >= $50?}
    CheckCosto -->|No| ErrorCosto[Mostrar error] --> BankMenu
    CheckCosto -->|Si| PayAhorcado[Restar $50 y actualizar archivo] --> Ahorcado[Jugar Ahorcado]

    %% Logica Ahorcado
    Ahorcado --> GameLoop{¿Intentos > 0 Y no Gano?}
    GameLoop -->|Si| Play[Pedir Letra y Validar] --> GameLoop
    GameLoop -->|No| CheckWin{¿Adivino la palabra?}
    CheckWin -->|Si| WinPrize[Sumar $150 y actualizar archivo] --> BankMenu
    CheckWin -->|No| LoseMsg[Mostrar palabra secreta] --> BankMenu

    %% 4. Volver
    OpcionB -->|4. Volver| MenuP

    %% Asignacion de clases esteticas
    class Start,Exit inicio;
    class MenuP,BankMenu,Ahorcado,Reg,RegInput,RegSave,LogInput,LogFail,Retiro,DoRetiro,ErrorSaldo,PayAhorcado,Play,WinPrize,LoseMsg,ErrorCosto,SetDefault,Deposito,DoDeposito,ErrorDep proceso;
    class OpcionP,LogCheck,OpcionB,CheckSaldo,CheckCosto,GameLoop,CheckWin,CheckDep decision;


