#include "ShadedSprite.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "../../funcs.hpp"

namespace component {
    ShadedSpriteRenderer::ShadedSpriteRenderer(
        entity::Entity* parent_
    ) : component::SpriteRenderer(parent_) {
    }
    void ShadedSpriteRenderer::Awake() {
        Initialize();
    }
    renderStruct ShadedSpriteRenderer::Render() {
        shader->setUniform("texture", sf::Shader::CurrentTexture);
        sprite.setPosition(parent->position.xy);
        return {&sprite, shader.get()};
    }

}
