# 🎓 EXPLICACIÓN COMPLETA - iter (ex01)

## ❓ Pregunta 1: ¿Por qué `void (*function)(...)`? ¿Qué es el `*`?

### 📌 El `*` significa "PUNTERO A FUNCIÓN"

```cpp
void (*function)(T const &)
     ↑
     └─ Este asterisco significa "puntero a función"
```

### 🔍 Desglose completo:

```cpp
void (*function)(T const &)
│    │  │        │
│    │  │        └─ Parámetro que recibe la función
│    │  └─ Nombre del puntero a función
│    └─ * = Es un PUNTERO
└─ Tipo de retorno de la función
```

**Traducción:**
> "function es un PUNTERO que apunta a una función que:
> - No devuelve nada (void)
> - Recibe un parámetro de tipo T const &"

---

## 🎨 Analogía: Puntero a Función

```
ANALOGÍA CON DIRECCIONES:
════════════════════════════════════════════════════════

int* p;  → p es un PUNTERO a int
         → Guarda la DIRECCIÓN de un int

void (*f)(...);  → f es un PUNTERO a función
                 → Guarda la DIRECCIÓN de una función


EJEMPLO CON FUNCIONES:
════════════════════════════════════════════════════════

void imprimir(int x) {     ← Esta es una FUNCIÓN
    std::cout << x;
}

void (*puntero)(int);      ← puntero es una VARIABLE
                           ← que guarda la dirección de una función

puntero = imprimir;        ← Ahora puntero apunta a imprimir

puntero(42);               ← Llama a imprimir(42)
                           ← Imprime: 42
```

---

## 🔬 Ejemplo Detallado: Punteros a Función

```cpp
// ==========================================
// PASO 1: Definir una función normal
// ==========================================
void saludar(int const & numero) {
    std::cout << "Hola " << numero << std::endl;
}

// ==========================================
// PASO 2: Crear un puntero a esa función
// ==========================================
void (*ptr)(int const &);  // Declaración del puntero
//   ↑
//   └─ ptr es un puntero a función

// ==========================================
// PASO 3: Asignar la función al puntero
// ==========================================
ptr = saludar;  // Ahora ptr "apunta" a saludar
//              (guarda la dirección de saludar)

// ==========================================
// PASO 4: Llamar a la función a través del puntero
// ==========================================
ptr(42);  // Llama a saludar(42)
          // Imprime: "Hola 42"
```

### Visualización:

```
MEMORIA:
════════════════════════════════════════════════════

┌─────────────────────────┐
│ Función: saludar        │
│ Dirección: 0x1000       │ ← La función está aquí
│ Código: { cout << ... } │
└─────────────────────────┘
          ↑
          │ (apunta)
          │
┌─────────────────────────┐
│ ptr                     │
│ Valor: 0x1000           │ ← ptr guarda la dirección
└─────────────────────────┘


CUANDO HACES ptr(42):
════════════════════════════════════════════════════
ptr(42)  →  Busca dirección en ptr (0x1000)
         →  Va a esa dirección
         →  Ejecuta la función que está ahí (saludar)
         →  Imprime "Hola 42"
```

---

## ❓ Pregunta 2: ¿Por qué necesitamos SOBRECARGAS?

### 🎯 PROBLEMA: Hay 2 tipos de funciones

```cpp
// TIPO 1: Funciones que NO modifican (const)
void imprimir(int const & x) {
    std::cout << x;  // Solo LEE x, no lo modifica
}

// TIPO 2: Funciones que SÍ modifican (non-const)
void duplicar(int& x) {
    x = x * 2;  // MODIFICA x
}
```

**¿Qué pasa si solo tenemos UNA versión de iter?**

```cpp
// ❌ SOLO una versión (no funciona bien):
template<typename T>
void iter(T* array, size_t len, void (*f)(T const &)) {
    for (size_t i = 0; i < len; i++) {
        f(array[i]);
    }
}

// Uso:
int nums[] = {1, 2, 3};

iter(nums, 3, imprimir);  // ✅ OK (imprimir es const)
iter(nums, 3, duplicar);  // ❌ ERROR! duplicar no es const
```

**El error:**
```
duplicar espera:  int&
iter pasa:        int const &

¡NO COINCIDEN! ❌
```

---

