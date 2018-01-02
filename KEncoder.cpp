#include "KEncoder.h"

#include "stdio.h"

extern "C"
{
    #include "libavutil/opt.h"
    #include "libavutil/imgutils.h"
}

KEncoder::KEncoder() : 
    mInputFileName(NULL),
    mOutputFileName(NULL),
    mBitRate(0),
    mFrameRate(0),
    mFrameCount(0),
    mWidth(0),
    mHeight(0),
    pFileIn(NULL),
    pFileOut(NULL),
    mCodec(NULL),
    mCodecCtx(NULL),
    mFrame(NULL),
    mPacket(NULL)
{
    printf("new KEncoder %p\n", this);
}

KEncoder::~KEncoder()
{
    printf("delete KEncoder %p\n", this);
    if (!pFileIn)
    {
        fclose(pFileIn);
        pFileIn = NULL;
    }
    if (!pFileOut)
    {
        fclose(pFileOut);
        pFileOut = NULL;
    }
}

KErrors KEncoder::configure(InputParameter *pParameter)
{
    if (!pParameter)
    {
        return ERROR_NO_INPUT_PARAMETER;
    }
    mInputFileName = pParameter->mInputFileName;
    mOutputFileName = pParameter->mOutputFileName;
    mBitRate = pParameter->mBitRate;
    mFrameRate = pParameter->mFrameRate;
    mFrameCount = pParameter->mFrameCount;
    mWidth = pParameter->mWidth;
    mHeight = pParameter->mHeight;

    pFileIn = fopen(mInputFileName, "rb+");
    if (!pFileIn)
    {
        return ERROR_CAN_NOT_OPEN_INPUT_FILE;
    }

    pFileOut = fopen(mOutputFileName, "wb+");
    if (!pFileOut)
    {
        return ERROR_CAN_NOT_OPEN_OUTPUT_FILE;
    }

    // 1
    avcodec_register_all();

    // 2
    mCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!mCodec)
    {
        return ERROR_FF_FIND_ENCODER;
    }

    // 3
    mCodecCtx = avcodec_alloc_context3(mCodec);
    if (!mCodecCtx)
    {
        return ERROR_FF_ALLOC_AVCODECCONTEXT;
    }

    // 4
    mCodecCtx->width = mWidth;
    mCodecCtx->height = mHeight;
    mCodecCtx->bit_rate = mBitRate;
    AVRational r = {1, mFrameRate};
    mCodecCtx->time_base = r;

    // 5
    mCodecCtx->gop_size = 12;
    mCodecCtx->max_b_frames = 1;
    mCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    av_opt_set(mCodecCtx->priv_data, "preset", "slow", 0);

    // 6
    mFrame = av_frame_alloc();
    if (!mFrame)
    {
        return ERROR_FF_ALLOC_AVFRAME;
    }
    mFrame->width = mCodecCtx->width;
    mFrame->height = mCodecCtx->height;
    mFrame->format = mCodecCtx->pix_fmt;

    // 7
    int res = 0;
    res = av_image_alloc(mFrame->data, mFrame->linesize, mFrame->width, mFrame->height, (AVPixelFormat) mFrame->format, 32);
    if (res < 0)
    {
        return ERROR_FF_ALLOC_IMAGE;
    }

    printf("configure[w: %d, h: %d, br: %d, fr: %d, fc: %d]\n", mWidth, mHeight, mBitRate, mFrameRate, mFrameCount);
    return NO_ERROR;
}

KErrors KEncoder::start()
{
    

    return NO_ERROR;
}
