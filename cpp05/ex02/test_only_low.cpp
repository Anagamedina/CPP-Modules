#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main(){
    std::cout << "=== TESTING ONLY LOW-LEVEL BUREAUCRAT ===" << std::endl;
    
    Bureaucrat lowLevel("Low Clerk", 140);
    ShrubberyCreationForm shrubbery("test_garden");
    
    std::cout << "Low Clerk grade: " << lowLevel.getGrade() << std::endl;
    std::cout << "Shrubbery grade to execute: " << shrubbery.getGradeToExecute() << std::endl;
    std::cout << "Can execute? " << (lowLevel.getGrade() <= shrubbery.getGradeToExecute() ? "YES" : "NO") << std::endl;
    
    std::cout << "\nBefore execution - files:" << std::endl;
    system("ls -la *_shrubbery 2>/dev/null || echo 'No shrubbery files'");
    
    try {
        lowLevel.signForm(shrubbery);
        std::cout << "\nTrying to execute..." << std::endl;
        lowLevel.executeForm(shrubbery);
        std::cout << "SUCCESS!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    
    std::cout << "\nAfter execution - files:" << std::endl;
    system("ls -la *_shrubbery 2>/dev/null || echo 'No shrubbery files'");
    
    return 0;
}









