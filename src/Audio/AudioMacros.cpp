#include "AudioMacros.hpp"
#include <AL/al.h>
#include <iostream>
#include <string>

bool check_al_errors(const std::string filename, const int linenumber, std::string arg) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << "AL Error: " << filename << ":" << linenumber << " ->" << std::endl;
        std::cerr << "\t" << arg << std::endl << "\tgot AL error: ";
        switch (error) {
            case AL_INVALID_NAME:
                std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
                break;
            case AL_INVALID_ENUM:
                std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
                break;
            case AL_INVALID_VALUE:
                std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
                break;
            case AL_INVALID_OPERATION:
                std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
                break;
            case AL_OUT_OF_MEMORY:
                std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
                break;
            default:
                std::cerr << "UNKNOWN AL ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}
