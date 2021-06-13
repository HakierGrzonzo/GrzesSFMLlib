#include "Entity-System.hpp"
#include "ChunkCoord.hpp"
#include "Entity-Tags.hpp"
#include "../funcs.hpp"
#include "Entity.hpp"
#include "../Component/templates/Physics.hpp"
#include "Inputs.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <box2d/b2_contact.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_world_callbacks.h>
#include <chrono>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <vector> 

float getScale(int height, int width) {
    float combinedRes = height + width;
    return resolutionRatio * (1 / combinedRes);
}

namespace entity {

    void ContactListener::BeginContact(b2Contact* contact) {
        auto bodyAuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        auto bodyBuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        if (bodyAuserdata != nullptr && bodyBuserdata != nullptr) {
            bodyAuserdata->OnCollisionEnter(bodyBuserdata);
            bodyBuserdata->OnCollisionEnter(bodyAuserdata);
        }
    }
    void ContactListener::EndContact(b2Contact* contact) {
        auto bodyAuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        auto bodyBuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        if (bodyAuserdata != nullptr && bodyBuserdata != nullptr) {
            bodyAuserdata->OnCollisionLeave(bodyBuserdata);
            bodyBuserdata->OnCollisionLeave(bodyAuserdata);
        }
    }

    EntitySystem::EntitySystem(sf::RenderWindow* windowRef_) {
        // setup view
        windowRef = windowRef_;
        zoom = getScale(explode(windowRef->getSize()));
        view.setSize(explode(windowRef->getSize()));
        view.zoom(zoom);
        //view.setCenter(100.f, 100.f);
        background = std::vector<std::shared_ptr<Entity>>();
        normal = std::vector<std::shared_ptr<Entity>>();
        top = std::vector<std::shared_ptr<Entity>>();

        contactListener = ContactListener();
        physicsWorld = std::shared_ptr<b2World>(new b2World(b2Vec2(0., 0.))); 
        physicsWorld->SetContactListener(&contactListener);

        inputHandler = InputDirector();
        lastTime = std::chrono::steady_clock::now();
        isSmoothed = false;
    }

