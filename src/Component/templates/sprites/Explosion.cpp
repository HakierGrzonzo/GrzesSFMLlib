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
            float range = explosion->getRange() / 2;
            auto size = sprite.getTextureRect();
            // we assume that texture is square
            float ratio = (2 * range) / float(size.height);
            sprite.setScale(sf::Vector2f(ratio, ratio));
            sprite.setOrigin(sf::Vector2f(range / 2, range / 2));
        }

        void Explosion::FixedUpdate(double timeStep) {
            renderCounter += timeStep * 3;
            shader->setUniform("renderCount", renderCounter);
        }

        void Explosion::LateFixedUpdate() {
            if (renderCounter > length) {
                parent->scene->deleteEntity(parent);
            }
        }
    }
}
