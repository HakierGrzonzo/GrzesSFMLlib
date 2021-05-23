#pragma once

#include "../Entity.hpp"

namespace entity {
    class testEntity : public Entity {
        public:
            testEntity(utils::Position position_, const EntitySystem* scene_ = nullptr);
            void Initialize();
            virtual ~testEntity();
    };
}
