# Guía de Usuario - CPP07

¡Hola! En este módulo he trabajado con una de las herramientas más potentes de C++: los **Templates** (plantillas). Gracias a ellos, he podido escribir código genérico que funciona con cualquier tipo de dato sin tener que repetir lógica.

## Cómo empezar

Cada ejercicio tiene su propio `Makefile` configurado para C++98.

### Compilación

Para compilar, entra en la carpeta del ejercicio y ejecuta:

```bash
cd ex00 # O ex01, ex02
make
```

Esto generará el ejecutable correspondiente.

### Ejecución de los ejercicios

#### ex00: Funciones Genéricas
He implementado tres funciones básicas que seguro que conoces, pero ahora funcionan con cualquier tipo (siempre que soporten los operadores de comparación):
- `swap`: Intercambia dos valores.
- `min`: Devuelve el menor de dos valores.
- `max`: Devuelve el mayor de dos valores.

```bash
./whatever
```

#### ex01: Iterador Genérico
He creado una función `iter` que recorre un array de cualquier tipo y aplica una función a cada uno de sus elementos. Es una forma muy limpia de procesar colecciones de datos.

```bash
./iter
```

#### ex02: Clase Array Genérica
Este es el plato fuerte. He diseñado mi propia clase `Array` que puede almacenar cualquier tipo de dato. Incluye gestión dinámica de memoria, constructores de copia y protección contra accesos fuera de los límites.

```bash
./array
```

## Limpieza

Puedes limpiar el proyecto con los comandos habituales:

```bash
make clean    # Borra los archivos objeto
make fclean   # Borra objetos y el ejecutable
make re       # Recompila todo
```

¡Espero que disfrutes viendo cómo el mismo código puede manejar tantos tipos de datos diferentes!
