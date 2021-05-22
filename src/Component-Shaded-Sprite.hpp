#pragma once 
#include "Component.hpp"
#include "Entity.hpp"
#include "Component-Sprite.hpp"
#include <SFML/Graphics/Shader.hpp>

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
        sf::Shader shader;
    };
}
