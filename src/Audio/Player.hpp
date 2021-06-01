#pragma once

#include <string>
#include <vector>
#include <memory>
extern "C" {
#include <libavcodec/packet.h>
#include <libavutil/channel_layout.h>
#include <libavutil/frame.h>
#include <libavutil/mem.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}
namespace audio {

    class Player {
        public:
            Player(std::string filename);
            virtual std::vector<uint8_t>* getBytes();
            virtual ~Player();
        protected:
            void decode(AVPacket* pkt);
            AVCodec* codec;
            AVCodecContext* codecContext;
            AVFormatContext* inputContext;
            std::vector<uint8_t> decodedData;
            AVFrame* frame;
            AVFrame* resampledFrame;
            SwrContext* resampleContext;
    };
}
