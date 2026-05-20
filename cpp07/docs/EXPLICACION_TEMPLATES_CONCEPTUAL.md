# 🎯 TEMPLATES EN C++ - Explicación Conceptual

## 🤔 ¿Qué es la Programación Genérica?

La **programación genérica** es escribir código que funciona con **cualquier tipo de datos**, sin tener que reescribir el mismo código para cada tipo.

### 💡 Analogía: La Receta de Tarta

Imagina que tienes una receta genérica de **"Tarta de `<sabor>`"**:

```
RECETA: Tarta de <sabor>
─────────────────────────
1. Mezclar harina, huevos, azúcar
2. Añadir <sabor>
3. Hornear 40 minutos

Esta receta sirve para:
• Tarta de <chocolate>
• Tarta de <manzana>
• Tarta de <queso>
• Tarta de <cualquier cosa>
```

**No necesitas una receta diferente para cada sabor** - solo cambias el ingrediente `<sabor>`.

Lo mismo pasa con los templates en C++:
- La **receta** = Template (plantilla)
- El **`<sabor>`** = Parámetro de tipo
- Las **tartas específicas** = Instancias concretas

---

## 🎯 El Problema que Resuelven los Templates

### ❌ SIN Templates: Código Repetitivo

Imagina que quieres una función para encontrar el menor de dos valores:

```cpp
// Para enteros
int menor(int a, int b) {
    return (a < b) ? a : b;
}

// Para doubles
double menor(double a, double b) {
    return (a < b) ? a : b;
}

// Para strings
string menor(string a, string b) {
    return (a < b) ? a : b;
}

// Para fechas
CFecha menor(CFecha a, CFecha b) {
    return (a < b) ? a : b;
}

// ❌ PROBLEMA: El mismo código repetido 1000 veces
// ❌ Solo cambia el TIPO, la lógica es IDÉNTICA
```

### ✅ CON Templates: Código Genérico

```cpp
// UNA SOLA función para TODOS los tipos
template<typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}

// Ahora puedes usarla con CUALQUIER tipo:
int x = menor(10, 20);           // Funciona con int
double y = menor(3.14, 2.71);    // Funciona con double
string s = menor("hola", "adiós"); // Funciona con string
CFecha f = menor(fecha1, fecha2); // Funciona con CFecha

// ✅ Una sola definición, infinitos tipos
```

---

## 🧠 ¿Cómo Funcionan los Templates?

### Concepto Clave: NO son funciones, son MOLDES

```
┌─────────────────────────────────────────────────────────┐
│  IMPORTANTE: Un template NO es código ejecutable       │
│                                                         │
│  Es un MOLDE que usa el compilador para GENERAR        │
│  código real cuando lo necesites                       │
└─────────────────────────────────────────────────────────┘
```

### Proceso de Compilación

```
1. ESCRIBES el template:
   ─────────────────────────────────────────────
   template<typename T>
   T menor(T a, T b) {
       return (a < b) ? a : b;
   }


2. USAS el template:
   ─────────────────────────────────────────────
   int x = menor(10, 20);      // a y b son int
   double y = menor(3.14, 2.71); // a y b son double


3. COMPILADOR genera funciones reales:
   ─────────────────────────────────────────────
   // El compilador automáticamente crea:
   
   int menor(int a, int b) {      // ← Generada para int
       return (a < b) ? a : b;
   }
   
   double menor(double a, double b) { // ← Generada para double
       return (a < b) ? a : b;
   }


4. EN EJECUCIÓN:
   ─────────────────────────────────────────────
   Solo existen las funciones CONCRETAS
   El template ya no existe
```

### Visualización del Proceso

```
TEMPLATE (Código Fuente):
┌──────────────────────────────┐
│ template<typename T>         │
│ T menor(T a, T b) {          │
│     return (a < b) ? a : b;  │
│ }                            │
└──────────────┬───────────────┘
               │
               │ COMPILADOR genera funciones
               │
               ↓
┌──────────────┴───────────────┬──────────────────────┐
│                              │                      │
↓                              ↓                      ↓
int menor(int, int)    double menor(double, double)  string menor(string, string)
     ↓                         ↓                           ↓
  [ejecutable]             [ejecutable]               [ejecutable]
```

---

## 📝 Sintaxis de Templates de Función

### Estructura Básica

```cpp
template<typename T>  // ← Declaración del parámetro de tipo
T nombreFuncion(T parametro1, T parametro2) {
    // Código que usa T
}
```

### Desglose:

