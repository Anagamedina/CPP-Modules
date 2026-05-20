# 🔒 GUÍA: ¿Cuándo usar const?

## 🎯 Regla de Oro

```
╔════════════════════════════════════════════════════════════╗
║                    REGLA PRINCIPAL                         ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║  Usa const SIEMPRE que NO necesites modificar algo         ║
║                                                            ║
║  Si la función SOLO LEE → usa const                        ║
║  Si la función MODIFICA → NO uses const                    ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
```

---

## 📋 Casos Prácticos

### ✅ CASO 1: Parámetros de Función

#### 🔍 Pregunta: ¿La función modifica el parámetro?

```cpp
// ❓ ¿Esta función modifica a o b?
template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Solo COMPARA, no modifica
}

// Respuesta: NO modifica
// ✅ Entonces usa const:
template<typename T>
T const & min(T const & a, T const & b) {
    return (a < b) ? a : b;
}
```

```cpp
// ❓ ¿Esta función modifica a y b?
template<typename T>
void swap(T a, T b) {
    T temp = a;
    a = b;         // ← SÍ MODIFICA a
    b = temp;      // ← SÍ MODIFICA b
}

// Respuesta: SÍ modifica
// ✅ Entonces NO uses const, usa solo &:
template<typename T>
void swap(T& a, T& b) {  // Sin const
    T temp = a;
    a = b;
    b = temp;
}
```

---

### 📊 Tabla de Decisión Rápida

```
╔═══════════════════════╦═══════════════╦═══════════════════════╗
║   ¿QUÉ HACE?          ║   USA         ║      EJEMPLO          ║
╠═══════════════════════╬═══════════════╬═══════════════════════╣
║                       ║               ║                       ║
║ Solo LEE              ║ T const &     ║ min, max, imprimir    ║
║ (no modifica)         ║               ║                       ║
║                       ║               ║                       ║
╠═══════════════════════╬═══════════════╬═══════════════════════╣
║                       ║               ║                       ║
║ MODIFICA              ║ T&            ║ swap, incrementar     ║
║ (cambia el valor)     ║ (sin const)   ║                       ║
║                       ║               ║                       ║
╠═══════════════════════╬═══════════════╬═══════════════════════╣
║                       ║               ║                       ║
║ Copia pequeña         ║ T             ║ int, char, bool       ║
║ (int, char, etc.)     ║ (por valor)   ║                       ║
║                       ║               ║                       ║
╚═══════════════════════╩═══════════════╩═══════════════════════╝
```

---

## 🎨 Ejemplos Visuales

### Ejemplo 1: Imprimir (solo lee) → usa `const`

```cpp
// ✅ CORRECTO: Solo lee, no modifica
void imprimir(int const & numero) {
    std::cout << numero << std::endl;
    // numero = 10;  ← ERROR: no puedes modificar (tiene const)
}

int main() {
    int x = 42;
    imprimir(x);
    // x sigue siendo 42 (no cambió)
}
```

**Flujo:**
```
x = 42
  │
  ↓ (referencia const)
imprimir(x)
  │
  └→ Solo LEE x
  
x = 42  ← Sin cambios
```

### Ejemplo 2: Incrementar (modifica) → NO uses `const`

```cpp
// ✅ CORRECTO: Modifica, sin const
void incrementar(int& numero) {  // Sin const
    numero++;  // Puede modificar
}

int main() {
    int x = 42;
    incrementar(x);
    // x ahora es 43 (cambió)
}
```

**Flujo:**
```
x = 42
  │
  ↓ (referencia sin const)
incrementar(x)
  │
  └→ MODIFICA x++
  
x = 43  ← ¡Cambió!
```

### Ejemplo 3: min (solo lee) → usa `const`

```cpp
// ✅ CORRECTO: Solo compara, no modifica
template<typename T>
T const & min(T const & a, T const & b) {
    return (a < b) ? a : b;
    // a = 10;  ← ERROR: no puedes modificar (tiene const)
    // b = 20;  ← ERROR: no puedes modificar (tiene const)
}

int main() {
    int x = 10, y = 20;
    int menor = min(x, y);
    // x sigue siendo 10, y sigue siendo 20
}
```

**Flujo:**
```
x = 10, y = 20
  │      │
  ↓      ↓ (referencias const)
min(x, y)
  │
  └→ Solo COMPARA, no modifica
  
x = 10, y = 20  ← Sin cambios
menor = 10
```

