#ifndef K_ENCODER_H_

#define K_ENCODER_H_

#include "getopt.h"
#include "InputParameter.h"
#include "KErrors.h"

class KEncoder
{
public:
    KEncoder();
    KErrors configure(InputParameter *pParameter);

private:
    char* mInputFileName;
    char* mOutputFileName;
    int mBitRate;
    int mFrameRate;
    int mFrameCount;
    int mWidth;
    int mHeight;
};

#endif
