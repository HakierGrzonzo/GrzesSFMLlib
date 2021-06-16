#pragma once
#include "../Component.hpp"

namespace component {
    class EnemyController : public Component {
        public:
            EnemyController(entity::Entity* parent_);
            void Update();
        private:
            std::weak_ptr<entity::Entity> lastVisitedEntity;
    };
}
