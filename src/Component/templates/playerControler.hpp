#pragma once

#include "../Component.hpp"
#include "Physics.hpp"
#include <box2d/b2_math.h>
#include <memory>

namespace component {
    class PlayerControler : public Component {
        public:
            PlayerControler(entity::Entity* parent_);
            void FixedUpdate(double _);
            friend entity::InputDirector;
        protected:
            static void moveLeft(void* callback);
            static void moveRight(void* callback);
            static void moveDown(void* callback);
            static void moveUp(void* callback);
            b2Vec2 playerForce {0, 0};
        private:
            std::shared_ptr<entity::callBackContainer> callbacks[4];
    };
}
