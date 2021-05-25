#include "ResourceManager.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include "../funcs.hpp"

namespace utils {
    const std::string ResourceManager::GetPrefix() {
        return "resources/";
    }

    std::shared_ptr<sf::Texture> ResourceManager::GetTexture(std::string name) {
        try {
            return textureCache.at(name);
        }
        catch (...){
            print("Loading asset: " + name);
            auto newTexture = std::make_shared<sf::Texture>(sf::Texture());
            assertCond(!newTexture->loadFromFile(GetPrefix() + name), "Failed to load: " + name);
            textureCache.emplace(name, newTexture);
            return newTexture;
        }
    }

    std::shared_ptr<sf::Font> ResourceManager::GetFont(std::string name) {
        try {
            return fontCache.at(name);
        }
        catch (...){
            print("Loading asset: " + name);
            auto newFont = std::make_shared<sf::Font>(sf::Font());
            assertCond(!newFont->loadFromFile(GetPrefix() + name), "Failed to load: " + name);
            fontCache.emplace(name, newFont);
            return newFont;
        }
    }

    std::unique_ptr<sf::Shader> ResourceManager::GetShader(std::string name) {
        auto shader = std::unique_ptr<sf::Shader>(new sf::Shader());
        std::string source;
        try {
            source = loadedShaders.at(name);
        }
        catch (...){ 
            print("Loading asset: " + name);
            std::ifstream sourceFile = std::ifstream(GetPrefix() + name, std::ios::binary);
            assertCond(!sourceFile.is_open(), "Failed to open file: " + name);
            source = std::string(std::istreambuf_iterator<char>(sourceFile), {});
            loadedShaders.emplace(name, source);
        }
        assertCond(!(shader->loadFromMemory(source, sf::Shader::Fragment)), "Failed to compile shader!: " + name);
        return shader;
    }
    std::map<std::string, std::shared_ptr<sf::Texture>> ResourceManager::textureCache =
        std::map<std::string, std::shared_ptr<sf::Texture>>();
    std::map<std::string, std::shared_ptr<sf::Font>> ResourceManager::fontCache =
        std::map<std::string, std::shared_ptr<sf::Font>>();
    std::map<std::string, std::string> ResourceManager::loadedShaders =
        std::map<std::string, std::string>();
}
