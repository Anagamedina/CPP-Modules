# Documentación de Desarrollo - CPP06

En este módulo me he centrado en la seguridad de tipos y en cómo C++ nos ofrece herramientas mucho más potentes y seguras que el casting tradicional de C.

## Arquitectura y Decisiones Técnicas

He estructurado los ejercicios para demostrar los cuatro tipos de casting principales de C++:

### 1. static_cast (ex00)
Lo he utilizado en el `ScalarConverter` para las conversiones numéricas estándar. Es ideal porque se verifica en tiempo de compilación y es mucho más legible que el cast de C.

### 2. reinterpret_cast (ex01)
Este es el "cast de bajo nivel". Lo he empleado para convertir punteros a `uintptr_t`. Es una operación que trata los datos como simples bits, lo cual es necesario para tareas de serialización pero debe usarse con extrema precaución.

### 3. dynamic_cast (ex02)
Para la identificación de tipos en tiempo de ejecución (RTTI), he usado `dynamic_cast`. 
- **Con punteros**: Devuelve `NULL` si la conversión falla, lo que permite usar un simple `if`.
- **Con referencias**: Lanza una excepción `std::bad_cast` si falla, lo que me obligó a implementar bloques `try-catch` para la identificación segura.

## Retos Técnicos

- **Manejo de Pseudo-literales**: En el ex00, gestionar `nan`, `+inf`, `-inf` tanto para float como para double requirió una lógica de detección cuidadosa para cumplir con los requisitos del subject.
- **Clases Polimórficas**: Para que `dynamic_cast` funcione, la clase base debe tener al menos un método virtual (normalmente el destructor). Me aseguré de que `Base` fuera polimórfica para permitir esta identificación.
- **Serialización Segura**: Garantizar que el puntero recuperado en el ex01 fuera idéntico al original fue clave para validar la implementación del `Serializer`.

## TODO: Diagrama de Diseño de Software

- [ ] Diseñar un diagrama que ilustre el flujo de conversión de tipos en el `ScalarConverter` y la jerarquía de clases de `Base`.

---
