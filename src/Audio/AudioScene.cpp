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
#include <vector>
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

    void AudioScene::Update(sf::Vector2f refrencePos, double timedelta, float slowdown) {
        auto newSources = std::vector<std::shared_ptr<source>>();
        for (unsigned long long i = 0; i < sources.size(); i++) {
            ALint state = AL_PLAYING;
            alCall(alGetSourcei(sources[i]->source, AL_SOURCE_STATE, &state));
            if (sources[i]->owner.expired() || state != AL_PLAYING) {
                alCall(alDeleteSources(1, &sources[i]->source));
                alCall(alDeleteBuffers(1, &sources[i]->buffer));
            } else {
                const sf::Vector2f currentPos = sources[i]->owner.lock()->position.xy;
                sf::Vector2f newPos = currentPos - refrencePos;
                sf::Vector2f velocity = newPos - sources[i]->lastPos;
                velocity /= float(timedelta);
                sources[i]->lastPos = newPos;
                alCall(alSource3f(sources[i]->source, AL_POSITION, sf2al(newPos)));
                alCall(alSource3f(sources[i]->source, AL_VELOCITY, sf2al(velocity)));
                alCall(alSourcef(sources[i]->source, AL_PITCH, 1 / slowdown));
                newSources.push_back(sources[i]);
            }
        }
        lastPos = refrencePos;
        sources = newSources;
    }
    
    std::weak_ptr<source> AudioScene::addSource(
            std::weak_ptr<entity::Entity> owner, 
            std::string filename, 
            float gain, 
            bool looping
        ) {
        assertCond(owner.expired(), "What are you drinking?");
        auto sourceRef = std::shared_ptr<source>(new source {
                utils::ResourceManager::GetPlayer(filename)
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
        sourceRef->lastPos = pos;
        alCall(alSource3f(sourceRef->source, AL_POSITION, sf2al(pos)));
        // todo velocity
        alCall(alSource3f(sourceRef->source, AL_VELOCITY, 0, 0, 0));
        alCall(alSourcei(sourceRef->source, AL_LOOPING, looping));
        alCall(alSourcei(sourceRef->source, AL_BUFFER, sourceRef->buffer));
        alCall(alSourcePlay(sourceRef->source));
        sources.push_back(sourceRef);
        return std::weak_ptr<source>(sourceRef);
    }

    unsigned long long AudioScene::getSourceSize() {
        return sources.size();
    }

    AudioScene::~AudioScene() {
        print("Closing OpenAL context!");
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(alContext);
        alcCloseDevice(alDevice);
    }
}
