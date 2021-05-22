#pragma once 

#include "Entity.hpp"
#include "Entity-System.hpp"
#include "Utils-Position.hpp"

namespace entity {
    class background : public Entity {
    public:
        background(const EntitySystem* scene_ = nullptr);
        void Initialize();
        void LateInitialize();
    };
}