### Ejemplo 4: swap (modifica) → NO uses `const`

```cpp
// ✅ CORRECTO: Modifica ambos, sin const
template<typename T>
void swap(T& a, T& b) {  // Sin const
    T temp = a;
    a = b;     // Puede modificar a
    b = temp;  // Puede modificar b
}

int main() {
    int x = 10, y = 20;
    swap(x, y);
    // x ahora es 20, y ahora es 10 (intercambiados)
}
```

**Flujo:**
```
x = 10, y = 20
  │      │
  ↓      ↓ (referencias sin const)
swap(x, y)
  │
  └→ MODIFICA ambos
  
x = 20, y = 10  ← ¡Cambiaron!
```

---

## 🔬 Desglose Completo de const

### 1. `const` en el tipo de retorno

```cpp
// Devuelve referencia constante (no se puede modificar)
T const & min(T const & a, T const & b) {
  ↑
  └─ El valor retornado no se puede modificar
  
// Ejemplo:
int x = 10, y = 20;
min(x, y) = 100;  // ❌ ERROR: min devuelve const &
```

### 2. `const` en los parámetros

```cpp
// Parámetros constantes (la función no los puede modificar)
T const & min(T const & a, T const & b) {
              ↑             ↑
              └─────────────┴─ No se pueden modificar dentro de la función
    
    // a = 10;  ← ERROR
    // b = 20;  ← ERROR
    return (a < b) ? a : b;  // Solo puede leerlos
}
```

### 3. `const` en métodos de clase

```cpp
class MiClase {
private:
    int valor;
    
public:
    // Método const: NO modifica el objeto
    int getValor() const {  // ← const aquí
        return valor;       // Solo lee
        // valor = 10;      // ❌ ERROR: no puede modificar
    }
    
    // Método sin const: SÍ puede modificar
    void setValor(int v) {  // ← Sin const
        valor = v;          // Puede modificar
    }
};
```

---

## 🎯 Casos Específicos en Templates

### CASO A: Funciones que solo leen

```cpp
// ✅ Solo leen → const &
template<typename T>
T const & max(T const & a, T const & b);

template<typename T>
bool sonIguales(T const & a, T const & b);

template<typename T>
void imprimir(T const & valor);

template<typename T>
T const & primero(T const * array, size_t size);
```

**¿Por qué `const &`?**
- ✅ No copia (eficiente)
- ✅ No modifica (seguro)
- ✅ Funciona con objetos grandes

### CASO B: Funciones que modifican

```cpp
// ✅ Modifican → & sin const
template<typename T>
void swap(T& a, T& b);

template<typename T>
void incrementar(T& valor);

template<typename T>
void ordenar(T* array, size_t size);

template<typename T>
void rellenar(T& contenedor, T const & valor);
```

**¿Por qué `&` sin const?**
- ✅ Necesitan modificar los valores
- ✅ Los cambios deben persistir

### CASO C: Tipos pequeños (copia barata)

```cpp
// ✅ Tipos pequeños → por valor (T)
template<typename T>
T suma(T a, T b) {  // int, char, bool
    return a + b;
}

// Pero para objetos grandes → const &
template<typename T>
bool comparar(T const & a, T const & b) {  // string, vector, etc.
    return a == b;
}
```

---

## 📝 Guía de Decisión Paso a Paso

```
PASO 1: ¿La función modifica el parámetro?
┌────────────────────────────────────────┐
│ SÍ → Usa T&                            │
│ NO → Continúa al PASO 2                │
└────────────────────────────────────────┘

PASO 2: ¿El tipo es pequeño? (int, char, bool)
┌────────────────────────────────────────┐
│ SÍ → Usa T (por valor)                 │
│ NO → Continúa al PASO 3                │
└────────────────────────────────────────┘

PASO 3: ¿Solo necesitas leer el valor?
┌────────────────────────────────────────┐
│ SÍ → Usa T const &                     │
│ NO → Reconsiderar (probablemente T&)   │
└────────────────────────────────────────┘
```

### Ejemplos aplicando la guía:

