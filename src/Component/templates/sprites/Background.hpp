#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include "../Renderable.hpp"

namespace component {
    class shadedBackground : public component::Renderable {
        // draws a shader to the whole window background
        // use Initialize() to setup shader and 
        // Update() / FixedUpdate() to set uniforms
        //
        // passes vec2 `pos` with window's view position and
        // vec2 `size` with window size
        // Call setView() to set window from gameloop()
    public:
        shadedBackground(entity::Entity* parent_);
        virtual void Initialize();
        void Awake() override;
        void setView(sf::Window* window);
        renderStruct Render() override;
    protected:
        std::unique_ptr<sf::Shader> shader;
    private:
        sf::RectangleShape renderTarget;
        sf::RenderWindow* windowref = nullptr;
        sf::Vector2f lastSize;
    };
}
