# Guía de Usuario - CPP09

¡Hola! Este es el último módulo de la piscina, donde ponemos a prueba todo lo aprendido sobre la STL para resolver problemas del mundo real. En este caso, nos centramos en el intercambio de Bitcoin.

## Cómo empezar

El proyecto utiliza un `Makefile` estándar para la compilación.

### Compilación

Para compilar el ejercicio, entra en la carpeta y ejecuta:

```bash
cd ex00
make
```

Esto generará el ejecutable `btc`.

### Ejecución de los ejercicios

#### ex00: Bitcoin Exchange
He desarrollado una herramienta que calcula el valor de una cantidad de Bitcoin en una fecha específica, consultando una base de datos histórica.

Para usarlo, necesitas un archivo de entrada con el formato `fecha | valor`. Por ejemplo:

```bash
./btc input.txt
```

El programa leerá el archivo `data.csv` (que debe estar en la misma carpeta) y te mostrará el valor convertido para cada fecha, manejando automáticamente las fechas que no existen buscando la más cercana anterior.

## Limpieza

Como siempre, puedes limpiar los archivos temporales con:

```bash
make clean    # Borra los archivos objeto
make fclean   # Borra objetos y el ejecutable
make re       # Recompila todo
```

¡Espero que esta herramienta te sea útil para seguir el rastro de tus Bitcoins imaginarios!
