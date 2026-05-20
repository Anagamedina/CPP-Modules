# 🎨 RESUMEN VISUAL - Conceptos ex00

## 1️⃣ ¿Qué es un template?

```
┌──────────────────────────────────────────────────────────┐
│  TEMPLATE = MOLDE/RECETA                                 │
│                                                          │
│  Como una receta de galletas:                            │
│  ┌────────────────────────────────────────────┐          │
│  │ Receta de Galletas de <sabor>              │          │
│  │ 1. Mezclar harina + azúcar                 │          │
│  │ 2. Añadir <sabor>                          │          │
│  │ 3. Hornear                                 │          │
│  └────────────────────────────────────────────┘          │
│                                                          │
│  Esta receta sirve para:                                 │
│  • Galletas de <chocolate>                               │
│  • Galletas de <vainilla>                                │
│  • Galletas de <naranja>                                 │
│                                                          │
│  template<typename T> funciona igual:                    │
│  • T = chocolate → swap de chocolate                     │
│  • T = int → swap de int                                 │
│  • T = string → swap de string                           │
└──────────────────────────────────────────────────────────┘
```

---

## 2️⃣ `template<typename T>` explicado

```
template<typename T>
    ↓       ↓       ↓
    │       │       └─ Nombre del parámetro (puede ser A, B, X, Tipo, etc.)
    │       └─ "T es un TIPO" (int, double, string...)
    └─ "Esto es un molde/plantilla"


EJEMPLOS DE USO:
────────────────────────────────────────────────────────────

int a = 5, b = 10;
swap(a, b);
         ↓
El compilador ve: "a y b son int"
         ↓
Genera: template<typename int> → swap para int


string s1 = "hi", s2 = "bye";
swap(s1, s2);
         ↓
El compilador ve: "s1 y s2 son string"
         ↓
Genera: template<typename string> → swap para string
```

---

## 3️⃣ `T const &` desglosado

```
T const & min(T const & a, T const & b)
│   │   │      │   │   │ │      │
│   │   │      │   │   │ │      └─ nombre del parámetro
│   │   │      │   │   │ └─ referencia (&)
│   │   │      │   │   └─ constante (no modificable)
│   │   │      │   └─ tipo T
│   │   │      └─ primer parámetro
│   │   └─ referencia (no copia)
│   └─ constante (no modificable)
│
└─ tipo de retorno


VISUALIZACIÓN:
────────────────────────────────────────────────────────────

SIN const & (hace COPIA):
───────────────────────────────────
    string s1 = "hola mundo";
    string s2 = "adios mundo";
    
    min(s1, s2)
        ↓
    Se crean COPIAS de s1 y s2
    [LENTO, usa mucha memoria]


CON const & (pasa REFERENCIA):
───────────────────────────────────
    string s1 = "hola mundo";
    string s2 = "adios mundo";
    
    min(s1, s2)
        ↓
    Pasa las DIRECCIONES de s1 y s2
    [RÁPIDO, no usa memoria extra]
    
    
ANALOGÍA:
───────────────────────────────────
Sin &:     "Dame una COPIA del libro"
           (tienes que fotocopiar todo)
           
Con &:     "Dame la DIRECCIÓN donde está el libro"
           (solo compartes la ubicación)
```

---

## 4️⃣ El operador `::`

```
╔══════════════════════════════════════════════════════════╗
║              ¿QUÉ ES :: ?                                ║
╠══════════════════════════════════════════════════════════╣
║                                                          ║
║  :: = Operador de Resolución de Ámbito                   ║
║                                                          ║
║  Le dice al compilador:                                  ║
║  "Busca esta función en el ámbito GLOBAL"                ║
║                                                          ║
╚══════════════════════════════════════════════════════════╝


PROBLEMA: std TAMBIÉN tiene swap, min y max
════════════════════════════════════════════════════════════

#include <algorithm>  ← Incluye std::swap, std::min, std::max

template<typename T>
void swap(T& a, T& b) {  ← TU función (global)
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 5, b = 10;
    
    swap(a, b);      ← ¿Cuál swap? ¡AMBIGUO!
    ::swap(a, b);    ← TU swap (global) ✅
    std::swap(a, b); ← swap de std ✅
}


VISUALIZACIÓN DE ÁMBITOS:
════════════════════════════════════════════════════════════

              MUNDO C++
    ┌──────────────────────────────┐
    │   ÁMBITO GLOBAL              │
    │   ┌──────────────────┐       │
    │   │ ::swap           │ ←┐    │
    │   │ ::min            │  │    │
    │   │ ::max            │  │    │
    │   └──────────────────┘  │    │
    │                         │    │
    │   namespace std {       │    │
    │   ┌──────────────────┐  │    │
    │   │ std::swap        │  │    │
    │   │ std::min         │  │    │
    │   │ std::max         │  │    │
    │   └──────────────────┘  │    │
    │   }                     │    │
    └─────────────────────────┼────┘
                              │
                              │
    ::swap dice: "Usa este" ──┘
```