## ✅ SOLUCIÓN: Hacer SOBRECARGAS

```cpp
// SOBRECARGA 1: Para funciones const
template<typename T>
void iter(T* array, size_t length, void (*function)(T const &)) {
    for (size_t i = 0; i < length; i++) {
        function(array[i]);  // Pasa const &
    }
}

// SOBRECARGA 2: Para funciones non-const
template<typename T>
void iter(T* array, size_t length, void (*function)(T&)) {
    for (size_t i = 0; i < length; i++) {
        function(array[i]);  // Pasa &
    }
}
```

**Ahora funciona con AMBOS tipos:**

```cpp
int nums[] = {1, 2, 3};

iter(nums, 3, imprimir);  // ✅ Usa sobrecarga 1 (const)
iter(nums, 3, duplicar);  // ✅ Usa sobrecarga 2 (non-const)
```

---

## ❓ Pregunta 3: ¿Cuál es la DIFERENCIA entre const y non-const?

### 🔍 LA DIFERENCIA VISUAL:

```cpp
// ════════════════════════════════════════════════════════
// FUNCIONES CONST (no modifican)
// ════════════════════════════════════════════════════════
void imprimir(int const & x) {
//                ↑
//                └─ const = NO puede modificar

    std::cout << x;    // ✅ OK: solo lee
    // x = 10;         // ❌ ERROR: no puede modificar
}

// ════════════════════════════════════════════════════════
// FUNCIONES NON-CONST (sí modifican)
// ════════════════════════════════════════════════════════
void duplicar(int& x) {
//               ↑
//               └─ SIN const = SÍ puede modificar

    x = x * 2;         // ✅ OK: puede modificar
}
```

### 📊 Tabla Comparativa:

```
╔═══════════════════╦════════════════════╦═══════════════════════╗
║   CARACTERÍSTICA  ║    const &         ║    & (non-const)      ║
╠═══════════════════╬════════════════════╬═══════════════════════╣
║                   ║                    ║                       ║
║ ¿Puede modificar? ║ ❌ NO              ║ ✅ SÍ                 ║
║                   ║                    ║                       ║
╠═══════════════════╬════════════════════╬═══════════════════════╣
║                   ║                    ║                       ║
║ Ejemplo           ║ void f(T const &x) ║ void f(T& x)          ║
║                   ║                    ║                       ║
╠═══════════════════╬════════════════════╬═══════════════════════╣
║                   ║                    ║                       ║
║ Uso típico        ║ Leer, imprimir,    ║ Modificar,            ║
║                   ║ comparar           ║ incrementar, cambiar  ║
║                   ║                    ║                       ║
╚═══════════════════╩════════════════════╩═══════════════════════╝
```

---

## 🎨 Ejemplo Completo Paso a Paso

```cpp
// ==========================================
// DEFINIR FUNCIONES
// ==========================================

// Función que SOLO LEE (const)
void mostrar(int const & x) {
    std::cout << x << " ";
}

// Función que MODIFICA (non-const)
void incrementar(int& x) {
    x++;
}

// ==========================================
// MAIN
// ==========================================
int main() {
    int numeros[] = {1, 2, 3, 4, 5};
    
    std::cout << "Original: ";
    iter(numeros, 5, mostrar);
    // Usa: void iter(T*, size_t, void (*)(T const &))
    std::cout << std::endl;
    
    iter(numeros, 5, incrementar);
    // Usa: void iter(T*, size_t, void (*)(T&))
    
    std::cout << "Incrementado: ";
    iter(numeros, 5, mostrar);
    std::cout << std::endl;
}
```

### 🔄 Proceso Detallado:

```
PASO 1: iter(numeros, 5, mostrar)
════════════════════════════════════════════════════════

El compilador ve:
• mostrar tiene firma: void mostrar(int const &)
• Busca iter que acepte: void (*)(int const &)
• Encuentra: la sobrecarga 1

Ejecuta:
┌─────────────────────────────────────┐
│ for (i = 0; i < 5; i++) {          │
│     mostrar(numeros[i]);           │
│ }                                   │
└─────────────────────────────────────┘

Salida: 1 2 3 4 5


PASO 2: iter(numeros, 5, incrementar)
════════════════════════════════════════════════════════

El compilador ve:
• incrementar tiene firma: void incrementar(int&)
• Busca iter que acepte: void (*)(int&)
• Encuentra: la sobrecarga 2

Ejecuta:
┌─────────────────────────────────────┐
│ for (i = 0; i < 5; i++) {          │
│     incrementar(numeros[i]);       │
│     // Modifica cada elemento      │
│ }                                   │
└─────────────────────────────────────┘

Array ahora: [2, 3, 4, 5, 6]


PASO 3: iter(numeros, 5, mostrar) de nuevo
════════════════════════════════════════════════════════

Salida: 2 3 4 5 6  ← ¡Cambiaron!
```

