#ifndef f_VIDEOSOURCE_I
#define f_VIDEOSOURCE_I

#include <Windows.h>
#include "VideoSource_List.h"

typedef struct
{
	DWORD*				lpdwFiles;
	VIDEOSOURCE*		videosource;

	__int64				iSize;
} VIDEO_STREAM_INFO;




#endif