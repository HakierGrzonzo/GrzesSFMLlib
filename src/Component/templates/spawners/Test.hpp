#pragma once

#include "../Spawner.hpp"

namespace component {
    namespace spawners {
        template <class T>
        class Generic : public component::Spawner {
            public:
                Generic(entity::Entity* parent_) : Spawner(parent_) {};
                void Spawn(utils::Position spawnAt) {
                    parent->scene->addEntity(new T(spawnAt, parent->scene));
                }
        };
    }
}
