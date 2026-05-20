# 🚀 INSTRUCCIONES PARA COMPILAR Y PROBAR CPP07

## 📁 Estructura de Archivos

```
cpp07/
├── ex00/
│   ├── whatever.hpp
│   ├── main.cpp
│   └── Makefile
├── ex01/
│   ├── iter.hpp
│   ├── main.cpp
│   └── Makefile
└── ex02/
    ├── Array.hpp
    ├── main.cpp
    └── Makefile
```

---

## 🎯 EJERCICIO 00: swap, min, max

### 📝 ¿Qué hace?

Implementa 3 funciones template:
- `swap`: Intercambia dos valores
- `min`: Devuelve el menor (si son iguales, devuelve el segundo)
- `max`: Devuelve el mayor (si son iguales, devuelve el segundo)

### ▶️ Compilar y Ejecutar

```bash
cd ex00
make
./whatever
```

### 📊 Salida Esperada

```
a = 3, b = 2
min( a, b ) = 2
max( a, b ) = 3
c = chaine2, d = chaine1
min( c, d ) = chaine1
max( c, d ) = chaine2
```

### 🧪 Verificar Memory Leaks

```bash
valgrind --leak-check=full ./whatever
```

### 🔍 Puntos Clave

```cpp
// ✅ CORRECTO: Usa ::
::swap(a, b);  // Tu función
::min(a, b);
::max(a, b);

// ❌ INCORRECTO: Sin ::
swap(a, b);  // Puede llamar a std::swap

// ✅ Las funciones devuelven referencias const
T const & min(T const & a, T const & b);

// ✅ swap no devuelve nada
void swap(T& a, T& b);
```

---

## 🎯 EJERCICIO 01: iter

### 📝 ¿Qué hace?

Implementa `iter`: función que aplica otra función a cada elemento de un array.

```cpp
template<typename T, typename F>
void iter(T* array, size_t length, F function);
```

### ▶️ Compilar y Ejecutar

```bash
cd ex01
make
./iter
```

### 📊 Salida Esperada

```
╔════════════════════════════════════════╗
║   TEST 1: Array de enteros (const)    ║
╚════════════════════════════════════════╝
Array original: 1 2 3 4 5 

╔════════════════════════════════════════╗
║   TEST 2: Incrementar elementos        ║
╚════════════════════════════════════════╝
Después de incrementar: 2 3 4 5 6 

╔════════════════════════════════════════╗
║   TEST 3: Duplicar elementos           ║
╚════════════════════════════════════════╝
Después de duplicar: 4 6 8 10 12 

╔════════════════════════════════════════╗
║   TEST 4: Array de strings             ║
╚════════════════════════════════════════╝
Palabras: Hola Mundo CPP Templates 

╔════════════════════════════════════════╗
║   TEST 5: Array de chars               ║
╚════════════════════════════════════════╝
Texto original: hello
En mayúsculas: HELLO
```

### 🔍 Puntos Clave

```cpp
// Funciona con const reference (no modifica)
void printInt(int const & x) {
    std::cout << x;
}
iter(array, len, printInt);

// Funciona con non-const reference (sí modifica)
void incrementInt(int & x) {
    x++;
}
iter(array, len, incrementInt);

// iter soporta AMBOS casos
```

---

## 🎯 EJERCICIO 02: Array

### 📝 ¿Qué hace?

Implementa una clase template `Array<T>` que gestiona un array dinámico:
- Constructor vacío
- Constructor con tamaño
- Constructor de copia (copia profunda)
- Operador de asignación (copia profunda)
- Operador `[]` con verificación de límites
- Método `size()`

### ▶️ Compilar y Ejecutar

```bash
cd ex02
make
./array
```

### 📊 Salida Esperada

```
Excepción capturada: índice negativo
Excepción capturada: índice fuera de rango

=== TEST ARRAY VACÍO ===
Tamaño array vacío: 0

=== TEST ARRAY DE STRINGS ===
Tamaño: 5
Contenido: Hola Mundo CPP Module 07 

=== TEST COPIA PROFUNDA ===
Original: 10 20 30 
Copia: 10 20 30 

Después de modificar original[0] = 999:
Original[0]: 999
Copia[0]: 10 (no cambió, copia profunda)

=== TEST INICIALIZACIÓN POR DEFECTO ===
Valores por defecto: 0 0 0 0 0 (todos deberían ser 0)
```

### 🔍 Puntos Clave

#### 1. Constructor con Tamaño

```cpp
Array(unsigned int n) : _elements(new T[n]()), _size(n) {
//                                       ↑↑
//                                       └─ () inicializa a 0
}

// Ejemplos:
Array<int> nums(5);     // [0, 0, 0, 0, 0]
Array<double> d(3);     // [0.0, 0.0, 0.0]
Array<string> s(2);     // ["", ""]
```

#### 2. Copia Profunda (IMPORTANTE)

