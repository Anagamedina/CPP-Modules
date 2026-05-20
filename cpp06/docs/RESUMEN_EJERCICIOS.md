# 📚 RESUMEN COMPLETO - CPP06 (EX00, EX01, EX02)

## 🎯 Visión General del Módulo

Este módulo enseña los **4 tipos de casting en C++**:
- `static_cast` - Conversiones seguras en compilación
- `dynamic_cast` - Identificación de tipos en ejecución
- `reinterpret_cast` - Reinterpretación de bits
- `const_cast` - Modificar calificadores const

---

## 📋 EJERCICIOS

### **EX00: Scalar Converter**
**Objetivo**: Convertir literales entre tipos primitivos (char, int, float, double)
**Cast usado**: `static_cast`

```cpp
// Input: "42"
// Output:
//   char: '*'
//   int: 42
//   float: 42.0f
//   double: 42.0
```

**Conceptos aprendidos:**
- ✅ Conversiones seguras con `static_cast`
- ✅ Parsing de strings con `strtol()` y `strtod()`
- ✅ Manejo de valores especiales (NaN, infinito)
- ✅ Validación de rangos y overflow

**Archivos:**
- `ScalarConverter.hpp` - Declaración de la clase
- `ScalarConverter.cpp` - Implementación (funciones de detección, conversión e impresión)
- `main.cpp` - Programa que recibe un literal como argumento
- `EXPLICACION_SENCILLA.md` - Guía detallada

---

### **EX01: Serialization**
**Objetivo**: Serializar punteros (convertir a número y viceversa)
**Cast usado**: `reinterpret_cast`

```cpp
// Serializar
Data* ptr = &original;
unsigned long num = Serializer::serialize(ptr);

// Deserializar
Data* restaurado = Serializer::deserialize(num);
// restaurado == ptr (mismo puntero)
```

**Conceptos aprendidos:**
- ✅ Serialización de punteros con `reinterpret_cast`
- ✅ Conversión entre punteros y números
- ✅ Limitaciones de la serialización
- ✅ Compatibilidad C++98 con `unsigned long`

**Archivos:**
- `Serializer.hpp` - Declaración de la clase y struct Data
- `Serializer.cpp` - Funciones serialize() y deserialize()
- `main.cpp` - Tests de serialización
- `EXPLICACION_EX01.md` - Guía detallada

---

### **EX02: Identify Real Type**
**Objetivo**: Identificar el tipo real de objetos en tiempo de ejecución
**Cast usado**: `dynamic_cast`

```cpp
// Generar objeto aleatorio
Base* obj = generate();  // Puede ser A, B o C

// Identificar tipo
identify(obj);  // Output: "Tipo identificado: A" (por ejemplo)
```

**Conceptos aprendidos:**
- ✅ Identificación de tipos con `dynamic_cast`
- ✅ Diferencia entre punteros y referencias
- ✅ Manejo de excepciones `std::bad_cast`
- ✅ Clases polimórficas (con `virtual`)

**Archivos:**
- `Base.hpp/cpp` - Clase base polimórfica
- `A.hpp/cpp`, `B.hpp/cpp`, `C.hpp/cpp` - Clases derivadas
- `main.cpp` - Funciones generate() e identify()
- `EXPLICACION_EX02.md` - Guía detallada

---

## 🔄 COMPARACIÓN DE LOS 4 CASTS

| Cast | Uso | Verificación | Peligrosidad | Ejercicio |
|------|-----|--------------|--------------|-----------|
| `static_cast` | Conversiones conocidas | Compilación | Media | **EX00** |
| `dynamic_cast` | Downcasting seguro | Ejecución | Baja | **EX02** |
| `reinterpret_cast` | Reinterpretación de bits | Ninguna | Alta | **EX01** |
| `const_cast` | Modificar const | Ninguna | Media | - |

---

## 📊 TABLA RESUMEN DE EJERCICIOS

### **EX00: Scalar Converter**
```
INPUT               PROCESO                    OUTPUT
"42"         →   Detectar tipo (int)    →   char: '*'
                 Parsear con strtol()       int: 42
                 Convertir con              float: 42.0f
                 static_cast                double: 42.0
```

### **EX01: Serialization**
```
PUNTERO          SERIALIZAR                 DESERIALIZAR
Data* ptr    →   reinterpret_cast      →   reinterpret_cast
0x16dd96c30      unsigned long             Data* restaurado
                 6137932848                0x16dd96c30
```

### **EX02: Identify**
```
OBJETO           GENERAR                    IDENTIFICAR
Base* obj    →   rand() % 3            →   dynamic_cast<A*>()
                 new A/B/C()                dynamic_cast<B*>()
                                           dynamic_cast<C*>()
```

---

## 🎯 CONCEPTOS CLAVE POR EJERCICIO

### **EX00: Conversiones de Tipos Primitivos**
```cpp
// De char a otros tipos
char c = 'A';
int i = static_cast<int>(c);         // 65
float f = static_cast<float>(c);     // 65.0f
double d = static_cast<double>(c);   // 65.0

// De int a otros tipos
int i = 42;
char c = static_cast<char>(i);       // '*'
float f = static_cast<float>(i);     // 42.0f
double d = static_cast<double>(i);   // 42.0

// Casos especiales
double nan = std::numeric_limits<double>::quiet_NaN();
double inf = std::numeric_limits<double>::infinity();
```

### **EX01: Serialización de Punteros**
```cpp
// Serializar: puntero → número
Data* ptr = &objeto;
unsigned long num = reinterpret_cast<unsigned long>(ptr);

// Deserializar: número → puntero
Data* restaurado = reinterpret_cast<Data*>(num);

// ⚠️ IMPORTANTE: Solo funciona si el objeto sigue existiendo
```

