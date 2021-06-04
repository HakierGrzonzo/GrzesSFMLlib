#pragma once

#include "Physics.hpp"
#include <box2d/b2_circle_shape.h>

namespace component {
    class Bullet : public PhysicsBody {
        public:
            Bullet(entity::Entity* parent);
            void Awake();
            void LateFixedUpdate();
            void FixedUpdate(double timeStep);
            // Deal damage and destroy itself
            void OnCollisionEnter(PhysicsBody* other);
            // setDamage for this bullet
            // negative damage will heal target
            void setDamage(int newDamage);
        protected:
            b2CircleShape shape;
            int damage;
            double deleteAfter;
        private:
            bool isDone;
    };
}
