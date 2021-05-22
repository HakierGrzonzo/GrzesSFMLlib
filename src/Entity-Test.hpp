#pragma once

#include "Entity.hpp"
#include "Entity-System.hpp"
#include "Utils-Position.hpp"

namespace entity {
    class testEntity : public Entity {
        public:
            testEntity(utils::Position position_, const EntitySystem* scene_ = nullptr);
            void Initialize();
    };
}
