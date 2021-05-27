#include "CameraSmoother.hpp"
#include "../funcs.hpp"
#include "Operations.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    CameraSmoother::CameraSmoother(sf::Vector2f maxChange_, sf::Vector2f initialiPos) {
        maxChange = maxChange_;
        lastChange = sf::Vector2f();
        lastPosition = initialiPos;
        wasInCenter = true;
    }

    sf::Vector2f CameraSmoother::calculatePosition(
            sf::Vector2f wantedPosition,
            sf::Vector2f bounds,
            sf::Vector2f center,
            double timeStep
            ) {
        bounds = bounds * .5;
        sf::Vector2f wantedChange = wantedPosition - lastPosition;
        sf::Vector2f changeInChange = wantedChange - lastChange;
        double factor = fmax(200 / (length((lastPosition - center)) + 1), 1)* timeStep;
        sf::Vector2f allowedChange = maxChange * factor;
        print(factor)
        printVec2(allowedChange);
        printVec2(wantedChange);
        sf::Vector2f newOffset = lastPosition + lastChange + minimize(
                changeInChange,
                ensureSignVec(changeInChange, allowedChange)
            ) - center;
        printVec2(ensureSignVec(newOffset, bounds));
        printVec2(newOffset)
        newOffset = minimize(newOffset, ensureSignVec(newOffset, bounds));
        lastChange = newOffset + center - lastPosition;
        lastPosition = center + newOffset;
        return lastPosition;
    }
}
