#include "Pistol.hpp"
#include "../../../funcs.hpp"
#include "../../../Utils/Operations.hpp"
#include "../../../Entity/templates/Bullet.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <box2d/b2_math.h>

namespace component {
    namespace guns {
        Pistol::Pistol(entity::Entity* parent) : component::Gun(parent) {
            shootingSpeed = .35;
            timeSinceLastShot = 0;
        }

        void Pistol::Shoot() {
            if (timeSinceLastShot > shootingSpeed) {
                timeSinceLastShot = 0;
                sf::Vector2i mousePos = sf::Mouse::getPosition(*parent->scene->windowRef);
                auto gamePos = parent->scene->windowRef->mapPixelToCoords(mousePos);
                auto relativePos = gamePos - parent->position.xy;
                // normalize vec
                relativePos /= length(relativePos);
                auto bulletPos = parent->position.xy + relativePos * float(200);
                auto bullet = parent->scene->addEntity(
                    new entity::Bullet(
                            utils::Position(bulletPos), 
                            parent->scene
                        )
                    );
                auto bulletPhys = bullet.lock()->GetComponent<component::Bullet>();
                assertNotNull(bulletPhys);
                bulletPhys->setDamage(50);
                auto physBody = parent->GetComponent<component::PhysicsBody>();
                assertNotNull(physBody);
                b2Vec2 setSpeed = physBody->body->GetLinearVelocity();
                setSpeed.x += relativePos.x * 1.5;
                setSpeed.y += relativePos.y * 1.5;
                bulletPhys->body->SetLinearVelocity(setSpeed);
                // Play sound
                parent->scene->audioScene.addSource(
                    bullet,
                    "sfx/shoot1.wav.aac"
                );
            }
        }

        void Pistol::FixedUpdate(double timeStep) {
            timeSinceLastShot += timeStep;
        }
    }
}
