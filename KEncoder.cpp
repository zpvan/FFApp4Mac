#include "KEncoder.h"

#include "stdio.h"

KEncoder::KEncoder() : 
    mInputFileName(NULL),
    mOutputFileName(NULL),
    mBitRate(0),
    mFrameRate(0),
    mFrameCount(0),
    mWidth(0),
    mHeight(0)
{

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

    return NO_ERROR;
}
