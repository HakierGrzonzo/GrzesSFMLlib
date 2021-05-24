#pragma once

#include "../Component.hpp"

namespace component {
    class Creature : public Component {
        public:
            Creature(entity::Entity* parent_);
            void FixedUpdate(double timeStep);
            unsigned int getHP();
            unsigned int getMaxHP();
            void setHP(unsigned int hp_);
            void setMaxHP(unsigned int hp_);
            unsigned int changeHP(int changeBy);
            virtual ~Creature();
        protected:
            unsigned int hp;
            unsigned int maxHP;
    };
}
