#include <SFML/Graphics/Shader.hpp>
#include <exception>
#include <iostream>
#include <string>
#ifdef BOXER
#include <boxer/boxer.h>
#endif
#include "gameloop.hpp"

int main() {
    if (!sf::Shader::isAvailable()) {
#ifdef BOXER
        boxer::show(
                "Shaders are not available on this platform, please use a gpu from later than 2005",
                "A very sad crash handler",
                boxer::Style::Error);
#else
        std::cerr << "Shaders are not available on this platform, please use a gpu from later than 2005" << std::endl;
        system("pause");
#endif
        return 1;
    }
    try {
        gameloop();
    } catch(const std::exception& e) {
#ifdef BOXER
        boxer::show(
                (std::string("Unfortunatly we had encountered an Exception:\n\n ") + std::string(e.what())).c_str(),
                "A very sad crash handler",
                boxer::Style::Error);
#else
        std::cerr.flush();
        std::cout << "The application has encountered an exception:" << std::endl;
        std::cout << e.what() << std::endl;
        system("pause");
#endif
        return 1;
    }
}
