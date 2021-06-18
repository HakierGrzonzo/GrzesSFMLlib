#include "TutorialText.hpp"
#include "Renderable.hpp"
#include "../../funcs.hpp"
#include "../../Utils/ResourceManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace component {
    TutorialText::TutorialText(entity::Entity* parent_) : Renderable(parent_) {
        time = 0;
    }
    void TutorialText::Awake() {
        textFont = utils::ResourceManager::GetFont("fonts/futura.ttf");
        text.setFont(*textFont.get());
        text.setFillColor(sf::Color::White);
        text.setString("WASD to move\nctrl to slow down time\nspace to shoot");
    }

    void TutorialText::FixedUpdate(double timeDelta) {
        time += timeDelta;
        if (time > 12 && time <= 16)
            text.setString("Go kill some enemies...");
        else if (time > 16 && time <= 20)
            text.setString("...before there are to many of them!");
        else if (time > 20) 
            parent->scene->deleteEntity(parent);
    }

    renderStruct TutorialText::Render() {
        text.setCharacterSize(125 * std::sqrt(parent->scene->zoom));
        text.setOrigin(sf::Vector2f(
                text.getGlobalBounds().width / 2,
                text.getGlobalBounds().height / 2
            ));
        text.setPosition(sf::Vector2f());
        return renderStruct {&text, nullptr};
    }

}
