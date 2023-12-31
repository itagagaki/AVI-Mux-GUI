#ifndef I_VIDEOSOOURCE_MATROSKA
#define I_VIDEOSOOURCE_MATROSKA

#include <wtypes.h>
#include "VideoSource_generic.h"
#include "../Matroska.h"
#include <string>

typedef struct
{
	MATROSKA*	m;
	int			iStream;
	__int64		size;
} VIDEOSOURCEFROMMATROSKA_DATA;


class VIDEOSOURCEFROMMATROSKA: public VIDEOSOURCE
{
	private:
		VIDEOSOURCEFROMMATROSKA_DATA	info;
		AVIStreamHeader					avistreamheader;
		READ_INFO						curr_lace;
		bool							bDelace;
		int								iPos;
		int								iBytePosInLace;
		__int64							iNextTimecode;
	protected:
		__int64		virtual GetUnstretchedDuration();
		__int64		virtual GetExactSize();
		MATROSKA* GetSource();
		int GetSourceStream();
	public:
		VIDEOSOURCEFROMMATROSKA();
		VIDEOSOURCEFROMMATROSKA(MATROSKA* matroska, int iStream = -1);
		void		virtual *GetFormat(void);
		AVIStreamHeader virtual *GetAVIStreamHeader(void);
		int			virtual GetFrame(void* lpDest,DWORD* lpdwSize,__int64* lpiTimecode = nullptr,
										ADVANCEDREAD_INFO* lpAARI = nullptr);
		__int64	virtual	GetNanoSecPerFrame(void);
		int		virtual GetNbrOfFrames(DWORD dwKind=FT_ALL);
		int		virtual GetResolution(int* lpdwWidth,int* lpdwHeight);
		void	virtual GetOutputResolution(RESOLUTION* r);
		int		virtual Enable(int bEnabled);
		bool	virtual IsKeyFrame(DWORD dwNbr = CN_CURRENT_CHUNK);
		bool	virtual IsEndOfStream();
		char	virtual* GetCodecID();
		bool	virtual IsOpen();
		int		virtual Open(MATROSKA* matroska, int iStream = -1);
		void	virtual ReInit();
		int		virtual Seek(__int64 iTime);
		int		virtual GetFormatSize(void);
		void	virtual GetCropping(RECT* r);
		DWORD	virtual GetFourCC();
		virtual ~VIDEOSOURCEFROMMATROSKA();
		int		virtual GetStrippableHeaderBytes(void* pBuffer, int max);
		int		virtual	GetName(char* lpDest);
		int		virtual GetLanguageCode(std::string& result);

};

#endif