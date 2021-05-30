#pragma once

#include "../Component.hpp"

namespace component {
    class Debug : public Component {
        public:
            Debug(entity::Entity* parent_);
            virtual ~Debug();
            void Awake();
            void Update();
            void FixedUpdate(double timestep);
            void LateFixedUpdate();
        private:
            unsigned int id;
            static unsigned int idCounter;
    };
}
