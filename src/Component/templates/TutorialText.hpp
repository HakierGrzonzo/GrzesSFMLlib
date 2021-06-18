#pragma once

#include "../Component.hpp"
#include "Renderable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

namespace component {
    class TutorialText : public Renderable {
        public:
            TutorialText(entity::Entity* parent_);
            void Awake();
            void FixedUpdate(double timeDelta);
            renderStruct Render();
        private:
            sf::Text text;
            std::shared_ptr<sf::Font> textFont;
            float time;
    };
}
