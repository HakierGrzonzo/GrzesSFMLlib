#pragma once

#include "Entity.hpp"
#include "EntitySystem.hpp"
#include "Position.hpp"

namespace entity {
    class playerEntity : public Entity {
        public:
            playerEntity(utils::Position position_, const EntitySystem* scene_ = nullptr);
            void Initialize();
            void LateInitialize();
    };
}
