#pragma once

#include "../Entity.hpp"

namespace entity {
    class HPeffect : public Entity {
        public:
            HPeffect(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            virtual ~HPeffect();
    };
}
