#pragma once 
#include "../Component.hpp"
#include "Sprite.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <memory>

namespace component {
    class ShadedSpriteRenderer : public component::SpriteRenderer {
        // Simple Sprinte + Shader class
        // Setup shader and Sprite in Initialize()
        // Modify Uniforms in Update() or FixedUpdate()
    public:
        ShadedSpriteRenderer(entity::Entity* parent_);
        void Awake() override;
        renderStruct Render() override;
    protected:
        std::unique_ptr<sf::Shader> shader;
    };
}
