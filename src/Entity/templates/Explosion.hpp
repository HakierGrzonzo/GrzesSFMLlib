#pragma once

#include "../Entity.hpp"
#include "../../Component/templates/Explosion.hpp"

namespace entity {
    class Explosion : public Entity {
        public:
            Explosion(utils::Position position, EntitySystem* scene);
            void Initialize();
    };
}
