#pragma once

#include "../Component.hpp"
#include <memory>

namespace component {
    class Gun : public Component {
        public:
            Gun(entity::Entity* parent_);
            void Awake();
            virtual void Shoot() = 0;
        private:
            friend entity::InputDirector;
            static void ShootCallback(void* ptr);
            std::shared_ptr<entity::callBackContainer> callback;
    };
}
