#include "ZoomVideoSDKRawDataPipeDelegate.h"
#include "helpers/zoom_video_sdk_user_helper_interface.h"
//getRawShare
//getRawVideo


using namespace ZOOMVIDEOSDK;
std::vector<ZoomVideoSDKRawDataPipeDelegate*> ZoomVideoSDKRawDataPipeDelegate::list_;
int ZoomVideoSDKRawDataPipeDelegate::instance_count = 0;

ZoomVideoSDKRawDataPipeDelegate::ZoomVideoSDKRawDataPipeDelegate(IZoomVideoSDKUser* user)
{
	instance_id_ = instance_count++;
	user_ = user;
	user_->GetVideoPipe()->subscribe(ZoomVideoSDKResolution_360P, this);
	list_.push_back(this);
}

ZoomVideoSDKRawDataPipeDelegate::ZoomVideoSDKRawDataPipeDelegate(IZoomVideoSDKUser* user, bool isShareScreen)
{
	instance_id_ = instance_count++;
	user_ = user;
	user_->GetSharePipe()->subscribe(ZoomVideoSDKResolution_360P, this);
	list_.push_back(this);
}

ZoomVideoSDKRawDataPipeDelegate::~ZoomVideoSDKRawDataPipeDelegate()
{
	// finish ffmpeg encoding
	log(L"********** [%d] Finishing encoding, user: %s, %dx%d.\n", instance_id_, user_->getUserName(), in_width, in_height);


	user_->GetVideoPipe()->unSubscribe(this);
	log(L"********** [%d] UnSubscribe, user: %s.\n", instance_id_, user_->getUserName());
	instance_count--;
	user_ = nullptr;
}


ZoomVideoSDKRawDataPipeDelegate* ZoomVideoSDKRawDataPipeDelegate::find_instance(IZoomVideoSDKUser* user)
{
	for (auto iter = list_.begin(); iter != list_.end(); iter++)
	{
		ZoomVideoSDKRawDataPipeDelegate* item = *iter;
		if (item->user_ == user)
		{
			return item;
		}
	}
	return nullptr;
}

void ZoomVideoSDKRawDataPipeDelegate::stop_encoding_for(IZoomVideoSDKUser* user)
{
	ZoomVideoSDKRawDataPipeDelegate* encoder = ZoomVideoSDKRawDataPipeDelegate::find_instance(user);
	if (encoder)
	{
		encoder->~ZoomVideoSDKRawDataPipeDelegate();
	}
}


void ZoomVideoSDKRawDataPipeDelegate::stop_encoding_for(IZoomVideoSDKUser* user, bool isShareScreen)
{
	ZoomVideoSDKRawDataPipeDelegate* encoder = ZoomVideoSDKRawDataPipeDelegate::find_instance(user);
	if (encoder)
	{
		encoder->~ZoomVideoSDKRawDataPipeDelegate();
	}
}
int j = 0;

void ZoomVideoSDKRawDataPipeDelegate::onRawDataFrameReceived(YUVRawDataI420* data)
{
	//getRawVideo
	const zchar_t* userName = user_->getUserName();
	const zchar_t* userID = user_->getUserID();
	const int width = data->GetStreamWidth();
	const int height = data->GetStreamHeight();
	const int bufLen = data->GetBufferLen();
	const int rotation = data->GetRotation();
	const int sourceID = data->GetSourceID();


}

void ZoomVideoSDKRawDataPipeDelegate::onRawDataStatusChanged(RawDataStatus status)
{
	log(L"********** [%d] onRawDataStatusChanged, user: %s, %d.\n", instance_id_, user_->getUserName(), status);
	if (status == RawData_On)
	{
	}
	else
	{
	}
}

void ZoomVideoSDKRawDataPipeDelegate::err_msg(int code)
{
	char errbuf[100];
	
	printf("%s\n", errbuf);
}

void ZoomVideoSDKRawDataPipeDelegate::log(const wchar_t* format, ...)
{

}