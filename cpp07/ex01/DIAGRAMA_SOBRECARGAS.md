# 🎨 DIAGRAMA VISUAL - Sobrecargas de iter

## 🔑 Concepto Principal

```
HAY 2 TIPOS DE FUNCIONES EN C++:
════════════════════════════════════════════════════════

Tipo 1: Funciones que SOLO LEEN (const)
        ────────────────────────────────
        void f(T const & x) {
            std::cout << x;  // Solo lee
        }

Tipo 2: Funciones que MODIFICAN (non-const)
        ────────────────────────────────
        void f(T& x) {
            x++;  // Modifica
        }


PROBLEMA: iter debe funcionar con AMBOS tipos
SOLUCIÓN: Hacer 2 sobrecargas (una para cada tipo)
```

---

## 📊 Visualización del Problema

```
TENEMOS ESTAS FUNCIONES:
════════════════════════════════════════════════════════

┌──────────────────────────┐        ┌──────────────────────────┐
│ void mostrar(int const &)│        │ void incrementar(int&)   │
│ {                        │        │ {                        │
│   cout << x;             │        │   x++;                   │
│ }                        │        │ }                        │
│                          │        │                          │
│ TIPO: const &            │        │ TIPO: & (non-const)      │
└──────────────────────────┘        └──────────────────────────┘


SI SOLO TUVIÉRAMOS UNA VERSIÓN DE ITER:
════════════════════════════════════════════════════════

void iter(T* arr, size_t len, void (*f)(T const &)) {
    // Solo acepta funciones const
}

int nums[] = {1, 2, 3};

iter(nums, 3, mostrar);      // ✅ FUNCIONA
                             // mostrar ES const

iter(nums, 3, incrementar);  // ❌ ERROR
                             // incrementar NO es const
                             // Es T&, no T const &
```

---

## ✅ Solución: Dos Sobrecargas

```
SOBRECARGA 1                           SOBRECARGA 2
(para funciones const)                 (para funciones non-const)
════════════════════════════════       ════════════════════════════════

void iter(                             void iter(
    T* array,                              T* array,
    size_t length,                         size_t length,
    void (*function)(T const &)            void (*function)(T&)
) {                                    ) {
    for (i...) {                           for (i...) {
        function(array[i]);                    function(array[i]);
    }                                      }
}                                      }

ACEPTA:                                ACEPTA:
• mostrar(T const &)                   • incrementar(T&)
• imprimir(T const &)                  • duplicar(T&)
• comparar(T const &)                  • modificar(T&)
```

---

## 🔄 Proceso de Selección

```
CUANDO LLAMAS A iter:
════════════════════════════════════════════════════════

int nums[] = {1, 2, 3};

LLAMADA 1:
──────────────────────────────────────
iter(nums, 3, mostrar);

1. Compilador ve: mostrar tiene firma void(int const &)
2. Busca iter que acepte: void(*)(int const &)
3. Encuentra: SOBRECARGA 1 ✅
4. Usa esa versión


LLAMADA 2:
──────────────────────────────────────
iter(nums, 3, incrementar);

1. Compilador ve: incrementar tiene firma void(int&)
2. Busca iter que acepte: void(*)(int&)
3. Encuentra: SOBRECARGA 2 ✅
4. Usa esa versión
```

---

## 📌 ¿Por qué el `*` (puntero)?

```
ANALOGÍA:
════════════════════════════════════════════════════════

int x = 42;           // x es un int
int* p = &x;          // p es un PUNTERO a int
                      // p guarda la DIRECCIÓN de x

void mostrar(int x);  // mostrar es una FUNCIÓN
void (*f)(int);       // f es un PUNTERO a función
f = mostrar;          // f guarda la DIRECCIÓN de mostrar


VISUALIZACIÓN:
════════════════════════════════════════════════════════

MEMORIA:
┌──────────────────────┐
│ Función: mostrar     │
│ Dirección: 0x1000    │ ← La función está aquí
│ Código: { cout... }  │
└──────────────────────┘
         ↑
         │ (apunta)
         │
┌──────────────────────┐
│ f (puntero)          │
│ Valor: 0x1000        │ ← f guarda la dirección
└──────────────────────┘


USO:
f(42);  →  Busca dirección (0x1000)
        →  Ejecuta función en 0x1000
        →  Llama a mostrar(42)
```

---

## 🎯 Ejemplo Completo con Flujo

```cpp
// ════════════════════════════════════════════════════════
// DEFINICIONES
// ════════════════════════════════════════════════════════

void mostrar(int const & x) {
    std::cout << x << " ";
}

void duplicar(int& x) {
    x *= 2;
}

// ════════════════════════════════════════════════════════
// MAIN
// ════════════════════════════════════════════════════════

int main() {
    int nums[] = {1, 2, 3};
    
    // ANTES:
    std::cout << "Antes: ";
    iter(nums, 3, mostrar);
    // Output: "Antes: 1 2 3 "
    
    // MODIFICAR:
    iter(nums, 3, duplicar);
    
    // DESPUÉS:
    std::cout << "Después: ";
    iter(nums, 3, mostrar);
    // Output: "Después: 2 4 6 "
}
```

### Flujo Detallado:

