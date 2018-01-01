#ifndef K_ENCODER_H_

#define K_ENCODER_H_

#include "getopt.h"
#include "InputParameter.h"

class KEncoder
{
public:
    void init(int argc, char **argv);
    KEncoder(InputParameter *pParameter);

private:
    char* mInputFileName;
    char* mOutputFileName;

    
};

#endif
