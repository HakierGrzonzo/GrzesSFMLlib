#include "Sprite.hpp"
#include "../../funcs.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace component {
    SpriteRenderer::SpriteRenderer(entity::Entity* parent_) : component::Renderable(parent_) {}
    void SpriteRenderer::Awake() {
        Initialize();
    }
    renderStruct SpriteRenderer::Render() {
        sprite.setPosition(parent->position.xy);
        return renderStruct {&sprite, nullptr};
    }
    void SpriteRenderer::Initialize() {}

    sf::Vector2f SpriteRenderer::getSpriteSize() {
        auto bounds = sprite.getGlobalBounds();
        return sf::Vector2f(bounds.width, bounds.height);
    }
}
