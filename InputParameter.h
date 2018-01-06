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
    VIDEO_OUTPUT_FILE = 'vofn',
    AUDIO_OUTPUT_FILE = 'aofn',
};

class InputParameter
{
public:
	char *mInputFileName;
	char *mOutputFileName;
	char *mVideoOutputFileName;
	char *mAudioOutputFileName;

	int mBitRate;
	int mFrameRate;
	int mFrameCount;
	int mWidth;
	int mHeight;
};

#endif