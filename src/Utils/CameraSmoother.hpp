#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    class CameraSmoother {
        public:
            CameraSmoother(sf::Vector2f maxChange_);
            // maxChange in position change per second
            sf::Vector2f calculatePosition(
                    sf::Vector2f wantedPosition, 
                    sf::Vector2u bounds, 
                    double timeStep);
        private:
            sf::Vector2f maxChange;
            sf::Vector2f lastChange;
            sf::Vector2f lastPosition;
    };
}
