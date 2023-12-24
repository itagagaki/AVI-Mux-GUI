#ifndef I_VIDEOSOURCE_LIST
#define I_VIDEOSOURCE_LIST

#include <wtypes.h>
#include "VideoSource_generic.h"

typedef struct
{
	VIDEOSOURCE**	videosources;
	VIDEOSOURCE*	curr_source;
	int				iCount;
	int				iActiveSource;
} VIDEOSOURCELIST_INFO;

class VIDEOSOURCELIST: public VIDEOSOURCE
{
	private:
		VIDEOSOURCELIST_INFO	info;
	protected:
		__int64		virtual GetUnstretchedDuration();
	public:
		VIDEOSOURCELIST(void);
		~VIDEOSOURCELIST(void);
		int					Append(VIDEOSOURCE* pNext);
		DWORD		virtual Close(bool bCloseSource);
		int			virtual Enable(int bEnabled);
		int			virtual GetFrame(void* lpDest,DWORD* lpdwSize,__int64* lpiTimecode = nullptr, ADVANCEDREAD_INFO* lpAARI = nullptr);
		int			virtual GetLatestReference(int* lpiCount = nullptr, __int64* lpiRef1 = nullptr, __int64* lpiRef2 = nullptr);
		int			virtual GetNbrOfFrames(DWORD dwKind=FT_ALL);
		void		virtual *GetFormat(void);
		int			virtual GetResolution(int* lpdwWidth,int* lpdwHeight);
/*		void		virtual GetOutputResolution(RESOLUTION* r);
*/
		AVIStreamHeader virtual *GetAVIStreamHeader(void);
		__int64		virtual	GetNanoSecPerFrame(void);
		char		virtual* GetCodecID();
		bool		virtual IsAVIOutputPossible();
		void		virtual AllowAVIOutput(bool bAllow);
		bool		virtual IsEndOfStream();
		bool		virtual IsKeyFrame(DWORD dwNbr = CN_CURRENT_CHUNK);
		__int64		virtual GetSize(void);
		void		virtual ReInit();
		int			virtual Seek(__int64 iTime);
		int			virtual GetFormatSize(void);
		DWORD		virtual GetFourCC(void);
//		void		virtual GetCropping(RECT* r);
		int			virtual GetStrippableHeaderBytes(void* pBuffer, int max);
};

#endif