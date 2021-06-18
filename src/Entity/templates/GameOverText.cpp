
#include "GameOverText.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/GameOverText.hpp"

namespace entity {
    GameOverText::GameOverText(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::visual, scene_) {
    }

    void GameOverText::Initialize() {
        add_component(component::GameOverText);
    }
}
