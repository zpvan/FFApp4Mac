#ifndef INPUT_PARAMETER_H_

#define INPUT_PARAMETER_H_

#include "stdio.h"

enum 
{
    FUNCTION = 'func',
    BITRATE = 'brat',
    FRAMERATE = 'frat',
    FRAMECOUNT = 'fcot',
    VIDEO_RESOLUTION = 'vren',
    INPUT_FILE = 'i',
    OUTPUT_FILE = 'o',
};

class InputParameter
{
public:
	char *mInputFileName;
	char *mOutputFileName;

	int mBitRate;
	int mFrameRate;
	int mFrameCount;
	int mWidth;
	int mHeight;
};

#endif