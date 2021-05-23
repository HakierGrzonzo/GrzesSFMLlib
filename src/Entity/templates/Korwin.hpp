#pragma once

#include "../Entity.hpp"

namespace entity {
    namespace tests {
        class korwintest : public Entity {
        public:
            korwintest(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            void LateInitialize();
        };
    }
}
