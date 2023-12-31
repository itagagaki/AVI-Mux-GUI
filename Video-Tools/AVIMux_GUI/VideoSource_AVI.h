#ifndef I_VIDEOSOURCE_AVI
#define I_VIDEOSOURCE_AVI

#include <wtypes.h>
#include "VideoSource_generic.h"

typedef struct
{
	AVIFILEEX**	avifile;
	int			iCount;
	int			iActiveFile;
} VIDEOSOURCEFROMAVI_DATA;

class VIDEOSOURCEFROMAVI: public VIDEOSOURCE
{
	private:
		VIDEOSOURCEFROMAVI_DATA  info;
	protected:
		__int64		virtual GetUnstretchedDuration();
		__int64		virtual GetExactSize(void);
	public:
		VIDEOSOURCEFROMAVI();
		virtual ~VIDEOSOURCEFROMAVI();
		void		virtual* GetFormat();
		int			virtual	Open(AVIFILEEX* avifile);
		int			virtual GetFrame(void* lpDest,DWORD* lpdwSize,__int64* lpiTimecode = nullptr, ADVANCEDREAD_INFO* lpAARI = nullptr);
		int			virtual GetName(char *lpDest);
		int			virtual GetResolution(int* lpiWidth,int* lpiHeight);
		DWORD		virtual GetPos();
		int			virtual GetNbrOfFrames(DWORD dwKind=FT_ALL);
		AVIStreamHeader virtual *GetAVIStreamHeader(void);
		__int64		virtual	GetNanoSecPerFrame(void);
		void		virtual GetOutputResolution(RESOLUTION* r);
		void		virtual ReInit();
		int			virtual Seek(__int64 iTime);
		bool		virtual IsEndOfStream();
		bool		virtual IsKeyFrame(DWORD dwNbr = CN_CURRENT_CHUNK);
		bool		virtual IsCFR(void);
		int			virtual GetFormatSize(void);
		void		virtual GetCropping(RECT* r);
		DWORD		virtual GetFourCC();

};


#endif