#pragma once

#include "../Component.hpp"

namespace component {
    class Creature : public Component {
        public:
            Creature(entity::Entity* parent_);
            // checks if should be deleted
            void FixedUpdate(double timeStep);
            // getters
            unsigned int getHP();
            unsigned int getMaxHP();
            // setters
            void setHP(unsigned int hp_);
            void setMaxHP(unsigned int hp_);
            // call this to modify hp
            virtual unsigned int changeHP(int changeBy);
            virtual ~Creature();
        protected:
            // called before deletion
            virtual void onDeathHook();
            unsigned int hp;
            unsigned int maxHP;
    };
}
