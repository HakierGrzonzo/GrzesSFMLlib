#include "CameraSmoother.hpp"
#include "Operations.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    CameraSmoother::CameraSmoother(sf::Vector2f maxChange_) {
        maxChange = maxChange_;
        lastChange = sf::Vector2f();
        lastPosition = sf::Vector2f();
    }

    sf::Vector2f CameraSmoother::calculatePosition(
            sf::Vector2f wantedPosition,
            sf::Vector2u bounds,
            double timeStep
            ) {
        sf::Vector2f allowedChange = maxChange * timeStep;

        sf::Vector2f floatBounds = ensureSignVec(
                wantedPosition, sf::Vector2f(explodeOp(bounds, / 2.0))
            );
        sf::Vector2f wantedChange = wantedPosition - lastPosition;
    }
}
