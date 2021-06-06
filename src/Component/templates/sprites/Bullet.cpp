#include "Bullet.hpp"
#include "../Physics.hpp"
#include "../../../funcs.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include "../../../Utils/Operations.hpp"
#include <SFML/System/Vector2.hpp>

namespace component {
    namespace sprites {
        Bullet::Bullet(entity::Entity* parent_) : 
        component::ShadedSpriteRenderer(parent_) {
            renderCounter = 0;
        }
        
        void Bullet::Initialize() {
            texture = utils::ResourceManager::GetTexture("bullet1.png");
            shader = utils::ResourceManager::GetShader("shaders/bullet.frag");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }

        void Bullet::FixedUpdate(double timeStep) {
            renderCounter += timeStep;
            shader->setUniform("renderCounter", renderCounter);
        }

        void Bullet::LateFixedUpdate() {
            auto physRef = parent->GetComponent<component::PhysicsBody>();
            assertNotNull(physRef);
            auto speed = box2sf(physRef->body->GetLinearVelocity());
            // normalize speed
            speed /= length(speed);
            // map shader from <-1;1> to <0;1>
            speed /= float(2);
            speed += sf::Vector2f(.5, .5);
            shader->setUniform("speed", speed);
        }
    }
}
