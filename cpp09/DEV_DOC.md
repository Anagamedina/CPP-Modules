# Documentación de Desarrollo - CPP09

En este módulo final, el reto ha sido aplicar los contenedores de la STL para gestionar grandes volúmenes de datos históricos y realizar búsquedas eficientes.

## Arquitectura y Diseño

Para el ejercicio de Bitcoin Exchange, he tomado las siguientes decisiones técnicas:

### 1. Elección del Contenedor
- **std::map**: He elegido `std::map<std::string, double>` para almacenar la base de datos de precios. 
- **¿Por qué?**: El `map` mantiene las claves (fechas) ordenadas automáticamente. Esto es fundamental para el requisito de encontrar la "fecha más cercana anterior" si una fecha exacta no existe, ya que el método `lower_bound` nos permite realizar esta búsqueda en tiempo logarítmico ($O(\log n)$).

### 2. Procesamiento de Datos
- **Lectura de CSV**: He implementado un sistema de parseo robusto para leer tanto la base de datos (`data.csv`) como el archivo de entrada del usuario.
- **Validación Estricta**: El programa verifica que las fechas tengan el formato `YYYY-MM-DD`, que los meses y días sean válidos, y que los valores estén dentro del rango permitido (0 a 1000 para el input).

## Retos Técnicos

- **Búsqueda de Fechas Inexistentes**: Implementar la lógica para retroceder a la fecha anterior más cercana usando iteradores de `map` fue el desafío más interesante. El uso de `lower_bound` y el manejo cuidadoso del iterador resultante fue clave.
- **Manejo de Errores**: Diseñar un sistema que informe de errores específicos (formato inválido, número negativo, número demasiado grande) sin detener la ejecución del programa para las siguientes líneas del archivo.
- **Eficiencia en Memoria**: Cargar miles de registros de un CSV en un `map` requiere una gestión eficiente de strings y doubles para no penalizar el rendimiento.

## TODO: Diagrama de Diseño de Software

- [ ] Crear un diagrama de flujo que ilustre el proceso de carga de la base de datos y la lógica de búsqueda de precios por fecha.

---
