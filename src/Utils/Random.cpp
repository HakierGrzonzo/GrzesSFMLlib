#include "Random.hpp"
#include <cstdlib>

namespace utils {
    void Random::init(unsigned int seed) {
        srand(seed);
    }

    int Random::getI(int max) {
        return rand() % max;
    }

    float Random::getF(float max) {
        return (float(rand()) / (RAND_MAX - 1.)) * max;
    }
}
