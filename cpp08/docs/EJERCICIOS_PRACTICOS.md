# 🏋️ EJERCICIOS PRÁCTICOS CPP08

## 📝 Ejercicio 00: Easy Find

### **Objetivo:**
Crear una función template que busque un valor en cualquier contenedor STL.

### **Conceptos Clave:**
- Templates con contenedores STL
- Iteradores
- Algoritmos STL (`std::find`)
- Manejo de excepciones

### **Implementación Base:**
```cpp
#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw std::exception();
    }
    return it;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lista = {10, 20, 30, 40, 50};
    
    try {
        auto it1 = easyfind(vec, 3);
        std::cout << "Encontrado en vector: " << *it1 << std::endl;
        
        auto it2 = easyfind(lista, 30);
        std::cout << "Encontrado en lista: " << *it2 << std::endl;
        
        // Esto lanzará excepción
        easyfind(vec, 99);
    } catch (const std::exception& e) {
        std::cout << "Valor no encontrado!" << std::endl;
    }
    
    return 0;
}
```

### **Puntos Importantes:**
- `typename T::iterator` es necesario para templates
- `std::find` devuelve `end()` si no encuentra
- Lanzar excepción cuando no se encuentra

---

## 📝 Ejercicio 01: Span

### **Objetivo:**
Implementar una clase que almacene números y calcule distancias entre ellos.

### **Conceptos Clave:**
- Contenedores STL (`std::vector`)
- Algoritmos de ordenación (`std::sort`)
- Cálculos matemáticos
- Gestión de memoria

### **Implementación Base:**
```cpp
#include <vector>
#include <algorithm>
#include <exception>
#include <iostream>

class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    Span(unsigned int n) : _maxSize(n) {}
    
    void addNumber(int number) {
        if (_numbers.size() >= _maxSize) {
            throw std::exception();
        }
        _numbers.push_back(number);
    }
    
    int shortestSpan() const {
        if (_numbers.size() < 2) {
            throw std::exception();
        }
        
        std::vector<int> sorted = _numbers;
        std::sort(sorted.begin(), sorted.end());
        
        int minSpan = sorted[1] - sorted[0];
        for (size_t i = 1; i < sorted.size() - 1; ++i) {
            int span = sorted[i + 1] - sorted[i];
            if (span < minSpan) {
                minSpan = span;
            }
        }
        return minSpan;
    }
    
    int longestSpan() const {
        if (_numbers.size() < 2) {
            throw std::exception();
        }
        
        std::vector<int> sorted = _numbers;
        std::sort(sorted.begin(), sorted.end());
        
        return sorted.back() - sorted.front();
    }
};

int main() {
    Span sp = Span(5);
    
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    
    std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    
    return 0;
}
```

---

## 📝 Ejercicio 02: Mutated Stack

### **Objetivo:**
Crear una pila (stack) con funcionalidades adicionales usando STL.

### **Conceptos Clave:**
- `std::stack`
- Iteradores personalizados
- Herencia o composición
- Algoritmos STL

### **Implementación Base:**
```cpp
#include <stack>
#include <iostream>
#include <algorithm>

template<typename T>
class MutantStack : public std::stack<T> {
public:
    // Alias para acceder al contenedor subyacente
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    
    iterator begin() {
        return this->c.begin();
    }
    
    iterator end() {
        return this->c.end();
    }
    
    const_iterator begin() const {
        return this->c.begin();
    }
    
    const_iterator end() const {
        return this->c.end();
    }
};

int main() {
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Iterando con iteradores:" << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Usando algoritmo STL
    std::sort(mstack.begin(), mstack.end());
    
    std::cout << "Después de ordenar:" << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## 🔧 EJERCICIOS DE PRÁCTICA

### **Ejercicio 1: Contador de Palabras**
```cpp
#include <map>
#include <string>
#include <iostream>

void contarPalabras(const std::string& texto) {
    std::map<std::string, int> contador;
    
    // Aquí iría la lógica para dividir el texto en palabras
    // y contar cada una usando el map
    
    for (const auto& par : contador) {
        std::cout << par.first << ": " << par.second << std::endl;
    }
}
```

### **Ejercicio 2: Eliminar Duplicados**
```cpp
#include <vector>
#include <set>
#include <algorithm>

std::vector<int> eliminarDuplicados(const std::vector<int>& vec) {
    std::set<int> conjunto(vec.begin(), vec.end());
    return std::vector<int>(conjunto.begin(), conjunto.end());
}
```

### **Ejercicio 3: Búsqueda Binaria**
```cpp
#include <vector>
#include <algorithm>

bool buscarBinario(const std::vector<int>& vec, int valor) {
    return std::binary_search(vec.begin(), vec.end(), valor);
}
```

---

## 🎯 CONCEPTOS AVANZADOS

### **1. Iteradores Personalizados**
```cpp
class MiIterador {
private:
    int* ptr;
    
public:
    MiIterador(int* p) : ptr(p) {}
    
    int& operator*() { return *ptr; }
    MiIterador& operator++() { ++ptr; return *this; }
    bool operator!=(const MiIterador& other) { return ptr != other.ptr; }
};
```

### **2. Algoritmos con Lambdas (C++11)**
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Contar números pares
int pares = std::count_if(vec.begin(), vec.end(), 
    [](int n) { return n % 2 == 0; });

// Transformar cada elemento
std::transform(vec.begin(), vec.end(), vec.begin(),
    [](int n) { return n * 2; });
```

### **3. Functores (Function Objects)**
```cpp
class Multiplicador {
private:
    int factor;
    
public:
    Multiplicador(int f) : factor(f) {}
    
    int operator()(int n) const {
        return n * factor;
    }
};

// Uso:
Multiplicador por3(3);
std::vector<int> vec = {1, 2, 3, 4, 5};
std::transform(vec.begin(), vec.end(), vec.begin(), por3);
```

---

## 🚀 TIPS PARA CPP08

1. **Lee la documentación**: `cppreference.com` es tu mejor amigo
2. **Practica iteradores**: Son la clave de la STL
3. **Usa algoritmos STL**: No reinventes la rueda
4. **Experimenta**: Prueba diferentes contenedores
5. **Optimiza**: Aprende cuándo usar cada contenedor

¡Con estos conceptos estarás listo para dominar CPP08! 🎯
