### **EX02: Identificación de Tipos**
```cpp
// Con punteros (retorna NULL si falla)
Base* base_ptr = generate();
if (A* a = dynamic_cast<A*>(base_ptr)) {
    // Es tipo A
}

// Con referencias (lanza excepción si falla)
try {
    A& a = dynamic_cast<A&>(*base_ptr);
    // Es tipo A
} catch (std::bad_cast&) {
    // No es tipo A
}
```

---

## 🔧 COMPATIBILIDAD C++98

### **Características usadas (disponibles en C++98):**

✅ **static_cast** - Conversiones seguras
✅ **dynamic_cast** - Identificación de tipos
✅ **reinterpret_cast** - Reinterpretación de bits
✅ **const_cast** - Modificar const
✅ **Excepciones** (`try`, `catch`, `throw`)
✅ **Clases virtuales** (`virtual`)
✅ **`unsigned long`** - Para serialización
✅ **`strtol()`, `strtod()`** - Parsing C++98

### **Características NO usadas (no disponibles en C++98):**

❌ **`nullptr`** - Se usa `NULL`
❌ **`auto`** - Se declaran tipos explícitamente
❌ **`<cstdint>`** - Se usa `unsigned long`
❌ **`std::stoi()`, `std::stod()`** - Se usa `strtol()`, `strtod()`
❌ **Range-based for** - Se usa for tradicional

---

## 📁 ESTRUCTURA DE ARCHIVOS

```
cpp06/
├── ex00/                    # Scalar Converter
│   ├── ScalarConverter.hpp
│   ├── ScalarConverter.cpp  # ← Funciones únicas (check*, display*)
│   ├── main.cpp
│   ├── Makefile
│   └── EXPLICACION_SENCILLA.md
│
├── ex01/                    # Serialization
│   ├── Serializer.hpp       # ← unsigned long (C++98)
│   ├── Serializer.cpp
│   ├── main.cpp
│   ├── Makefile
│   └── EXPLICACION_EX01.md
│
├── ex02/                    # Identify
│   ├── Base.hpp/cpp
│   ├── A.hpp/cpp
│   ├── B.hpp/cpp
│   ├── C.hpp/cpp
│   ├── main.cpp
│   ├── Makefile
│   └── EXPLICACION_EX02.md
│
└── RESUMEN_EJERCICIOS.md    # ← Este archivo
```

---

## 🧪 COMPILAR Y PROBAR TODO

```bash
# EX00
cd ex00 && make && ./scalar_converter 42
cd ex00 && ./scalar_converter nan
cd ex00 && ./scalar_converter 3.14f

# EX01
cd ../ex01 && make && ./serializer

# EX02
cd ../ex02 && make && ./identify

# Limpiar todo
cd ex00 && make fclean
cd ../ex01 && make fclean
cd ../ex02 && make fclean
```

---

## 💡 TIPS DE ESTUDIO

### **1. Estudia en orden:**
1. **EX00** primero (más sencillo - `static_cast`)
2. **EX01** segundo (concepto nuevo - `reinterpret_cast`)
3. **EX02** tercero (más complejo - `dynamic_cast`)

### **2. Entiende las diferencias:**
- **EX00**: Convertir **valores** (char ↔ int ↔ float ↔ double)
- **EX01**: Convertir **punteros a números** (Data* ↔ unsigned long)
- **EX02**: Identificar **tipos de objetos** (Base* → A*, B*, C*)

### **3. Practica los conceptos:**
- Modifica los valores de entrada
- Añade más casos de prueba
- Experimenta con diferentes tipos

### **4. Lee los archivos de explicación:**
- `EXPLICACION_SENCILLA.md` (ex00)
- `EXPLICACION_EX01.md` (ex01)
- `EXPLICACION_EX02.md` (ex02)

---

## 🎓 CONCEPTOS IMPORTANTES

### **1. ¿Cuándo usar cada cast?**

```cpp
// static_cast: Conversiones seguras conocidas
int i = 42;
double d = static_cast<double>(i);  // ✅ Seguro

// dynamic_cast: Downcasting con verificación
Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base);  // ✅ Seguro
if (derived != NULL) { /* usar */ }

// reinterpret_cast: Manipulación de bits (peligroso)
int* ptr = new int(42);
unsigned long num = reinterpret_cast<unsigned long>(ptr);  // ⚠️ Peligroso

// const_cast: Modificar const (rara vez necesario)
const int* const_ptr = &valor;
int* ptr = const_cast<int*>(const_ptr);  // ⚠️ Peligroso
```

### **2. Reglas de oro:**

1. **Prefiere `static_cast`** para conversiones normales
2. **Usa `dynamic_cast`** para downcasting seguro
3. **Evita `reinterpret_cast`** a menos que sea necesario
4. **Nunca uses `const_cast`** para modificar objetos realmente const
5. **Siempre verifica** el resultado de `dynamic_cast`

### **3. Errores comunes:**

❌ **Usar `static_cast` para downcasting sin verificar**
❌ **Asumir que `reinterpret_cast` es seguro**
❌ **Olvidar verificar el resultado de `dynamic_cast`**
❌ **No manejar excepciones de `dynamic_cast` con referencias**
❌ **Usar `const_cast` para modificar objetos const**

---

## 🚀 ¡ÉXITO!

Ahora tienes una comprensión completa de:
- ✅ Los 4 tipos de casting en C++
- ✅ Conversiones de tipos primitivos (ex00)
- ✅ Serialización de punteros (ex01)
- ✅ Identificación de tipos en runtime (ex02)
- ✅ Compatibilidad con C++98

¡Sigue practicando y experimentando! 🎉

