# ¿Por qué la serie de Jacobsthal empieza distinto en `cpp09` y en `cpp09_defensa`?

Las dos versiones generan la serie de Jacobsthal **con la misma fórmula recurrente** y llegan **al mismo resultado de inserción**. Lo único que cambia es **dónde empieza la semilla** y **dónde se filtran los números inútiles**. No es un error de ninguna: son dos formas de organizar el mismo cálculo.

---

## 1. Recordatorio: ¿qué es la serie de Jacobsthal?

La definición matemática "pura" es:

```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)
```

Y sale esto:

```
n:    0  1  2  3  5  11  21  43 ...
J(n): 0, 1, 1, 3, 5, 11, 21, 43 ...
       ^^^^^^^
       estos 3 primeros (0, 1, 1) NO sirven como "saltos" de inserción
```

Para Ford-Johnson lo que nos interesa son los **límites de los grupos de inserción**, que son: **1, 3, 5, 11, 21, 43...** (es decir, la serie a partir del segundo `1`, sin el `0` ni el `1` duplicado).

> Idea clave: el `0` y el primer `1` duplicado **no aportan ningún grupo nuevo**, son "ruido" al principio de la serie.

---

## 2. Versión `cpp09` (la simple): empieza en `1, 3`

Aquí la función hace **todo de una vez**: genera la serie Y construye el orden de inserción en la misma función. Por eso arranca directamente con los números **útiles** (`1` y `3`) y se salta el `0, 1, 1`.

```cpp
// cpp09/ex02/PmergeMe.cpp
std::vector<size_t> jacob;
jacob.push_back(1);   // <-- empieza en 1
jacob.push_back(3);   // <-- y 3 (ya saltamos el 0, 1, 1)
while (jacob.back() < n)
    jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
// genera: 1, 3, 5, 11, 21, 43 ...
```

**¿Por qué puede empezar en 1, 3?** Porque esta función NO pretende ser la serie matemática completa; solo necesita **los saltos que de verdad usa**. Como el `0` y el `1` duplicado no sirven, los omite desde el principio. Es un atajo limpio: genero solo lo que voy a usar.

---

## 3. Versión `cpp09_defensa` (la purista): empieza en `0, 1`

Aquí el trabajo está **separado en dos funciones**:

### Paso A — generar la serie matemática "pura" (con 0 y 1)

```cpp
// cpp09_defensa/ex02/PmergeMe.cpp  ->  createJacobsthalSequence()
int a = 0;
int b = 1;
jacobSequence.push_back(a);   // <-- empieza en 0
jacobSequence.push_back(b);   // <-- y 1 (la serie matematica de verdad)
while (b < sizePendientList)
{
    int nextNumber = b + 2 * a;
    jacobSequence.push_back(nextNumber);
    a = b;
    b = nextNumber;
}
// genera: 0, 1, 1, 3, 5, 11, 21 ...
```

### Paso B — al construir el orden, se descartan los inútiles

```cpp
// cpp09_defensa/ex02/PmergeMe.cpp  ->  buildJacobsthalInsertionOrder()
int lastJacobNumber = 1;
for (size_t i = 0; i < jacobSequence.size(); ++i)
{
    int j = jacobSequence[i];
    if (j <= lastJacobNumber)   // <-- AQUI se filtran el 0, el 1 y el 1 duplicado
        continue;
    ...
}
```

> Es decir: la versión defensa **sí genera el `0, 1, 1`**, pero luego los **tira a la basura** con ese `if (j <= lastJacobNumber) continue;`. El resultado final de saltos vuelve a ser `3, 5, 11, 21...`.

**¿Por qué lo hace así?** Porque separa responsabilidades:
- una función "genera la serie de Jacobsthal de libro" (fiel a la definición matemática),
- y otra función "decide el orden de inserción" (y ahí ya filtra lo que no sirve).

Es más académico/purista, pero también más largo.

---

## 4. Comparación lado a lado

| | `cpp09` (simple) | `cpp09_defensa` (purista) |
|---|---|---|
| Semilla inicial | `1, 3` | `0, 1` |
| Serie que genera | `1, 3, 5, 11, 21...` | `0, 1, 1, 3, 5, 11, 21...` |
| ¿Filtra el 0 y el 1? | No hace falta (no los crea) | Sí, con `if (j <= lastJacobNumber) continue;` |
| ¿En cuántas funciones? | 1 (todo junto) | 2 (generar + ordenar) |
| Saltos de inserción finales | `1, 3, 5, 11, 21...` | `3, 5, 11, 21...` (mismos grupos) |
| Resultado del ordenamiento | **Idéntico** | **Idéntico** |

---

## 5. Resumen para la defensa (frase corta)

> "Las dos usan la misma fórmula `J(n) = J(n-1) + 2·J(n-2)`. En la versión simple arranco directamente en `1, 3` porque solo me interesan los saltos útiles, así que me salto el `0` y el `1` que no aportan ningún grupo nuevo. En la versión purista genero la serie matemática completa empezando en `0, 1` y luego descarto esos primeros valores al construir el orden de inserción. El resultado final es el mismo; solo cambia si filtro al generar o al ordenar."

### Y si te preguntan "¿da igual entonces?"

Sí, da igual para la **correctitud**. La diferencia es de **estilo**:
- `cpp09`: más directo, menos código, genera solo lo necesario.
- `cpp09_defensa`: más fiel a la teoría, separa "qué es la serie" de "cómo la uso".
