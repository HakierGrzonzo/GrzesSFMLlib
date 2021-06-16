#pragma once
#include "Creature.hpp"

namespace component {
    class Player : public Creature {
        public: 
            Player(entity::Entity* parent_);
            void FixedUpdate(double timeStep);
            unsigned int changeHP(int changeBy);
        protected:
            float regenPeriod;
        private:
            float timeSinceLastRegen;
            float timeSinceLastDamage;
    };
}