```
PASO 1: iter(nums, 3, mostrar)
════════════════════════════════════════════════════════

Compilador selecciona:
┌──────────────────────────────────────────────┐
│ void iter(T*, size_t, void (*)(T const &))  │ ← Esta
└──────────────────────────────────────────────┘

Porque:
mostrar tiene firma: void(int const &)
Coincide con: void (*)(T const &)

Ejecuta:
i=0: mostrar(nums[0]) → imprime "1 "
i=1: mostrar(nums[1]) → imprime "2 "
i=2: mostrar(nums[2]) → imprime "3 "

Array sigue igual: [1, 2, 3]


PASO 2: iter(nums, 3, duplicar)
════════════════════════════════════════════════════════

Compilador selecciona:
┌──────────────────────────────────────────────┐
│ void iter(T*, size_t, void (*)(T&))         │ ← Esta
└──────────────────────────────────────────────┘

Porque:
duplicar tiene firma: void(int&)
Coincide con: void (*)(T&)

Ejecuta:
i=0: duplicar(nums[0]) → nums[0] = 1*2 = 2
i=1: duplicar(nums[1]) → nums[1] = 2*2 = 4
i=2: duplicar(nums[2]) → nums[2] = 3*2 = 6

Array cambia: [2, 4, 6]


PASO 3: iter(nums, 3, mostrar) de nuevo
════════════════════════════════════════════════════════

Usa misma sobrecarga que PASO 1

Ejecuta:
i=0: mostrar(nums[0]) → imprime "2 "
i=1: mostrar(nums[1]) → imprime "4 "
i=2: mostrar(nums[2]) → imprime "6 "

Array sigue: [2, 4, 6]
```

---

## 🔍 Diferencia const vs non-const VISUALIZADA

```
FUNCIÓN CON const &:
════════════════════════════════════════════════════════

void mostrar(int const & x) {
    std::cout << x;     // ✅ OK: solo lee
    // x = 10;          // ❌ ERROR: no puede modificar
    // x++;             // ❌ ERROR: no puede modificar
}

int nums[] = {1, 2, 3};
mostrar(nums[0]);

ANTES:  nums[0] = 1
LLAMA:  mostrar(nums[0])
DESPUÉS: nums[0] = 1  ← NO CAMBIA


FUNCIÓN SIN const (solo &):
════════════════════════════════════════════════════════

void duplicar(int& x) {
    x = x * 2;          // ✅ OK: puede modificar
    x++;                // ✅ OK: puede modificar
}

int nums[] = {1, 2, 3};
duplicar(nums[0]);

ANTES:  nums[0] = 1
LLAMA:  duplicar(nums[0])
DESPUÉS: nums[0] = 2  ← ¡CAMBIA!
```

---

## 💡 Tabla Resumen Final

```
╔════════════════════╦══════════════════════╦══════════════════════╗
║   CONCEPTO         ║   const &            ║   & (non-const)      ║
╠════════════════════╬══════════════════════╬══════════════════════╣
║                    ║                      ║                      ║
║ Sintaxis           ║ void f(T const & x)  ║ void f(T& x)         ║
║                    ║                      ║                      ║
╠════════════════════╬══════════════════════╬══════════════════════╣
║                    ║                      ║                      ║
║ ¿Puede modificar?  ║ ❌ NO                ║ ✅ SÍ                ║
║                    ║                      ║                      ║
╠════════════════════╬══════════════════════╬══════════════════════╣
║                    ║                      ║                      ║
║ Ejemplos           ║ mostrar, imprimir,   ║ incrementar,         ║
║                    ║ comparar, buscar     ║ duplicar, modificar  ║
║                    ║                      ║                      ║
╠════════════════════╬══════════════════════╬══════════════════════╣
║                    ║                      ║                      ║
║ Sobrecarga iter    ║ void (*)(T const &)  ║ void (*)(T&)         ║
║ que acepta         ║                      ║                      ║
║                    ║                      ║                      ║
╚════════════════════╩══════════════════════╩══════════════════════╝
```

---

## 🎓 Mini-Test

```cpp
// ¿Qué sobrecarga se usa en cada caso?

int nums[] = {1, 2, 3};

// 1.
void print(int const & x) { std::cout << x; }
iter(nums, 3, print);
// Respuesta: Sobrecarga const (void (*)(T const &))

// 2.
void triple(int& x) { x *= 3; }
iter(nums, 3, triple);
// Respuesta: Sobrecarga non-const (void (*)(T&))

// 3.
void show(int const & x) { std::cout << x; }
iter(nums, 3, show);
// Respuesta: Sobrecarga const (void (*)(T const &))

// 4.
void add10(int& x) { x += 10; }
iter(nums, 3, add10);
// Respuesta: Sobrecarga non-const (void (*)(T&))
```

---

## 🎯 Conclusión Simple

```
┌──────────────────────────────────────────────────────────┐
│                  RESUMEN ULTRA-SIMPLE                    │
├──────────────────────────────────────────────────────────┤
│                                                          │
│  1. (*) = PUNTERO                                        │
│     void (*f)(...) = puntero a función                   │
│                                                          │
│  2. DOS SOBRECARGAS                                      │
│     • Una para funciones const (solo leen)               │
│     • Otra para funciones non-const (modifican)          │
│                                                          │
│  3. DIFERENCIA                                           │
│     • const & → NO modifica                              │
│     • & → SÍ modifica                                    │
│                                                          │
│  El compilador AUTOMÁTICAMENTE elige la correcta         │
│  según el tipo de función que pases                      │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

---

**¡Ahora deberías entender completamente las sobrecargas!** 🎉



















