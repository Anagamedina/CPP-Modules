### CPP Module 08 – Contenedores, iteradores y algoritmos (enunciado en castellano)

- **Objetivo**: practicar plantillas (templates) trabajando con contenedores de la STL, iteradores y algoritmos de `<algorithm>`.
- **Normas**:
  - Compilar con `-Wall -Wextra -Werror -std=c++98`.
  - No usar nada fuera del estándar permitido para el módulo.
  - Código limpio, clases/funciones en archivos adecuados.

---

### ex00 – easyfind
- **Descripción**: Implementa una función plantilla `easyfind` que busque un `int` dentro de un contenedor y devuelva un iterador al elemento encontrado. Si no existe, debe lanzar una excepción.
- **Requisitos**:
  - Debe funcionar con cualquier contenedor que tenga `begin()` y `end()` y cuyos valores sean comparables con `int` (p. ej. `std::vector<int>`, `std::list<int>`, `std::deque<int>`).
  - Usa `std::find` internamente.
  - Proporciona overloads para contenedor const y no-const.
  - Lanza `std::runtime_error` (u otra excepción estándar razonable) si no encuentra el valor.
- **Entrega**:
  - `easyfind.hpp` (header-only)
  - `main.cpp` con pruebas sencillas.

---

### ex01 – Span
- **Descripción**: Implementa una clase `Span` que almacena enteros con una capacidad máxima fija y permite calcular:
  - `shortestSpan()`: la menor diferencia entre dos números del conjunto.
  - `longestSpan()`: la mayor diferencia entre dos números del conjunto.
- **Requisitos**:
  - Constructor que reciba la capacidad máxima (N).
  - Métodos para añadir números: individualmente y en rango (por iteradores) de forma eficiente.
  - Lanzar excepciones si no hay suficientes números para calcular los spans o si se sobrepasa la capacidad.
  - Complejidad: intenta que el cálculo sea eficiente (ordenar una vez cuando sea necesario, etc.).
- **Entrega**:
  - Archivos de clase (`Span.hpp`/`Span.cpp` o header-only) y `main.cpp` con pruebas.

---

### ex02 – MutantStack
- **Descripción**: Crea una clase `MutantStack` basada en `std::stack` que exponga iteradores para poder recorrer sus elementos.
- **Requisitos**:
  - Heredar o adaptar `std::stack<T>` para añadir `begin()`, `end()`, y si se desea `rbegin()`, `rend()`.
  - Mantener el comportamiento de `std::stack` (push, pop, top, etc.).
  - Debe ser compatible con C++98.
- **Entrega**:
  - `MutantStack.hpp` (y `.cpp` si lo separas) y `main.cpp` con pruebas que recorran el stack con iteradores.

---

### Compilación
- Usa `Makefile` con las reglas habituales: `all`, `clean`, `fclean`, `re`.
- Flags recomendadas: `-Wall -Wextra -Werror -std=c++98`.
- Para dependencias automáticas, puedes usar `-MMD` y mantener `.o` en `objs/` y `.d` en `deps/`.

---

### Consejos
- Evita copiar contenedores innecesariamente; usa referencias.
- Maneja correctamente los casos de error con excepciones claras.
- Escribe pruebas simples y progresivas para validar funcionalidades.















