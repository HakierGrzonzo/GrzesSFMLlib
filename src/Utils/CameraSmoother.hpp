#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    class CameraSmoother {
        public:
            CameraSmoother();
            CameraSmoother(float speedFactor, sf::Vector2f initialPos);
            // maxChange in position change per second
            sf::Vector2f calculatePosition(
                    sf::Vector2f currentVelocity, 
                    sf::Vector2f bounds, 
                    sf::Vector2f center, 
                    double timeStep);
        private:
            sf::Vector2f lastPosition;
            sf::Vector2f lastVelocity;
            float speedFactor;
            float lastSpeed;
    };
}
