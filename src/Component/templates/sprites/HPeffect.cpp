
#include "HPeffect.hpp"
#include "../../../funcs.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include "../Creature.hpp"

namespace component {
    namespace sprites {
        HPeffect::HPeffect(entity::Entity* parent_) : 
        component::Renderable(parent_) {
            renderCounter = 0;
        }
        
        void HPeffect::Awake() {
            renderTarget = sf::RectangleShape();
            renderTarget.setSize(sf::Vector2f(1000, 1000));
            texture = utils::ResourceManager::GetTexture("hp_effect.png");
            shader = utils::ResourceManager::GetShader("shaders/hp.frag");
            texture->setSmooth(true);
            renderTarget.setTexture(texture.get());
            player = parent->scene->GetEntityByTag(entity::player);
        }

        void HPeffect::FixedUpdate(double timeStep) {
            renderCounter += timeStep;
            shader->setUniform("renderCounter", renderCounter);
        }

        void HPeffect::LateFixedUpdate() {
            if (!player.expired()) {
                auto creature = player.lock()->GetComponent<component::Creature>();
                assertNotNull(creature);
                float hp_percent = float(creature->getHP()) / float(creature->getMaxHP());
                shader->setUniform("hp", hp_percent);
            }
        }

        renderStruct HPeffect::Render() {
            shader->setUniform("texture", sf::Shader::CurrentTexture);
            auto windowref = parent->scene->windowRef;
            auto windowSize = sf::Vector2f(windowref->getSize()) * parent->scene->zoom;
            renderTarget.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
            // set drawable size to window size
            sf::Vector2f scale;
            scale.x = windowSize.x / renderTarget.getSize().x;
            scale.y = windowSize.y / renderTarget.getSize().y;
            renderTarget.setScale(scale);
            scale /= float(2);
            windowSize /= parent->scene->zoom;
            shader->setUniform("scale", scale);
            // set drawable position to top left corner
            renderTarget.setPosition(windowref->mapPixelToCoords(sf::Vector2i(
                0, 0
            )));
            return renderStruct {&renderTarget, shader.get()};
        }
    }
}
