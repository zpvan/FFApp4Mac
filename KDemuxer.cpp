#include "KDemuxer.h"

#include "stdio.h"



KDemuxer::KDemuxer() :
	mInputFileName(NULL),
	mVideoOutputFileName(NULL),
	mAudioOutputFileName(NULL),
	pFileIn(NULL),
    pVideoFileOut(NULL),
    pAudioFileOut(NULL),
    mFmtCxt(NULL),
    mSt(NULL),
    mCodecCtx(NULL)
{
	printf("new KDemuxer: %p\n", this);
}

KDemuxer::~KDemuxer()
{
	printf("delete KDemuxer: %p\n", this);
	// if (!pFileIn)
	// {
	// 	fclose(pFileIn);
	// 	pFileIn = NULL;
	// }
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

	// pFileIn = fopen(mInputFileName, "rb+");
	// if (!pFileIn)
	// {
	// 	return ERROR_CAN_NOT_OPEN_INPUT_FILE;
	// }

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

	av_register_all();

	if (avformat_open_input(&mFmtCxt, mInputFileName, NULL, NULL) < 0)
	{
		return ERROR_FF_AVFORMAT_OPEN_INPUT;
	}

	if (avformat_find_stream_info(mFmtCxt, NULL) < 0)
	{
		return ERROR_FF_FIND_STREAM_INFO;
	}

	int video_index = -1;
	video_index = av_find_best_stream(mFmtCxt, (AVMediaType) AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (video_index >= 0)
	{
		mSt = mFmtCxt->streams[video_index];
		mCodecCtx = mSt->codec;
		printf("vcodec_id: 0x%x, AV_CODEC_ID_H264: 0x%x\n", mCodecCtx->codec_id, AV_CODEC_ID_H264);
		printf("w: %d, h: %d\n", mCodecCtx->width, mCodecCtx->height);
		printf("pix_fmt: %d, AV_PIX_FMT_YUV420P: %d\n", mCodecCtx->pix_fmt, AV_PIX_FMT_YUV420P);
	}

	int audio_index = -1;
	audio_index = av_find_best_stream(mFmtCxt, (AVMediaType) AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (audio_index >= 0)
	{
		mSt = mFmtCxt->streams[audio_index];
		mCodecCtx = mSt->codec;
		printf("acodec_id: 0x%x\n", mCodecCtx->codec_id);
	}
	av_dump_format(mFmtCxt, 0, mInputFileName, 0);

	return NO_ERROR;
}