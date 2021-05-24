#pragma once

#include "../Entity.hpp"

namespace entity {
    class HPdisplayer : public Entity {
        public:
            HPdisplayer(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            virtual ~HPdisplayer();
    };
}
