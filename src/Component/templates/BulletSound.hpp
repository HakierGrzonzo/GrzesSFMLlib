#pragma once

#include "../Component.hpp"

namespace component {
    class BulletSound : public Component {
        public:
            BulletSound(entity::Entity* parent_);
            void Update();
        private:
            bool isInitialized;
    };
}
