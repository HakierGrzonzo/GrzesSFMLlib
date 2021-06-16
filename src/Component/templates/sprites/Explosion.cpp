#include "Explosion.hpp"
#include "../Explosion.hpp"
#include "../../../funcs.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include "../../../Utils/Random.hpp"
#include <SFML/System/Vector2.hpp>

namespace component {
    namespace sprites {
        Explosion::Explosion(entity::Entity* parent_) : 
        component::ShadedSpriteRenderer(parent_) {
            // Explosion shader generates random patterns over time
            // so we offset its starting point by a multiple of its duration
            float offset = 1.5 * utils::Random::getI(2137);
            renderCounter = 0.2 + offset;
            length = 1.5 + offset;
            range = -1;
            animationSpeed = 1;
        }
        
        void Explosion::Initialize() {
            texture = utils::ResourceManager::GetTexture("circle.png");
            shader = utils::ResourceManager::GetShader("shaders/explosion.frag");
            texture->setSmooth(true);
            sprite.setTexture(*texture.get());
        }
        
        void Explosion::Update() {
            auto explosion = parent->GetComponent<component::Explosion>();
            assertNotNull(explosion);
            if (range != explosion->getRange()) {
                range = explosion->getRange();
                auto size = getSpriteSize();
                print(range / size.x);
                sprite.setOrigin(size / float(2));
                sprite.setScale(sf::Vector2f(
                    range / size.x,
                    range / size.y
                ));
                animationSpeed  = 900/(range);
            }
        }

        void Explosion::FixedUpdate(double timeStep) {
            renderCounter += timeStep * animationSpeed;
            shader->setUniform("renderCount", renderCounter);
        }

        void Explosion::LateFixedUpdate() {
            if (renderCounter > length) {
                parent->scene->deleteEntity(parent);
            }
        }
    }
}
