# 🔀 EXPLICACIÓN: SWITCH Y TRY-CATCH EN CPP06

## 📚 Índice
1. [Switch en los ejercicios](#switch)
2. [Try-Catch en los ejercicios](#try-catch)
3. [Comparaciones y cuándo usar cada uno](#comparaciones)
4. [Resumen por ejercicio](#resumen)

---

## 🔀 SWITCH

### **1. Dónde LO USAMOS en el código**

#### **EX02 - En la función `generate()`:**

```cpp
Base* generate(void) {
    int random = rand() % 3;  // Genera 0, 1 o 2
    
    switch (random) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
        default: return NULL;
    }
}
```

**¿Por qué switch aquí?**
- ✅ Tenemos un valor entero (0, 1, 2)
- ✅ Múltiples opciones mutuamente excluyentes
- ✅ Más claro y legible que múltiples `if-else`
- ✅ Fácil añadir más casos en el futuro

**Alternativa con if-else (menos clara):**
```cpp
Base* generate(void) {
    int random = rand() % 3;
    
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else if (random == 2)
        return new C();
    else
        return NULL;
}
```

**Comparación visual:**

```
SWITCH                          IF-ELSE
┌─────────────────────┐        ┌─────────────────────┐
│ switch (random) {   │        │ if (random == 0)    │
│   case 0: ...       │        │   ...               │
│   case 1: ...       │        │ else if (random==1) │
│   case 2: ...       │        │   ...               │
│   default: ...      │        │ else if (random==2) │
│ }                   │        │   ...               │
└─────────────────────┘        └─────────────────────┘
   Más compacto               Más verboso
   Intención clara            Menos claro
```

---

### **2. Dónde PODRÍAMOS usarlo (pero NO lo hicimos)**

#### **EX00 - Para detectar tipo del literal:**

**Lo que tenemos ahora (con if-else):**

```cpp
void ScalarConverter::convert(const std::string& literal) {
    if (checkIfChar(literal)) {
        // convertir desde char
    }
    else if (checkIfInteger(literal)) {
        // convertir desde int
    }
    else if (checkIfFloatType(literal)) {
        // convertir desde float
    }
    else if (checkIfDoubleType(literal)) {
        // convertir desde double
    }
    else {
        outputImpossibleForAll();
    }
}
```

**❌ NO podemos usar switch directamente porque:**
- `switch` solo funciona con tipos enteros/enum/char
- Aquí estamos evaluando condiciones booleanas (true/false)
- No tenemos un valor numérico para evaluar
- Las funciones `checkIfChar()` etc. retornan bool, no int

**✅ Pero PODRÍAMOS refactorizar con enum:**

```cpp
// Primero, definir un enum para los tipos
enum TipoLiteral {
    TIPO_CHAR,
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_DOUBLE,
    TIPO_INVALIDO
};

// Función auxiliar para detectar el tipo
TipoLiteral detectarTipo(const std::string& literal) {
    if (checkIfChar(literal)) return TIPO_CHAR;
    if (checkIfInteger(literal)) return TIPO_INT;
    if (checkIfFloatType(literal)) return TIPO_FLOAT;
    if (checkIfDoubleType(literal)) return TIPO_DOUBLE;
    return TIPO_INVALIDO;
}

// Ahora SÍ podemos usar switch
void ScalarConverter::convert(const std::string& literal) {
    TipoLiteral tipo = detectarTipo(literal);
    
    switch (tipo) {  // ✅ Ahora sí funciona con switch
        case TIPO_CHAR: {
            char c = literal[0];
            displayCharType(static_cast<double>(c));
            displayIntType(static_cast<double>(c));
            displayFloatType(static_cast<float>(c));
            displayDoubleType(static_cast<double>(c));
            break;
        }
        case TIPO_INT: {
            char* end;
            errno = 0;
            long num = std::strtol(literal.c_str(), &end, 10);
            if (errno == ERANGE || *end != '\0' ||
                num < std::numeric_limits<int>::min() ||
                num > std::numeric_limits<int>::max()) {
                outputImpossibleForAll();
                break;
            }
            int i = static_cast<int>(num);
            displayCharType(static_cast<double>(i));
            displayIntType(static_cast<double>(i));
            displayFloatType(static_cast<float>(i));
            displayDoubleType(static_cast<double>(i));
            break;
        }
        case TIPO_FLOAT: {
            // ... conversión desde float
            break;
        }
        case TIPO_DOUBLE: {
            // ... conversión desde double
            break;
        }
        case TIPO_INVALIDO:
        default:
            outputImpossibleForAll();
            break;
    }
}
```

**Ventajas de esta refactorización:**
- ✅ Más organizado y estructurado
- ✅ Fácil añadir nuevos tipos
- ✅ El switch hace explícitas todas las opciones
- ✅ El compilador advierte si falta un caso

**Desventajas:**
- ❌ Más líneas de código
- ❌ Función extra (`detectarTipo()`)
- ❌ Para este ejercicio simple, if-else es suficiente

---

### **3. Reglas de uso de switch**

**Switch SOLO funciona con:**
```cpp
// ✅ Tipos enteros
int valor = 5;
switch (valor) { ... }

// ✅ Caracteres
char letra = 'A';
switch (letra) { ... }

// ✅ Enumeraciones
enum Color { ROJO, VERDE, AZUL };
Color color = ROJO;
switch (color) { ... }

// ❌ NO funciona con:
std::string texto = "hola";
switch (texto) { ... }  // ERROR: no compila

// ❌ NO funciona con:
double decimal = 3.14;
switch (decimal) { ... }  // ERROR: no compila

// ❌ NO funciona con:
bool condicion = true;
switch (condicion) { ... }  // Técnicamente compila pero es mala práctica
```

**Estructura correcta de switch:**

```cpp
switch (variable) {
    case VALOR1:
        // código
        break;  // ← IMPORTANTE: sin break, continúa al siguiente caso
    
    case VALOR2:
        // código
        break;
    
    case VALOR3:
    case VALOR4:  // Múltiples casos pueden compartir código
        // código compartido
        break;
    
    default:  // Caso por defecto (opcional pero recomendado)
        // código si ningún caso coincide
        break;
}
```

**Fall-through (sin break):**

```cpp
// A veces queremos que "caiga" al siguiente caso (sin break)
switch (random) {
    case 0:
        std::cout << "Es 0" << std::endl;
        // NO hay break: continúa a case 1
    case 1:
        std::cout << "Es 0 o 1" << std::endl;
        break;
    case 2:
        std::cout << "Es 2" << std::endl;
        break;
}

// Si random = 0:
// Output:
//   Es 0
//   Es 0 o 1

// Si random = 1:
// Output:
//   Es 0 o 1
```

---

## 🎯 TRY-CATCH

### **1. Dónde LO USAMOS en el código**

#### **EX02 - En la función `identify(Base&)` con referencias:**

```cpp
void identify(Base& p) {
    // Intentar convertir a A&
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "Tipo identificado: A" << std::endl;
        return;
    } catch (std::bad_cast&) {
        // No es tipo A, continuamos
    }
    
    // Intentar convertir a B&
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "Tipo identificado: B" << std::endl;
        return;
    } catch (std::bad_cast&) {
        // No es tipo B, continuamos
    }
    
    // Intentar convertir a C&
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "Tipo identificado: C" << std::endl;
        return;
    } catch (std::bad_cast&) {
        // No es tipo C
    }
    
    std::cout << "Tipo desconocido" << std::endl;
}
```

**¿Por qué try-catch aquí?**

1. **`dynamic_cast` con referencias lanza excepción si falla**
   ```cpp
   Base& ref = ...;
   A& a = dynamic_cast<A&>(ref);  // Lanza std::bad_cast si falla
   ```

2. **No podemos verificar con `if` porque son referencias**
   ```cpp
   // ❌ NO FUNCIONA con referencias (no hay NULL)
   if (dynamic_cast<A&>(ref)) { ... }  // ERROR: no se puede comparar
   ```

3. **Es la ÚNICA forma de manejar el fallo con referencias**
   ```cpp
   // Sin try-catch: el programa crashea si falla
   A& a = dynamic_cast<A&>(ref);  // ❌ Crashea si ref no es tipo A
   
   // Con try-catch: controlamos el error
   try {
       A& a = dynamic_cast<A&>(ref);  // ✅ Capturamos el error
   } catch (std::bad_cast&) {
       // Manejamos el error
   }
   ```

4. **Evita que el programa crashee**

**Flujo visual:**

```
INTENTO 1: dynamic_cast<A&>
    ↓
¿Es tipo A?
    ├─ SÍ → Output "A" → return
    └─ NO → Lanza std::bad_cast
               ↓
           catch captura
               ↓
        Continuar a INTENTO 2

INTENTO 2: dynamic_cast<B&>
    ↓
¿Es tipo B?
    ├─ SÍ → Output "B" → return
    └─ NO → Lanza std::bad_cast
               ↓
           catch captura
               ↓
        Continuar a INTENTO 3

INTENTO 3: dynamic_cast<C&>
    ↓
¿Es tipo C?
    ├─ SÍ → Output "C" → return
    └─ NO → Lanza std::bad_cast
               ↓
           catch captura
               ↓
        Output "Tipo desconocido"
```

---

### **2. Diferencia con punteros (NO necesita try-catch)**

#### **Con punteros: SIN try-catch**

```cpp
void identify(Base* p) {
    // Con punteros: NO necesitamos try-catch
    if (dynamic_cast<A*>(p)) {  // Retorna NULL si falla
        std::cout << "Tipo identificado: A" << std::endl;
        return;
    }
    
    if (dynamic_cast<B*>(p)) {
        std::cout << "Tipo identificado: B" << std::endl;
        return;
    }
    
    if (dynamic_cast<C*>(p)) {
        std::cout << "Tipo identificado: C" << std::endl;
        return;
    }
    
    std::cout << "Tipo desconocido" << std::endl;
}
```

**¿Por qué NO necesita try-catch?**

```cpp
Base* ptr = ...;
A* a = dynamic_cast<A*>(ptr);

// Si ptr apunta a un objeto A:
//   → dynamic_cast retorna puntero válido
//   → a != NULL

// Si ptr NO apunta a un objeto A:
//   → dynamic_cast retorna NULL
//   → a == NULL

// Podemos verificar con if:
if (a != NULL) {  // ✅ Funciona porque puede ser NULL
    // Es tipo A
}
```

**Comparación visual:**

```
CON PUNTEROS                    CON REFERENCIAS
┌─────────────────────┐        ┌─────────────────────┐
│ dynamic_cast<A*>()  │        │ dynamic_cast<A&>()  │
│         ↓           │        │         ↓           │
│   ¿Es tipo A?       │        │   ¿Es tipo A?       │
│   ├─ SÍ → puntero   │        │   ├─ SÍ → referencia│
│   └─ NO → NULL      │        │   └─ NO → EXCEPCIÓN │
│         ↓           │        │         ↓           │
│   if (ptr != NULL)  │        │   catch(bad_cast)   │
└─────────────────────┘        └─────────────────────┘
  Verificación simple           Manejo de excepciones
```

---

### **3. Dónde PODRÍAMOS usarlo (pero NO es necesario)**

#### **EX00 - Para manejar errores de parsing (solo en C++11+)**

```cpp
// Si usáramos std::stoi en lugar de strtol (C++11, no C++98)
void ScalarConverter::convertToInteger(const std::string& literal) {
    try {
        int i = std::stoi(literal);  // Puede lanzar std::invalid_argument
        displayCharType(static_cast<double>(i));
        displayIntType(static_cast<double>(i));
        displayFloatType(static_cast<float>(i));
        displayDoubleType(static_cast<double>(i));
    } catch (std::invalid_argument& e) {
        // No se pudo convertir
        outputImpossibleForAll();
    } catch (std::out_of_range& e) {
        // Número demasiado grande
        outputImpossibleForAll();
    }
}

// ⚠️ Pero en C++98 usamos strtol que NO lanza excepciones
// Usamos verificación manual:
char* end;
errno = 0;
long num = std::strtol(literal.c_str(), &end, 10);
if (errno == ERANGE || *end != '\0') {
    outputImpossibleForAll();
}
```

**Ventaja de try-catch:**
- ✅ Más claro: separa código normal de manejo de errores
- ✅ Automático: no olvidas verificar errores

**Desventaja de try-catch:**
- ❌ Más lento que verificación manual
- ❌ No disponible en C++98 para estas funciones

#### **EX01 - Serialización con validación**

```cpp
// Podríamos añadir validación con excepciones
class SerializerException : public std::exception {
public:
    const char* what() const throw() {
        return "Error de serialización";
    }
};

unsigned long Serializer::serialize(Data* ptr) {
    if (ptr == NULL) {
        throw SerializerException();  // Lanzar excepción si es NULL
    }
    return reinterpret_cast<unsigned long>(ptr);
}

Data* Serializer::deserialize(unsigned long raw) {
    if (raw == 0) {
        throw SerializerException();  // Lanzar excepción si es 0
    }
    return reinterpret_cast<Data*>(raw);
}

// En main:
int main() {
    try {
        // Intentar serializar puntero NULL
        unsigned long num = Serializer::serialize(NULL);
    } catch (SerializerException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    try {
        // Intentar deserializar 0
        Data* ptr = Serializer::deserialize(0);
    } catch (SerializerException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

**¿Por qué NO lo hacemos en el ejercicio?**
- El ejercicio no requiere validación
- Añade complejidad innecesaria
- El sujeto no lo pide

---

### **4. Estructura de try-catch**

**Sintaxis básica:**

```cpp
try {
    // Código que puede lanzar excepciones
    operacion_peligrosa();
} catch (TipoExcepcion1& e) {
    // Manejo de excepción tipo 1
} catch (TipoExcepcion2& e) {
    // Manejo de excepción tipo 2
} catch (...) {
    // Captura CUALQUIER excepción (catch-all)
}
```

**Múltiples catches:**

```cpp
try {
    int valor = procesar_input(input);
    guardar_en_archivo(valor);
} catch (std::invalid_argument& e) {
    std::cerr << "Argumento inválido: " << e.what() << std::endl;
} catch (std::out_of_range& e) {
    std::cerr << "Fuera de rango: " << e.what() << std::endl;
} catch (std::ios_base::failure& e) {
    std::cerr << "Error de archivo: " << e.what() << std::endl;
} catch (std::exception& e) {
    std::cerr << "Error general: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "Error desconocido" << std::endl;
}
```

**Orden de catches (de más específico a más general):**

```cpp
try {
    // código
} catch (ClaseDerivada& e) {  // ← Más específica primero
    // ...
} catch (ClaseBase& e) {      // ← Más general después
    // ...
} catch (...) {                // ← Catch-all al final
    // ...
}

// ❌ INCORRECTO (el catch general captura todo):
try {
    // código
} catch (...) {                // Captura TODO
    // Este catch capturará TODAS las excepciones
}
catch (std::exception& e) {    // ← Nunca se ejecuta
    // Este código es inalcanzable
}
```

**Re-lanzar excepciones:**

```cpp
try {
    operacion();
} catch (std::exception& e) {
    std::cerr << "Error capturado: " << e.what() << std::endl;
    // Hacer algo (logging, limpieza, etc.)
    throw;  // ← Re-lanzar la misma excepción
}
```

---

## 📊 COMPARACIONES

### **1. SWITCH vs IF-ELSE**

| Característica | `switch` | `if-else` |
|----------------|----------|-----------|
| **Tipo de condición** | Solo enteros/enum/char | Cualquier condición booleana |
| **Múltiples valores** | Muy claro y compacto | Puede ser verboso |
| **Rangos de valores** | ❌ No soporta (`case 1..10:`) | ✅ Soporta (`if (x >= 1 && x <= 10)`) |
| **Rendimiento** | Ligeramente más rápido* | Normal |
| **Legibilidad** | Mejor para muchos casos (5+) | Mejor para pocas condiciones (2-3) |
| **Mantenibilidad** | Fácil añadir casos | Puede volverse confuso |
| **Fall-through** | ✅ Posible (sin break) | ❌ No tiene |

\* *El compilador puede optimizar switch a una tabla de saltos (jump table)*

**Ejemplo comparativo:**

```cpp
// SWITCH (más claro con muchos casos)
switch (dia) {
    case 1: std::cout << "Lunes"; break;
    case 2: std::cout << "Martes"; break;
    case 3: std::cout << "Miércoles"; break;
    case 4: std::cout << "Jueves"; break;
    case 5: std::cout << "Viernes"; break;
    case 6: std::cout << "Sábado"; break;
    case 7: std::cout << "Domingo"; break;
    default: std::cout << "Inválido"; break;
}

// IF-ELSE (más verboso)
if (dia == 1) std::cout << "Lunes";
else if (dia == 2) std::cout << "Martes";
else if (dia == 3) std::cout << "Miércoles";
else if (dia == 4) std::cout << "Jueves";
else if (dia == 5) std::cout << "Viernes";
else if (dia == 6) std::cout << "Sábado";
else if (dia == 7) std::cout << "Domingo";
else std::cout << "Inválido";
```

**Cuándo usar switch:**
- ✅ Múltiples casos basados en un valor entero/enum
- ✅ 5 o más casos diferentes
- ✅ Los casos son valores específicos (no rangos)
- ✅ Necesitas fall-through entre casos

**Cuándo usar if-else:**
- ✅ Condiciones complejas (`if (x > 10 && y < 20)`)
- ✅ Rangos de valores (`if (edad >= 18)`)
- ✅ Condiciones booleanas
- ✅ Menos de 5 casos

---

### **2. TRY-CATCH vs Códigos de Error**

| Característica | `try-catch` | Verificar códigos |
|----------------|-------------|-------------------|
| **Cuando falla** | Lanza excepción | Retorna NULL/false/código |
| **Verificación** | Automática (catch) | Manual (if) |
| **Limpieza de código** | Separa lógica normal de errores | Mezclado |
| **Rendimiento** | Más lento (cuando hay excepción) | Más rápido |
| **Uso** | Errores excepcionales | Validaciones normales |
| **Propagación** | Automática hacia arriba | Manual |
| **Recursos** | RAII funciona bien | Puede requerir limpieza manual |

**Ejemplo comparativo:**

```cpp
// CON TRY-CATCH (separa lógica de errores)
try {
    Archivo archivo("datos.txt");
    archivo.escribir("Hola");
    archivo.escribir("Mundo");
    archivo.cerrar();
    // Lógica normal sin verificaciones
} catch (ArchivoNoExiste& e) {
    std::cerr << "Archivo no existe" << std::endl;
} catch (ErrorEscritura& e) {
    std::cerr << "Error al escribir" << std::endl;
}

// CON CÓDIGOS DE ERROR (verificación manual)
Archivo* archivo = abrirArchivo("datos.txt");
if (archivo == NULL) {
    std::cerr << "Archivo no existe" << std::endl;
    return;
}

if (!archivo->escribir("Hola")) {
    std::cerr << "Error al escribir" << std::endl;
    cerrarArchivo(archivo);
    return;
}

if (!archivo->escribir("Mundo")) {
    std::cerr << "Error al escribir" << std::endl;
    cerrarArchivo(archivo);
    return;
}

cerrarArchivo(archivo);
```

**Cuándo usar try-catch:**
- ✅ Errores realmente excepcionales (archivo no encontrado, sin memoria)
- ✅ Errores que deben propagarse varios niveles
- ✅ Código más limpio (sin if en cada línea)
- ✅ Cuando usas RAII (destructores automáticos)

**Cuándo usar códigos de error:**
- ✅ Validaciones normales (input inválido)
- ✅ Rendimiento crítico
- ✅ C++98 con funciones que no lanzan excepciones
- ✅ Código simple y lineal

---

## 📝 RESUMEN POR EJERCICIO

### **EX00 - Scalar Converter**

**❌ NO usa switch**
- Razón: Las condiciones son booleanas, no valores enteros
- Código actual usa if-else para verificar tipos
- Podría refactorizarse con enum + switch, pero no es necesario

**❌ NO usa try-catch**
- Razón: Usamos `strtol` y `strtod` que NO lanzan excepciones
- Verificamos errores manualmente con `errno` y puntero `end`
- En C++11+ podríamos usar `std::stoi` con try-catch, pero no en C++98

**✅ Usa if-else**
- Para verificar el tipo del literal
- Simple y suficiente para 4 casos

---

### **EX01 - Serialization**

**❌ NO usa switch**
- Razón: No hay múltiples casos numéricos que evaluar
- Solo hay 2 funciones simples (serialize y deserialize)

**❌ NO usa try-catch**
- Razón: No hay operaciones que lancen excepciones
- `reinterpret_cast` nunca lanza excepciones
- Podríamos añadir validación con excepciones, pero no es necesario

**✅ Simple y directo**
- Solo conversiones con `reinterpret_cast`
- No necesita control de flujo complejo

---

### **EX02 - Identify**

**✅ USA switch**
- Dónde: En `generate()` para crear objetos aleatorios
- Por qué: Tenemos un valor entero (0, 1, 2) con 3 casos
- Más claro que if-else para este caso

**✅ USA try-catch**
- Dónde: En `identify(Base&)` con referencias
- Por qué: `dynamic_cast` con referencias lanza `std::bad_cast` si falla
- Es la ÚNICA forma de manejar el error con referencias

**✅ NO usa try-catch**
- Dónde: En `identify(Base*)` con punteros
- Por qué: Con punteros, `dynamic_cast` retorna NULL (no lanza excepción)
- Usamos verificación simple con if

---

## 💡 CONCLUSIÓN GENERAL

### **¿Por qué se usan?**

**Switch:**
- Cuando tienes un valor entero/enum con múltiples casos posibles
- Hace el código más claro y mantenible
- Ejemplo: Elegir entre opciones numeradas (0, 1, 2, etc.)

**Try-catch:**
- Cuando una operación puede lanzar una excepción
- Separar lógica normal de manejo de errores
- Ejemplo: `dynamic_cast` con referencias OBLIGA a usarlo

### **En nuestros ejercicios específicamente:**

1. **Switch en `generate()`**
   - Perfecto para elegir entre 3 opciones basadas en número aleatorio
   - Más claro que 3 if-else

2. **Try-catch en `identify(Base&)`**
   - Obligatorio porque `dynamic_cast` con referencias lanza excepciones
   - No hay alternativa (referencias no pueden ser NULL)

3. **If-else en resto del código**
   - Suficiente para condiciones booleanas simples
   - No necesitamos la complejidad de switch o try-catch

### **Principio general:**

> Usa la herramienta más simple que resuelva el problema.
> 
> - ¿Valor entero con múltiples casos? → switch
> - ¿Condición booleana? → if-else
> - ¿Operación que lanza excepciones? → try-catch
> - ¿Código de error simple? → verificación manual

---

## 🎓 EJERCICIOS DE PRÁCTICA

Para entender mejor, intenta:

1. **Refactorizar EX00 con switch + enum**
2. **Añadir validación con excepciones en EX01**
3. **Implementar `identify()` solo con referencias (sin punteros)**

¡Espero que esta explicación te haya ayudado a entender cuándo y por qué usar switch y try-catch! 🚀



