#include "client/Packet.h"

Packet::Packet() :
        pkt(av_packet_alloc()) {
}

AVPacket *Packet::get() {
    return pkt;
}

void Packet::write(FILE *outfile) {
    //esto es lento porque es escritura en disco
    fwrite(pkt->data, 1, pkt->size, outfile);
    av_packet_unref(pkt);
}

Packet::~Packet() {
    av_packet_free(&pkt);
}
