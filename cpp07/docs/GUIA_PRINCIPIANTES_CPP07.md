# 🎓 GUÍA PARA PRINCIPIANTES - CPP Module 07

## 📖 ¿Qué vas a aprender?

En este módulo aprenderás a usar **templates** (plantillas) en C++98. Los templates te permiten escribir código que funciona con **cualquier tipo de datos**.

---

## 🎯 EJERCICIO 00: Funciones Template Básicas

### 📝 ¿Qué tienes que hacer?

Implementar 3 funciones template simples:
- `swap`: Intercambia dos valores
- `min`: Devuelve el menor de dos valores  
- `max`: Devuelve el mayor de dos valores

### 💡 Concepto Clave

En lugar de escribir una función para cada tipo:

```cpp
// ❌ Forma antigua: repetitiva
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

// ... ¡Repetir para cada tipo!
```

Escribes **UNA SOLA** función template:

```cpp
// ✅ Forma moderna: una función para todos los tipos
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

### 📂 Estructura de Archivos

```
ex00/
├── whatever.hpp    ← Aquí van las funciones template
├── main.cpp        ← Programa de prueba
└── Makefile
```

### ✍️ Paso 1: Crear `whatever.hpp`

```cpp
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// ==========================================
// SWAP: Intercambia dos valores
// ==========================================
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ==========================================
// MIN: Devuelve el menor de dos valores
// ==========================================
template<typename T>
T min(T const & a, T const & b) {
    return (a < b) ? a : b;
}

// ==========================================
// MAX: Devuelve el mayor de dos valores
// ==========================================
template<typename T>
T max(T const & a, T const & b) {
    return (a > b) ? a : b;
}

#endif
```

### 📋 Explicación Línea por Línea

```cpp
template<typename T>
// ↑ Esto dice: "Esta es una función genérica"
//    T puede ser cualquier tipo (int, double, string, etc.)

void swap(T& a, T& b) {
//         ↑    ↑
//    Referencias (se modifican los originales)

    T temp = a;
    // ↑ Crea una variable temporal del mismo tipo T
    
    a = b;     // a toma el valor de b
    b = temp;  // b toma el valor original de a
}
```

### 🧪 Paso 2: Crear `main.cpp` para probar

```cpp
#include <iostream>
#include "whatever.hpp"

int main() {
    std::cout << "=== TEST 1: SWAP con int ===" << std::endl;
    int a = 2;
    int b = 3;
    
    std::cout << "Antes:  a = " << a << ", b = " << b << std::endl;
    ::swap(a, b);  // :: significa "usa la función global, no la de std"
    std::cout << "Después: a = " << a << ", b = " << b << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== TEST 2: MIN y MAX con int ===" << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== TEST 3: SWAP con string ===" << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    
    std::cout << "Antes:  c = " << c << ", d = " << d << std::endl;
    ::swap(c, d);
    std::cout << "Después: c = " << c << ", d = " << d << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== TEST 4: MIN y MAX con string ===" << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
    
    return 0;
}
```

### 📊 Salida Esperada

```
=== TEST 1: SWAP con int ===
Antes:  a = 2, b = 3
Después: a = 3, b = 2

=== TEST 2: MIN y MAX con int ===
min(a, b) = 2
max(a, b) = 3

=== TEST 3: SWAP con string ===
Antes:  c = chaine1, d = chaine2
Después: c = chaine2, d = chaine1

=== TEST 4: MIN y MAX con string ===
min(c, d) = chaine1
max(c, d) = chaine2
```

### 🔍 ¿Cómo Funciona?

```
Cuando escribes:
─────────────────────────────────────
int a = 5, b = 10;
swap(a, b);

El compilador ve:
─────────────────────────────────────
• a y b son tipo int
• Genera automáticamente:
  
  void swap(int& a, int& b) {
      int temp = a;
      a = b;
      b = temp;
  }

Cuando escribes:
─────────────────────────────────────
string s1 = "hola", s2 = "adiós";
swap(s1, s2);

El compilador ve:
─────────────────────────────────────
• s1 y s2 son tipo string
• Genera automáticamente:
  
  void swap(string& a, string& b) {
      string temp = a;
      a = b;
      b = temp;
  }
