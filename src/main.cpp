#include <SFML/Graphics/Shader.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boxer/boxer.h>
#include "gameloop.hpp"

int main() {
    if (!sf::Shader::isAvailable()) {
        boxer::show(
                "Shaders are not available on this platform, please use a gpu from later than 2005",
                "A very sad crash handler",
                boxer::Style::Error);
        return 1;
    }
    try {
        gameloop();
    } catch(const std::exception& e) {
        std::cerr.flush();
        std::cout << e.what() << std::endl;
        boxer::show(
                (std::string("Unfortunatly we had encountered an Exception:\n\n ") + std::string(e.what())).c_str(),
                "A very sad crash handler",
                boxer::Style::Error);
        return 1;
    }
}
