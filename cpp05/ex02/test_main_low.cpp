#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main(){
    std::cout << "=== TESTING MAIN PROGRAM LOW-LEVEL PART ===" << std::endl;
    
    // Create bureaucrats
    Bureaucrat highLevel("High Manager", 3);
    Bureaucrat lowLevel("Low Clerk", 140);
    
    // Create form
    ShrubberyCreationForm shrubbery("garden");
    
    std::cout << "Files before any execution:" << std::endl;
    system("ls -la *_shrubbery 2>/dev/null || echo 'No shrubbery files'");
    
    // First: High Manager executes (this creates the file)
    std::cout << "\n--- High Manager executes first ---" << std::endl;
    try {
        highLevel.signForm(shrubbery);
        highLevel.executeForm(shrubbery);
        std::cout << "High Manager SUCCESS!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "High Manager ERROR: " << e.what() << std::endl;
    }
    
    std::cout << "\nFiles after High Manager:" << std::endl;
    system("ls -la *_shrubbery 2>/dev/null || echo 'No shrubbery files'");
    
    // Second: Low Clerk tries to execute (this should fail)
    std::cout << "\n--- Low Clerk tries to execute ---" << std::endl;
    try {
        lowLevel.signForm(shrubbery);
        lowLevel.executeForm(shrubbery);
        std::cout << "Low Clerk SUCCESS!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Low Clerk ERROR: " << e.what() << std::endl;
    }
    
    std::cout << "\nFiles after Low Clerk:" << std::endl;
    system("ls -la *_shrubbery 2>/dev/null || echo 'No shrubbery files'");
    
    return 0;
}









