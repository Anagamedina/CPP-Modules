#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main(){
    std::cout << "=== TESTING HIGH-LEVEL BUREAUCRAT ===" << std::endl;
    
    Bureaucrat highLevel("High Manager", 3);
    ShrubberyCreationForm shrubbery("test_garden");
    
    std::cout << "High Manager grade: " << highLevel.getGrade() << std::endl;
    std::cout << "Shrubbery grade to execute: " << shrubbery.getGradeToExecute() << std::endl;
    
    try {
        highLevel.signForm(shrubbery);
        highLevel.executeForm(shrubbery);
        std::cout << "SUCCESS!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    
    return 0;
}