---

## 5️⃣ Ejemplo COMPLETO paso a paso

```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5, y = 10;
    ::swap(x, y);
}
```

### 📍 PASO 1: El compilador ve `::swap(x, y)`

```
┌────────────────────────────┐
│ x = 5  (tipo: int)         │
│ y = 10 (tipo: int)         │
└────────────────────────────┘
         ↓
Compilador: "x e y son int, entonces T = int"
```

### 📍 PASO 2: Genera la función concreta

```
El compilador GENERA automáticamente:

void swap(int& a, int& b) {  // T = int
    int temp = a;            // temp es int
    a = b;
    b = temp;
}
```

### 📍 PASO 3: Ejecuta el código

```
ANTES:
┌─────────┬─────────┐
│ x = 5   │ y = 10  │
└─────────┴─────────┘

DURANTE swap(x, y):
┌─────────────────────┐
│ temp = 5  (copia x) │
│ x = 10    (x toma y)│
│ y = 5     (y toma temp)│
└─────────────────────┘

DESPUÉS:
┌─────────┬─────────┐
│ x = 10  │ y = 5   │
└─────────┴─────────┘
```

---

## 6️⃣ Diferencia entre & y const &

```
╔════════════════════════════════════════════════════════╗
║           SWAP usa &  (no const)                       ║
╠════════════════════════════════════════════════════════╣
║                                                        ║
║  void swap(T& a, T& b)                                 ║
║              ↑      ↑                                  ║
║              └──────┴─ SIN const (puede modificar)     ║
║                                                        ║
║  ¿Por qué?                                             ║
║  Porque swap NECESITA modificar a y b                  ║
║                                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║         MIN y MAX usan const &                         ║
╠════════════════════════════════════════════════════════╣
║                                                        ║
║  T const & min(T const & a, T const & b)               ║
║                    ↑           ↑                       ║
║                    └───────────┴─ CON const            ║
║                                                        ║
║  ¿Por qué?                                             ║
║  Porque min/max solo LEEN a y b (no modifican)         ║
║                                                        ║
╚════════════════════════════════════════════════════════╝


EJEMPLO VISUAL:
────────────────────────────────────────────────────────

SWAP (modifica):
    int a = 5, b = 10;
    swap(a, b);
         ↓
    a = 10, b = 5  ← ¡CAMBIARON!

MIN (no modifica):
    int a = 5, b = 10;
    int resultado = min(a, b);
         ↓
    a = 5, b = 10  ← ¡NO CAMBIARON!
    resultado = 5
```

---

## 🎯 TABLA RESUMEN FINAL

```
╔════════════════╦═══════════════════════════════════════════╗
║   CONCEPTO     ║             SIGNIFICADO                   ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ template       ║ Molde/plantilla para generar código      ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ typename T     ║ T es un parámetro de TIPO                 ║
║                ║ (int, double, string, etc.)               ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ T&             ║ Referencia a T (puede modificar)          ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ T const &      ║ Referencia constante a T                  ║
║                ║ (no puede modificar, no copia)            ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ ::             ║ Operador de ámbito global                 ║
║                ║ "Usa la función global, no la de std"     ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ ::swap         ║ TU función swap (la que definiste)        ║
║                ║                                           ║
╠════════════════╬═══════════════════════════════════════════╣
║                ║                                           ║
║ std::swap      ║ Función swap de la biblioteca estándar    ║
║                ║                                           ║
╚════════════════╩═══════════════════════════════════════════╝
```

---

## 💡 Mini-Test de Comprensión

### Pregunta 1:
```cpp
template<typename T>
void swap(T& a, T& b);
```
¿Swap es un template?
- ✅ SÍ (tiene template<typename T>)

### Pregunta 2:
```cpp
template<typename T>
T const & min(T const & a, T const & b);
```
¿Min puede modificar a o b?
- ❌ NO (tienen const)

### Pregunta 3:
```cpp
int x = 5, y = 10;
::swap(x, y);
```
¿Qué hace `::`?
- ✅ Llama a TU función swap (no std::swap)

### Pregunta 4:
```cpp
string s1 = "hola", s2 = "mundo";
min(s1, s2);
```
¿Se copian s1 y s2?
- ❌ NO (usa const &, pasa referencias)

---

**¡Ahora deberías entender todos los conceptos!** 🎉



















