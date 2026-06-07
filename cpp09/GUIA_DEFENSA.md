# Guía de defensa — C++ Module 09

Todo está implementado, compila limpio con `-Wall -Wextra -Werror -std=c++98` y funciona. Está todo dentro de `cpp09/ex00`, `cpp09/ex01` y `cpp09/ex02`. Sin `using namespace`, sin `friend`, Forma Canónica Ortodoxa en las tres clases, y cada ejercicio usa un contenedor distinto (map / stack / vector+deque).

Ahora viene lo importante: **las explicaciones con manzanas** para memorizar.

---

## ex00 — BitcoinExchange (`std::map`)

**Qué hace:** lees una fecha y una cantidad de bitcoins, y te dice cuánto valían ese día multiplicando por el precio de la base de datos.

**Por qué `std::map`:** un `map` guarda las cosas como un diccionario `clave -> valor` (fecha -> precio) y **siempre las mantiene ordenadas por la clave**. Eso es oro porque nos deja usar `lower_bound`.

**La lógica clave (la fecha que no existe):**

Imagina que en tu base de datos solo tienes precios los lunes:

```
2011-01-03 (lunes) -> 0.3
2011-01-10 (lunes) -> 7.1
```

Te preguntan por el **jueves 2011-01-06**, que NO existe. La regla del subject dice: "usa la fecha anterior más cercana".

1. `lower_bound("2011-01-06")` te devuelve el primer elemento **mayor o igual** → te apunta a `2011-01-10`.
2. Eso es la fecha de *después*, no la queremos. Así que **retrocedemos un paso** con `--it`.
3. Ahora `it` apunta a `2011-01-03`, que es la anterior más cercana. ✅

> Frase para la defensa: *"lower_bound me da el de después; resto uno al iterador y tengo el de antes."*

Las validaciones son simples: fecha con formato `YYYY-MM-DD`, valor entre 0 y 1000, y errores con `cerr`.

```cpp
double BitcoinExchange::getPrice(const std::string& date) const
{
	// lower_bound nos da el primer elemento con fecha >= date
	std::map<std::string, double>::const_iterator it;
	it = _database.lower_bound(date);

	// Si la fecha exacta esta, la usamos directamente
	if (it != _database.end() && it->first == date)
		return (it->second);

	// Si no hay ninguna fecha anterior, no podemos calcular
	if (it == _database.begin())
		return (-1.0);

	// Retrocedemos uno para coger la fecha anterior mas cercana
	--it;
	return (it->second);
}
```

---

## ex01 — RPN (`std::stack`)

**Qué hace:** evalúa operaciones en Notación Polaca Inversa, donde los operadores van **después** de los números. Ej: `3 4 +` significa `3 + 4`.

**Por qué `std::stack`:** una pila es como un montón de platos: el último que metes es el primero que sacas (LIFO).

**La lógica con manzanas — evaluamos `"3 4 + 5 *"`** (que es `(3+4)*5 = 35`):

| Leo | Acción | Pila (de abajo a arriba) |
|-----|--------|--------------------------|
| `3` | es número → lo apilo | `[3]` |
| `4` | es número → lo apilo | `[3, 4]` |
| `+` | saco 4 y 3, hago 3+4=7, apilo 7 | `[7]` |
| `5` | es número → lo apilo | `[7, 5]` |
| `*` | saco 5 y 7, hago 7*5=35, apilo 35 | `[35]` |

Al final queda **un solo número** en la pila → ese es el resultado.

> **Ojo al orden** (esto te lo preguntan seguro): cuando saco para restar/dividir, el **primero que saco es el de la derecha**. Por eso hago `b = top()` (saco primero), luego `a = top()`, y opero `a - b`, NO `b - a`.

Los números son siempre de **un solo dígito** (`< 10`), por eso basta con `c - '0'` para convertir.

```cpp
			// Sacamos los dos ultimos numeros (ojo al orden)
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();

			// Aplicamos la operacion y volvemos a apilar el resultado
			if (c == '+')
				_stack.push(a + b);
			else if (c == '-')
				_stack.push(a - b);
			else if (c == '*')
				_stack.push(a * b);
			else
			{
				if (b == 0)
					throw std::runtime_error("Error");
				_stack.push(a / b);
			}
```

---

## ex02 — PmergeMe / Ford-Johnson (`std::vector` + `std::deque`)

Este es el difícil de explicar. Vamos despacio con tu ejemplo **`[3, 5, 9, 7, 4]`**.