```

### ⚠️ Errores Comunes

```cpp
// ❌ ERROR: No usar ::
int a = 5, b = 10;
swap(a, b);  // ¡Puede llamar a std::swap!

// ✅ CORRECTO: Usar ::
::swap(a, b);  // Llama a tu función

// ❌ ERROR: Tipos diferentes
int a = 5;
double b = 10.5;
swap(a, b);  // Error: T no puede ser int y double a la vez

// ✅ CORRECTO: Mismo tipo
int a = 5;
int b = 10;
swap(a, b);  // OK: T = int para ambos
```

---

## 🎯 EJERCICIO 01: Función iter

### 📝 ¿Qué tienes que hacer?

Implementar una función template `iter` que aplica una función a cada elemento de un array.

### 💡 Concepto Clave

```cpp
// Imagina que tienes un array:
int numeros[] = {1, 2, 3, 4, 5};

// Y quieres imprimir cada número
// En lugar de escribir:
for (int i = 0; i < 5; i++) {
    imprimir(numeros[i]);
}

// Usas iter:
iter(numeros, 5, imprimir);  // ¡Más elegante!
```

### 📂 Estructura de Archivos

```
ex01/
├── iter.hpp        ← Función template iter
├── main.cpp        ← Programa de prueba
└── Makefile
```

### ✍️ Paso 1: Crear `iter.hpp`

```cpp
#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>  // Para size_t

// ==========================================
// ITER: Aplica una función a cada elemento
// ==========================================
template<typename T, typename F>
void iter(T* array, size_t length, F function) {
    if (array == NULL || function == NULL)
        return;
    
    for (size_t i = 0; i < length; i++) {
        function(array[i]);
    }
}

#endif
```

### 📋 Explicación Detallada

```cpp
template<typename T, typename F>
//              ↑         ↑
//              |         └─ Tipo de la función
//              └─ Tipo de los elementos del array

void iter(T* array, size_t length, F function) {
//        ↑         ↑              ↑
//        |         |              └─ Función a aplicar
//        |         └─ Número de elementos
//        └─ Puntero al array

    // Aplicar la función a cada elemento
    for (size_t i = 0; i < length; i++) {
        function(array[i]);
        //       ↑
        //       └─ Pasar cada elemento a la función
    }
}
```

### 🧪 Paso 2: Crear `main.cpp`

```cpp
#include <iostream>
#include <string>
#include "iter.hpp"

// ==========================================
// FUNCIONES DE PRUEBA
// ==========================================

// Función que imprime un int
void printInt(int const & x) {
    std::cout << x << " ";
}

// Función que imprime un string
void printString(std::string const & s) {
    std::cout << s << " ";
}

// Función que incrementa un int
void incrementInt(int & x) {
    x++;
}

// Función que duplica un int
void doubleInt(int & x) {
    x *= 2;
}

int main() {
    std::cout << "=== TEST 1: Imprimir array de enteros ===" << std::endl;
    int numeros[] = {1, 2, 3, 4, 5};
    size_t len = 5;
    
    std::cout << "Array original: ";
    ::iter(numeros, len, printInt);
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 2: Incrementar cada elemento ===" << std::endl;
    ::iter(numeros, len, incrementInt);
    std::cout << "Array después de incrementar: ";
    ::iter(numeros, len, printInt);
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 3: Duplicar cada elemento ===" << std::endl;
    ::iter(numeros, len, doubleInt);
    std::cout << "Array después de duplicar: ";
    ::iter(numeros, len, printInt);
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 4: Array de strings ===" << std::endl;
    std::string palabras[] = {"Hola", "Mundo", "C++", "Templates"};
    std::cout << "Palabras: ";
    ::iter(palabras, 4, printString);
    std::cout << std::endl;
    
    return 0;
}
```

### 📊 Salida Esperada

```
=== TEST 1: Imprimir array de enteros ===
Array original: 1 2 3 4 5 

=== TEST 2: Incrementar cada elemento ===
Array después de incrementar: 2 3 4 5 6 

=== TEST 3: Duplicar cada elemento ===
Array después de duplicar: 4 6 8 10 12 

