/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by anamedin         #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include <string>
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"

int main() {
    std::cout << "=== CPP05 EX03 - INTERN & FACTORY PATTERN ===" << std::endl << std::endl;
    
    // 1️⃣ CREAR OBJETOS
    Bureaucrat* jefe = new Bureaucrat("Arthur Dent", 1);
    Intern becario;
    
    std::cout << "Bureaucrat: " << *jefe << std::endl;
    std::cout << "Intern creado." << std::endl << std::endl;
    
    // 2️⃣ CREAR FORMULARIOS (Factory Pattern)
    std::cout << "--- CREANDO FORMULARIOS ---" << std::endl;
    AForm* formularios[4];
    
    // Formularios válidos
    formularios[0] = becario.makeForm("presidential pardon", "Zaphod Beeblebrox");
    formularios[1] = becario.makeForm("robotomy request", "Marvin");
    formularios[2] = becario.makeForm("shrubbery creation", "Slartibartfast");
    
    // Formulario inválido (demostrar excepción)
    try {
        formularios[3] = becario.makeForm("formulario imposible", "Target");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        formularios[3] = NULL;
    }
    
    std::cout << std::endl;
    
    // 3️⃣ PROCESAR FORMULARIOS (Polimorfismo)
    std::cout << "--- PROCESANDO FORMULARIOS ---" << std::endl;
    for (int i = 0; i < 3; ++i) {
        if (formularios[i]) {
            try {
                std::cout << "\nProcesando: " << formularios[i]->getName() << std::endl;
                jefe->signForm(*formularios[i]);
                jefe->executeForm(*formularios[i]);
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
    
    // 4️⃣ LIMPIAR MEMORIA
    std::cout << "\n--- LIMPIEZA ---" << std::endl;
    for (int i = 0; i < 4; ++i) {
        if (formularios[i]) {
            delete formularios[i];
        }
    }
    delete jefe;
    
    std::cout << "Programa completado." << std::endl;
    return 0;
}









