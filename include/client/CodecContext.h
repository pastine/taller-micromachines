#ifndef CODEC_CONTEXT_H
#define CODEC_CONTEXT_H

extern "C" {
#include <libavcodec/avcodec.h>
}

class CodecContext {
private:
    AVCodecContext* codecContext;

public:
    explicit CodecContext(AVCodec *codec);

    ~CodecContext();

    AVCodecContext *get();

    int getHeight();

    int getWidth();

    int getPixFmt();
};


#endif //CODEC_CONTEXT_H
