#pragma once
#include "../Component.hpp"

namespace component {
    template <class T>
    class WallPlacer : public Component {
        public:
            WallPlacer(entity::Entity* parent_) :
                Component(parent_){}
            void Awake() {

            }
            void LateFixedUpdate();
        private:
            entity::Entity* getEntityPrototype(
                    utils::Position pos, 
                    entity::EntitySystem scene) {
                return new T(pos, scene);
            }
    };
}
