#include "playerControler.hpp"
#include "Physics.hpp"
#include "../../funcs.hpp"
#include <SFML/Window/Keyboard.hpp>

#define PlayerSpeed 0.1

namespace component {
    PlayerControler::PlayerControler(entity::Entity* parent_) :
            Component(parent_) {
        callbacks[0] = parent->scene->inputHandler.subscribe(sf::Keyboard::W, &PlayerControler::moveUp, (void*) this);
        callbacks[1] = parent->scene->inputHandler.subscribe(sf::Keyboard::S, &PlayerControler::moveDown, (void*) this);
        callbacks[2] = parent->scene->inputHandler.subscribe(sf::Keyboard::A, &PlayerControler::moveLeft, (void*) this);
        callbacks[3] = parent->scene->inputHandler.subscribe(sf::Keyboard::D, &PlayerControler::moveRight, (void*) this);
        print(reinterpret_cast<void*>(PlayerControler::moveDown));
    }

    void PlayerControler::moveLeft(void* callback) {
        print("here2");
        print(callback);
        std::cout.flush();
        PlayerControler* thisPtr = (PlayerControler*) callback;
        thisPtr->playerForce.x -= 1;
    }

    void PlayerControler::moveRight(void* callback) {
        PlayerControler* thisPtr = (PlayerControler*) callback;
        thisPtr->playerForce.x += 1;
    }

    void PlayerControler::moveUp(void* callback) {
        PlayerControler* thisPtr = (PlayerControler*) callback;
        thisPtr->playerForce.y -= 1;
    }

    void PlayerControler::moveDown(void* callback) {
        PlayerControler* thisPtr = (PlayerControler*) callback;
        thisPtr->playerForce.y += 1;
    }

    void PlayerControler::FixedUpdate(double _) {
        if (playerForce.Length() > .001) {
            auto playerPhys = parent->GetComponent<PhysicsBody>();
            playerForce.Normalize();
            playerForce.x *= PlayerSpeed;
            playerForce.y *= PlayerSpeed;
            playerPhys->body->ApplyForceToCenter(playerForce, true);
        }
        playerForce = b2Vec2 {0, 0};
    }
}
