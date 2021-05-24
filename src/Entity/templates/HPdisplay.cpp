#include "HPdisplay.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/HPdisplayer.hpp"

namespace entity {
    HPdisplayer::HPdisplayer(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::test, scene_) {
        Initialize();
    }

    void HPdisplayer::Initialize() {
        add_component(component::HPdisplayer);
    }
    HPdisplayer::~HPdisplayer() {}
}
