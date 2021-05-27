#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    class CameraSmoother {
        public:
            CameraSmoother(sf::Vector2f maxChange_, sf::Vector2f initialPos);
            // maxChange in position change per second
            sf::Vector2f calculatePosition(
                    sf::Vector2f wantedPosition, 
                    sf::Vector2f bounds, 
                    sf::Vector2f center, 
                    double timeStep);
        private:
            sf::Vector2f maxChange;
            sf::Vector2f lastChange;
            sf::Vector2f lastPosition;
            bool wasInCenter;
    };
}
