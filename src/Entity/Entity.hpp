#pragma once

#define EntityDefined

#ifndef ComponentDefined
    #include "../Component/Component.hpp"
#endif

#include "../Utils/Position.hpp"
#include "Entity-Tags.hpp"
#include <vector>
#include <memory>
#include "../funcs.hpp"

namespace entity {
    class EntitySystem;
    class Entity {
    public:
        Entity(
            utils::Position position_, 
            entityTags tag_, 
            EntitySystem* scene_
        );
        // Entities can be searched by their tags
        entityTags tag;
        utils::Position position;
        // pointer to parent scene
        EntitySystem* scene;
        // vector of components
        std::vector<std::unique_ptr<component::Component>> components;
        template <class T>
        T* GetComponent() {
            /*
             * Returns the first component of type T,
             * if no such component is found it returns nullptr
             */
            static int cachedIndex = -1;
            /*
            if (cachedIndex != -1 && cachedIndex < components.size()) {
                T* cachedPtr = dynamic_cast<T*>(components[cachedIndex].get());
                if (cachedPtr != nullptr) {
                    return cachedPtr;
                } else {
                    print("Cache hit miss " << cachedIndex);
                    cachedIndex = -1;
                }
            }
            */
            T* res = nullptr;
            for (unsigned int i = 0; i < components.size(); i++) {
                T* someComponent = dynamic_cast<T*>(components[i].get());
                if (someComponent != nullptr) {
                    cachedIndex = i;
                    res = someComponent;
                    break;
                }
            }
            return res;
        }
        // Use the addComponent() macro here to add components
        virtual void Initialize();
        // You can modify components here, called after Awake() on all components
        virtual void LateInitialize();
        virtual ~Entity();
    };
}

#ifndef EntitySystemDefined
    #include "Entity-System.hpp"
#endif
