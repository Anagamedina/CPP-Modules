# Guía de Usuario - CPP06

¡Hola! En este módulo he explorado el sistema de tipos de C++ y cómo realizar conversiones (casts) de forma segura y eficiente. Aquí te explico cómo puedes probar los ejercicios que he implementado.

## Cómo empezar

Al igual que en los otros módulos, cada ejercicio tiene su propio `Makefile`.

### Compilación

Para compilar cualquiera de los ejercicios, entra en su carpeta y ejecuta:

```bash
cd ex00 # O ex01, ex02
make
```

Esto generará un ejecutable específico para cada prueba.

### Ejecución de los ejercicios

#### ex00: Conversor de Escalares
He creado una herramienta que toma un literal (como un char, un int, un float o un double) y lo convierte a los demás tipos, manejando casos especiales como `nan`, `inf` y desbordamientos.

```bash
./scalar_converter "42.0f"
./scalar_converter "a"
./scalar_converter "nan"
```

#### ex01: Serialización
En este ejercicio, demuestro cómo podemos convertir un puntero a un tipo entero (`uintptr_t`) y volver a recuperarlo sin perder la información. Es una técnica fundamental para la serialización de datos.

```bash
./serializer
```

#### ex02: Identificación de Tipos
Aquí he implementado un sistema que genera objetos de clases derivadas (`A`, `B` o `C`) de forma aleatoria y luego es capaz de identificarlos correctamente, ya sea mediante punteros o referencias, sin usar el tipo real directamente.

```bash
./identify
```

## Limpieza

Para mantener el espacio limpio, puedes usar:

```bash
make clean    # Borra los archivos objeto
make fclean   # Borra objetos y el ejecutable
make re       # Recompila todo
```

¡Espero que te sirva para entender mejor cómo manejo los tipos en C++!
