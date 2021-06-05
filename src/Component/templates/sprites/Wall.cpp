#include "Wall.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include "../../../funcs.hpp"
#include <SFML/System/Vector2.hpp>

namespace component {
    namespace sprites {
        Wall::Wall(entity::Entity* parent_) 
            : component::SpriteRenderer(parent_){}

        void Wall::Initialize() {
            texture = utils::ResourceManager::GetTexture("wall1.png");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
            sprite.scale(sf::Vector2f(.5, .5));
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }


}
