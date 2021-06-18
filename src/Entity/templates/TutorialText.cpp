#include "TutorialText.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/TutorialText.hpp"

namespace entity {
    TutorialText::TutorialText(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::visual, scene_) {
    }

    void TutorialText::Initialize() {
        add_component(component::TutorialText);
    }
}