=== TEST 4: Array de strings ===
Palabras: Hola Mundo C++ Templates 
```

### 🔍 ¿Cómo Funciona iter?

```
Llamada:
─────────────────────────────────────
int nums[] = {1, 2, 3};
iter(nums, 3, printInt);

Proceso:
─────────────────────────────────────
Iteración 1: i = 0
  → function(nums[0])  // printInt(1)
  → Imprime: 1

Iteración 2: i = 1
  → function(nums[1])  // printInt(2)
  → Imprime: 2

Iteración 3: i = 2
  → function(nums[2])  // printInt(3)
  → Imprime: 3
```

### 💡 Versión Avanzada (Opcional)

```cpp
// Si quieres practicar más, puedes hacer que iter
// también funcione con funciones const:

template<typename T>
void iter(T* array, size_t length, void (*f)(T&)) {
    for (size_t i = 0; i < length; i++) {
        f(array[i]);
    }
}

template<typename T>
void iter(T* array, size_t length, void (*f)(T const &)) {
    for (size_t i = 0; i < length; i++) {
        f(array[i]);
    }
}
```

---

## 🎯 EJERCICIO 02: Clase Template Array

### 📝 ¿Qué tienes que hacer?

Crear una clase template `Array<T>` que gestione un array dinámico de cualquier tipo.

### 💡 Concepto Clave

```cpp
// En lugar de crear una clase para cada tipo:
class IntArray { ... };     // Para int
class DoubleArray { ... };  // Para double
class StringArray { ... };  // Para string

// Creas UNA clase template que funciona con todos:
template<typename T>
class Array { ... };

// Uso:
Array<int> nums(10);        // Array de 10 ints
Array<double> decimals(5);  // Array de 5 doubles
Array<string> words(3);     // Array de 3 strings
```

### 📂 Estructura de Archivos

```
ex02/
├── Array.hpp       ← Clase template Array
├── main.cpp        ← Programa de prueba
└── Makefile
```

### ✍️ Paso 1: Crear `Array.hpp`

```cpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>  // Para size_t

template<typename T>
class Array {
private:
    T*      _elements;  // Puntero al array dinámico
    size_t  _size;      // Tamaño del array
    
public:
    // ==========================================
    // CONSTRUCTOR POR DEFECTO (array vacío)
    // ==========================================
    Array() : _elements(NULL), _size(0) {
    }
    
    // ==========================================
    // CONSTRUCTOR CON TAMAÑO
    // ==========================================
    Array(unsigned int n) : _elements(new T[n]()), _size(n) {
        // new T[n]() inicializa todos los elementos a 0/vacío
    }
    
    // ==========================================
    // CONSTRUCTOR DE COPIA
    // ==========================================
    Array(Array const & other) : _elements(NULL), _size(0) {
        *this = other;
    }
    
    // ==========================================
    // OPERADOR DE ASIGNACIÓN
    // ==========================================
    Array & operator=(Array const & other) {
        if (this != &other) {
            // Liberar memoria antigua
            delete[] _elements;
            
            // Copiar tamaño
            _size = other._size;
            
            // Crear nuevo array
            if (_size > 0) {
                _elements = new T[_size];
                // Copiar elementos
                for (size_t i = 0; i < _size; i++) {
                    _elements[i] = other._elements[i];
                }
            } else {
                _elements = NULL;
            }
        }
        return *this;
    }
    
    // ==========================================
    // DESTRUCTOR
    // ==========================================
    ~Array() {
        delete[] _elements;
    }
    
    // ==========================================
    // OPERADOR [] (acceso por índice)
    // ==========================================
    T & operator[](size_t index) {
        if (index >= _size) {
            throw std::exception();
        }
        return _elements[index];
    }
    
    const T & operator[](size_t index) const {
        if (index >= _size) {
            throw std::exception();
        }
        return _elements[index];
    }
    
    // ==========================================
    // SIZE: Devuelve el tamaño del array
    // ==========================================
    size_t size() const {
        return _size;
    }
};

#endif
```

### 📋 Explicación de Cada Parte

#### 1️⃣ Constructor con Tamaño

```cpp
Array(unsigned int n) : _elements(new T[n]()), _size(n) {
//                                       ↑↑
//                                       └┴─ () inicializa a 0
}

