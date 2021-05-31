#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include "Player.hpp"

namespace audio {
    class AudioScene {
        public:
            AudioScene();
            virtual ~AudioScene();
        protected:
            std::unique_ptr<Player> testPlayer;
        private:
            ALCdevice* alDevice;
            ALCcontext* alContext;
    };
}
