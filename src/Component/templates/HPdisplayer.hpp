#pragma once

#include "../Component.hpp"
#include "Creature.hpp"
#include "Renderable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

namespace component {
    class HPdisplayer : public Renderable {
        public:
            HPdisplayer(entity::Entity* parent_);
            void Awake();
            void FixedUpdate(double timedelta);
            renderStruct Render();
        private:
            sf::Text text;
            std::shared_ptr<sf::Font> textFont;
            std::weak_ptr<entity::Entity> entityToTrack;
            bool isValid;
    };
}
