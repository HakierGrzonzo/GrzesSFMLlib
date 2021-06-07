#pragma once 
#include "../Entity.hpp"

namespace entity {
    class Wall : public Entity {
        public:
            Wall(
                utils::Position position_,
                EntitySystem* scene_
            );
            void Initialize();
    };
}
