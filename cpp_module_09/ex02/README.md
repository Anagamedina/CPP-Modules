# ex02 — PmergeMe

Programa del **Módulo 09** que ordena una secuencia de enteros positivos usando el algoritmo **Ford–Johnson** (merge-insertion sort), con dos contenedores STL: `std::vector` y `std::list`.

Referencia del subject: *The Art of Computer Programming*, Vol. 3, Merge Insertion (p. 184).

---

## Objetivo

- Leer números desde la línea de comandos.
- Ordenarlos con Ford–Johnson (no `std::sort` como motor principal).
- Mostrar la secuencia **antes** y **después**, y el **tiempo** de cada contenedor.
- Soportar secuencias grandes (≥ 3000 enteros).

---

## Contenedores

| Contenedor | Uso |
|------------|-----|
| `std::vector` | Ordenación con acceso aleatorio y búsqueda binaria eficiente |
| `std::list` | Misma lógica, implementación aparte (sin función genérica compartida) |

En ex00 se usa `map` y en ex01 `stack`; aquí se eligen **vector** y **list**.

---

## Algoritmo (resumen)

Ford–Johnson, en pocas fases:

1. Si hay **tamaño impar**, guardar el último elemento como **sobrante**.
2. **Emparejar** elementos: en cada par, mayor (`a`) y menor (`b`).
3. **Ordenar recursivamente** solo la cadena de mayores (`A`).
4. **Reordenar** menores (`B`) y `pairs` para que sigan alineados con `A` ordenado.
5. Crear la **main chain** con `A` e insertar `b₁` al inicio **sin comparar**.
6. Insertar el resto de menores en orden **Jacobsthal**, con **búsqueda binaria acotada** hasta su `a` pareja.
7. Insertar el **sobrante** (si existía) con búsqueda en toda la cadena.

```text
 ENTRADA → parejas → ordenar A → realinear B → main chain + Jacobsthal → sobrante → ORDENADO
```

Guías detalladas con ejemplos y diagramas:

- [docs/exemple-case.md](docs/exemple-case.md) — ejemplo paso a paso (7 números)
- [docs/flow-algorithm.md](docs/flow-algorithm.md) — flujo visual completo
- [docs/implementation_plan.md](docs/implementation_plan.md) — plan de implementación

---

## Estructura del proyecto

```text
ex02/
├── main.cpp           # Entrada del programa
├── PmergeMe.hpp/cpp   # Clase principal + Ford–Johnson
├── Utils.hpp          # Mensajes de error y helpers de impresión
├── Makefile           # Compilación subject (C++98)
├── CMakeLists.txt     # Build alternativo (CLion)
├── README.md
├── docs/              # Documentación del algoritmo
├── tests/             # Tests unitarios (GoogleTest)
└── extern/googletest/ # GTest local (tras make setup en tests/)
```

---

## Compilación y ejecución

### Makefile (entrega 42)

```bash
make
./PmergeMe 3 5 9 7 4
```

Reglas: `all`, `clean`, `fclean`, `re`, `test`.

Flags: `-Wall -Wextra -Werror -std=c++98`.

### Ejemplo de salida (subject)

```text
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : ...
Time to process a range of 5 elements with std::list   : ...
```

### Prueba con muchos números

```bash
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr '\n' ' ')
```

---

## Validación de entrada (reglas del proyecto)

Además de lo que pide el subject (enteros positivos, errores en `stderr`), esta implementación también:

- Rechaza **caracteres no numéricos** y valores ≤ 0.
- Rechaza **overflow** de `int`.
- Rechaza **duplicados**.
- Rechaza secuencias **ya ordenadas** (≥ 2 elementos).

Mínimo **2 argumentos** numéricos: `./PmergeMe n1 n2`.

Web para generar numero random:
https://www.calculatorsoup.com/calculators/statistics/random-number-generator.php

---

## Tests unitarios

Los tests usan **GoogleTest** en local (`extern/googletest`), sin depender del sistema.

```bash
# Primera vez: descargar GTest
make -C tests setup

# Compilar y ejecutar tests
make test
# o desde tests/:
make && ./run_tests
```

Casos cubiertos: básicos (1–3 elementos), validación, ordenación de 100 y 200, números aleatorios únicos.

---

## CMake (opcional / CLion)

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

---

## Archivos a entregar

- `Makefile`
- `main.cpp`
- `PmergeMe.hpp`
- `PmergeMe.cpp`

`Utils.hpp`, `docs/` y `tests/` son complementos del repositorio.

---

## Referencias rápidas

| Tema                    | Dónde                                                      |
|-------------------------|------------------------------------------------------------|
| Ejemplo 7 números       | [docs/exemple-case.md](docs/exemple-case.md)               |
| Diagrama de flujo       | [docs/exemple-case.md](docs/exemple-case.md) (mermaid)     |
| Plan de fases en código | [docs/implementation_plan.md](docs/implementation_plan.md) |
| Subject PDF             | `../subject/en.subject_cpp09.pdf`                          |
