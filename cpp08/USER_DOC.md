# Guía de Usuario - CPP08

¡Hola! En este módulo he explorado la **STL** (Standard Template Library), que es básicamente la caja de herramientas definitiva de C++. He aprendido a usar contenedores, algoritmos e iteradores para manejar datos de forma profesional.

## Cómo empezar

Cada ejercicio tiene su propio `Makefile` listo para usar.

### Compilación

Para compilar, entra en la carpeta del ejercicio y ejecuta:

```bash
cd ex00 # O ex01, ex02
make
```

Esto generará el ejecutable correspondiente.

### Ejecución de los ejercicios

#### ex00: Easyfind
He implementado una función genérica que busca un entero dentro de cualquier contenedor secuencial (como `std::vector` o `std::list`). Si el valor existe, te devuelve su posición; si no, lanza una excepción.

```bash
./easyfind
```

#### ex01: Span
Aquí he creado una clase llamada `Span` que puede almacenar una cantidad determinada de números. Lo interesante es que puede calcular automáticamente el "espacio" (span) más corto y más largo entre todos los números almacenados. ¡Incluso puede manejar miles de números a la vez!

```bash
./span
```

#### ex02: MutantStack
El `std::stack` de C++ es genial, pero tiene un problema: ¡no se puede iterar! En este ejercicio, he "mutado" el stack estándar para añadirle iteradores, permitiendo recorrerlo como si fuera un vector o una lista, pero manteniendo su comportamiento de pila.

```bash
./mutantstack
```

## Limpieza

Para limpiar los archivos generados:

```bash
make clean    # Borra los archivos objeto
make fclean   # Borra objetos y el ejecutable
make re       # Recompila todo
```

¡Espero que te sirva para ver el potencial de la STL en mis ejercicios!
