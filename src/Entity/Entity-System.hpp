#pragma once

#include "../Component/Component.hpp"
#include "Entity-Tags.hpp"
#include "Inputs.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#ifndef AudioSceneDefined
#include "../Audio/AudioScene.hpp"
#endif
#define EntitySystemDefined
#ifndef EntityDefined
    #include "Entity.hpp"
#endif
#include <memory>
#include <vector>
#include <box2d/b2_world.h>

namespace entity {

    // define layers
    enum layers {
        back,
        normal,
        top
    };
    const layers allLayers[] = {back, normal, top};
    
    // helper class for EntitySystem
    class ContactListener : public b2ContactListener {
        public:
            void BeginContact(b2Contact* contact);
            void EndContact(b2Contact* contact);
    };
    class EntitySystem {
        public:
            // vectors with entities for three layers
            std::vector<std::shared_ptr<Entity>> background;
            std::vector<std::shared_ptr<Entity>> normal;
            std::vector<std::shared_ptr<Entity>> top;

            // pointer to a box2d world
            // is a shared ptr so component deconstructors can use it
            std::shared_ptr<b2World> physicsWorld;

            // constructor
            EntitySystem(sf::RenderWindow* windowRef, float* zoom);

            // deletes an entity
            void deleteEntity(const Entity* toDelete);

            // returns first entity in normal with tag
            std::weak_ptr<Entity> GetEntityByTag(entityTags tag);

            // returns all entities in normal with tag
            std::vector<std::weak_ptr<Entity>> GetEntitiesByTag(entityTags tag);

            // call Update() on all components in all entities
            void doUpdateTick();

            // call FixedUpdate() on all components in all entities, then do box2d physics step
            void doFixedUpdateTick(double timeDelta);

            std::weak_ptr<Entity> getWeakPtr(Entity* entity);

            // add Entity to a layer, calls Initialize() on entity, then
            // calls Awake() on components, then LateInitialize() on entity
            std::weak_ptr<Entity> addEntity(Entity* entity, layers layer = layers::normal);
            
            // input handler
            InputDirector inputHandler;
            
            // renderTarget
            sf::RenderWindow* windowRef;

            // audio Scene
            audio::AudioScene audioScene;
            
            // pointer to zoom factor
            float* zoom;
            // destructor
            virtual ~EntitySystem();

        private:
            // get Vector that is connected with layer e.g. back -> background
            std::vector<std::shared_ptr<Entity>>* getVectorByLayer(layers layer);
            ContactListener contactListener;

    };
}

