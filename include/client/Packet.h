#ifndef PACKET_H
#define PACKET_H

extern "C" {
#include <libavcodec/avcodec.h>
}

class Packet {
private:
    AVPacket* pkt;

public:
    Packet();
    ~Packet();

    AVPacket *get();

    void write(FILE *outfile);
};


#endif //PACKET_H
