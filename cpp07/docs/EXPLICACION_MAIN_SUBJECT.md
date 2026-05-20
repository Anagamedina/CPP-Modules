# 📋 MAIN.CPP DEL SUBJECT - Explicación Completa

## 🎯 ¿Para qué es este main?

Este es el **programa de prueba OFICIAL** que el subject proporciona para verificar que tu clase `Array<T>` funciona correctamente en el **ejercicio 02**.

Es como un **test automático** que verifica:
- ✅ Constructor con tamaño
- ✅ Operador `[]`
- ✅ Constructor de copia (copia profunda)
- ✅ Verificación de límites (excepciones)
- ✅ Gestión de memoria correcta

---

## 📊 Desglose Línea por Línea

```cpp
#include <iostream>
#include <Array.hpp>

#define MAX_VAL 750
```

**Qué hace:**
- Incluye tu clase `Array<T>`
- Define `MAX_VAL = 750` (tamaño del array de prueba)

---

### 🔸 BLOQUE 1: Crear Arrays y Llenarlos

```cpp
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);  // ← Crea Array de 750 ints
    int* mirror = new int[MAX_VAL];  // ← Array normal de comparación
    
    srand(time(NULL));  // ← Inicializa generador de números aleatorios
    
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();  // ← Genera número aleatorio
        numbers[i] = value;        // ← Lo guarda en tu Array
        mirror[i] = value;         // ← Lo guarda en array normal
    }
```

**Propósito:**
```
1. Crea tu Array<int> con 750 elementos
2. Crea un array normal (mirror) del mismo tamaño
3. Llena AMBOS con los MISMOS valores aleatorios
4. mirror sirve para COMPARAR después
```

**Visualización:**
```
numbers (tu Array):   [random1, random2, random3, ...]  750 elementos
mirror (array C):     [random1, random2, random3, ...]  750 elementos
                       ↑         ↑         ↑
                       └─────────┴─────────┴─ MISMOS valores
```

**Prueba:**
- ✅ Constructor con tamaño: `Array<int> numbers(MAX_VAL)`
- ✅ Operador `[]` para asignar: `numbers[i] = value`

---

### 🔸 BLOQUE 2: Test de Copia Profunda (CRUCIAL)

```cpp
    //SCOPE
    {
        Array<int> tmp = numbers;  // ← Constructor de copia
        Array<int> test(tmp);      // ← Otro constructor de copia
    }  // ← tmp y test se destruyen aquí
```

**Propósito:**
```
Verificar que la COPIA PROFUNDA funciona correctamente
```

**¿Qué se está probando?**

1. **Constructor de copia:**
   ```cpp
   Array<int> tmp = numbers;  // Copia numbers a tmp
   ```

2. **Otro constructor de copia:**
   ```cpp
   Array<int> test(tmp);  // Copia tmp a test
   ```

3. **Destrucción al salir del scope:**
   ```cpp
   }  // ← Aquí se destruyen tmp y test
   ```

**La Prueba Crítica:**
```
SI la copia es SUPERFICIAL (mala):
────────────────────────────────────────────────
numbers, tmp y test apuntan a LA MISMA memoria
Cuando se destruyen tmp y test → se libera la memoria
numbers queda apuntando a memoria LIBERADA
¡CRASH! o valores corruptos


SI la copia es PROFUNDA (buena):
────────────────────────────────────────────────
numbers tiene su propia memoria
tmp tiene su propia copia
test tiene su propia copia
Cuando se destruyen tmp y test → se libera SU memoria
numbers sigue intacto con SU memoria
✅ TODO BIEN
```

**Visualización:**

```
COPIA SUPERFICIAL (❌ MAL):
──────────────────────────────────────
numbers: [ptr] ──┐
tmp:     [ptr] ──┼─→ [1, 2, 3, ...] ← MISMA memoria
test:    [ptr] ──┘

Al salir del scope:
• Se destruye tmp → libera memoria
• Se destruye test → intenta liberar de nuevo
• numbers apunta a memoria liberada
• ¡CRASH!


COPIA PROFUNDA (✅ BIEN):
──────────────────────────────────────
numbers: [ptr] ──→ [1, 2, 3, ...]  ← Memoria 1
tmp:     [ptr] ──→ [1, 2, 3, ...]  ← Memoria 2 (copia)
test:    [ptr] ──→ [1, 2, 3, ...]  ← Memoria 3 (copia)

Al salir del scope:
• Se destruye tmp → libera Memoria 2
• Se destruye test → libera Memoria 3
• numbers sigue con Memoria 1
• ✅ TODO BIEN
```

---

### 🔸 BLOQUE 3: Verificar que los Valores Siguen Correctos

```cpp
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
```

**Propósito:**
```
Verificar que después de crear y destruir copias,
numbers TODAVÍA tiene los valores correctos
```

**¿Qué prueba?**
- Si ves el mensaje "didn't save the same value!!" → ❌ Copia profunda FALLÓ
- Si no aparece el mensaje → ✅ Copia profunda funcionó

**Por qué es importante:**
```
Si la copia fuera superficial:
• Al destruir tmp y test, se liberaría la memoria
• numbers quedaría apuntando a basura
• Los valores en numbers estarían corruptos
• mirror[i] != numbers[i] → ERROR
```

---

### 🔸 BLOQUE 4: Test de Índice Negativo

```cpp
    try
    {
        numbers[-2] = 0;  // ← Intentar acceder a índice negativo
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';  // ← Debe capturar excepción
    }
```

**Propósito:**
```
Verificar que tu operador [] detecta índices NEGATIVOS
y lanza una excepción
```

