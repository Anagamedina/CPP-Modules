# Documentación de Desarrollo - CPP07

En este módulo me he sumergido en la programación genérica. Los templates no son solo una forma de ahorrar código, sino una filosofía de diseño que permite separar la lógica de los tipos de datos.

## Arquitectura y Diseño

He aplicado templates tanto a nivel de funciones como de clases:

### 1. Template Functions (ex00 y ex01)
- **Deducción de tipos**: He aprovechado la capacidad del compilador para deducir los tipos automáticamente en la mayoría de los casos.
- **Sobrecarga y Templates**: En el ex01, diseñé la función `iter` para que fuera lo suficientemente flexible como para aceptar funciones normales y funciones template como parámetros.

### 2. Template Classes (ex02)
- **Gestión de Memoria Genérica**: En la clase `Array`, el reto fue manejar la reserva de memoria con `new T[n]` de forma que funcione tanto para tipos básicos como para objetos complejos.
- **Implementación en el .hpp**: Como bien sabemos, en C++98 (y en general con templates), la implementación debe estar en el archivo de cabecera para que el compilador pueda instanciar el código cuando se usa.

## Retos Técnicos

- **C++98 y Templates**: Mantener la compatibilidad con C++98 significó evitar características modernas como `nullptr` o `static_assert`, confiando en las técnicas clásicas de plantillas.
- **Deep Copy en Clases Genéricas**: Asegurar que el constructor de copia y el operador de asignación realizaran una copia profunda de los elementos, independientemente de su tipo, fue crucial para la estabilidad de la clase `Array`.
- **Manejo de Excepciones**: Implementar el acceso mediante el operador `[]` con verificación de límites y lanzamiento de `std::exception` para garantizar la seguridad del código.

## TODO: Diagrama de Diseño de Software

- [ ] Crear un diagrama que muestre la estructura de la clase template `Array` y cómo se instancia para diferentes tipos de datos.

---
