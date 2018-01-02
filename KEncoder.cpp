#include "KEncoder.h"

#include "stdio.h"

KEncoder::KEncoder() : 
    mInputFileName(NULL),
    mOutputFileName(NULL),
    mBitRate(0),
    mFrameRate(0),
    mFrameCount(0),
    mWidth(0),
    mHeight(0),
    pFileIn(NULL),
    pFileOut(NULL)
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

    pFileIn = fopen(mInputFileName, "rb");
    if (!pFileIn)
    {
        return ERROR_CAN_NOT_OPEN_INPUT_FILE;
    }

    pFileOut = fopen(mOutputFileName, "wb");
    if (!pFileOut)
    {
        return ERROR_CAN_NOT_OPEN_OUTPUT_FILE;
    }

    return NO_ERROR;
}
