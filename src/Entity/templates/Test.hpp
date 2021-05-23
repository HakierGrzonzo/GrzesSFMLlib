#pragma once

#include "../Entity.hpp"

namespace entity {
    class testEntity : public Entity {
        public:
            testEntity(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            virtual ~testEntity();
    };
}
