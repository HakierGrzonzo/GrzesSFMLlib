#include "Entity.hpp"
#include "funcs.hpp"
#include "Component-Sprite.hpp"
#include "Component-Sprite-Test.hpp"
#include <SFML/System/Vector2.hpp>

namespace component {
    namespace sprites {
        testSprite::testSprite(entity::Entity* parent_) 
            : component::SpriteRenderer(parent_){}

        void testSprite::Initialize() {
            assertCond(!texture.loadFromFile("resources/dev test.png"), "player failed to load texture");
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sprite.setScale(sf::Vector2f(.4, .4));
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }


}
