#pragma once
extern "C" {
#include <libavutil/error.h>
}
#include <string>

#define stringify(var) #var

std::string decodeError(int ret) {
    if (ret >= 0) {
        return std::to_string(ret);
    }
    else {
        char errorbuf[500];
        av_strerror(ret, errorbuf, 500);
        return errorbuf;
    }
}
