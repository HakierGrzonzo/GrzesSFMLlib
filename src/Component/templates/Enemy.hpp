#pragma once
#include "Creature.hpp"

namespace component {
    class Enemy : public Creature {
        public: 
            Enemy(entity::Entity* parent_);
        protected:
            void onDeathHook();
    };
}
