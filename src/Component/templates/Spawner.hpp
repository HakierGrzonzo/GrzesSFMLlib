#pragma once

#include "../Component.hpp"

namespace component {
    class Spawner : public Component {
        public:
            Spawner(entity::Entity* parent_);
            // pass entity as value, entity has to be uninitialized!
            void stopSpawning();
            // start spawning every `rate` seconds, 
            // on circle with `radius`, up to `limit` (-1 is infinity)
            void startSpawning(double rate, double radius, int limit = -1);
            void FixedUpdate(double timeStep);

            // entities will be spawned at update
            void Update();
        protected:
            double spawnRate;
            double spawnRadius;
            int limit;
            virtual void Spawn(utils::Position spawnAt) = 0;
        private:
            double timeSinceLastSpawn;
            bool isActive;
    };
}