    void EntitySystem::doTick() {
        // get time since last frame
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeSpan = now - lastTime;
        double timeSinceLastFrame = timeSpan.count();
        lastTime = now;
        float slowdown = 1;
        // if window is not focused -> slow motion;
        if(!windowRef->hasFocus()) {
            slowdown = 50;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
            slowdown = 2;
        }
        timeSinceLastFrame /= slowdown;

        // poll for resize event
        sf::Event event;
        while (windowRef->pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                windowRef->close();
            if (event.type == sf::Event::EventType::Resized) {
                // handle changed window size
                auto windowSize = windowRef->getSize();
                view.setSize((float) windowSize.x, (float) windowSize.y);
                zoom = getScale(explode(windowSize));
                view.zoom(zoom);
                print("Window size changed!");
                printVec2(windowSize);
            }
        }

        // Clear line
        std::cout << "\33[2K";
        // print fps and other stats
        std::cout << "fps: " <<
            1.0 / timeSpan.count() <<
            "\tframetime: " <<
            timeSinceLastFrame <<
            "\tentities: " <<
                background.size() +
                normal.size() +
                top.size() <<
            "\tsources: " <<
            audioScene.getSourceSize() <<
            "\r"; 
        std::cout.flush();
        
        bool doFocus = false;
        utils::Position preUpdatePos;
        if (!focusedEntity.expired()) {
            doFocus = true;
            preUpdatePos = focusedEntity.lock()->position;
        }

        doUpdateTick();

        doFixedUpdateTick(timeSinceLastFrame);
        
        // do Camera movement
        if (doFocus && !focusedEntity.expired()) {
            auto focusedPhys = focusedEntity.lock()->
                GetComponent<component::PhysicsBody>();
            sf::Vector2f newViewPos;
            if (focusedPhys) {
                if (!isSmoothed) {
                    smoother = utils::CameraSmoother(
                        10,
                        preUpdatePos.xy
                    );
                    isSmoothed = true;
                }
                newViewPos = smoother.calculatePosition(
                    box2sf(focusedPhys->body->GetLinearVelocity()),
                    view.getSize(),
                    focusedEntity.lock()->position.xy,
                    timeSinceLastFrame
                );
            } else {
                isSmoothed = false;
                newViewPos = focusedEntity.lock()->position.xy;
            }
            view.setCenter(newViewPos);
            audioScene.Update(newViewPos, timeSinceLastFrame, slowdown);
            windowRef->setView(view);
        }

        // do rendering
        windowRef->clear();
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto entity = vectorRef->operator[](i);
                auto rendererable = entity->GetComponent<component::Renderable>();
                if (rendererable) {
                    auto renderStruct = rendererable->Render();
                    assertNotNull(renderStruct.drawable);
                    if (renderStruct.shader) {
                        windowRef->draw(*(renderStruct.drawable), renderStruct.shader);
                    } else {
                        windowRef->draw(*(renderStruct.drawable));
                    }
                }
            }
        }
        windowRef->display();
    }

    std::vector<std::shared_ptr<Entity>>* EntitySystem::getVectorByLayer(layers layer) {
        switch (layer) {
            case layers::back: 
                return &background;
            case layers::normal:
                return &normal;
            case layers::top:
                return &top;
            default:
                // komputer pijany
                throw std::runtime_error("Are you on sth?");
        }
    }

    std::weak_ptr<Entity> EntitySystem::addEntity(Entity* entity, layers layer) {
        auto entityRef = std::shared_ptr<Entity>(entity);
        entityRef->Initialize();
        auto physics = entityRef->GetComponent<component::PhysicsBody>();
        if (physics != nullptr) {
            physics->world = physicsWorld;
        }
        for (unsigned long int i = 0; i < entityRef->components.size(); i++) {
            entityRef->components[i]->Awake();
        }
        if (layer == layers::normal) normal.push_back(entityRef);
        elif (layer == layers::back) background.push_back(entityRef);
        else top.push_back(entityRef);
        entityRef->LateInitialize();
        return std::weak_ptr<Entity>(entityRef);
    }

    void EntitySystem::doUpdateTick() {
        // do chunkCache update
        if (chunkCache) {
            delete chunkCache;
        }
        chunkCache = new std::unordered_map<sf::Vector2i, std::vector<std::weak_ptr<Entity>>, coordHash>();
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto entity = vectorRef->operator[](i);
                auto coord = getChunkCoord(entity->position.xy);
                try {
                    chunkCache->at(coord).push_back(entity);
                } catch (...) {
                    chunkCache->emplace(coord, std::vector<std::weak_ptr<Entity>>());
                    chunkCache->at(coord).push_back(entity);
                }
            }
        }
        // do input funcs if focused
        if (windowRef->hasFocus()) {
            inputHandler.doTick();
        }
        // do component Update()
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto entity = vectorRef->operator[](i);
                for (unsigned long int j = 0; j < entity->components.size(); j++) {
                    entity->components[j]->Update();
                }
            }
        }
    }

    void EntitySystem::doFixedUpdateTick(double timeDelta) {
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto entity = vectorRef->operator[](i);
                for (unsigned long int j = 0; j < entity->components.size(); j++) {
                    entity->components[j]->FixedUpdate(timeDelta);
                }
            }
        }
        // do physics stuff
        physicsWorld->Step(timeDelta, 8, 3);

        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto entity = vectorRef->operator[](i);
                for (unsigned long int j = 0; j < entity->components.size(); j++) {
                    entity->components[j]->LateFixedUpdate();
                }
            }
        }
    }

    std::weak_ptr<Entity> EntitySystem::GetEntityByTag(entityTags tag) {
        std::weak_ptr<Entity> res = std::weak_ptr<Entity>(std::shared_ptr<Entity>(nullptr));
        for (unsigned long int i = 0; i < normal.size(); i++) {
            if (normal[i]->tag == tag){
                res = std::weak_ptr<Entity>(normal[i]);
                break;
            }
        }
        return res;
    }

    std::vector<std::weak_ptr<Entity>> EntitySystem::GetEntitiesByTag(entityTags tag) {
        auto resultVec = std::vector<std::weak_ptr<Entity>>();
        for (unsigned long int i = 0; i < normal.size(); i++) {
            if (normal[i]->tag == tag){
                resultVec.push_back(normal[i]);
            }
        }
        return resultVec;
    }

    std::weak_ptr<Entity> EntitySystem::getWeakPtr(Entity* entity) {
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                auto compared = vectorRef->operator[](i);
                if (compared.get() == entity) {
                    return std::weak_ptr<Entity>(compared);
                }
            }
        }
        throw std::runtime_error("Failed to find entity!");
    }

    void EntitySystem::deleteEntity(const Entity* toDelete) {
        for (const auto i : allLayers) {
            auto vectorRef = getVectorByLayer(i);
            for (unsigned long int i = 0; i < vectorRef->size(); i++) {
                if (vectorRef->operator[](i).get() == toDelete) {
                    vectorRef->erase(vectorRef->begin() + i);
                    // Escape all loops
                    goto ENTITY_FOUND;
                }
            }
        }
        // If not found → throw error
        throw std::runtime_error("Entity not found");
    ENTITY_FOUND:
        return;
    }

    std::vector<std::weak_ptr<Entity>>
    EntitySystem::getEntitiesInRadius(Entity* refrence, float radius, bool ignoreBullets) {
        assertNotNull(chunkCache);
        auto res = std::vector<std::weak_ptr<Entity>>();
        auto topChunk = getChunkCoord(sf::Vector2f(refrence->position.xy.x + radius, refrence->position.xy.y + radius));
        auto bottomChunk = getChunkCoord(sf::Vector2f(refrence->position.xy.x - radius, refrence->position.xy.y - radius));
        for (float x = bottomChunk.x; x <= topChunk.x; x++) {
            for (float y = bottomChunk.y; y <= topChunk.y; y++) {
                auto currentChunk = sf::Vector2i(x, y);
                try {
                    auto entities = &chunkCache->at(currentChunk);
                    for (unsigned long long i = 0; i < entities->size(); i++) {
                        auto current = entities->operator[](i);
                        if (!current.expired()) {
                            auto currentRef = current.lock();
                            if (refrence->position.distanceTo(currentRef->position) < radius
                                    && currentRef.get() != refrence) {
                                if (currentRef->tag != bullet || !ignoreBullets)
                                    res.push_back(current);
                            }
                        }
                    }
                } catch (...) {
                    //print("Empty chunk");
                    //printVec2(currentChunk);
                }
            }
        }
        return res;
    }
    EntitySystem::~EntitySystem() {
        if (chunkCache)
            delete chunkCache;
    }
}
