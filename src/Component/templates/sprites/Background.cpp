#include "Background.hpp"
#include "../../../funcs.hpp"
#include "../../../Utils/ResourceManager.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace component {
    shadedBackground::shadedBackground(entity::Entity* parent_) : Renderable(parent_) {
        renderTarget = sf::RectangleShape();
    }
    void shadedBackground::Awake() {
        Initialize();
    }

    void shadedBackground::Initialize() {
        shader = utils::ResourceManager::GetShader("shaders/background.frag");
    }
    renderStruct shadedBackground::Render() {
        auto windowref = parent->scene->windowRef;
        auto windowSize = sf::Vector2f(windowref->getSize()) * parent->scene->zoom;
        renderTarget.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
        // set drawable size to window size
        renderTarget.setSize(windowSize);
        // set drawable position to top left corner
        renderTarget.setPosition(windowref->mapPixelToCoords(sf::Vector2i(
            0, 0
        )));
        // get windows center position
        auto position = windowref->getView().getCenter();
        // set top left corner coords
        shader->setUniform("pos", sf::Vector2f(position.x - windowSize.x / 2,  position.y - windowSize.y / 2));
        // set window size
        shader->setUniform("size", windowSize);
        return renderStruct {&renderTarget, shader.get()};
    }
}
