#include "Component-Korwin.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "funcs.hpp"

namespace component {
    namespace sprites {
        korwin::korwin(
            entity::Entity* parent_
        ) :component::ShadedSpriteRenderer(parent_) {
            renderCounter = 0;
        }
        void korwin::FixedUpdate(double timeDelta) {
            renderCounter += timeDelta * 5;
            shader.setUniform("renderCount", renderCounter);
        }
        void korwin::Initialize() {
            assertCond(!texture.loadFromFile("resources/test.png"), "korwin failed to load texture");
            assertCond(!shader.loadFromFile(
                    "resources/shaders/testFrag.frag", 
                    sf::Shader::Fragment),
                "korwin failed to load shader");
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }
}
