#include "Renderable.hpp"
#include <stdexcept>

namespace component {
    Renderable::Renderable(entity::Entity* parent_) : component::Component(parent_) {}
}
