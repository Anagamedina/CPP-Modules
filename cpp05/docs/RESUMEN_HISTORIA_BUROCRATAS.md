
---

## 📚 Historia: *El Burócrata que Firmó (o no) el Destino de la Tierra*

En el principio, antes de que existieran los snacks galácticos y los sistemas de notificación interplanetaria, alguien decidió que **el universo necesitaba formularios**.
Así nació el **Departamento Galáctico de Trámites y Sellos (DGTS)**, donde cada estrella, planeta y agujero negro debía **aprobar un formulario en triplicado** antes de existir… o explotar.

---

### 👔 El Burocratísimo Jeltz

Entre los burocratas de más alto **grade**, Prostetnic Vogon Jeltz era famoso:

* `grade = 3` (porque 1 es demasiado aburrido y 150 demasiado perezoso).
* Especialista en **excepciones**: `GradeTooHighException` y `GradeTooLowException` eran su pan de cada día.
* Su pasatiempo: escribir poesía que podría **destruir civilizaciones** si alguien se atrevía a leerla en voz alta.

Un día, Jeltz recibió un formulario inusual:

```cpp
PlanetaryRelocationForm earthForm;
```

> “Target: Earth. Executor grade required: 5 o superior. Procedimiento: obligatorio… con café opcional.”

---

### 🪐 El Problema Terrícola

Mientras tanto, en la Tierra, un joven burócrata terrestre llamado **Arthur Dent** aprendía que **no todos los formularios se firman solos**.
Intentó increpar:

> —¡No podemos demoler la Tierra!
> —¿Grade de Arthur? —preguntó Jeltz mientras revisaba su lista—
> —…42 —respondió Arthur con nerviosismo.
> —`GradeTooLowException` —dijo Jeltz, desplegando el formulario con una sonrisa burocrática—.
> “Necesitas al menos grade 5 para ejecutar PlanetaryRelocationForm.”

Arthur suspiró: “Siempre me toca la parte aburrida: manejar el **beSigned()** y no los rayos láser intergalácticos.”

---

### ✨ La Magia de los Formularios

Gracias a la **abstracción y polimorfismo** aprendidos en el módulo:

```cpp
AForm* form = intern.makeForm("PlanetaryRelocationForm", "Earth");
form->beSigned(boss);       // Solo grade alto puede firmar
form->execute(boss);         // ¡Bam! Tierra lista para teleportarse
```

* **Intern**: el empleado que hace cafés y crea formularios sin preguntar.
* **Bureaucrat**: decide si firmas o lanzas una excepción.
* **Formularios específicos**: desde `ShrubberyCreationForm` (árboles ASCII) hasta `PlanetaryRelocationForm` (traslado de planetas).

Cuando Jeltz finalmente firmó:

> “¡Planetary Relocation Request for Earth is being processed!”
> “Intergalactic Transport Beam activated!”
> “Earth has successfully been relocated!”

Arthur no entendió nada, pero al menos **no había poesía destructiva**… esta vez.

---

### 🌟 Moral del Módulo 05

En el universo:

* **Grade bajo = excepciones constantes**
* **Grade alto = poder para mover planetas (o crear árboles ASCII)**
* **Todo formulario mal firmado = desastre cósmico garantizado**

Y, sobre todo: **si el burócrata no firma, ni la Tierra ni tu código sobreviven.**

---


