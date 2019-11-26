#ifndef FORMAT_OUTPUT_H
#define FORMAT_OUTPUT_H

extern "C" {
#include <libavformat/avformat.h>
}

class FormatOutput {
private:
    AVOutputFormat *avOutputFormat;
    AVCodec *codec;

public:
    FormatOutput();

    AVCodec *getCodec();
};

#endif //FORMAT_OUTPUT_H