```
┌───────────────────────────────────────────────────────────┐
│  template<typename T>                                     │
│  ─────────────────────                                    │
│  • template     → Palabra clave: "esto es un template"    │
│  • typename     → "T es un TIPO" (puede ser int, double...)│
│  • T            → Nombre del parámetro (puede ser A, B, X...)│
│                                                            │
│  NOTA: typename se puede escribir también como class:     │
│        template<class T>  ← Hace lo mismo                 │
└───────────────────────────────────────────────────────────┘
```

---

## 🎨 Ejemplos Conceptuales

### Ejemplo 1: Función swap genérica

```cpp
// SIN template (necesitas 3 funciones):
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

void swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}

// CON template (solo 1 función para todos):
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

**Uso:**
```cpp
int x = 5, y = 10;
swap(x, y);  // Compilador genera: swap(int&, int&)

double a = 3.14, b = 2.71;
swap(a, b);  // Compilador genera: swap(double&, double&)

string s1 = "hola", s2 = "adiós";
swap(s1, s2);  // Compilador genera: swap(string&, string&)
```

### Ejemplo 2: Función max genérica

```cpp
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Uso:
int mayor1 = max(10, 20);        // T = int
double mayor2 = max(3.14, 2.71); // T = double
char mayor3 = max('a', 'z');     // T = char
```

---

## 🔍 Deducción de Tipos

El compilador **deduce automáticamente** el tipo T:

```cpp
template<typename T>
T suma(T a, T b) {
    return a + b;
}

// El compilador deduce T automáticamente:
int x = suma(5, 10);      // T = int (deduce de 5 y 10)
double y = suma(3.14, 2.71); // T = double (deduce de 3.14 y 2.71)

// También puedes especificarlo explícitamente:
int z = suma<int>(5, 10);  // T = int (lo especificas tú)
```

### Reglas de Deducción

```
┌────────────────────────────────────────────────────────┐
│  REGLA 1: Todos los parámetros T deben ser iguales    │
│  ───────────────────────────────────────────────────   │
│                                                        │
│  ✅ Correcto:                                          │
│     suma(5, 10)        // T = int para ambos           │
│                                                        │
│  ❌ Error:                                             │
│     suma(5, 3.14)      // T = int o double?            │
│                        // ¡AMBIGÜEDAD!                 │
│                                                        │
│  Solución:                                             │
│     suma<double>(5, 3.14)  // Especificar T            │
│     suma(5.0, 3.14)        // Hacer ambos double       │
│                                                        │
└────────────────────────────────────────────────────────┘
```

---

## 🎯 Múltiples Parámetros de Tipo

Puedes tener varios parámetros:

```cpp
template<typename T1, typename T2>
void mostrar(T1 primero, T2 segundo) {
    cout << primero << " - " << segundo << endl;
}

// Uso:
mostrar(42, "hola");        // T1=int, T2=const char*
mostrar(3.14, 100);         // T1=double, T2=int
mostrar("edad:", 25);       // T1=const char*, T2=int
```

### Ejemplo Práctico: pair genérico

```cpp
template<typename T1, typename T2>
struct Par {
    T1 primero;
    T2 segundo;
    
    Par(T1 p, T2 s) : primero(p), segundo(s) {}
};

// Uso:
Par<int, string> p1(42, "respuesta");
Par<double, char> p2(3.14, 'π');
Par<string, string> p3("nombre", "Juan");
```

---

## 🔧 Especialización de Templates

A veces necesitas que el template se comporte **diferente para un tipo específico**.

### Concepto

```
┌─────────────────────────────────────────────────────┐
│  Template General → Funciona para TODOS los tipos   │
│  Especialización  → Versión ESPECIAL para UN tipo   │
└─────────────────────────────────────────────────────┘
```

### Ejemplo: Comparar cadenas

```cpp
// TEMPLATE GENERAL (funciona para casi todo)
template<typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}

// ESPECIALIZACIÓN para char* (cadenas C)
template<>
char* menor<char*>(char* a, char* b) {
    return (strcmp(a, b) < 0) ? a : b;
}

// Uso:
int x = menor(10, 20);           // Usa template general
double y = menor(3.14, 2.71);    // Usa template general
char* s = menor("hola", "adiós"); // Usa ESPECIALIZACIÓN
```

### ¿Por qué?

```
SIN especialización:
──────────────────────────────────
char* cad1 = "hola";
char* cad2 = "adiós";
menor(cad1, cad2);  // Compara DIRECCIONES, no contenido
                    // ❌ INCORRECTO

CON especialización:
──────────────────────────────────
char* cad1 = "hola";
char* cad2 = "adiós";
menor(cad1, cad2);  // Usa strcmp
                    // ✅ CORRECTO
