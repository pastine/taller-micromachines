extern "C" {
#include <libavformat/avformat.h>
}
#include "client/FormatOutput.h"
#include <string>

FormatOutput::FormatOutput() {
    av_register_all();
    std::string f = "micromachines.mp4";
    this->avOutputFormat = av_guess_format(NULL, f.c_str(), NULL);
    if (!this->avOutputFormat) {
        this->avOutputFormat = av_guess_format("mpeg", NULL, NULL);
    }
    this->codec = avcodec_find_encoder(this->avOutputFormat->video_codec);
}

AVCodec *FormatOutput::getCodec() {
    return this->codec;
}