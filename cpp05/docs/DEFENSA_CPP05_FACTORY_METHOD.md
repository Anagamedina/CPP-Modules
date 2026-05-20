# 🎯 DEFENSA CPP05: Factory Method vs Abstract Factory


## 🏗️ IMPLEMENTACIÓN: Factory Method

```cpp
class Intern { // Factory Method
public:
    AForm* makeForm(const std::string& formName, const std::string& target);
private:
    static AForm* createShrubberyForm(const std::string& target);
    static AForm* createRobotomyForm(const std::string& target);
    static AForm* createPresidentialForm(const std::string& target);
};
```

### Características del Factory Method implementado:
- ✅ **Un solo método público**: `makeForm()`
- ✅ **Métodos privados estáticos** para crear cada tipo
- ✅ **No hay métodos virtuales** en Intern
- ✅ **Intern no es una interfaz**
- ✅ **Clase concreta** con responsabilidad única

---

## 🏭 Abstract Factory (lo que NO implemente)

```cpp
// ESTO sería Abstract Factory (pero NO lo hiciste)
class IFormFactory { // INTERFAZ
public:
    virtual AForm* createShrubbery() = 0;
    virtual AForm* createRobotomy() = 0;
    virtual AForm* createPresidential() = 0;
    virtual ~IFormFactory() = 0;
};

class ConcreteFormFactory : public IFormFactory {
public:
    virtual AForm* createShrubbery() override { return new ShrubberyCreationForm(); }
    virtual AForm* createRobotomy() override { return new RobotomyRequestForm(); }
    virtual AForm* createPresidential() override { return new PresidentialPardonForm(); }
};
```

### Características del Abstract Factory (no implementado):
- ❌ **Interfaz abstracta** con múltiples métodos virtuales
- ❌ **Múltiples métodos públicos** para cada tipo
- ❌ **Herencia obligatoria** para implementar
- ❌ **Mayor complejidad** sin beneficio en este caso

---

## 📊 COMPARACIÓN DIRECTA

| Aspecto | Tu código (Factory Method) | Abstract Factory |
|---------|---------------------------|------------------|
| **Intern** | Clase concreta | Interfaz abstracta |
| **Métodos** | Un método público | Múltiples métodos virtuales |
| **Virtual** | No usa virtual | Usa virtual |
| **Complejidad** | Simple | Compleja |
| **Flexibilidad** | Alta para tu caso | Alta pero más compleja |
| **Mantenimiento** | Fácil | Más difícil |
| **Extensibilidad** | Excelente | Excelente |

---

## 🎯 ¿POR QUÉ FACTORY METHOD ES MEJOR PARA ESTE CASO?

### 1. **Simplicidad**
```cpp
// Tu implementación es clara y directa
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Lógica simple de creación
    if (formName == "shrubbery creation") return createShrubberyForm(target);
    if (formName == "robotomy request") return createRobotomyForm(target);
    // ...
}
```

### 2. **Responsabilidad única**
- Intern tiene **una sola responsabilidad**: crear formularios
- **Un solo punto de entrada**: `makeForm()`
- **No hay herencia innecesaria**

### 3. **Extensibilidad**
```cpp
// Agregar nuevo formulario es fácil
static AForm* createNewForm(const std::string& target) {
    return new NewForm(target);
}
```

### 4. **Cumple con SOLID**
- **S**ingle Responsibility: Intern solo crea formularios
- **O**pen/Closed: Abierto para extensión, cerrado para modificación
- **L**iskov Substitution: No aplica (no hay herencia)
- **I**nterface Segregation: No aplica (no hay interfaz)
- **D**ependency Inversion: No aplica (no hay dependencias)

---

## 🚀 EVOLUCIÓN DEL DISEÑO EN CPP05

### **Ex00: Bureaucrat**
```cpp
class Bureaucrat {
    // Clase concreta con encapsulación
    // Excepciones personalizadas
    // Validación de grades
};
```

### **Ex01: Form + Asociación**
```cpp
class Form {
    void beSigned(const Bureaucrat& b); // ASOCIACIÓN
    // Form usa Bureaucrat (no herencia)
    // Composición débil
};
```

### **Ex02: AForm + Abstracción**
```cpp
class AForm { // Clase abstracta
    virtual void execute(const Bureaucrat& executor) const = 0; // FUNCIÓN PURA
};

class ShrubberyCreationForm : public AForm {
    void execute(const Bureaucrat& executor) const override; // IMPLEMENTACIÓN
};
```

### **Ex03: Intern + Factory Method**
```cpp
class Intern { // Factory Method
    AForm* makeForm(const std::string& formName, const std::string& target);
    // Un solo método público
    // Métodos privados estáticos
    // No necesita virtual
};
```

---

## 🎓 CONCEPTOS CLAVE DEMOSTRADOS

### 1. **Factory Method Pattern**
- **Definición**: Patrón que delega la creación de objetos a subclases
- **Implementación**: Clase concreta con método de creación
- **Ventaja**: Simplicidad y flexibilidad

### 2. **Clase Abstracta vs Interfaz**
- **AForm**: Clase abstracta con función pura `execute()`
- **Intern**: Clase concreta (no interfaz)
- **Diferencia**: AForm define comportamiento, Intern implementa creación

### 3. **Polimorfismo**
- **AForm**: Interfaz común para todos los formularios
- **Intern**: Crea objetos polimórficos
- **Resultado**: Código flexible y extensible

---

## 🏆 DEFENSA FINAL

### **"¿Por qué Factory Method y no Abstract Factory?"**

1. **Simplicidad**: Un solo método público vs múltiples métodos virtuales
2. **Responsabilidad única**: Intern solo crea formularios
3. **Extensibilidad**: Fácil agregar nuevos tipos de formularios
4. **Mantenibilidad**: Código más fácil de entender y modificar
5. **Cumple requisitos**: El patrón Factory Method es perfecto para este caso

### **"¿Por qué Intern no es una interfaz?"**

1. **No necesita herencia**: Una sola implementación es suficiente
2. **Responsabilidad única**: Solo crea formularios
3. **Simplicidad**: No requiere la complejidad de una interfaz
4. **Factory Method**: El patrón no requiere interfaz

### **"¿Por qué no métodos virtuales en Intern?"**

1. **No hay herencia**: Intern no se extiende
2. **Una sola implementación**: No necesita polimorfismo
3. **Factory Method**: El patrón no requiere virtual
4. **Simplicidad**: Código más directo y eficiente

---


