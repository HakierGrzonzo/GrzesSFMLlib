#pragma once
#include "../Entity.hpp"

namespace entity {
    class Target : public Entity {
        public:
            Target(utils::Position position, entity::EntitySystem* scene);
            void Initialize();
    };
}
