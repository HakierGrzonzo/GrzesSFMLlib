#include "Spawner.hpp"
#include "../../funcs.hpp"
#include "../../Utils/Random.hpp"
#include <cstdlib>
#include <math.h>

bool randomBool() {
    return (rand() % 2 == 0);
}

namespace component {
    Spawner::Spawner(entity::Entity* parent_) : Component(parent_) {
        spawnRate = 10;
        spawnRadius = 300;
        timeSinceLastSpawn = 0;
        isActive = false;
        limit = -1;
        //srand(time(nullptr));
    }

    void Spawner::stopSpawning() {
        isActive = false;
        timeSinceLastSpawn = 0;
    }

    void Spawner::FixedUpdate(double timeStep) {
        if (isActive) timeSinceLastSpawn += timeStep;
    }
    
    void Spawner::startSpawning(double rate, double radius, int limit_) {
        isActive = true;
        spawnRate = rate;
        spawnRadius = radius;
        limit = limit_;
        print("set up spawner!");
    }

    void Spawner::Update() {
        if (timeSinceLastSpawn > spawnRate && 
                (limit > 0 || limit == -1) &&
                isActive
                ) {
            // get random x that is -radius < x < radius
            float x = (utils::Random::getF(spawnRadius * 2.) - spawnRadius);
            /*
             * Calculate y as point on a circle, according to equation:
             * \[
             *      y = y_{spawner} \pm \sqrt{r^2 - \left( x - x_{spawner} \right)}
             * ]\
             * where we randomly decide if $\pm$ is + or -
             *
             */
            float y = parent->position.xy.y + 
                (randomBool() ? sqrt(sqr(spawnRadius) - sqr(x)) : - sqrt(sqr(spawnRadius) - sqr(x)));
            // add spawner position to x
            x += parent->position.xy.x;
            utils::Position spawnLocation = utils::Position(x, y);
            Spawn(spawnLocation);
            timeSinceLastSpawn = 0;
            if (limit > 0) {
                limit--;
            }
        }
    }
}
