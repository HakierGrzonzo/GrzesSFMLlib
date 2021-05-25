#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <memory>
#include <string>


namespace utils {
    class ResourceManager {
        public:
            static const std::string GetPrefix();
            // Get assets by refrence
            static std::shared_ptr<sf::Texture> GetTexture(std::string name);
            static std::shared_ptr<sf::Font> GetFont(std::string name);
            // Get shader by value
            static std::unique_ptr<sf::Shader> GetShader(std::string name);
            // Flush Cache
            static void Flush();
        private:
            static std::map<std::string, std::shared_ptr<sf::Texture>> textureCache;
            static std::map<std::string, std::shared_ptr<sf::Font>> fontCache;
            static std::map<std::string, std::string> loadedShaders;
    };
}
