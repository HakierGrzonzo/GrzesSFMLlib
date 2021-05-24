#include "HPdisplayer.hpp"
#include "Creature.hpp"
#include "Renderable.hpp"
#include "../../funcs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace component {
    HPdisplayer::HPdisplayer(entity::Entity* parent_) : Renderable(parent_) {
        isValid = true;
    }
    void HPdisplayer::Awake() {
        assertCond(!textFont.loadFromFile("resources/fonts/futura.ttf"), 
                "Could not load font!");
        text.setFont(textFont);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        entityToTrack = parent->scene->GetEntityByTag(entity::player);
    }
    void HPdisplayer::FixedUpdate(double timedelta) {
        if (!isValid) {
            parent->scene->deleteEntity(parent);
        }
    }

    renderStruct HPdisplayer::Render() {
        if (entityToTrack.expired()) {
            isValid = false;
            print("Tracked entity has expired!");
            return renderStruct {&text, nullptr};
        }
        auto trackedEntity = entityToTrack.lock();
        auto trackedCreature = trackedEntity->GetComponent<Creature>();
        assertCond(trackedCreature == nullptr, "Tracked Entity has no Creature component");
        std::string hpText = std::to_string(trackedCreature->getHP()) + "/" + std::to_string(trackedCreature->getMaxHP());
        text.setString(hpText);
        text.setOrigin(sf::Vector2f(
                text.getGlobalBounds().width / 2,
                text.getGlobalBounds().height / 2
            ));
        sf::Vector2f newPos = trackedEntity->position.xy;
        newPos.y += 100;
        text.setPosition(newPos);
        return renderStruct {&text, nullptr};
    }

}