```cpp
// EJEMPLO 1: min
// ¿Modifica? NO → PASO 2
// ¿Pequeño? Puede ser grande (string) → PASO 3
// ¿Solo lee? SÍ
// ✅ Resultado: T const &
template<typename T>
T const & min(T const & a, T const & b);


// EJEMPLO 2: swap
// ¿Modifica? SÍ
// ✅ Resultado: T&
template<typename T>
void swap(T& a, T& b);


// EJEMPLO 3: suma
// ¿Modifica? NO → PASO 2
// ¿Pequeño? Generalmente sí (int, double)
// ✅ Resultado: T
template<typename T>
T suma(T a, T b);


// EJEMPLO 4: imprimir
// ¿Modifica? NO → PASO 2
// ¿Pequeño? Puede ser grande (string) → PASO 3
// ¿Solo lee? SÍ
// ✅ Resultado: T const &
template<typename T>
void imprimir(T const & valor);
```

---

## ⚠️ Errores Comunes

### Error 1: Usar const cuando necesitas modificar

```cpp
❌ INCORRECTO:
template<typename T>
void incrementar(T const & valor) {  // const impide modificar
    valor++;  // ERROR: no puedes modificar
}

✅ CORRECTO:
template<typename T>
void incrementar(T& valor) {  // Sin const
    valor++;  // OK
}
```

### Error 2: No usar const cuando solo lees

```cpp
❌ INEFICIENTE:
template<typename T>
void imprimir(T valor) {  // Hace una COPIA
    std::cout << valor;
}

✅ CORRECTO:
template<typename T>
void imprimir(T const & valor) {  // Referencia, no copia
    std::cout << valor;
}
```

### Error 3: Olvidar const en métodos que no modifican

```cpp
❌ INCORRECTO:
class Array {
    size_t size() {  // ← Falta const
        return _size;
    }
};

✅ CORRECTO:
class Array {
    size_t size() const {  // ← const porque no modifica el objeto
        return _size;
    }
};
```

---

## 🎓 Resumen en Una Imagen

```
┌──────────────────────────────────────────────────────────┐
│              ¿CUÁNDO USAR const?                         │
├──────────────────────────────────────────────────────────┤
│                                                          │
│  🔍 PREGUNTA: ¿Necesitas MODIFICAR el parámetro?        │
│                                                          │
│     ┌─────────────┬─────────────┐                       │
│     │     NO      │     SÍ      │                       │
│     ↓             ↓             │                       │
│  ┌─────────┐  ┌─────────┐      │                       │
│  │ const & │  │    &    │      │                       │
│  │         │  │(sin     │      │                       │
│  │ Ejemplo:│  │ const)  │      │                       │
│  │ min,    │  │         │      │                       │
│  │ max,    │  │ Ejemplo:│      │                       │
│  │ print   │  │ swap,   │      │                       │
│  │         │  │ increm. │      │                       │
│  └─────────┘  └─────────┘      │                       │
│                                                          │
│  VENTAJAS de const &:                                    │
│  ✅ No copia (rápido)                                    │
│  ✅ No modifica (seguro)                                 │
│  ✅ Funciona con objetos grandes                         │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

---

## 💡 Reglas Prácticas

```
1. Por defecto, usa const &
   ────────────────────────────────────
   Siempre que no necesites modificar

2. Solo quita const si DEBES modificar
   ────────────────────────────────────
   swap, incrementar, modificar, etc.

3. Métodos que no cambian el objeto → const
   ────────────────────────────────────
   size(), empty(), get(), etc.

4. Para tipos pequeños (int, char) → por valor
   ────────────────────────────────────
   No hace falta const & para int

5. Si tienes duda → usa const &
   ────────────────────────────────────
   Es más seguro y eficiente
```

---

## ✅ Checklist Rápido

Antes de escribir una función, pregúntate:

```
☐ ¿La función modifica los parámetros?
   → NO: usa const &
   → SÍ: usa & (sin const)

☐ ¿El tipo es pequeño (int, char)?
   → SÍ: puedes usar T (por valor)
   → NO: usa const & o &

☐ ¿Es un método de clase?
   → ¿Modifica el objeto? NO → añade const al final
   → ¿Modifica el objeto? SÍ → sin const

☐ ¿Devuelves una referencia?
   → ¿Quieres que se pueda modificar? NO → const &
   → ¿Quieres que se pueda modificar? SÍ → &
```

---

**¡Ahora sabrás cuándo usar const!** 🎉

La regla simple: **Si no modificas, usa const** ✨



















