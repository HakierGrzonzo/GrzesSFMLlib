#pragma once

#include "../Component.hpp"

namespace component {
    class Explosion : public Component {
        // Creates explosion on Update()
        public:
            Explosion(entity::Entity* parent_);
            // returns the damage that explosion had dealt for a given
            // normalized distance 
            virtual int dealDamage(float distance);
            void Update();
            float getRange();
        protected:
            bool hadExploded;
            float range;
    };
}
