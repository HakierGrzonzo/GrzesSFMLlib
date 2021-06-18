#pragma once

#include "../Entity.hpp"
#include "../../Component/templates/BigExplosion.hpp"

namespace entity {
    class BigExplosion : public Entity {
        public:
            BigExplosion(utils::Position position, EntitySystem* scene);
            void Initialize();
            void LateInitialize();
    };
}
