#pragma once

#include "../Component/Component.hpp"
#include "../Component/templates/Renderable.hpp"
#include "Entity-Tags.hpp"
#include "Inputs.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <ctime>
#ifndef AudioSceneDefined
#include "../Audio/AudioScene.hpp"
#endif
#define EntitySystemDefined
#ifndef EntityDefined
    #include "Entity.hpp"
#endif
#include "ChunkCoord.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <box2d/b2_world.h>
#include "../Utils/CameraSmoother.hpp"

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
            // constructor
            EntitySystem(sf::RenderWindow* windowRef);

            void doTick();

            // vectors with entities for three layers
            std::vector<std::shared_ptr<Entity>> background;
            std::vector<std::shared_ptr<Entity>> normal;
            std::vector<std::shared_ptr<Entity>> top;

            // Chunk cache:
            std::unordered_map<sf::Vector2i, std::vector<std::weak_ptr<Entity>>, coordHash>* chunkCache;

            // pointer to a box2d world
            // is a shared ptr so component deconstructors can use it
            std::shared_ptr<b2World> physicsWorld;

            // deletes an entity
            void deleteEntity(const Entity* toDelete);

            // returns first entity in normal with tag
            std::weak_ptr<Entity> GetEntityByTag(entityTags tag);

            // returns all entities in normal with tag
            std::vector<std::weak_ptr<Entity>> GetEntitiesByTag(entityTags tag);

            std::weak_ptr<Entity> getWeakPtr(Entity* entity);

            // add Entity to a layer, calls Initialize() on entity, then
            // calls Awake() on components, then LateInitialize() on entity
            std::weak_ptr<Entity> 
            addEntity(Entity* entity, layers layer = layers::normal);

            // Get entities in radius
            // Does not return refrence entity
            // if exclude is set it will ignore entities with `tag`
            std::vector<std::weak_ptr<Entity>> 
            getEntitiesInRadius(
                    Entity* refrence, 
                    float radius, 
                    entityTags tag = bullet,
                    bool exclude = true
            );
            
            // input handler
            InputDirector inputHandler;
            
            // renderTarget
            sf::RenderWindow* windowRef;

            // audio Scene
            audio::AudioScene audioScene;
            
            // pointer to zoom factor
            float zoom;
            // destructor
            virtual ~EntitySystem();
            
            std::weak_ptr<Entity> focusedEntity;
        private:
            sf::View view;

            // call Update() on all components in all entities
            void doUpdateTick();
            bool isSmoothed;

            // call FixedUpdate() on all components in all entities, then do box2d physics step
            void doFixedUpdateTick(double timeDelta);

            std::chrono::time_point<std::chrono::steady_clock> lastTime;
            // get Vector that is connected with layer e.g. back -> background
            std::vector<std::shared_ptr<Entity>>* getVectorByLayer(layers layer);
            ContactListener contactListener;
            utils::CameraSmoother smoother;

    };
}

