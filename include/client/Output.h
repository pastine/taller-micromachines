#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H

#include "Frame.h"
#include "Packet.h"
#include "FormatOutput.h"
#include "CodecContext.h"

/**
 * Clase que encapsula lógica la salida de video
 * Se recomienda modularizar aun más esta clase, reforzando RAII
 */
class Output {
private:
    FormatOutput format;
    CodecContext codecContext;
    FILE *outputFile;
    Frame frame;
    Packet pkt;

public:
    // Ctor
    Output();

    // Dtor
    ~Output();

    // Escribe un frame a disco. Utiliza `swsContext` para convertir
    // de RGB24 a YUV420p
    void writeFrame(const char *data, SwsContext *swsContext);

    // Cierra el stream de video
    void close();
};

#endif
