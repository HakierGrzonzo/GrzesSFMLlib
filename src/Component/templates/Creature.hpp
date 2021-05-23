#pragma once

#include "../Component.hpp"
#include <climits>

namespace component {
    class Creature : public Component {
        public:
            Creature(entity::Entity* parent_);
            void FixedUpdate(double timeStep);
            unsigned int GetHP();
            void SetHP(int hp_);
            unsigned int ChangeHP(int changeBy);
            virtual ~Creature();
        protected:
            unsigned int hp;
            unsigned int maxHP;
    };
}