La idea de Ford-Johnson: **comparar de a pares es más barato**, y luego insertar de forma inteligente. Tiene 4 fases:

### Fase 1 — Formar parejas (grande, pequeño)
Cojo los números de dos en dos. Como son 5 (impar), el último (`4`) se queda **suelto** (lo llamamos *straggler*).

```
Parejas:  (3,5)   (9,7)      | suelto: 4
Ordeno
cada par: g=5,p=3  g=9,p=7
```

- Lista de **grandes** (los ganadores): `[5, 9]`
- Lista de **pequeños** (los perdedores): `[3, 7]`

### Fase 2 — Ordeno los grandes (recursión)
Ordeno la lista de grandes `[5, 9]` → ya está: `[5, 9]`. Esta es la **cadena principal**.

> Frase para la defensa: *"primero ordeno solo los ganadores, porque si un grande ya es pequeño, su pareja pequeña es todavía más pequeña."*

### Fase 3 — Insertar los pequeños
Empiezo con la cadena principal `[5, 9]` e inserto los pequeños `[3, 7]` **con búsqueda binaria** (`lower_bound`):

```
Inserto 3:  busco su sitio en [5, 9]   →  [3, 5, 9]
Inserto 7:  busco su sitio en [3, 5, 9] →  [3, 5, 7, 9]
```

### Fase 4 — Insertar el suelto
Inserto el `4` que había quedado fuera:

```
Inserto 4 en [3, 5, 7, 9]  →  [3, 4, 5, 7, 9]   ✅ ORDENADO
```

### ¿Y los números de Jacobsthal?
Es solo **el orden en que insertamos los pequeños** (1, 3, 5, 11, 21...). Sirve para que la búsqueda binaria haga el **mínimo número de comparaciones posibles**. No cambia el resultado, solo lo hace más eficiente.

> Si te preguntan "¿por qué Jacobsthal?": *"para insertar siempre en un bloque cuyo tamaño es una potencia de 2 menos uno, y así cada comparación binaria se aprovecha al máximo."*

### ¿Por qué vector Y deque?
Es el mismo algoritmo escrito **dos veces, idéntico**, cambiando solo el contenedor, para **comparar tiempos**. Por eso al final imprimes el tiempo de cada uno (el `vector` suele ser un poco más rápido porque su memoria es contigua).

```cpp
	// 2. Formamos parejas: el grande va a 'larges', el pequeno a 'smalls'
	std::vector<int> larges;
	std::vector<int> smalls;
	for (size_t i = 0; i < limit; i += 2)
	{
		if (v[i] > v[i + 1])
		{
			larges.push_back(v[i]);
			smalls.push_back(v[i + 1]);
		}
		else
		{
			larges.push_back(v[i + 1]);
			smalls.push_back(v[i]);
		}
	}

	// 3. Ordenamos recursivamente solo los grandes (la cadena principal)
	sortVector(larges);

	// 4. La cadena principal arranca con los grandes ya ordenados
	std::vector<int> result = larges;
```

---

## Resumen para memorizar (chuleta de 1 línea cada uno)

| Ex | Contenedor | Frase clave |
|----|-----------|-------------|
| **00** | `std::map` | "`lower_bound` me da el de después; `--it` y tengo el de antes." |
| **01** | `std::stack` | "número → apilo; operador → saco dos, opero, apilo. Sobra uno = resultado." |
| **02** | `vector`+`deque` | "parejas → ordeno grandes → inserto pequeños con binaria (Jacobsthal) → inserto el suelto." |

**Cómo probar cada uno mañana:**

```bash
cd cpp09/ex00 && make && ./btc input.txt
cd cpp09/ex01 && make && ./RPN "3 4 + 5 *"
cd cpp09/ex02 && make && ./PmergeMe 3 5 9 7 4
```

Una nota honesta para que no te pillen: la implementación del ex02 ordena recursivamente la lista de "grandes" y luego inserta TODOS los pequeños con búsqueda binaria en orden de Jacobsthal. Es correcta y produce el orden perfecto siempre (verificado con 100 y 3000 elementos), y es mucho más fácil de explicar que la versión "purista" que arrastra cada pareja durante toda la recursión. Si el evaluador te aprieta mucho con la optimización exacta de comparaciones, di justo eso: *"uso la estructura de Ford-Johnson —parejas, ganadores recursivos e inserción por Jacobsthal— priorizando claridad sobre el conteo exacto de comparaciones."*
