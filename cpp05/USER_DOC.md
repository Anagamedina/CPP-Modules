# Guía de Usuario - CPP05

¡Hola! En esta guía te explico cómo puedes probar y ejecutar los diferentes ejercicios que he desarrollado para el módulo CPP05. Este módulo se centra en el mundo de la burocracia, los formularios y cómo manejar situaciones inesperadas mediante excepciones.

## Cómo empezar

Para probar cualquiera de los ejercicios, solo tienes que entrar en su carpeta correspondiente y usar el `Makefile` que he preparado.

### Compilación

He configurado los Makefiles para que cumplan estrictamente con el estándar C++98. Para compilar, simplemente ejecuta:

```bash
cd ex00 # O ex01, ex02, ex03
make
```

Esto generará un ejecutable (normalmente llamado `bureaucrat` o `form`).

### Ejecución de los ejercicios

Aquí te detallo qué hace cada uno y cómo puedes verlo en acción:

#### ex00: El Burócrata
En este primer ejercicio, he creado la clase base `Bureaucrat`. Puedes ver cómo el sistema valida los rangos (de 1 a 150) y lanza excepciones si intentas crear un burócrata con un rango inválido o si intentas subir/bajar su rango fuera de los límites.

```bash
./bureaucrat
```

#### ex01: Formularios
Aquí he introducido los formularios. Verás cómo los burócratas intentan firmar documentos. Si el rango del burócrata no es suficiente, el sistema te avisará con una excepción clara.

```bash
./form
```

#### ex02: Formularios Específicos
Este es el ejercicio más visual. He implementado tres tipos de formularios:
1. **ShrubberyCreationForm**: Crea un archivo con un árbol ASCII.
2. **RobotomyRequestForm**: Intenta "robotizar" a alguien con un 50% de éxito (hace ruidos de taladro).
3. **PresidentialPardonForm**: Concede un perdón presidencial.

```bash
./form
```

#### ex03: El Becario (Intern)
En este último paso, he añadido a un "Intern" que se encarga de crear los formularios por nosotros. Solo tienes que decirle el nombre del formulario y el objetivo, y él se encargará de instanciar el objeto correcto.

```bash
./intern
```

## Limpieza

Si quieres limpiar los archivos temporales y los ejecutables, puedes usar:

```bash
make clean    # Elimina los archivos objeto
make fclean   # Elimina objetos y el ejecutable
make re       # Recompila todo desde cero
```

Espero que te sea útil para navegar por mi código. ¡Cualquier duda, aquí estoy!
