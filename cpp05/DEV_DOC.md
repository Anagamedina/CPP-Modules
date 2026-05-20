# Documentación de Desarrollo - CPP05

En este documento te cuento cómo he diseñado la arquitectura de este módulo y las decisiones técnicas que he tomado. Mi objetivo ha sido crear un sistema robusto, escalable y que aproveche al máximo las capacidades de C++98.

## Arquitectura y Diseño

He estructurado el proyecto siguiendo una jerarquía clara de clases, donde la abstracción es la protagonista.

### Jerarquía de Clases
- **Bureaucrat**: Es la entidad principal que interactúa con el sistema. He aplicado encapsulamiento estricto para proteger el rango (grade) del burócrata.
- **AForm (Clase Abstracta)**: En el ejercicio 02, decidí convertir la clase `Form` en `AForm` (Abstract Form). Esto me permitió definir una interfaz común para todos los formularios sin permitir que se instancien formularios "genéricos".

### Patrones de Diseño Utilizados

He implementado varios patrones para resolver problemas específicos:

1.  **Factory Method (en ex03)**: La clase `Intern` utiliza este patrón para crear formularios. En lugar de usar un `if-else` gigante o un `switch`, he optado por un array de punteros a funciones miembro. Esto hace que el código sea mucho más limpio y fácil de extender.
2.  **Template Method**: En la clase base `AForm`, he definido el esqueleto del algoritmo de ejecución, dejando que las clases derivadas implementen los detalles específicos del "trabajo" que realiza cada formulario.
3.  **Strategy**: Cada formulario concreto (`Shrubbery`, `Robotomy`, `Presidential`) representa una estrategia diferente de ejecución, permitiendo cambiar el comportamiento en tiempo de ejecución según el tipo de objeto.

## Retos Técnicos

Durante el desarrollo, me enfrenté a varios desafíos interesantes:

- **Gestión de Excepciones en C++98**: Implementar excepciones personalizadas heredando de `std::exception` y asegurándome de que el `throw()` (especificador de excepción) fuera correcto para cumplir con el estándar.
- **Punteros a Funciones**: En el `Intern`, configurar el array de punteros a funciones para que devolvieran el tipo base `AForm*` fue un reto de sintaxis, pero valió la pena por la elegancia que aporta al diseño.
- **Limpieza de Memoria**: Al usar el patrón Factory, es crucial que el usuario del `Intern` sepa que es responsable de liberar la memoria del formulario creado. He puesto especial cuidado en que no haya fugas de memoria (memory leaks).

## TODO: Diagrama de Diseño de Software

- [ ] Crear y enlazar aquí el diagrama de clases UML detallado para visualizar la jerarquía de `Bureaucrat` y `AForm`.

---

*Nota: He organizado todos los apuntes previos y diagramas en la carpeta [**docs/**](./docs/) para mantener la raíz del módulo limpia y enfocada.*
