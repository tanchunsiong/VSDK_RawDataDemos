#pragma once
//getRawShare
//getRawVideo

#define __STDC_CONSTANT_MACROS
extern "C"
{
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
#include "libavutil/pixfmt.h"
#include "libavutil/opt.h"
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libavcodec/avcodec.h"
}

#include <vector>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std::chrono;

#include "helpers/zoom_video_sdk_user_helper_interface.h"
#include <vector>

using namespace ZOOMVIDEOSDK;

class ZoomVideoSDKRawDataPipeDelegate :
	public  IZoomVideoSDKRawDataPipeDelegate
{
	virtual void onRawDataFrameReceived(YUVRawDataI420* data);
	virtual void onRawDataStatusChanged(RawDataStatus status);
	static ZoomVideoSDKRawDataPipeDelegate* find_instance(IZoomVideoSDKUser* user);


	int instance_id_;
	static int instance_count;
	static std::vector<ZoomVideoSDKRawDataPipeDelegate*> list_;
	IZoomVideoSDKUser* user_;



	int ffmpeg_start(const char* userName, const char* userID, int sourceID);
	int ffmpeg_flush(AVFormatContext* fmt_ctx, unsigned int stream_index);
	int ffmpeg_stop();
	int ffmpeg_filter(uint8_t* Y, uint8_t* U, uint8_t* V);
	int ffmpeg_encode();
	int ffmpeg_filter_init();

	// ffmpeg filter
	AVFrame* frame_in;
	AVFrame* frame_out;
	unsigned char* frame_buffer_in;
	unsigned char* frame_buffer_out;
	int in_width = 0;
	int in_height = 0;
	int out_width = 1280;
	int out_height = 720;

	AVFilterContext* buffersink_ctx;
	AVFilterContext* buffersrc_ctx;
	AVFilterGraph* filter_graph;
	//static int video_stream_index = -1;
	const AVFilter* buffersrc;
	const AVFilter* buffersink;
	AVFilterInOut* outputs;
	AVFilterInOut* inputs;

	

	

	//Output YUV
	FILE* fp_yuv;
	int isOutputYUV = 0;

	// ffmpeg encoding
	AVFormatContext* pFormatCtx;
	const AVOutputFormat* fmt;
	AVStream* video_st;
	AVCodecContext* pCodecCtx;
	const AVCodec* pCodec;
	AVPacket pkt;
	//uint8_t* picture_buf;
	AVFrame* pFrame;
	int picture_size;
	int y_size;
	int framecnt = 0;
	int is_ffmpeg_encoding_on = 0;
	int current_sourceID = -1;
	// struct _timeb start_tstruct;
	steady_clock::time_point start_time;

	//Output video file name.
	char fn_out[120];


public:
	//this is for preview only, doesn't need user
	ZoomVideoSDKRawDataPipeDelegate();
	ZoomVideoSDKRawDataPipeDelegate(IZoomVideoSDKUser* user);
	~ZoomVideoSDKRawDataPipeDelegate();


	
	 void start_encoding_for(IZoomVideoSDKUser* user);
	 void stop_encoding_for(IZoomVideoSDKUser* user);
	 void log(const wchar_t* format, ...);
	 void err_msg(int code);
};




