# 🧪 PRUEBA DE DIAGRAMAS MERMAID

> **Instrucciones**: Abre este archivo en **Preview Mode** (Cmd+Shift+V en VSCode/Cursor)

---

---

## 1️⃣ Diagrama Simple - Flujo Básico
```mermaid
flowchart TD
    Start[Inicio] --> Check{Condición}
    Check -->|Sí| Yes[Opción SI]
    Check -->|No| No[Opción NO]
    Yes --> End[Fin]
    No --> End


---

## 2️⃣ Diagrama de Clases - ScalarConverter

```mermaid
classDiagram
    class ScalarConverter {
        -ScalarConverter()
        -ScalarConverter(const ScalarConverter&)
        -operator=(const ScalarConverter&)
        -~ScalarConverter()
        +convert(string literal)$ void
    }
```

---

## 3️⃣ Diagrama de Clases - Serializer

```mermaid
classDiagram
    class Data {
        <<struct>>
        +int numero
        +char letra
        +float decimal
    }
    
    class Serializer {
        <<static class>>
        -Serializer()
        +serialize(Data* ptr)$ unsigned long
        +deserialize(unsigned long raw)$ Data*
    }
    
    Serializer ..> Data : uses
```

---

## 4️⃣ Diagrama de Secuencia - Serialización

```mermaid
sequenceDiagram
    participant M as main
    participant S as Serializer
    participant Mem as Memoria
    
    M->>Mem: Crear Data original
    Mem-->>M: Objeto en 0x7fff...
    
    M->>S: serialize(&original)
    S-->>M: 140734799814816
    
    M->>S: deserialize(num)
    S-->>M: Data* = 0x7fff...
    
    M->>Mem: Acceder a datos
    Mem-->>M: {42, 'A', 3.14}
```

---

## 5️⃣ Diagrama de Flujo - ScalarConverter Convert

```mermaid
flowchart TD
    Start([INICIO]) --> Input[Recibir literal]
    Input --> Char{Es CHAR?}
    Char -->|SI| ProcessChar[Procesar como char]
    Char -->|NO| Int{Es INT?}
    Int -->|SI| ProcessInt[Procesar como int]
    Int -->|NO| Float{Es FLOAT?}
    Float -->|SI| ProcessFloat[Procesar como float]
    Float -->|NO| Double{Es DOUBLE?}
    Double -->|SI| ProcessDouble[Procesar como double]
    Double -->|NO| Invalid[Input invalido]
    
    ProcessChar --> Output[Imprimir 4 tipos]
    ProcessInt --> Output
    ProcessFloat --> Output
    ProcessDouble --> Output
    Invalid --> ImpossibleAll[Impossible para todos]
    
    Output --> End([FIN])
    ImpossibleAll --> End
    
    style Start fill:#90EE90
    style End fill:#90EE90
    style Invalid fill:#FFB6C1
    style ImpossibleAll fill:#FFB6C1
```

---

## 6️⃣ Diagrama con Colores - Tipos de Datos

```mermaid
flowchart LR
    A[Input String] --> B{Detectar Tipo}
    B -->|CHAR| C[char c]
    B -->|INT| D[int i]
    B -->|FLOAT| E[float f]
    B -->|DOUBLE| F[double d]
    
    C --> G[Convertir a 4 tipos]
    D --> G
    E --> G
    F --> G
    
    style C fill:#FFE4B5
    style D fill:#B0E0E6
    style E fill:#DDA0DD
    style F fill:#98FB98
```

---

## 7️⃣ Diagrama de Estado - Conversión

```mermaid
stateDiagram-v2
    [*] --> Deteccion
    Deteccion --> CHAR : checkIfChar()
    Deteccion --> INT : checkIfInteger()
    Deteccion --> FLOAT : checkIfFloatType()
    Deteccion --> DOUBLE : checkIfDoubleType()
    
    CHAR --> Convertir
    INT --> Convertir
    FLOAT --> Convertir
    DOUBLE --> Convertir
    
    Convertir --> Imprimir
    Imprimir --> [*]
```

---

## 8️⃣ Diagrama de Gantt - Proceso de Conversión

```mermaid
gantt
    title Proceso ScalarConverter
    dateFormat X
    axisFormat %s
    
    section Detección
    checkIfChar      :0, 1s
    checkIfInteger   :1s, 1s
    checkIfFloatType :2s, 1s
    checkIfDoubleType:3s, 1s
    
    section Conversión
    Parsear valor    :4s, 2s
    Validar rango    :6s, 1s
    
    section Output
    displayCharType  :7s, 1s
    displayIntType   :8s, 1s
    displayFloatType :9s, 1s
    displayDoubleType:10s, 1s
```

---

## 9️⃣ Diagrama de Memoria - Serialización

```mermaid
graph TB
    subgraph Memoria[Memoria RAM]
        Obj[Data original<br/>0x7fff5fbff8a0<br/>numero=42 letra=A decimal=3.14]
    end
    
    subgraph Variables[Variables]
        Ptr1[ptr: Data*<br/>0x7fff5fbff8a0]
        Num[serializado: ulong<br/>140734799814816]
        Ptr2[restaurado: Data*<br/>0x7fff5fbff8a0]
    end
    
    Ptr1 -.->|apunta a| Obj
    Ptr1 -->|serialize| Num
    Num -->|deserialize| Ptr2
    Ptr2 -.->|apunta a| Obj
    
    style Obj fill:#FFE4B5
    style Ptr1 fill:#87CEEB
    style Num fill:#90EE90
    style Ptr2 fill:#87CEEB
```

---

## 🔟 Diagrama ER - Relación entre Clases

```mermaid
erDiagram
    SERIALIZER ||--o{ DATA : "serializa/deserializa"
    
    SERIALIZER {
        static_method serialize
        static_method deserialize
    }
    
    DATA {
        int numero
        char letra
        float decimal
    }
```

---


