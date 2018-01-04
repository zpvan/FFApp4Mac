#include "KEncoder.h"

#include "stdio.h"

extern "C"
{
    #include "libavutil/opt.h"
    #include "libavutil/imgutils.h"
    #include "libavutil/samplefmt.h"
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
    mFrame(NULL)
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

    // 1 initialization
    avcodec_register_all();

    // 2 find specified codec encoder
    mCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!mCodec)
    {
        return ERROR_FF_FIND_ENCODER;
    }

    // 3 alloc context for the encoder
    mCodecCtx = avcodec_alloc_context3(mCodec);
    if (!mCodecCtx)
    {
        return ERROR_FF_ALLOC_AVCODECCONTEXT;
    }

    // 4 configure parameter from user
    mCodecCtx->width = mWidth;
    mCodecCtx->height = mHeight;
    mCodecCtx->bit_rate = mBitRate;
    AVRational r = {1, mFrameRate};
    mCodecCtx->time_base = r;

    // 5 configure specified parameter
    mCodecCtx->gop_size = 12;
    mCodecCtx->max_b_frames = 1;
    mCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    av_opt_set(mCodecCtx->priv_data, "preset", "slow", 0);

    // 6 open the encoder
    if (avcodec_open2(mCodecCtx, mCodec, NULL) < 0)
    {
        return ERROR_FF_OPEN_AVCODEC;
    }

    // 7 alloc avframe pointer
    mFrame = av_frame_alloc();
    if (!mFrame)
    {
        return ERROR_FF_ALLOC_AVFRAME;
    }
    mFrame->width = mCodecCtx->width;
    mFrame->height = mCodecCtx->height;
    mFrame->format = mCodecCtx->pix_fmt;

    // 8 alloc memory for the avframe
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
    int got_pkt = 0;
    int idx = 0;
    for (idx = 0; idx < mFrameCount; ++idx)
    {
        // 9 init avpacket
        av_init_packet(&mPacket);
        mPacket.data = NULL;
        mPacket.size = 0;

        // 10 read yuv from file to avframe
        readYUV420PToAVFrame();

        // 11 
        mFrame->pts = idx;

        // 12
        
        if (avcodec_encode_video2(mCodecCtx, &mPacket, mFrame, &got_pkt) < 0)
        {
            return ERROR_FF_ENCODE_VIDEO;
        }
        /*
        if (avcodec_send_frame(mCodecCtx, mFrame) < 0)
        {
            return ERROR_FF_ENCODE_VIDEO;
        }
        got_pkt = avcodec_receive_packet(mCodecCtx, &mPacket);
        */
        // 13
        if (got_pkt)
        {
            printf("encode number: %d\n", idx);
            fwrite(mPacket.data, 1, mPacket.size, pFileOut);
            av_packet_unref(&mPacket);
        }
    }

    do
    {
        if (avcodec_encode_video2(mCodecCtx, &mPacket, NULL, &got_pkt) < 0)
        {
            return ERROR_FF_ENCODE_VIDEO;
        }
        /*
        if (avcodec_send_frame(mCodecCtx, mFrame) < 0)
        {
            return ERROR_FF_ENCODE_VIDEO;
        }
        got_pkt = avcodec_receive_packet(mCodecCtx, &mPacket);
        */
        if (got_pkt)
        {
            printf("encode number: %d\n", idx++);
            fwrite(mPacket.data, 1, mPacket.size, pFileOut);
            av_packet_unref(&mPacket);
        }
    } while (got_pkt);

    return NO_ERROR;
}

void KEncoder::readYUV420PToAVFrame()
{
    // 0->Y
    // 1->U
    // 2->V
    for (int color = 0; color < 3; ++color)
    {
        int color_width = ((color == 0) ? mWidth : (mWidth / 2));
        int color_height = ((color == 0) ? mHeight : (mHeight / 2));
        int color_stride = mFrame->linesize[color];

        if (color_width == color_stride)
        {
            fread(mFrame->data[color], color_width * color_height, 1, pFileIn);
        } 
        else 
        {
            for (int row = 0; row < color_height; ++row)
            {
                fread(mFrame->data[color] + row * color_stride, color_width, 1, pFileIn);
            }
        }
    }
}