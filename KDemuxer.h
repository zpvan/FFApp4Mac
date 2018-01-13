#ifndef K_DEMUXER_H_

#define K_DEMUXER_H_

#include "KErrors.h"
#include "InputParameter.h"

extern "C"
{
	#include "libavformat/avformat.h"
}

class KDemuxer
{
public:
	KDemuxer();
	~KDemuxer();
	KErrors configure(InputParameter *pParameter);
	KErrors start();

private:
	char* mInputFileName;
	char* mVideoOutputFileName;
	char* mAudioOutputFileName;

	FILE *pFileIn;
    FILE *pVideoFileOut;
    FILE *pAudioFileOut;

    AVFormatContext *mFmtCxt;
    AVStream *mSt;
    AVCodecContext *mCodecCtx;
    AVCodec *mCodec;
    AVPacket packet;

    int video_index;
    int audio_index;
};

#endif