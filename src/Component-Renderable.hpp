#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "Utils-Position.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct renderStruct {
    sf::Drawable* drawable;
    sf::Shader* shader;
};

namespace component {
    class Renderable : public component::Component {
        // Anything that has to be drawn to a screen must descend from this class
    public:
        Renderable(entity::Entity* parent_);
        // Called before drawing, must return a sf::Drawable*
        // and can optionaly return a sf::Shader* 
        virtual renderStruct Render() = 0;
    };
}
