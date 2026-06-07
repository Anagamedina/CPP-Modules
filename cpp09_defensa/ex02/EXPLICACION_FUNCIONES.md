# Mi Guía de Funciones (PmergeMe)

He escrito este código pensando en que sea fácil de explicar. Aquí tienes el desglose de qué hace cada parte y por qué la he puesto ahí.

---

## 1. Estructura y Limpieza
*   **`parseArguments`**: Es mi "filtro". Antes de hacer nada, me aseguro de que los números sean válidos (positivos, sin letras, sin duplicados y que no desborden el `int`). Si la lista ya está ordenada, también aviso.
*   **`run`**: Es el punto de entrada principal. Aquí preparo los contenedores, imprimo el estado inicial ("Before"), ejecuto las ordenaciones y al final muestro los tiempos ("After").

## 2. El Algoritmo (Templates en `.tpp`)
He usado **templates** para no repetir código. Como `vector` y `deque` funcionan casi igual con sus iteradores, una sola función me sirve para los dos.
*   **`mergeInsertSort`**: Es el corazón del Ford-Johnson. 
    1.  Separo el número "suelto" si son impares.
    2.  Hago parejas y me quedo con los grandes.
    3.  Llamo a la función otra vez (recursión) para ordenar esos grandes.
    4.  Meto los pequeños en los huecos usando Jacobsthal para no hacer comparaciones de más.
*   **`binarySearchInsertPos`**: Es mi buscador inteligente. En lugar de mirar uno a uno, divide la lista por la mitad hasta encontrar el sitio exacto. Ahorra muchísimo tiempo.

## 3. Mis Ayudantes (Lógica de Apoyo en `.cpp`)
*   **`createOrderedPairs`**: Simplemente junta los números de dos en dos y pone el mayor primero.
*   **`extractA` / `extractB`**: Separa los "ganadores" de los "perdedores" de las parejas.
*   **`reorderBNumbersAndPairs`**: **¡Ojo aquí!** Esta es clave. Cuando ordeno los grandes, sus parejas pequeñas se quedan descolocadas. Esta función las vuelve a alinear para que cada pequeño sepa quién era su "pareja ganadora".
*   **`createJacobsthalSequence`** y **`buildJacobsthalInsertionOrder`**: Generan esos números mágicos (1, 3, 5, 11...) que me dicen en qué orden exacto debo insertar los pequeños para ser lo más eficiente posible.

---

### Puntos para lucirme en la defensa:
1.  **Templates**: "He usado plantillas para que el código sea genérico y evitar la duplicación entre `vector` y `deque`."
2.  **Jacobsthal**: "Uso esta serie porque matemáticamente es la que minimiza el número de comparaciones al insertar elementos en una lista ordenada."
3.  **Recursión**: "El algoritmo es recursivo sobre los elementos mayores de cada pareja, lo que reduce el problema a la mitad en cada paso."
