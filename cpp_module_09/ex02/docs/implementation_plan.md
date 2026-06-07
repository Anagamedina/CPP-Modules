# Implementation Plan - Exercise 02: PmergeMe

Este plan detalla la implementación del algoritmo **Ford-Johnson** (Merge-Insertion Sort) para ordenar una secuencia de enteros positivos utilizando dos contenedores distintos (`std::vector` y `std::list`).

## User Review Required

> [!IMPORTANT]
> **Elección de Contenedores**: Dado que `std::map` (ex00) y `std::stack`/`std::deque` (ex01) están prohibidos, utilizaremos **`std::vector`** y **`std::list`**. Esto permitirá observar una diferencia clara de rendimiento, ya que el algoritmo Ford-Johnson depende fuertemente del acceso aleatorio para la búsqueda binaria, algo en lo que `std::list` es mucho más lento.

> [!WARNING]
> **Duplicados**: El subject permite decidir cómo manejarlos. Propongo **mantener los duplicados** como elementos individuales en la secuencia ordenada (comportamiento estándar de un sort), a menos que prefieras que los filtremos.

## Proposed Changes

### [Component] PmergeMe Engine

#### [NEW] [PmergeMe.hpp](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex02/PmergeMe.hpp)
- Definición de la clase `PmergeMe` (Forma Canónica Ortodoxa).
- Contenedores para almacenar la secuencia: `std::vector<int>` y `std::list<int>`.
- Métodos para el algoritmo:
    - `sortVector()`: Implementación específica para vector.
    - `sortList()`: Implementación específica para lista (evitando funciones genéricas como pide el PDF).
    - `getJacobsthalSequence()`: Generador de números para el orden de inserción.
    - `binarySearchInsertion()`: Lógica para insertar elementos del *pend* en la *main chain*.

#### [NEW] [PmergeMe.cpp](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex02/PmergeMe.cpp)
- **Fase de Emparejamiento**: Dividir elementos en pares, comparar y separar en "grandes" y "pequeños".
- **Fase Recursiva**: Ordenar recursivamente la cadena principal (los elementos grandes).
- **Fase de Inserción**: Usar los números de Jacobsthal para insertar los elementos pequeños en la cadena principal mediante búsqueda binaria optimizada.
- **Medición de Tiempo**: Uso de `clock()` o `gettimeofday()` para capturar el tiempo exacto de procesamiento.

#### [NEW] [main.cpp](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex02/main.cpp)
- Validación estricta de argumentos (solo enteros positivos, manejar >3000 elementos).
- Control de flujo: Mostrar "Before", ejecutar sorts, mostrar "After" y los tiempos de ejecución.

#### [NEW] [Makefile](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex02/Makefile)
- Reglas: `all`, `clean`, `fclean`, `re`. Compilación con `-std=c++98`.

## Open Questions

- **Nivel de detalle del Sort**: ¿Quieres que implemente la lógica de Jacobsthal completa (más eficiente en comparaciones) o una versión de Merge-Insert Sort simplificada?
- **Formato de tiempo**: El PDF dice que el formato es libre. ¿Prefieres microsegundos (`us`) o milisegundos (`ms`)?

## Verification Plan

### Manual Verification
- Pruebas con secuencias pequeñas: `./PmergeMe 3 5 9 7 4`
- Pruebas con secuencias grandes (3000+): `./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "``
- Verificación de errores: `./PmergeMe "-1" "2"`, `./PmergeMe "abc" "1"`
- Verificar que la secuencia final esté realmente ordenada usando `sort -n` en bash para comparar.
