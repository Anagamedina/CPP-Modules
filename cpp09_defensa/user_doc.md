# Guía de Usuario: CPP Module 09 (Defensa)

Este documento explica cómo compilar y probar los tres ejercicios del Módulo 09. Todos los ejercicios cumplen con el estándar C++98 y las reglas de la Forma Canónica Ortodoxa.

---

## Reglas Generales de Compilación

Todos los ejercicios incluyen un `Makefile` que compila con los siguientes flags:
- `c++`
- `-Wall -Wextra -Werror`
- `-std=c++98`

Comandos disponibles en cada carpeta:
- `make`: Compila el ejecutable.
- `make clean`: Elimina los archivos objeto (`.o`).
- `make fclean`: Elimina los archivos objeto y el ejecutable.
- `make re`: Ejecuta `fclean` y luego `make`.

---

## ex00: Bitcoin Exchange (btc)

Este programa calcula el valor de una cantidad de Bitcoin en una fecha específica basándose en una base de datos CSV.

### Compilación
```bash
cd ex00
make
```

### Uso
```bash
./btc input.txt
```

### Casos de Prueba Recomendados
1. **Entrada Válida:**
   - `2011-01-03 | 3` -> Debe mostrar el cálculo correcto.
   - `2011-01-03 | 1.2` -> Soporta decimales.
2. **Fecha Inexistente (Búsqueda del más cercano):**
   - Si pides una fecha que no está en `data.csv`, el programa debe usar la fecha anterior más cercana.
3. **Errores de Formato:**
   - `2001-42-42` -> Error: bad input.
   - `2012-01-11 | -1` -> Error: not a positive number.
   - `2012-01-11 | 2147483648` -> Error: too large a number.

---

## ex01: Reverse Polish Notation (RPN)

Calculadora que utiliza la Notación Polaca Inversa. Los números deben ser menores de 10 (un solo dígito).

### Compilación
```bash
cd ex01
make
```

### Uso
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

### Casos de Prueba Recomendados
1. **Operaciones Simples:**
   - `"3 4 +"` -> Resultado: 7.
   - `"7 7 * 7 -"` -> Resultado: 42.
2. **Expresiones Complejas:**
   - `"1 2 * 2 / 2 * 2 4 - +"` -> Resultado: 0.
3. **Errores:**
   - `"1 2 + +"` -> Error (faltan operandos).
   - `"5 0 /"` -> Error (división por cero).
   - `"(1 + 1)"` -> Error (caracteres no permitidos).

---

## ex02: PmergeMe

Ordena una secuencia de números enteros positivos utilizando el algoritmo Ford-Johnson (Merge-Insertion Sort). Compara el rendimiento entre `std::vector` y `std::deque`.

### Compilación
```bash
cd ex02
make
```

### Uso
```bash
./PmergeMe 3 5 9 7 4
```

### Casos de Prueba Recomendados
1. **Secuencia Pequeña:**
   - `3 5 9 7 4` -> Debe mostrar "Before", "After" y los tiempos de ambos contenedores.
2. **Secuencia Grande (Rendimiento):**
   - Usa el siguiente comando para generar 1000 números aleatorios:
     ```bash
     ./PmergeMe `shuf -i 1-100000 -n 1000 | tr "\n" " "`
     ```
3. **Errores:**
   - `1 2 abc` -> Error: caracteres inválidos.
   - `1 -2` -> Error: solo números positivos.
   - `5 5` -> Error: número duplicado.
   - `1 2 3` -> Error: la lista ya está ordenada.

---

¡Mucha suerte en la defensa!