```cpp
Array<int> original(3);
original[0] = 10;

Array<int> copia(original);  // Constructor de copia
original[0] = 999;

// copia[0] sigue siendo 10 (copia independiente)
```

**Por qué es importante:**
```
❌ COPIA SUPERFICIAL (malo):
original: [ptr] ──┐
                  ↓
             [10, 20, 30]  ← MISMA memoria
                  ↑
copia:    [ptr] ──┘
// Si borras original, copia apunta a memoria liberada

✅ COPIA PROFUNDA (bueno):
original: [ptr] ──→ [10, 20, 30]
copia:    [ptr] ──→ [10, 20, 30]  (copia independiente)
```

#### 3. Operador [] con Protección

```cpp
T & operator[](size_t index) {
    if (index >= _size) {
        throw std::exception();  // Lanza excepción
    }
    return _elements[index];
}

// Uso:
Array<int> arr(5);
arr[0] = 10;   // ✅ OK
arr[10] = 20;  // ❌ Lanza excepción
```

---

## 🧪 Testing Completo

### Compilar Todos los Ejercicios

```bash
# Desde cpp07/
for dir in ex00 ex01 ex02; do
    echo "=== Compilando $dir ==="
    cd $dir
    make
    cd ..
done
```

### Ejecutar Todos los Ejercicios

```bash
echo "=== Ejecutando ex00 ==="
./ex00/whatever

echo "\n=== Ejecutando ex01 ==="
./ex01/iter

echo "\n=== Ejecutando ex02 ==="
./ex02/array
```

### Verificar Memory Leaks en Todos

```bash
for dir in ex00 ex01 ex02; do
    echo "=== Verificando $dir ==="
    valgrind --leak-check=full ./$dir/$(ls $dir | grep -v '\.')
done
```

---

## 📋 Checklist de Evaluación

### ex00:
```
✅ Compila con -std=c++98 -Wall -Wextra -Werror
✅ swap intercambia correctamente
✅ min devuelve el menor (o segundo si iguales)
✅ max devuelve el mayor (o segundo si iguales)
✅ Funciona con int y string
✅ Sin memory leaks
✅ Templates en .hpp
```

### ex01:
```
✅ Compila sin errores
✅ iter aplica función a cada elemento
✅ Funciona con funciones const reference
✅ Funciona con funciones non-const reference
✅ Funciona con diferentes tipos (int, string, char)
✅ Sin memory leaks
✅ Templates en .hpp
```

### ex02:
```
✅ Compila sin errores
✅ Constructor vacío funciona
✅ Constructor con tamaño inicializa a 0
✅ Constructor de copia hace copia profunda
✅ Operador = hace copia profunda
✅ Operador [] lanza excepción fuera de rango
✅ size() devuelve el tamaño correcto
✅ Sin memory leaks
✅ Templates en .hpp
```

---

## ⚠️ Errores Comunes

### 1. No usar :: antes de las funciones

```cpp
❌ swap(a, b);     // Puede llamar a std::swap
✅ ::swap(a, b);   // Llama a tu función
```

### 2. Poner templates en .cpp

```cpp
❌ whatever.cpp con implementación
✅ whatever.hpp con TODO (declaración + implementación)
```

### 3. No inicializar con ()

```cpp
❌ new T[n];      // NO inicializa (basura)
✅ new T[n]();    // Inicializa a 0/vacío
```

### 4. Copia superficial en Array

```cpp
❌ _elements = other._elements;  // Copia el puntero (superficial)
✅ // Crear nuevo array y copiar elementos uno por uno
   _elements = new T[_size];
   for (...) _elements[i] = other._elements[i];
```

### 5. No liberar memoria en operador =

```cpp
❌ Array & operator=(Array const & other) {
       _elements = new T[other._size];  // Memory leak
   }

✅ Array & operator=(Array const & other) {
       delete[] _elements;  // Liberar primero
       _elements = new T[other._size];
   }
```

---

## 🎓 Conceptos Clave a Entender

### 1. Templates NO son código ejecutable

```
Template → Molde/Receta
         ↓ (compilador genera)
Código real → Ejecutable

El template existe solo en tiempo de compilación
En el ejecutable solo están las funciones concretas generadas
```

### 2. typename T = parámetro de tipo

```cpp
template<typename T>  // T puede ser int, double, string, etc.
```

### 3. Definición en .hpp (OBLIGATORIO)

```
Templates DEBEN estar completos en .hpp
El compilador necesita ver la definición para generar código
NO separar en .cpp (no funcionará)
```

### 4. Deducción automática de tipos

```cpp
int a = 5, b = 10;
::swap(a, b);  // Compilador deduce: T = int

string s1 = "hi", s2 = "bye";
::swap(s1, s2);  // Compilador deduce: T = string
```

---

## 🚀 ¡Listo para Probar!

1. Compila cada ejercicio con `make`
2. Ejecuta y verifica la salida
3. Prueba con valgrind para memory leaks
4. Si todo funciona, ¡estás listo! 🎉

**¡Buena suerte!** 💪



















