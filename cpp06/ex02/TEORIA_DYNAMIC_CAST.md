# 📚 TEORÍA COMPLETA - DYNAMIC CAST (CPP06 EX02)

## 🎯 Objetivo del Ejercicio

El ejercicio de **Identificación de Tipos** enseña a usar `dynamic_cast` para determinar el tipo real de un objeto en tiempo de ejecución. Es fundamental para entender RTTI (Run-Time Type Information) y el polimorfismo en C++.

---

## 🔧 1. CONCEPTOS FUNDAMENTALES

### 📋 **1.1 ¿Qué es el Polimorfismo?**

**Polimorfismo** = "muchas formas" - la capacidad de un objeto de tomar diferentes formas.

```cpp
class Animal {
public:
    virtual void hacerSonido() = 0;
    virtual ~Animal() {}
};

class Perro : public Animal {
public:
    void hacerSonido() { std::cout << "Guau!" << std::endl; }
};

class Gato : public Animal {
public:
    void hacerSonido() { std::cout << "Miau!" << std::endl; }
};

// Polimorfismo en acción:
Animal* animal = new Perro();  // Animal* apunta a Perro
animal->hacerSonido();  // Output: "Guau!" (llamada polimórfica)
```

**Representación en memoria:**

```
PUNTERO                OBJETO REAL
┌─────────────┐       ┌─────────────────┐
│ Animal* ptr │ ───→  │ Objeto Perro    │
│ Tipo: Animal│       │ Tipo REAL: Perro│
└─────────────┘       └─────────────────┘
```

### 📋 **1.2 ¿Qué es RTTI?**

**RTTI (Run-Time Type Information)** = Información de tipos en tiempo de ejecución.

Permite que el programa **sepa** qué tipo de objeto tiene realmente en runtime.

```cpp
Base* ptr = generate();  // Puede ser A, B o C

// Sin RTTI: No sabes qué tipo es
// Con RTTI: Puedes preguntarle al objeto qué tipo es
```

**Mecanismo de RTTI:**

```
CLASE POLIMÓRFICA
┌────────────────────────────────┐
│ Puntero a vtable               │ ← Añadido automáticamente
├────────────────────────────────┤
│ Miembros de la clase...        │
└────────────────────────────────┘
         ↓
    VTABLE (Tabla Virtual)
┌────────────────────────────────┐
│ type_info (información de tipo)│ ← RTTI
│ Punteros a funciones virtuales │
└────────────────────────────────┘
```

### 📋 **1.3 ¿Qué es dynamic_cast?**

`dynamic_cast` es un operador de casting que:
1. **Verifica** el tipo real del objeto en runtime
2. **Convierte** de forma segura entre tipos relacionados
3. **Retorna NULL** (punteros) o **lanza excepción** (referencias) si falla

```cpp
// Sintaxis
Derivada* ptr_derivada = dynamic_cast<Derivada*>(ptr_base);

// Si ptr_base realmente apunta a Derivada:
//   → dynamic_cast retorna el puntero convertido
// Si NO:
//   → dynamic_cast retorna NULL
```

---

## 🔄 2. DYNAMIC_CAST EN PROFUNDIDAD

### 📋 **2.1 Upcasting vs Downcasting**

**Upcasting** = Convertir de clase derivada a clase base (siempre seguro)
**Downcasting** = Convertir de clase base a clase derivada (necesita verificación)

```cpp
class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void metodoEspecifico() {}
};

// UPCASTING (Derived → Base): Siempre seguro
Derived* derived = new Derived();
Base* base = derived;  // Conversión implícita, siempre OK

// DOWNCASTING (Base → Derived): Necesita verificación
Base* base_ptr = new Derived();  // Sabemos que es Derived

// ❌ PELIGROSO: static_cast (sin verificación)
Derived* d1 = static_cast<Derived*>(base_ptr);

// ✅ SEGURO: dynamic_cast (con verificación)
Derived* d2 = dynamic_cast<Derived*>(base_ptr);
if (d2 != NULL) {
    d2->metodoEspecifico();  // Seguro
}
```

**Visualización:**

```
JERARQUÍA DE CLASES

      Base
        ↓
    Upcasting ✅ (siempre seguro)
        ↑
    Downcasting ⚠️ (necesita dynamic_cast)
        ↓
    Derived
```

