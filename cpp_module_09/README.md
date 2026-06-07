# C++ - Module 09 (STL)

Este repositorio contiene las soluciones para el **Módulo 09** de la serie de formación en C++ de la escuela 42. El objetivo principal de este módulo es profundizar en el uso de los contenedores de la **Standard Template Library (STL)**, analizando sus diferencias de rendimiento y aplicabilidad según el algoritmo.

## 📁 Estructura del Proyecto

| Ejercicio | Título | Contenedor(es) Principal(es) | Descripción |
| :--- | :--- | :--- | :--- |
| **[ex00](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex00)** | Bitcoin Exchange | `std::map` | Calculadora de valor de Bitcoin basada en una base de datos histórica. |
| **[ex01](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex01)** | RPN Calculator | `std::stack` | Evaluador de expresiones matemáticas en Notación Polaca Inversa. |
| **[ex02](file:///home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex02)** | PmergeMe | `std::vector`, `std::list` | Algoritmo de ordenación Ford-Johnson con comparación de rendimiento. |

---

## 🚀 Ejercicios

### [ex00] Bitcoin Exchange
El programa `btc` calcula el valor de una cantidad de Bitcoin en una fecha específica.
- **Aprendizaje**: Parseo de archivos CSV, manejo de claves ordenadas con `std::map` y búsqueda del "menor o igual más cercano" mediante `lower_bound`.
- **Uso**: `./btc input.txt`

### [ex01] RPN (Reverse Polish Notation)
Una calculadora científica que procesa expresiones matemáticas dadas en notación inversa (ej: `1 2 +`).
- Web para verificar : https://www.rpn-calc.com/
- Web para entender el problema :  https://notation-visualizer.ajayliu.com/stack
- **Aprendizaje**: Implementar un stack (LIFO) y entender como fuciona stack y validar estricta de expresiones.
- **Uso**: `./RPN "8 9 * 9 -"`

### [ex02] PmergeMe
Implementación del algoritmo de ordenación **Ford-Johnson** (Merge-Insertion Sort).
- **Aprendizaje**: Algoritmos complejos de ordenación recursiva e inserción binaria optimizada con números de Jacobsthal. Comparación de tiempos de ejecución entre contenedores secuenciales con distintas características de acceso (Vector vs List).
- **Uso**: `./PmergeMe 3 5 9 7 4`

---

## 🛠️ Herramientas de Testing

Cada ejercicio incluye validaciones robustas contra:
- Formatos de entrada malformados.
- Desbordamientos de memoria y tipos de datos.
- Búsqueda eficiente en grandes volúmenes de datos.

En el **ex00**, se incluye una pequeña suite de tests unitarios utilizando el framework **Acutest** (compatible con C++98) para asegurar la integridad de la lógica de fechas.

---

## ⚙️ Compilación
Todos los ejercicios se compilan utilizando `make` con flags de seguridad estrictos:
```bash
make all        # Compila el ejecutable
make clean      # Elimina objetos
make fclean     # Elimina objetos y ejecutable
make re         # Recompila todo
```

*Finalizado y validado en C++98.*
