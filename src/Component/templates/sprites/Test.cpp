#include "Test.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include <SFML/System/Vector2.hpp>
#include "../../../funcs.hpp"

namespace component {
    namespace sprites {
        testSprite::testSprite(entity::Entity* parent_) 
            : component::SpriteRenderer(parent_){}

        void testSprite::Initialize() {
            //assertCond(!texture.loadFromFile("resources/dev test.png"), "player failed to load texture");
            texture = utils::ResourceManager::GetTexture("dev test.png");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
            sprite.setScale(sf::Vector2f(.4, .4));
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }


}