### 📋 **2.2 dynamic_cast con Punteros**

```cpp
Base* base_ptr = generate();  // Puede ser A, B o C

// Intentar convertir a A*
A* a_ptr = dynamic_cast<A*>(base_ptr);

if (a_ptr != NULL) {
    // ✅ La conversión tuvo éxito
    // base_ptr apunta realmente a un objeto A
    std::cout << "Es tipo A" << std::endl;
} else {
    // ❌ La conversión falló
    // base_ptr NO apunta a un objeto A
    std::cout << "NO es tipo A" << std::endl;
}
```

**¿Qué hace dynamic_cast internamente?**

```
PASO 1: Recibe Base* que apunta a un objeto
┌─────────────────────────────┐
│ Base* base_ptr              │
│ Apunta a: ??? (A, B o C)    │
└─────────────────────────────┘

PASO 2: Consulta la vtable del objeto
┌─────────────────────────────┐
│ vtable del objeto           │
│ type_info: "clase B"        │
└─────────────────────────────┘

PASO 3: Compara con el tipo solicitado (A)
type_info del objeto: "B"
Tipo solicitado: "A"
¿Coinciden? NO

PASO 4: Retorna NULL (no coinciden)
A* resultado = NULL
```

### 📋 **2.3 dynamic_cast con Referencias**

```cpp
Base& base_ref = *generate();  // Referencia a Base

// Intentar convertir a A&
try {
    A& a_ref = dynamic_cast<A&>(base_ref);
    // ✅ La conversión tuvo éxito
    std::cout << "Es tipo A" << std::endl;
} catch (std::bad_cast& e) {
    // ❌ La conversión falló
    // Se lanzó una excepción
    std::cout << "NO es tipo A" << std::endl;
}
```

**Diferencias entre punteros y referencias:**

| Punteros | Referencias |
|----------|-------------|
| Retorna `NULL` si falla | Lanza `std::bad_cast` si falla |
| Fácil verificar con `if (ptr != NULL)` | Requiere `try-catch` |
| Puede ser `NULL` | Nunca puede ser "inválida" |
| Más común | Menos común |

---

## 🏗️ 3. IMPLEMENTACIÓN TÉCNICA

### 📋 **3.1 Requisitos para dynamic_cast**

**1. La clase base debe ser polimórfica**

```cpp
// ❌ NO FUNCIONA (clase no polimórfica)
class Base {
public:
    ~Base() {}  // Destructor NO virtual
};

// ✅ FUNCIONA (clase polimórfica)
class Base {
public:
    virtual ~Base() {}  // Destructor virtual
};
```

**¿Por qué necesita `virtual`?**

`virtual` hace que el compilador añada una **vtable** al objeto, que contiene la información de tipo (RTTI).

```
SIN virtual:
┌────────────────┐
│ Miembros       │
└────────────────┘

CON virtual:
┌────────────────┐
│ Puntero vtable │ ← RTTI está aquí
├────────────────┤
│ Miembros       │
└────────────────┘
```

**2. RTTI debe estar habilitado**

```bash
# Compilar con RTTI habilitado (por defecto)
g++ -std=c++98 main.cpp

# Compilar SIN RTTI (no funciona dynamic_cast)
g++ -std=c++98 -fno-rtti main.cpp  # ❌ dynamic_cast no funciona
```

### 📋 **3.2 Anatomía del Ejercicio**

**Jerarquía de clases:**

```cpp
class Base {
public:
    virtual ~Base() {}  // Hace la clase polimórfica
};

class A : public Base {};
class B : public Base {};
class C : public Base {};
```

**Función generate():**

```cpp
Base* generate(void) {
    int random = rand() % 3;
    
    switch (random) {
        case 0: return new A();  // Retorna A* como Base*
        case 1: return new B();  // Retorna B* como Base*
        case 2: return new C();  // Retorna C* como Base*
    }
}
```

**Función identify() con punteros:**

```cpp
void identify(Base* p) {
    // Probar si es A
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
        return;
    }
    
    // Probar si es B
    if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
        return;
    }
    
    // Probar si es C
    if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
        return;
    }
}
```

