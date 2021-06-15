#pragma once
#include "../Component.hpp"

namespace component {
    class EnemyTarget : public Component {
        public:
            EnemyTarget(entity::Entity* parent_);
            int getPriority();
            void modifyPriority(int modifyBy);
            void Awake();

            // decay priority if not player
            void FixedUpdate(double timeDelta);
        protected:
            int priority;
            float sinceTick;
    };
}
