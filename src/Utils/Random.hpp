#pragma once

namespace utils {
    class Random {
        public:
            static void init(unsigned int seed);
            static float getF(float max);
            static int getI(int max);
    };
}
