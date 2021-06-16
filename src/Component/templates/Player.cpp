#include "Player.hpp"

namespace component {
    Player::Player(entity::Entity* parent_) : Creature(parent_) {
        regenPeriod = .33;
        timeSinceLastDamage = 0;
        timeSinceLastRegen = 0;
    }
    
    void Player::FixedUpdate(double timeStep) {
        timeSinceLastDamage += timeStep;
        timeSinceLastRegen += timeStep;
        if (
                timeSinceLastRegen > regenPeriod &&
                timeSinceLastDamage > 3.) {
            changeHP(1);
            timeSinceLastRegen = 0;
        }
        Creature::FixedUpdate(timeStep);
    }

    unsigned int Player::changeHP(int changeBy) {
        if (changeBy < 0) {
            timeSinceLastDamage = 0;
        }
        return Creature::changeHP(changeBy);
    }
}
