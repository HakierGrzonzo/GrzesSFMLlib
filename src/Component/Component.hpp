#pragma once
#include <memory>
#define ComponentDefined

namespace entity {
    class Entity;
}

namespace component {
    class Component {
    public:
        Component(entity::Entity* parent_);
        virtual void Update(); // called every frame
        virtual void FixedUpdate(double timeDelta); // called every frame with timeDelta, after update
        virtual void LateFixedUpdate();
        virtual void Awake(); // called on creation
        virtual ~Component();
    protected:
        entity::Entity* parent; // pointer to Entity containing this component
    };
}
#ifndef EntityDefined
    #include "../Entity/Entity.hpp"
#endif
