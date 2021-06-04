#pragma once 
#include "../Entity.hpp"

namespace entity {
    class Bullet : public Entity {
        public:
            Bullet(
                utils::Position position_,
                EntitySystem* scene_
            );
            void Initialize();
    };
}