Ejemplos:
─────────────────────────────────────
Array<int> nums(5);
// Crea: [0, 0, 0, 0, 0]

Array<double> decimals(3);
// Crea: [0.0, 0.0, 0.0]

Array<string> words(2);
// Crea: ["", ""]
```

#### 2️⃣ Constructor de Copia

```cpp
Array(Array const & other) {
    *this = other;  // Usa el operador de asignación
}

Ejemplo:
─────────────────────────────────────
Array<int> original(3);
original[0] = 10;
original[1] = 20;
original[2] = 30;

Array<int> copia(original);  // Copia profunda
// copia tiene su propia memoria con [10, 20, 30]
```

#### 3️⃣ Operador de Asignación

```cpp
Array & operator=(Array const & other) {
    // 1. Verificar auto-asignación
    if (this != &other) {
        // 2. Liberar memoria antigua
        delete[] _elements;
        
        // 3. Copiar tamaño
        _size = other._size;
        
        // 4. Crear nuevo array
        _elements = new T[_size];
        
        // 5. Copiar cada elemento
        for (size_t i = 0; i < _size; i++) {
            _elements[i] = other._elements[i];
        }
    }
    return *this;
}
```

#### 4️⃣ Operador [] con Protección

```cpp
T & operator[](size_t index) {
    if (index >= _size) {
        throw std::exception();  // Lanza excepción si fuera de rango
    }
    return _elements[index];
}

Ejemplo:
─────────────────────────────────────
Array<int> nums(3);
nums[0] = 10;   // ✅ OK
nums[1] = 20;   // ✅ OK
nums[2] = 30;   // ✅ OK
nums[3] = 40;   // ❌ EXCEPCIÓN (fuera de rango)
```

### 🧪 Paso 2: Crear `main.cpp`

```cpp
#include <iostream>
#include <string>
#include "Array.hpp"

#define MAX_VAL 10

