#include "Player.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include "../../../funcs.hpp"

namespace component {
    namespace sprites {
        player::player(entity::Entity* parent_) 
            : component::SpriteRenderer(parent_){}

        void player::Initialize() {
            texture = utils::ResourceManager::GetTexture("antifachad.png");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }


}
