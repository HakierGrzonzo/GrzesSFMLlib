#include "CameraSmoother.hpp"
#include "../funcs.hpp"
#include "Operations.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    CameraSmoother::CameraSmoother() {};

    CameraSmoother::CameraSmoother(float speedFactor_, sf::Vector2f initialiPos) {
        lastPosition = initialiPos;
        speedFactor = speedFactor_;
        lastSpeed = 0;
        lastVelocity = sf::Vector2f();
    }

    sf::Vector2f CameraSmoother::calculatePosition(
            sf::Vector2f currentVelocity,
            sf::Vector2f bounds,
            sf::Vector2f center,
            double timeStep
            ) {
        double newSpeed = length(currentVelocity);
        if (abs(newSpeed - lastSpeed) > speedFactor * timeStep) {
            if (lastSpeed > newSpeed) {
                newSpeed = lastSpeed - speedFactor * timeStep;
            }
            else {
                newSpeed = lastSpeed + speedFactor * timeStep;
            }
        }
        lastSpeed = newSpeed;
        bounds = bounds * float(.5);
        if (newSpeed == 0) newSpeed += 0.00000001;
        currentVelocity /= float(newSpeed);
        sf::Vector2f newOffset = currentVelocity * float(newSpeed);
        newOffset = minimize(newOffset, ensureSignVec(newOffset, bounds)) * float(.5);
        return newOffset + center;
    }
}
