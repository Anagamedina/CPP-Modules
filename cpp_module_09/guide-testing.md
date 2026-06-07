Para estructurar las pruebas en tu proyecto, la mejor decisión depende de cómo se evalúa y compila. En el contexto de los **módulos de C++ (como los de 42/School)**, los ejercicios deben ser entregados como directorios **independientes y autónomos**.

Por lo tanto, la mejor práctica es utilizar una **estructura autocontenida (por ejercicio)**. A continuación te presento las dos opciones principales para que elijas la que mejor se adapte a tu flujo de trabajo:

---

### Opción A: Estructura Autocontenida (Recomendada para Módulos C++)
En este enfoque, cada ejercicio (`ex00`, `ex01`, `ex02`) tiene su propia carpeta `tests`. Esto mantiene cada ejercicio 100% independiente y listo para ser entregado individualmente sin dependencias externas.

```text
cpp_module_09/
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── BitcoinExchange.cpp
│   ├── BitcoinExchange.hpp
│   └── tests/
│       ├── Makefile           # Compila únicamente las pruebas de ex00
│       └── bitcoin_test.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── RPN.cpp
│   ├── RPN.hpp
│   └── tests/
│       ├── Makefile           # Compila únicamente las pruebas de ex01
│       └── rpn_test.cpp
└── ex02/
    ├── Makefile
    ├── main.cpp
    ├── PmergeMe.cpp
    ├── PmergeMe.hpp
    ├── namespaceUtils.hpp
    └── tests/
        ├── Makefile           # Compila únicamente las pruebas de ex02
        └── pmergeme_test.cpp
```

#### Ventajas de este enfoque:
1. **Independencia absoluta**: Puedes clonar o entregar `ex02` por sí solo, y sus pruebas irán con él.
2. **Sin interferencia en la entrega**: Si el evaluador o script de corrección compila con el `Makefile` principal en la raíz de `ex02`, no se enterará de la carpeta `tests/` a menos que tú lo decidas.
3. **Integración con Makefile principal**: Puedes agregar una regla `make test` en el `Makefile` principal de `ex02` que simplemente entre a la carpeta `tests/` y ejecute las pruebas de forma automática.

---

### Opción B: Estructura Centralizada (Ideal para Proyectos Grandes y CMake)
Si estás utilizando un sistema de construcción global como CMake (tienes un `CMakeLists.txt` en la raíz de `cpp_module_09`) y prefieres correr todas las pruebas del módulo de una sola vez, este enfoque centraliza los tests.

```text
cpp_module_09/
├── ex00/
│   ├── BitcoinExchange.cpp
│   └── ...
├── ex01/
│   ├── RPN.cpp
│   └── ...
├── ex02/
│   ├── PmergeMe.cpp
│   └── ...
└── tests/
    ├── CMakeLists.txt        # Configuración global de GoogleTest
    ├── ex00_bitcoin_test.cpp
    ├── ex01_rpn_test.cpp
    └── ex02_pmergeme_test.cpp
```

#### Ventajas de este enfoque:
1. **Un solo comando**: Compilas y ejecutas las pruebas de todos los ejercicios con un único comando desde la raíz.
2. **Configuración única**: Solo configuras GoogleTest una vez para todo el módulo en lugar de hacerlo por cada ejercicio.

---

### Mi recomendación para tu caso: **Opción A**
Dado que cada ejercicio tiene su propio ejecutable independiente (`PmergeMe`, `RPN`, `BTC`), la **Opción A** es mucho más limpia y segura.

Para implementarlo en `ex02` ahora mismo:
1. Crea una carpeta `tests/` dentro de `cpp_module_09/ex02/`.
2. Dentro de `tests/`, crea un archivo `pmergeme_test.cpp` que contenga las pruebas unitarias y tu función `main` para GoogleTest.
3. Crea un `Makefile` sencillo dentro de `tests/` que compile `PmergeMe.cpp` (del directorio padre `..`) junto con `pmergeme_test.cpp` para generar el ejecutable de pruebas.