---

## 🎯 ¿Por qué NECESITAS ambas sobrecargas?

```
SIN SOBRECARGAS (solo const):
════════════════════════════════════════════════════════

void iter(T* array, size_t len, void (*f)(T const &)) { ... }

int nums[] = {1, 2, 3};

iter(nums, 3, mostrar);      // ✅ OK
iter(nums, 3, incrementar);  // ❌ ERROR
                             // incrementar no es const!


CON SOBRECARGAS (const y non-const):
════════════════════════════════════════════════════════

void iter(T*, size_t, void (*)(T const &)) { ... }  // Para const
void iter(T*, size_t, void (*)(T&)) { ... }         // Para non-const

int nums[] = {1, 2, 3};

iter(nums, 3, mostrar);      // ✅ OK (usa sobrecarga const)
iter(nums, 3, incrementar);  // ✅ OK (usa sobrecarga non-const)
```

---

## 📝 Comparación Visual de las Sobrecargas

```
SOBRECARGA 1 (const):
════════════════════════════════════════════════════════
void iter(T* array, size_t length, void (*function)(T const &))
                                                    ↑
                                   Acepta funciones que NO modifican

Ejemplo de función compatible:
void imprimir(int const & x) {  // ← const
    std::cout << x;
}


SOBRECARGA 2 (non-const):
════════════════════════════════════════════════════════
void iter(T* array, size_t length, void (*function)(T&))
                                                    ↑
                                   Acepta funciones que SÍ modifican

Ejemplo de función compatible:
void incrementar(int& x) {  // ← Sin const
    x++;
}
```

---

## 💡 Resumen Simplificado

```
┌──────────────────────────────────────────────────────────┐
│                    RESUMEN                               │
├──────────────────────────────────────────────────────────┤
│                                                          │
│  1. void (*function)(...)                                │
│     ────────────────────────────────────────────────     │
│     • (*) = puntero a función                            │
│     • Guarda la DIRECCIÓN de una función                 │
│     • Permite pasar funciones como parámetros            │
│                                                          │
│  2. ¿Por qué sobrecargas?                                │
│     ────────────────────────────────────────────────     │
│     • Necesitas soportar 2 tipos de funciones:           │
│       - Funciones const (solo leen)                      │
│       - Funciones non-const (modifican)                  │
│                                                          │
│  3. Diferencia const vs non-const                        │
│     ────────────────────────────────────────────────     │
│     • const & → NO puede modificar                       │
│       Ejemplo: void print(T const &)                     │
│                                                          │
│     • & → SÍ puede modificar                             │
│       Ejemplo: void increment(T&)                        │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

---

## 🎓 Ejercicio de Comprensión

```cpp
// Pregunta: ¿Cuál sobrecarga se usa?

int nums[] = {1, 2, 3};

// 1.
void mostrar(int const & x) { std::cout << x; }
iter(nums, 3, mostrar);
// Respuesta: Sobrecarga const (1)

// 2.
void duplicar(int& x) { x *= 2; }
iter(nums, 3, duplicar);
// Respuesta: Sobrecarga non-const (2)

// 3.
void sumar(int& x) { x += 10; }
iter(nums, 3, sumar);
// Respuesta: Sobrecarga non-const (2)

// 4.
void imprimir(int const & x) { std::cout << x; }
iter(nums, 3, imprimir);
// Respuesta: Sobrecarga const (1)
```

---

**¿Quedó más claro ahora?** 😊

**Puntos clave:**
1. `*` = puntero a función (como `int*` es puntero a int)
2. Sobrecargas = para soportar funciones const y non-const
3. Diferencia = `const &` no modifica, `&` sí modifica



















