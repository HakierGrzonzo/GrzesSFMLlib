#pragma once
#include <SFML/Graphics.hpp>
#include "../ShadedSprite.hpp"

namespace component {
    namespace sprites {
        class HPeffect : public Renderable {
            public:
                HPeffect(entity::Entity* parent_);
                void FixedUpdate(double timeStep);
                void LateFixedUpdate();
                void Awake();
                renderStruct Render();
            private:
                float renderCounter;
                std::shared_ptr<sf::Texture> texture;
                std::unique_ptr<sf::Shader> shader;
                sf::RectangleShape renderTarget;
                std::weak_ptr<entity::Entity> player;
        };
    }
}
