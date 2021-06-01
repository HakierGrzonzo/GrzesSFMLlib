#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Player.hpp"
#ifndef EntityDefined
namespace entity {
    class Entity;
}
#endif


namespace audio {
    struct source {
        std::unique_ptr<Player> player;
        std::weak_ptr<entity::Entity> owner;
        ALuint buffer;
        ALuint source;
    };
    class AudioScene {
        public:
            AudioScene();
            void Update(sf::Vector2f refrencePos);
            std::weak_ptr<source> addSource(
                    std::weak_ptr<entity::Entity> owner, 
                    std::string filename, 
                    float gain = 1, 
                    bool looping = false
                );
            virtual ~AudioScene();
        private:
            ALCdevice* alDevice;
            ALCcontext* alContext;
            std::vector<std::shared_ptr<source>> sources;
            sf::Vector2f lastPos;
    };
}

#ifndef EntityDefined
#include "../Entity/Entity.hpp"
#endif
