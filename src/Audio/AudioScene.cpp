#include "AudioScene.hpp"
#include "AudioMacros.hpp"
#include "../funcs.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <libavcodec/codec_id.h>
#include <memory>
#include <stdexcept>
#include "Player.hpp"
#include "../Utils/ResourceManager.hpp"

namespace audio {
    AudioScene::AudioScene() {
        print("Opening OpenAL context!");
        alDevice = alcOpenDevice(nullptr);
        assertCond(alDevice == nullptr, "Failed to open OpenAL device!");
        alContext = alcCreateContext(alDevice, nullptr);
        assertCond(alContext == nullptr, "Failed to open OpenAL context!");
        ALCboolean contextMadeCurrent;
        bool success = alCall(contextMadeCurrent = alcMakeContextCurrent(alContext));
        assertCond(contextMadeCurrent != ALC_TRUE || !success, "Failed to set context current!");
        // Debug
        testPlayer = std::unique_ptr<Player>(new Player(
                    "resources/test.wav"
                ));
        auto bytesRef = testPlayer->getBytes();
        ALenum format = AL_FORMAT_MONO16;
        ALuint buffer;
        alCall(alGenBuffers(1, &buffer));
        alCall(alBufferData(buffer, format, bytesRef->data(), bytesRef->size(), 8000));

        ALuint source;
        alCall(alGenSources(1, &source));
        alCall(alSourcef(source, AL_PITCH, 1));
        alCall(alSourcef(source, AL_GAIN, 1.0));
        alCall(alSource3f(source, AL_POSITION, 5., 5., 5.));
        alCall(alSource3f(source, AL_VELOCITY, 5., 5., 5.));
        alCall(alSourcei(source, AL_LOOPING, true));
        alCall(alSourcei(source, AL_BUFFER, buffer));

        alCall(alSourcePlay(source));
    }

    AudioScene::~AudioScene() {
        print("Closing OpenAL context!");
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(alContext);
        alcCloseDevice(alDevice);
    }
}