```

---

## 🎭 Visualización Completa: Template en Acción

```
CÓDIGO FUENTE:
═══════════════════════════════════════════════════
template<typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}

int main() {
    int x = menor(10, 20);
    double y = menor(3.14, 2.71);
    string s = menor("a", "b");
}


PROCESO DE COMPILACIÓN:
═══════════════════════════════════════════════════

1. Compilador ve: menor(10, 20)
   ├─ Busca función menor(int, int)
   ├─ No existe
   ├─ Busca template menor<T>
   ├─ Encuentra el template
   ├─ Deduce: T = int (porque 10 y 20 son int)
   └─ GENERA automáticamente:
      
      int menor(int a, int b) {
          return (a < b) ? a : b;
      }

2. Compilador ve: menor(3.14, 2.71)
   ├─ Busca función menor(double, double)
   ├─ No existe
   ├─ Busca template menor<T>
   ├─ Encuentra el template
   ├─ Deduce: T = double
   └─ GENERA automáticamente:
      
      double menor(double a, double b) {
          return (a < b) ? a : b;
      }

3. Compilador ve: menor("a", "b")
   ├─ Deduce: T = const char*
   └─ GENERA automáticamente:
      
      const char* menor(const char* a, const char* b) {
          return (a < b) ? a : b;
      }


CÓDIGO EJECUTABLE FINAL:
═══════════════════════════════════════════════════
// El template YA NO EXISTE en el ejecutable
// Solo existen las funciones concretas:

int menor(int a, int b) { ... }
double menor(double a, double b) { ... }
const char* menor(const char* a, const char* b) { ... }

int main() {
    int x = menor(10, 20);      // Llama a int menor(int, int)
    double y = menor(3.14, 2.71); // Llama a double menor(double, double)
    string s = menor("a", "b");   // Llama a const char* menor(...)
}
```

---

## 📚 Organización del Código

### Problema Especial de los Templates

```
┌──────────────────────────────────────────────────────┐
│  IMPORTANTE: Los templates NO son código normal      │
│                                                      │
│  • NO se compilan por separado                       │
│  • El compilador necesita ver TODA la definición     │
│    cuando genera una instancia                       │
└──────────────────────────────────────────────────────┘
```

### ❌ Lo que NO funciona (como con funciones normales)

```cpp
// menor.h
template<typename T>
T menor(T a, T b);  // Solo declaración

// menor.cpp
template<typename T>
T menor(T a, T b) {  // Definición separada
    return (a < b) ? a : b;
}

// main.cpp
#include "menor.h"
int main() {
    int x = menor(10, 20);  // ❌ ERROR en enlazado
}

// ¿Por qué falla?
// El compilador compila main.cpp, ve menor.h (solo declaración)
// No puede generar menor(int, int) porque no ve la definición
```

### ✅ Solución 1: Modelo de Inclusión (RECOMENDADO)

Poner TODO en el .h:

```cpp
// menor.h
#ifndef MENOR_H
#define MENOR_H

template<typename T>
T menor(T a, T b) {  // Declaración Y definición
    return (a < b) ? a : b;
}

#endif
```

```cpp
// main.cpp
#include "menor.h"  // Incluye la definición completa

int main() {
    int x = menor(10, 20);  // ✅ Funciona
}
```

### ✅ Solución 2: .h + .cpp con inclusión del .cpp

```cpp
// menor.h
#ifndef MENOR_H
#define MENOR_H

template<typename T>
T menor(T a, T b);  // Declaración

#include "menor.cpp"  // ← Incluye el .cpp (inusual pero válido)
#endif
```

```cpp
// menor.cpp (NO se compila separadamente)
template<typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}
```

```cpp
// main.cpp
#include "menor.h"  // Indirectamente incluye menor.cpp

int main() {
    int x = menor(10, 20);  // ✅ Funciona
}
```

---

## 🎯 Requisitos para usar Templates

```
╔════════════════════════════════════════════════════════╗
║  Para que un tipo T funcione con un template,         ║
║  debe cumplir los REQUISITOS del template              ║
╠════════════════════════════════════════════════════════╣
║                                                        ║
║  Ejemplo: menor(T a, T b)                              ║
║  ─────────────────────────────────────────────────     ║
║  Requisito: T debe tener operador <                    ║
║                                                        ║
║  ✅ int, double, char → tienen <                       ║
║  ✅ string → tiene <                                   ║
║  ✅ CFecha → si defines operator<                      ║
║  ❌ MiClase → si NO defines operator<                  ║
║                                                        ║
╚════════════════════════════════════════════════════════╝
```

### Ejemplo con Clase Propia

```cpp
class CFecha {
private:
    int dia, mes, anio;
public:
    CFecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
    
