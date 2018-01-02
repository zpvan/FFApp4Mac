#ifndef K_ENCODER_H_

#define K_ENCODER_H_

#include "getopt.h"
#include "InputParameter.h"
#include "KErrors.h"
#include "stdint.h"

extern "C"
{
    #include "libavformat/avformat.h"
}

class KEncoder
{
public:
    KEncoder();
    ~KEncoder();
    KErrors configure(InputParameter *pParameter);
    KErrors start();

private:
    char* mInputFileName;
    char* mOutputFileName;
    int mBitRate;
    int mFrameRate;
    int mFrameCount;
    int mWidth;
    int mHeight;

    FILE *pFileIn;
    FILE *pFileOut;

    AVCodec *mCodec;
    AVCodecContext *mCodecCtx;
    AVFrame *mFrame;
    AVPacket *mPacket;
};

#endif
