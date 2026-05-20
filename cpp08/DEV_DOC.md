# Documentación de Desarrollo - CPP08

En este módulo me he centrado en aprovechar las estructuras de datos y algoritmos que ya vienen integrados en C++. La clave aquí no es reinventar la rueda, sino saber elegir la rueda adecuada para cada terreno.

## Arquitectura y Decisiones Técnicas

He estructurado el código para demostrar el uso de diferentes componentes de la STL:

### 1. Algoritmos Genéricos (ex00)
- **Uso de `std::find`**: En lugar de escribir mi propio bucle de búsqueda, he utilizado `std::find`, que es altamente eficiente y funciona con cualquier iterador de entrada.
- **Typename y Dependientes**: Tuve que usar la palabra clave `typename` para indicar al compilador que `T::iterator` es un tipo, algo fundamental cuando trabajamos con templates y contenedores.

### 2. Contenedores y Eficiencia (ex01)
- **std::vector**: Elegí `std::vector` para la clase `Span` por su acceso aleatorio rápido y su eficiencia en memoria.
- **Algoritmos de Ordenación**: Para calcular los spans, primero ordeno el contenedor con `std::sort`. Esto reduce la complejidad de encontrar el span más corto a una sola pasada lineal ($O(n)$ tras el $O(n \log n)$ de la ordenación).
- **Inserción por Rango**: Implementé una función para añadir muchos números de golpe usando iteradores, lo cual es mucho más eficiente que llamar a `addNumber` en un bucle.

### 3. Adaptadores de Contenedores (ex02)
- **Herencia de `std::stack`**: Mi clase `MutantStack` hereda directamente de `std::stack`. 
- **Acceso al Contenedor Subyacente**: He aprovechado que el contenedor interno de un stack (`c`) es un miembro protegido para exponer sus iteradores (`begin()`, `end()`, etc.). Esto permite que el stack sea iterable sin romper su interfaz original.

## Retos Técnicos

- **Comprensión de los Iteradores**: Entender la diferencia entre iteradores de entrada, salida, forward, bidireccionales y de acceso aleatorio fue clave para implementar `easyfind` y `MutantStack`.
- **Gestión de Grandes Volúmenes de Datos**: Probar la clase `Span` con más de 10,000 números para asegurar que los algoritmos de cálculo de span fueran lo suficientemente rápidos.
- **Sintaxis de Templates Complejos**: Manejar la sintaxis de iteradores dentro de clases template requiere mucha precisión para evitar errores de compilación crípticos.

## TODO: Diagrama de Diseño de Software

- [ ] Diseñar un diagrama que muestre la jerarquía de `MutantStack` y cómo expone los iteradores del contenedor subyacente.

---