    // ✅ Definir operator< para poder usar menor()
    bool operator<(const CFecha& otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes != otra.mes) return mes < otra.mes;
        return dia < otra.dia;
    }
};

// Ahora SÍ funciona:
CFecha f1(10, 5, 2023);
CFecha f2(15, 5, 2023);
CFecha menor_fecha = menor(f1, f2);  // ✅ Funciona
```

---

## 💡 Ventajas de los Templates

```
✅ CÓDIGO REUTILIZABLE
   ─────────────────────────────────────
   Una sola implementación para muchos tipos

✅ TYPE-SAFE (Seguro de tipos)
   ─────────────────────────────────────
   El compilador verifica tipos en compile-time

✅ SIN OVERHEAD EN RUNTIME
   ─────────────────────────────────────
   No hay costo en ejecución (todo se resuelve en compilación)

✅ OPTIMIZACIÓN
   ─────────────────────────────────────
   El compilador puede optimizar cada instancia

✅ FLEXIBILIDAD
   ─────────────────────────────────────
   Funciona con tipos que aún no existen
```

---

## ⚠️ Desventajas de los Templates

```
❌ TIEMPO DE COMPILACIÓN
   ─────────────────────────────────────
   Genera código para cada tipo → más lento compilar

❌ TAMAÑO DEL EJECUTABLE
   ─────────────────────────────────────
   Múltiples instancias → ejecutable más grande

❌ MENSAJES DE ERROR COMPLEJOS
   ─────────────────────────────────────
   Los errores de template son difíciles de leer

❌ TODO EN HEADERS
   ─────────────────────────────────────
   Definición completa debe estar visible
```

---

## 🎓 Casos de Uso Reales

### 1. Contenedores (STL)

```cpp
// vector es un template
template<typename T>
class vector {
    // ...
};

vector<int> numeros;
vector<string> nombres;
vector<CFecha> fechas;
```

### 2. Algoritmos (STL)

```cpp
// sort es un template
template<typename Iterator>
void sort(Iterator primero, Iterator ultimo);

vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end());  // Ordena ints

vector<string> s = {"c", "a", "b"};
sort(s.begin(), s.end());  // Ordena strings
```

### 3. Funciones Utilitarias

```cpp
template<typename T>
void imprimir(const T& valor) {
    cout << valor << endl;
}

imprimir(42);        // int
imprimir(3.14);      // double
imprimir("hola");    // const char*
```

---

## 🔑 Resumen Conceptual

```
┌──────────────────────────────────────────────────────┐
│             ¿QUÉ SON LOS TEMPLATES?                  │
├──────────────────────────────────────────────────────┤
│                                                      │
│  MOLDES que permiten escribir código GENÉRICO       │
│                                                      │
│  • NO son código ejecutable                          │
│  • Son instrucciones para el COMPILADOR              │
│  • Generan código real cuando se USAN                │
│  • Permiten REUTILIZACIÓN de código                  │
│                                                      │
│  SINTAXIS BÁSICA:                                    │
│  ──────────────────────────────────────────────────  │
│  template<typename T>                                │
│  T funcion(T parametro) {                            │
│      // código que usa T                             │
│  }                                                   │
│                                                      │
│  PROCESO:                                            │
│  ──────────────────────────────────────────────────  │
│  1. Escribes el template (molde)                     │
│  2. Usas el template con un tipo específico          │
│  3. Compilador GENERA función concreta               │
│  4. En ejecución: solo existe código concreto        │
│                                                      │
│  EJEMPLO COMPLETO:                                   │
│  ──────────────────────────────────────────────────  │
│  // Template (molde)                                 │
│  template<typename T>                                │
│  T menor(T a, T b) {                                 │
│      return (a < b) ? a : b;                         │
│  }                                                   │
│                                                      │
│  // Uso                                              │
│  int x = menor(10, 20);     // Genera menor(int, int)│
│  double y = menor(3.14, 2.71); // Genera menor(double, double)│
│                                                      │
│  VENTAJA PRINCIPAL:                                  │
│  ──────────────────────────────────────────────────  │
│  Escribes UNA VEZ, funciona con INFINITOS tipos      │
│                                                      │
└──────────────────────────────────────────────────────┘
```

---

**Autor**: CPP Module 07  
**Fecha**: Octubre 2025  
**Tema**: Templates - Programación Genérica en C++98

