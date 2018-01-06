#include "KDemuxer.h"

#include "stdio.h"

KDemuxer::KDemuxer() :
	mInputFileName(NULL),
	mVideoOutputFileName(NULL),
	mAudioOutputFileName(NULL),
	pFileIn(NULL),
    pVideoFileOut(NULL),
    pAudioFileOut(NULL)
{
	printf("new KDemuxer: %p\n", this);
}

KDemuxer::~KDemuxer()
{
	printf("delete KDemuxer: %p\n", this);
	if (!pFileIn)
	{
		fclose(pFileIn);
		pFileIn = NULL;
	}
	if (!pVideoFileOut)
	{
		fclose(pVideoFileOut);
		pVideoFileOut = NULL;
	}
	if (!pAudioFileOut)
	{
		fclose(pAudioFileOut);
		pAudioFileOut = NULL;
	}
}

KErrors KDemuxer::configure(InputParameter *pParameter)
{
	mInputFileName = pParameter->mInputFileName;
	mVideoOutputFileName = pParameter->mVideoOutputFileName;
	mAudioOutputFileName = pParameter->mAudioOutputFileName;

	pFileIn = fopen(mInputFileName, "rb+");
	if (!pFileIn)
	{
		return ERROR_CAN_NOT_OPEN_INPUT_FILE;
	}

	pVideoFileOut = fopen(mVideoOutputFileName, "wb+");
	if (!pVideoFileOut)
	{
		return ERROR_CAN_NOT_OPEN_OUTPUT_FILE;
	}

	pAudioFileOut = fopen(mAudioOutputFileName, "wb+");
	if (!pAudioFileOut)
	{
		return ERROR_CAN_NOT_OPEN_OUTPUT_FILE;
	}
}