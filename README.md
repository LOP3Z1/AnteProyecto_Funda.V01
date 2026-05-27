# AnteProyecto_Funda.V01
Creación del anteproyecto de fundamentos.
graph TD
    %% Estilos Generales Optimizados (Alto Contraste y Colores Llamativos)
    classDef inicio fill:#2ecc71,stroke:#27ae60,stroke-width:3px,color:#fff,font-weight:bold;
    classDef proceso fill:#1f618d,stroke:#1a5276,stroke-width:2px,color:#fff,font-weight:bold;
    classDef decision fill:#f4d03f,stroke:#d4ac0d,stroke-width:2px,color:#1b2631,font-weight:bold;

    %% Flujo Principal
    Start([Inicio: main]) --> MenuP[Mostrar Menu Principal]
    
    %% Menú Principal
    MenuP --> OpciónP{¿Qué opción elige?}
    OpciónP -->|1. Registrarse| Reg[registrarUsuario]
    OpciónP -->|2. Iniciar Sesión| Login[iniciarSesion]
    OpciónP -->|3. Salir| Exit([Fin del Programa])
    
    %% Registro
    Reg --> RegInput[Pedir Usuario y Clave]
    RegInput --> RegSave[Guardar en usuarios.txt con $500]
    RegSave --> MenuP
    
    %% Login
    Login --> LogInput[Pedir Credenciales]
    LogInput --> LogCheck{¿Existe en usuarios.txt?}
    LogCheck -->|No| LogFail[Mostrar Error] --> MenuP
    LogCheck -->|Sí| BankMenu[Mostrar Menu Banco]
    
    %% Menú de Banco
    BankMenu --> OpciónB{¿Qué opción elige?}
    
    %% Retiro
    OpciónB -->|1. Retirar| Retiro[Pedir Monto]
    Retiro --> CheckSaldo{¿Monto <= Saldo?}
    CheckSaldo -->|Sí| DoRetiro[Restar saldo y entregar] --> BankMenu
    CheckSaldo -->|No| ErrorSaldo[Mostrar error] --> BankMenu
    
    %% Ahorcado
    OpciónB -->|2. Jugar Ahorcado| CheckCosto{¿Saldo >= $50?}
    CheckCosto -->|No| ErrorCosto[Mostrar error] --> BankMenu
    CheckCosto -->|Sí| PayAhorcado[Restar $50] --> Ahorcado[Jugar Ahorcado]
    
    %% Lógica Ahorcado
    Ahorcado --> GameLoop{¿Intentos > 0 Y no Ganó?}
    GameLoop -->|Sí| Play[Pedir Letra y Validar] --> GameLoop
    GameLoop -->|No| CheckWin{¿Adivinó la palabra?}
    CheckWin -->|Sí| WinPrize[Sumar $150 al Saldo] --> BankMenu
    CheckWin -->|No| LoseMsg[Mostrar palabra secreta] --> BankMenu
    
    %% Volver
    OpciónB -->|3. Volver| MenuP

    %% Asignación de clases estéticas
    class Start,Exit inicio;
    class MenuP,BankMenu,Ahorcado,Reg,RegInput,RegSave,LogInput,LogFail,Retiro,DoRetiro,ErrorSaldo,PayAhorcado,Play,WinPrize,LoseMsg,ErrorCosto proceso;
    class OpciónP,LogCheck,OpciónB,CheckSaldo,CheckCosto,GameLoop,CheckWin decision;
