#include "AudioScene.hpp"
#include "AudioMacros.hpp"
#include "../funcs.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <libavcodec/codec_id.h>
#include <memory>
#include <stdexcept>
#include "Player.hpp"
#include "../Utils/ResourceManager.hpp"

namespace audio {
    AudioScene::AudioScene() {
        lastPos = sf::Vector2f();
        print("Opening OpenAL context!");
        alDevice = alcOpenDevice(nullptr);
        assertCond(alDevice == nullptr, "Failed to open OpenAL device!");
        alContext = alcCreateContext(alDevice, nullptr);
        assertCond(alContext == nullptr, "Failed to open OpenAL context!");
        ALCboolean contextMadeCurrent;
        bool success = alCall(contextMadeCurrent = alcMakeContextCurrent(alContext));
        assertCond(contextMadeCurrent != ALC_TRUE || !success, "Failed to set context current!");
    }

    void AudioScene::Update(sf::Vector2f refrencePos) {
        for (unsigned long long i = 0; i < sources.size(); i++) {
            if (sources[i]->owner.expired()) {
                print("Deleting source!");
                alCall(alDeleteSources(1, &sources[i]->source));
                alCall(alDeleteBuffers(1, &sources[i]->buffer));
            } else {
                sf::Vector2f newPos = sources[i]->owner.lock()->position.xy - refrencePos;
                alCall(alSource3f(sources[i]->source, AL_POSITION, sf2al(newPos)));
                // todo velocity
            }
        }
        lastPos = refrencePos;
    }
    
    std::weak_ptr<source> AudioScene::addSource(
            std::weak_ptr<entity::Entity> owner, 
            std::string filename, 
            float gain, 
            bool looping
        ) {
        print("Adding player for: " + filename);
        assertCond(owner.expired(), "What are you drinking?");
        auto sourceRef = std::shared_ptr<source>(new source {
                std::unique_ptr<Player>(new Player(filename))
            });
        sourceRef->owner = owner;
        ALenum format = AL_FORMAT_MONO16;
        auto bytesRef = sourceRef->player->getBytes();
        alCall(alGenBuffers(1, &sourceRef->buffer));
        alCall(alBufferData(sourceRef->buffer, format, bytesRef->data(), bytesRef->size(), SAMPLE_RATE));
        alCall(alGenSources(1, &sourceRef->source));
        alCall(alSourcef(sourceRef->source, AL_PITCH, 1));
        alCall(alSourcef(sourceRef->source, AL_GAIN, gain));
        // set position
        sf::Vector2f pos = owner.lock()->position.xy - lastPos;
        alCall(alSource3f(sourceRef->source, AL_POSITION, sf2al(pos)));
        // todo velocity
        alCall(alSource3f(sourceRef->source, AL_VELOCITY, 0, 0, 0));
        alCall(alSourcei(sourceRef->source, AL_LOOPING, looping));
        alCall(alSourcei(sourceRef->source, AL_BUFFER, sourceRef->buffer));
        alCall(alSourcePlay(sourceRef->source));
        sources.push_back(sourceRef);
        return std::weak_ptr<source>(sourceRef);
    }

    AudioScene::~AudioScene() {
        print("Closing OpenAL context!");
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(alContext);
        alcCloseDevice(alDevice);
    }
}