**Función identify() con referencias:**

```cpp
void identify(Base& p) {
    // Probar si es A
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    // Probar si es B
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    // Probar si es C
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::bad_cast&) {}
}
```

---

## 🔬 4. CASOS AVANZADOS

### 📋 **4.1 Múltiples Intentos de Conversión**

```cpp
void procesarObjeto(Base* obj) {
    // Intentar como A
    if (A* a = dynamic_cast<A*>(obj)) {
        std::cout << "Procesando como A" << std::endl;
        // Código específico para A
        return;
    }
    
    // Intentar como B
    if (B* b = dynamic_cast<B*>(obj)) {
        std::cout << "Procesando como B" << std::endl;
        // Código específico para B
        return;
    }
    
    // Intentar como C
    if (C* c = dynamic_cast<C*>(obj)) {
        std::cout << "Procesando como C" << std::endl;
        // Código específico para C
        return;
    }
    
    std::cout << "Tipo desconocido" << std::endl;
}
```

### 📋 **4.2 Patrón Visitor Simplificado**

```cpp
class Visitor {
public:
    void visit(Base* obj) {
        if (A* a = dynamic_cast<A*>(obj)) {
            visitA(a);
        } else if (B* b = dynamic_cast<B*>(obj)) {
            visitB(b);
        } else if (C* c = dynamic_cast<C*>(obj)) {
            visitC(c);
        }
    }
    
    virtual void visitA(A* a) = 0;
    virtual void visitB(B* b) = 0;
    virtual void visitC(C* c) = 0;
};
```

### 📋 **4.3 Cache de Tipos**

```cpp
class TypeCache {
    std::map<Base*, std::string> cache;
    
public:
    std::string getType(Base* obj) {
        // Verificar si ya está en caché
        if (cache.find(obj) != cache.end()) {
            return cache[obj];
        }
        
        // Determinar tipo
        std::string tipo;
        if (dynamic_cast<A*>(obj)) {
            tipo = "A";
        } else if (dynamic_cast<B*>(obj)) {
            tipo = "B";
        } else if (dynamic_cast<C*>(obj)) {
            tipo = "C";
        }
        
        // Guardar en caché
        cache[obj] = tipo;
        return tipo;
    }
};
```

---

## ⚡ 5. RENDIMIENTO Y OPTIMIZACIÓN

### 📋 **5.1 Costo de dynamic_cast**

```cpp
// Benchmark simplificado
#include <chrono>

void benchmark() {
    Base* obj = new A();
    const int iterations = 1000000;
    
    // Medir static_cast
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        A* a = static_cast<A*>(obj);
        (void)a;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto static_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Medir dynamic_cast
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        A* a = dynamic_cast<A*>(obj);
        (void)a;
    }
    end = std::chrono::high_resolution_clock::now();
    auto dynamic_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "static_cast: " << static_time.count() << " μs" << std::endl;
    std::cout << "dynamic_cast: " << dynamic_time.count() << " μs" << std::endl;
    
    delete obj;
}
```

**Resultados típicos:**
- `static_cast`: ~0 μs (optimizado completamente)
- `dynamic_cast`: ~50-100 μs (consulta vtable)

### 📋 **5.2 Alternativas Más Rápidas**

**Opción 1: Enum de Tipo**

```cpp
enum TipoObjeto { TIPO_A, TIPO_B, TIPO_C };

class Base {
    TipoObjeto tipo;
public:
    Base(TipoObjeto t) : tipo(t) {}
    virtual ~Base() {}
    TipoObjeto getTipo() const { return tipo; }
};

class A : public Base {
public:
    A() : Base(TIPO_A) {}
};

// Uso (más rápido que dynamic_cast)
if (obj->getTipo() == TIPO_A) {
    A* a = static_cast<A*>(obj);  // Seguro porque ya verificamos
}
```

**Opción 2: Función Virtual**

```cpp
class Base {
public:
    virtual ~Base() {}
    virtual std::string getTipo() const = 0;
};

class A : public Base {
public:
    std::string getTipo() const { return "A"; }
};

// Uso (más rápido que dynamic_cast)
if (obj->getTipo() == "A") {
    A* a = static_cast<A*>(obj);
}
```

---

