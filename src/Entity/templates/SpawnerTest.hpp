#pragma once

#include "../Entity.hpp"

namespace entity {
    class SpawnerTest : public Entity {
        public:
            SpawnerTest(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            void LateInitialize();
            virtual ~SpawnerTest();
    };
}
