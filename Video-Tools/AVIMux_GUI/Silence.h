#ifndef I_SILENCE
#define I_SILENCE

#include <wtypes.h>
#include "AudioSource_generic.h"
#include <string>

typedef struct
{
	DWORD	dwFormat;
	DWORD	dwChannels;
	DWORD	dwSize;
	DWORD	dwFreq;
	void*	lpData;
	float	fBitrate;
} SILENCE_DESCRIPTOR;

const int SSF_SUCCEEDED	= 0x01;
const int SSF_FAILED		= 0x00;

const int SSD_SUCCEEDED	= 0x01;
const int SSD_FAILED		= 0x00;

class SILENCE: public AUDIOSOURCE
{
	private:
		SILENCE_DESCRIPTOR*		lpSD;
		SILENCE_DESCRIPTOR		sdDesiredFormat;
		int						iCompatibleSource;
		int						iNbrOfDescs;
		int						SetDescriptor(const std::string& lpcName, DWORD dwSize,DWORD dwFormat,DWORD dwChannels,DWORD dwFreq,
			                                  float fBitrate,SILENCE_DESCRIPTOR* lpSD);
	public:
		SILENCE();
		~SILENCE();
		int virtual Init(const char* lpName=NULL);
		int virtual				Read(void*,DWORD,DWORD*,__int64*);
		int virtual				Close(void);
		int virtual				SetFormat(DWORD dwFormat,DWORD dwChannels,DWORD dwFreq,float fBitrate);
};


#endif