## 🧪 6. TESTING Y VERIFICACIÓN

### 📋 **6.1 Test: Todos los Tipos**

```cpp
void test_todos_tipos() {
    Base* objetos[] = { new A(), new B(), new C() };
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Objeto " << i << ": ";
        identify(objetos[i]);
        delete objetos[i];
    }
}
```

### 📋 **6.2 Test: Conversiones Inválidas**

```cpp
void test_conversiones_invalidas() {
    Base* base = new Base();  // Solo Base, no derivada
    
    A* a = dynamic_cast<A*>(base);
    assert(a == NULL);  // Debe ser NULL
    
    B* b = dynamic_cast<B*>(base);
    assert(b == NULL);  // Debe ser NULL
    
    delete base;
    std::cout << "Test conversiones inválidas: OK" << std::endl;
}
```

### 📋 **6.3 Test: Referencias con Excepciones**

```cpp
void test_referencias() {
    Base* obj = new B();
    
    try {
        A& a = dynamic_cast<A&>(*obj);
        assert(false);  // No debería llegar aquí
    } catch (std::bad_cast&) {
        std::cout << "Excepción capturada correctamente" << std::endl;
    }
    
    try {
        B& b = dynamic_cast<B&>(*obj);
        std::cout << "Conversión a B exitosa" << std::endl;
    } catch (std::bad_cast&) {
        assert(false);  // No debería lanzar excepción
    }
    
    delete obj;
}
```

---

## 💡 7. MEJORES PRÁCTICAS

### ✅ **Do's (Hacer)**

1. **Siempre verifica el resultado con punteros**
   ```cpp
   // ✅ BUENO
   A* a = dynamic_cast<A*>(ptr);
   if (a != NULL) {
       a->metodo();
   }
   ```

2. **Usa try-catch con referencias**
   ```cpp
   // ✅ BUENO
   try {
       A& a = dynamic_cast<A&>(ref);
       a.metodo();
   } catch (std::bad_cast&) {
       // Manejar error
   }
   ```

3. **Prefiere soluciones polimórficas cuando sea posible**
   ```cpp
   // ✅ MEJOR: Usar funciones virtuales
   class Base {
   public:
       virtual void procesar() = 0;
   };
   
   // En lugar de:
   if (A* a = dynamic_cast<A*>(ptr)) {
       // procesar A
   }
   ```

### ❌ **Don'ts (No hacer)**

1. **No ignores el resultado de dynamic_cast**
   ```cpp
   // ❌ PELIGROSO
   A* a = dynamic_cast<A*>(ptr);
   a->metodo();  // Puede crashear si a == NULL
   ```

2. **No uses dynamic_cast en loops críticos**
   ```cpp
   // ❌ LENTO
   for (int i = 0; i < 1000000; i++) {
       if (dynamic_cast<A*>(objetos[i])) {
           // ...
       }
   }
   ```

3. **No uses dynamic_cast como solución a mal diseño**
   ```cpp
   // ❌ MAL DISEÑO
   // Si necesitas saber el tipo constantemente,
   // considera rediseñar con funciones virtuales
   ```

---

## 🎯 8. RESUMEN TÉCNICO

### 📋 **Conceptos Clave**

1. **dynamic_cast** = Conversión segura con verificación en runtime
2. **RTTI** = Información de tipos en tiempo de ejecución
3. **Polimorfismo** = Necesario para dynamic_cast
4. **virtual** = Hace que RTTI esté disponible
5. **Punteros** = Retorna NULL si falla
6. **Referencias** = Lanza std::bad_cast si falla

### 📋 **Cuándo Usar dynamic_cast**

✅ **Usar cuando:**
- Necesitas downcasting seguro
- El tipo real puede variar
- La seguridad es más importante que el rendimiento

❌ **NO usar cuando:**
- Puedes usar funciones virtuales
- El rendimiento es crítico
- Ya conoces el tipo en compilación

---

## 🚀 9. PRÓXIMOS PASOS

Después de dominar este ejercicio:
- **Patrón Visitor** completo
- **typeid** para obtener información de tipo
- **std::type_info** para comparar tipos
- **Diseño polimórfico** avanzado

¡`dynamic_cast` es una herramienta poderosa para programación polimórfica segura!


























