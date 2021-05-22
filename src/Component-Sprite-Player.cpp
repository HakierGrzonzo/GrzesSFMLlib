#include "Component-Sprite-Player.hpp"
#include "Entity.hpp"
#include "funcs.hpp"
#include "Component-Sprite.hpp"

namespace component {
    namespace sprites {
        player::player(entity::Entity* parent_) 
            : component::SpriteRenderer(parent_){}

        void player::Initialize() {
            assertCond(!texture.loadFromFile("resources/antifachad.png"), "player failed to load texture");
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }


}