int main() {
    std::cout << "=== TEST 1: Array vacío ===" << std::endl;
    Array<int> empty;
    std::cout << "Tamaño: " << empty.size() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== TEST 2: Array de enteros ===" << std::endl;
    Array<int> numbers(MAX_VAL);
    std::cout << "Tamaño: " << numbers.size() << std::endl;
    
    // Llenar con valores
    for (unsigned int i = 0; i < MAX_VAL; i++) {
        numbers[i] = i * 10;
    }
    
    // Mostrar valores
    std::cout << "Valores: ";
    for (unsigned int i = 0; i < MAX_VAL; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 3: Copiar array ===" << std::endl;
    Array<int> copy(numbers);
    std::cout << "Tamaño copia: " << copy.size() << std::endl;
    std::cout << "Valores copia: ";
    for (unsigned int i = 0; i < copy.size(); i++) {
        std::cout << copy[i] << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 4: Modificar original (copia no cambia) ===" << std::endl;
    numbers[0] = 999;
    std::cout << "Original[0]: " << numbers[0] << std::endl;
    std::cout << "Copia[0]: " << copy[0] << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== TEST 5: Array de strings ===" << std::endl;
    Array<std::string> words(3);
    words[0] = "Hola";
    words[1] = "Mundo";
    words[2] = "C++";
    
    for (unsigned int i = 0; i < words.size(); i++) {
        std::cout << words[i] << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "=== TEST 6: Acceso fuera de rango ===" << std::endl;
    try {
        numbers[MAX_VAL] = 0;  // Fuera de rango
    } catch (std::exception & e) {
        std::cout << "Excepción capturada: Índice fuera de rango" << std::endl;
    }
    
    return 0;
}
```

### 📊 Salida Esperada

```
=== TEST 1: Array vacío ===
Tamaño: 0

=== TEST 2: Array de enteros ===
Tamaño: 10
Valores: 0 10 20 30 40 50 60 70 80 90 

=== TEST 3: Copiar array ===
Tamaño copia: 10
Valores copia: 0 10 20 30 40 50 60 70 80 90 

=== TEST 4: Modificar original (copia no cambia) ===
Original[0]: 999
Copia[0]: 0

=== TEST 5: Array de strings ===
Hola Mundo C++ 

=== TEST 6: Acceso fuera de rango ===
Excepción capturada: Índice fuera de rango
```

### 🔍 Conceptos Importantes

#### 1. Copia Profunda vs Copia Superficial

```
COPIA SUPERFICIAL (❌ Malo):
─────────────────────────────────────
Array<int> a(3);
Array<int> b = a;

a: [puntero] ────┐
                 ↓
            [10, 20, 30]  ← MISMA memoria
                 ↑
b: [puntero] ────┘

Problema: Si borras 'a', 'b' apunta a memoria liberada


COPIA PROFUNDA (✅ Bueno):
─────────────────────────────────────
Array<int> a(3);
Array<int> b = a;

a: [puntero] ──→ [10, 20, 30]  ← Memoria de 'a'

b: [puntero] ──→ [10, 20, 30]  ← Memoria de 'b' (copia)

Solución: Cada objeto tiene su propia memoria
```

#### 2. Inicialización con ()

```cpp
new T[n]     // Elementos NO inicializados (basura)
new T[n]()   // Elementos inicializados a 0/vacío

Ejemplos:
─────────────────────────────────────
int* a = new int[3];      // [?, ?, ?] basura
int* b = new int[3]();    // [0, 0, 0] inicializado

string* s1 = new string[2];    // ["", ""] strings vacíos
double* d = new double[4]();   // [0.0, 0.0, 0.0, 0.0]
```

---

## 🎓 Makefile para los Ejercicios

### Para ex00, ex01, ex02:

```makefile
NAME = program

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 📚 Resumen de Conceptos

### ✅ Lo que DEBES entender:

```
1. TEMPLATES SON MOLDES
   ─────────────────────────────────────
   • NO son código ejecutable
   • Son instrucciones para el compilador
   • El compilador genera código real cuando los usas

2. TYPENAME T = PARÁMETRO DE TIPO
   ─────────────────────────────────────
   • T puede ser cualquier tipo
   • El compilador lo deduce automáticamente
   • Puedes tener múltiples parámetros (T, U, V...)

3. DEFINICIÓN EN .HPP
   ─────────────────────────────────────
   • Los templates DEBEN estar en el .hpp
   • El compilador necesita ver toda la definición
   • NO separes en .cpp (no funcionará)

4. OPERADOR ::
   ─────────────────────────────────────
   • ::swap → tu función
   • swap → puede ser std::swap
   • Siempre usa :: en los ejercicios

5. COPIA PROFUNDA
   ─────────────────────────────────────
   • Cada objeto tiene su propia memoria
   • Constructor de copia crea nueva memoria
   • Operador = libera antigua y crea nueva
```

---

## 🎯 Checklist de Compilación

```
✅ Compila con -std=c++98
✅ Compila con -Wall -Wextra -Werror
✅ Sin warnings
✅ No memory leaks (ejecuta con valgrind)
✅ Usa const donde sea apropiado
✅ Usa referencias (&) donde sea apropiado
```

---

## 🚀 Cómo Empezar

### 1. Crea las carpetas:
```bash
mkdir -p ex00 ex01 ex02
```

### 2. Para cada ejercicio:
```bash
cd ex00
# Crea los archivos según la guía
# Compila y prueba
make
./program
```

### 3. Verifica memory leaks:
```bash
valgrind --leak-check=full ./program
```

---

## 💡 Consejos Finales

```
1. Empieza simple
   ────────────────────────────────
   • Primero haz que compile
   • Luego prueba con un tipo (int)
   • Después prueba con otros tipos

2. Usa const correctamente
   ────────────────────────────────
   • const & para parámetros que no modificas
   • & sin const para parámetros que modificas

3. Compila frecuentemente
   ────────────────────────────────
   • No escribas mucho código sin compilar
   • Es más fácil encontrar errores así

4. Lee los mensajes de error
   ────────────────────────────────
   • Los errores de template son largos
   • Busca el primer error del mensaje
   • Ignora el resto hasta arreglar ese

5. Prueba con diferentes tipos
   ────────────────────────────────
   • int, double, char
   • string
   • Tus propias clases
```

---

**¡Buena suerte!** 🍀

Recuerda: Los templates parecen complicados al principio, pero una vez que entiendes el concepto básico (son moldes para generar código), todo tiene sentido. ¡Tú puedes! 💪



















