#include "Korwin.hpp"
#include "../../Utils/ResourceManager.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "../../funcs.hpp"

namespace component {
    namespace sprites {
        korwin::korwin(
            entity::Entity* parent_
        ) :component::ShadedSpriteRenderer(parent_) {
            renderCounter = 0;
        }
        void korwin::FixedUpdate(double timeDelta) {
            renderCounter += timeDelta * 5;
            shader->setUniform("renderCount", renderCounter);
        }
        void korwin::Initialize() {
            texture = utils::ResourceManager::GetTexture("test.png");
            shader = utils::ResourceManager::GetShader("shaders/testFrag.frag");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }
}
