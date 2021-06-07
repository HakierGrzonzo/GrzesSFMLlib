#pragma once
#include "Renderable.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace component {
    class SpriteRenderer : public component::Renderable {
        // Simple Sprite handling class
        // Setup sprite in Initialize()
    public:
        SpriteRenderer(entity::Entity* parent_);
        void Awake() override;
        virtual void Initialize(); // set texture here
        renderStruct Render() override;
        sf::Vector2f getSpriteSize();
    protected:
        sf::Sprite sprite;
        std::shared_ptr<sf::Texture> texture;
    };
}