**¿Qué debe pasar?**
- Tu `operator[]` debe verificar: `if (index >= _size)`
- `-2` convertido a `size_t` es un número GIGANTE
- Es mayor que `_size` → lanza `std::exception`
- El `catch` captura la excepción
- ✅ Test pasado

**Si NO funcionara:**
```cpp
// ❌ Sin verificación:
T& operator[](size_t index) {
    return _elements[index];  // Acceso a memoria inválida
}

numbers[-2] = 0;  // ¡CRASH! o corrupción de memoria
```

---

### 🔸 BLOQUE 5: Test de Índice Fuera de Rango

```cpp
    try
    {
        numbers[MAX_VAL] = 0;  // ← Intentar acceder fuera del array
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';  // ← Debe capturar excepción
    }
```

**Propósito:**
```
Verificar que tu operador [] detecta índices
FUERA DE RANGO y lanza una excepción
```

**¿Qué debe pasar?**
- Array tiene índices válidos: `0` a `MAX_VAL - 1` (0 a 749)
- Intentas acceder a `numbers[750]` (fuera de rango)
- Tu `operator[]` verifica: `if (index >= _size)`
- 750 >= 750 → true → lanza `std::exception`
- El `catch` captura la excepción
- ✅ Test pasado

---

### 🔸 BLOQUE 6: Modificar y Limpiar

```cpp
    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();  // ← Llena con nuevos valores aleatorios
    }
    
    delete [] mirror;  // ← Libera memoria del array de comparación
    
    return 0;  // ← Fin del programa
}
```

**Propósito:**
```
1. Prueba más el operador [] asignando nuevos valores
2. Limpia la memoria de mirror
3. numbers se destruye automáticamente al salir de main
   (prueba que tu destructor funciona)
```

---

## 📊 Resumen de lo que Prueba

```
╔═══════════════════════════════╦═══════════════════════════════╗
║         QUÉ PRUEBA            ║         CÓMO                  ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Constructor con tamaño        ║ Array<int> numbers(750)       ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Operador [] asignación        ║ numbers[i] = value            ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Constructor de copia          ║ Array<int> tmp = numbers      ║
║ (copia profunda)              ║ Destruye tmp                  ║
║                               ║ Verifica que numbers sigue OK ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Operador [] lectura           ║ mirror[i] != numbers[i]       ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Excepción índice negativo     ║ numbers[-2] = 0               ║
║                               ║ Debe lanzar exception         ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Excepción fuera de rango      ║ numbers[MAX_VAL] = 0          ║
║                               ║ Debe lanzar exception         ║
║                               ║                               ║
╠═══════════════════════════════╬═══════════════════════════════╣
║                               ║                               ║
║ Destructor                    ║ Al salir de main              ║
║ (libera memoria)              ║ No memory leaks               ║
║                               ║                               ║
╚═══════════════════════════════╩═══════════════════════════════╝
```

---

## 🎯 ¿Cómo Usarlo?

### Opción 1: Usar este main en ex02

```bash
cd cpp07/ex02

# Copiar el main del subject
cp ../main.cpp .

# Compilar
make

# Ejecutar
./array
```

### Opción 2: Tener AMBOS mains

```bash
# main.cpp      → El del subject (básico)
# main_extra.cpp → Tu main con tests adicionales

# En el Makefile:
SRCS = main.cpp  # O main_extra.cpp según quieras probar
```

---

## ✅ Si Todo Funciona Bien

Deberías ver:
```bash
$ ./array
(sin errores ni crashes)
$ echo $?
0
```

No debería imprimir:
- ❌ "didn't save the same value!!"
- ❌ Crashes o segmentation faults
- ❌ Memory leaks (verificar con valgrind)

**Con valgrind:**
```bash
valgrind --leak-check=full ./array
# Debería decir: "All heap blocks were freed -- no leaks are possible"
```

---

## ⚠️ Errores Comunes que Este Test Detecta

### Error 1: Copia Superficial

```cpp
// ❌ INCORRECTO:
Array(Array const & other) {
    _size = other._size;
    _elements = other._elements;  // Copia el puntero (superficial)
}

// Al correr el main → CRASH o "didn't save the same value!!"
```

### Error 2: No Verificar Índice

```cpp
// ❌ INCORRECTO:
T& operator[](size_t index) {
    return _elements[index];  // Sin verificación
}

// Al correr el main → CRASH en numbers[-2] o numbers[MAX_VAL]
```

### Error 3: Memory Leak

```cpp
// ❌ INCORRECTO:
~Array() {
    // Olvidé delete[] _elements
}

// valgrind dirá: "definitely lost: X bytes"
```

---

## 🎓 Conclusión

```
┌──────────────────────────────────────────────────────────┐
│              ¿PARA QUÉ ES ESTE MAIN?                     │
├──────────────────────────────────────────────────────────┤
│                                                          │
│  Es el TEST OFICIAL del subject                          │
│                                                          │
│  Verifica que tu clase Array funciona:                   │
│  ✅ Constructores                                        │
│  ✅ Copia profunda                                       │
│  ✅ Operador []                                          │
│  ✅ Excepciones                                          │
│  ✅ Sin memory leaks                                     │
│                                                          │
│  Si este main funciona sin errores:                      │
│  → Tu implementación es CORRECTA                         │
│                                                          │
│  Úsalo para:                                             │
│  • Verificar tu código                                   │
│  • Comparar con tu propio main                           │
│  • Asegurar que cumples el subject                       │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

---

**¡Este main es tu mejor amigo para verificar que todo funciona!** 🎉

Cópialo a `ex02/`, compílalo y asegúrate de que no da errores.



















