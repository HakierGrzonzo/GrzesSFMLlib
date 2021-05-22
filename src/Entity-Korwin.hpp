#pragma once

#include "Entity.hpp"

namespace entity {
    namespace tests {
        class korwintest : public Entity {
        public:
            korwintest(utils::Position position_, const EntitySystem* scene_ = nullptr);
            void Initialize();
            void LateInitialize();
        };
    }
}
