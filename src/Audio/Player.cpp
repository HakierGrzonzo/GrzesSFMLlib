#include "Player.hpp"
#include "FFmpegMacros.hpp"
#include "AudioMacros.hpp"
#include "../funcs.hpp"
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/codec.h>
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>
#include <libavutil/samplefmt.h>
}
#include <memory>
#include <stdexcept>

std::string getFormatString(int format) {
    char buff[500];
    av_get_sample_fmt_string(buff, 500, (AVSampleFormat) format);
    return buff;
}

namespace audio {
    Player::Player(std::string filename) {
        print("Starting ffmpeg decoder")
        decodedData = std::vector<uint8_t>();
        inputContext = nullptr;
        frame = nullptr;
        int error;
        error = avformat_open_input(&inputContext, filename.c_str(), nullptr, nullptr);
        assertCond(error < 0, "Failed to open file:\t" + filename);

        error = avformat_find_stream_info(inputContext, nullptr);
        assertCond(error != 0, "Failed get stream info");
        assertCond(inputContext->nb_streams != 1, "Expected one stream, got more");
        codec = avcodec_find_decoder(inputContext->streams[0]->codecpar->codec_id);
        assertNotNull(codec);

        codecContext = avcodec_alloc_context3(codec);
        assertNotNull(codecContext);

        error = avcodec_parameters_to_context(codecContext, inputContext->streams[0]->codecpar);
        assertCond(error < 0, "Failed to send codecpars: " + decodeError(error));

        error = avcodec_open2(codecContext, codec, nullptr);
        assertCond(error < 0, "Failed to open decoder context: " + decodeError(error));

        resampleContext = swr_alloc();
        assertNotNull(resampleContext);

        // Set options for resampler input
        av_opt_set_int(resampleContext, "in_channel_layout", codecContext->channel_layout, 0);
        av_opt_set_int(resampleContext, "in_sample_rate", codecContext->sample_rate, 0);
        av_opt_set_sample_fmt(resampleContext, "in_sample_fmt", codecContext->sample_fmt, 0);
        
        // downmix to mono, as stereo is broken for now
        av_opt_set_int(resampleContext, "out_channel_layout",    AV_CH_LAYOUT_MONO, 0);
        av_opt_set_int(resampleContext, "out_sample_rate",       SAMPLE_RATE, 0);
        av_opt_set_sample_fmt(resampleContext, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);

        error = swr_init(resampleContext);
        assertCond(error < 0, "Failed to initialize resampling context!")

        resampledFrame = av_frame_alloc();
        resampledFrame->channel_layout = AV_CH_LAYOUT_MONO;
        resampledFrame->sample_rate = SAMPLE_RATE;
        resampledFrame->format = AV_SAMPLE_FMT_S16;
        assertNotNull(resampledFrame);
        // decode audio
        AVPacket* pkt = av_packet_alloc();
        assertNotNull(pkt);
        while (true) {
            if (!frame) {
                // alloc frame
                frame = av_frame_alloc();
                assertNotNull(frame);
            }
            error = av_read_frame(inputContext, pkt);
            if (error == AVERROR_EOF) {
                break;
            }
            assertCond(error < 0, "Failed to read frame: " + decodeError(error));
            if (pkt->size) {
                decode(pkt);
            }
        }
        // flush decoder
        pkt->data = nullptr;
        pkt->size = 0;

        decode(pkt);

        av_packet_free(&pkt);
    }

    void Player::decode(AVPacket* pkt) {
        int ret = avcodec_send_packet(codecContext, pkt);
        assertCond(ret < 0, "Failed to send packet");
        // read frames from decoder
        while (ret >= 0) {
            ret = avcodec_receive_frame(codecContext, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                return;
            else if (ret < 0)
                throw std::runtime_error("Failed to recive frame!");
            // resample frame
            int error = swr_convert_frame(resampleContext, resampledFrame, frame);
            assertCond(error < 0, "Failed to resample frame: " + decodeError(error));
            int sampleSize = av_get_bytes_per_sample((AVSampleFormat) resampledFrame->format);
            for (int i = 0; i < resampledFrame->nb_samples; i++) {
                for (int ch = 0; ch < resampledFrame->channels; ch++) {
                    for (int byte = 0; byte < sampleSize; byte++) {
                        uint8_t* dataptr = resampledFrame->data[ch] + i * sampleSize + byte; 
                        decodedData.push_back(*dataptr);
                    }
                }
            }
        }
    }

    std::vector<uint8_t>* Player::getBytes() {
        return &decodedData;
    }

    Player::~Player() {
        print("Deconstructor");

        if (frame) {
            av_frame_free(&frame);
        }
        if (resampledFrame) {
            av_frame_free(&resampledFrame);
        }
        if (codecContext) {
            avcodec_free_context(&codecContext);
        }
        if (inputContext) {
            avformat_close_input(&inputContext);
        }
    }
}
