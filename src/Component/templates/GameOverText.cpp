#include "GameOverText.hpp"
#include "Renderable.hpp"
#include "../../funcs.hpp"
#include "../../Utils/ResourceManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <sstream>
#include <iomanip>

namespace component {
    GameOverText::GameOverText(entity::Entity* parent_) : Renderable(parent_) {
        time = 0;
    }
    void GameOverText::Awake() {
        textFont = utils::ResourceManager::GetFont("fonts/futura.ttf");
        text.setFont(*textFont.get());
        text.setFillColor(sf::Color::White);
        entityToTrack = parent->scene->GetEntityByTag(entity::player);
    }
    void GameOverText::FixedUpdate(double timedelta) {
        if (!entityToTrack.expired()) time += timedelta;
    }

    renderStruct GameOverText::Render() {
        if (!entityToTrack.expired()) {
            // draw nothing
            return renderStruct {nullptr, nullptr};
        } else {
            // nobody is going to play this for days, so minutes will be eneugh
            int minutes = std::floor(time / 60);
            float seconds = time - minutes * 60;
            std::ostringstream timeStream;
            timeStream << minutes << ":";
            timeStream << std::setprecision(seconds >= 10 ? 4 : 3);
            timeStream << seconds;
            text.setCharacterSize(125 * parent->scene->zoom);
            text.setString(timeStream.str());
            text.setOrigin(sf::Vector2f(
                    text.getGlobalBounds().width / 2,
                    text.getGlobalBounds().height / 2
                ));
            auto windowref = parent->scene->windowRef;
            auto windowSize = sf::Vector2f(windowref->getSize()) * parent->scene->zoom;
            auto position = windowref->mapPixelToCoords(sf::Vector2i(0, 0)) +
                windowSize / float(2);
            text.setPosition(position);
            return renderStruct {&text, nullptr};
        }
    }

}
