#pragma once 

#include "../Entity.hpp"

namespace entity {
    class background : public Entity {
    public:
        background(const EntitySystem* scene_ = nullptr);
        void Initialize();
        void LateInitialize();
    };
}
