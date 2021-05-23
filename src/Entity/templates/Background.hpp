#pragma once 

#include "../Entity.hpp"

namespace entity {
    class background : public Entity {
    public:
        background(EntitySystem* scene_);
        void Initialize();
        void LateInitialize();
    };
}
