#ifndef I_MATROSKA
#define I_MATROSKA

#include <wtypes.h>
#include "Matroska_IDs.h"
#include "Matroska_Segment.h"
#include "Matroska_Writing.h"
#include "Queue.h"
#include "Buffers.h"
#include "Tags.h"
#include "Chapters.h"
#include "IBitStream.h"
#include "ITitleSet.h"
#include "Compression.h"
#include <vector>

const int		MMODE_READ	= 1;
const int		MMODE_WRITE = 2;
const int		MMODE_DUMMY = 4;
const int		MMODE_SEGINFO_ONLY = 8;

const int       MOPEN_OK	= 0x00;
const int		MOPEN_ERR	= 0x01;


/* note: these 2 must be handled by the app only, those
   are nothing but #defines here
*/

const int LINKTYPE_MEDIUM = 0x00;
const int LINKTYPE_HARD = 0x01;

char* MKV_LINKTYPE_NAMES[];

static const char* MSTRT_names[] = { "", "video", "audio", "complex", "", "", "", "", "",
									 "", "", "", "", "", "", "", "logo", "subs", "button", "",
									 "", "", "", "", "", "", "", "", "", "", "", "", "control"
									};



static const char* MDISPU_names[] = { "pixel", "centimeters", "inches" };

typedef struct
{
	__int64				qwLength;	// Nanoseconds
	int					mode;		// reading or writing
	int					iActiveSegment;
	int					iActiveTrack;
	__int64				iMinTimecode; // filter blocks of timecode < this
	int					bShiftFirstClusterTimecode2Zero;
} MATROSKA_INFO;


class READ_INFO
{
public:
	READ_INFO();

	int				iTrack; // index
	__int64			qwTimecode;
	__int64			qwDuration;
	int				iFlags;
	int				iLength;
	int				reference_types;
	std::vector<__int64>	references;
	std::vector<int>		frame_sizes;
	CBuffer*		pData;
};

const int CUE_VIDEO = 1;
const int CUE_AUDIO = 2;
const int CUE_SUBS  = 4;

typedef struct
{
	int		iVideo;
	int		iAudio;
	int		iSubtitles;
} DURATION_DEFAULTS;

typedef struct
{
		int						iAVImode;
		bool					bDeb0rkReferences;

		bool					bClusterIndex;
		__int64					bRandomizeElementOrder;
		
		__int64					iBlocksInCluster;

		bool					bClusterPosition;
		bool					bPrevClusterSize;
		bool					bCueBlockNumber;

		__int64					bWriteCues; // 1 video, 2 audio, 4 subs
		bool					bWriteFlagDefault;
		bool					bWriteFlagLacing;
		bool					bWriteFlagEnabled;
		bool					bWriteFlagForced;

		__int64					bDisplayWidth_Height;
		float					fSetDuration;
		__int64					i1stElementInFile;
		__int64					iAccumulatedOverhead;
		__int64					iClusterOverhead;
		__int64					iClusterCount;
		__int64					iCuePointsWritten;
		__int64					iCuePointsCreated;

		__int64*				iLastCuePointTimecode;
		__int64					iMaxClusterSize;
		__int64					iMaxClusterTime;
		__int64					iLimit1stCluster;

		__int64					min_cue_point_interval;
		__int64					max_cue_point_interval;
		
		__int64					iPosInSegment;
		__int64                 iPosOfReservedSpace;
		__int64					iSizeOfReservedSpace;
		__int64					iSeekheadPosInFile;
		__int64					iSeekheadSize;
		__int64					iSegInfoPosInFile;
		__int64					iSegPosInFile;
		__int64					iSegClientDataBegin;

		__int64					iTimecodeScale;
		__int64					iTracksPosInFile;
		__int64					iLatestTimecode;
		__int64					iEarliestTimecode;
		__int64					iTracksCopies;
		__int64					iTargetSeekhead;
		__int64					iLaceStyle;
		__int64					iCueAutosize;
		double					iCueTargetSizeRatio;

		__int64					matroska_version;

		DURATION_DEFAULTS		duration_default;


		bool					bUIDs[4];
		char					cUIDs[4][16];

		std::vector<CUE_POINT>	cues;
} WRITE_STATE;

const int LACESTYLE_XIPH		= 0x01;
const int LACESTYLE_EBML		= 0x02;
const int LACESTYLE_AUTO		= 0x03;
const int LACESTYLE_FIXED		= 0x04; // not allowed as parameter for SetLaceStyle!

// first cluster timecode:
const int SFCTZ_AUTO = 0x00;		// 0 <=> Segment.PrevID exists
const int SFCTZ_ENABLE = 0x01;		// 0
const int SFCTZ_DISABLE = 0x02;		// unmodified

// get track count
const int GTC_ALL = 0x00;
const int GTC_VIDEO = MSTRT_VIDEO;
const int GTC_AUDIO = MSTRT_AUDIO;
const int GTC_SUBTITLE = MSTRT_SUBT;

const int SAT_ALL = 0x00;
const int SAT_VIDEO = MSTRT_VIDEO;
const int SAT_AUDIO = MSTRT_AUDIO;
const int SAT_SUBTITLE = MSTRT_SUBT;

const int ATTACHMENTINDEX_INVALID = -1;

typedef struct 
{
	int	iCount;
	int iFrameCount;
	int iTotalHdrSize;
} LACE_STATS;

typedef struct
{
	int iCount;
	int iOverhead;
} CLUSTER_STATS;

typedef struct
{
	int			iCount;
	ADDBLOCK*	block;
	int*		used;
	int*		block_of_stream;
} WRITE_BUFFER;

char* matroska_GetCompileTimestamp();

const int UIDTYPE_SEGMENTUID = 0x00;
const int UIDTYPE_PREVUID    = 0x01;
const int UIDTYPE_NEXTUID    = 0x02;
const int UIDTYPE_SEGMENTFAMILY = 0x03;
char* MKV_UID_NAMES[];

/* to be used with a (future) MATROSKA::Enable() functioon */
#define MF_WRITE_PREV_CLUSTER_SIZE  0x00000001
#define MF_WRITE_CLUSTER_POSITION   0x00000002

#define MF_WRITE_CLUSTER_INDEX      0x00000004
#define MF_WRITE_DISPLAY_WH         0x00000008
#define MF_WRITE_CUE_BLOCK_NUMBER   0x00000010
#define MF_WRITE_CUES               0x00000020
#define MF_CUE_AUTO_SIZE      0x00000040
#define MF_WRITE_FLAG_DEFAULT 0x00000080
#define MF_WRITE_FLAG_ENABLED 0x00000100
#define MF_WRITE_FLAG_LACED   0x00000200
#define MF_WRITE_FLAG_FORCED  0x00000400
#define MF_SHIFT_FIRST_CLUSTER_TIMECODE 0x00000800
#define MF_WRITE_RANDOM_ELEMENT_ORDER 0x00001000

#define MFA_ENABLE 0x17
#define MFA_DISABLE 0x23
#define MFA_RETRIEVE_ONLY 0x41

class MATROSKA : public CHasTitles
{
	private:
	// access
		bool				CanRead();
		bool				CanWrite();
	// read and parse EBML header
		bool				ParseEBMLHeader(EBML_INFO& ebml_info, EBMLElement* parent);

	// reading
		EBMLELEMENTLIST*	e_EBML;
		EBMLELEMENTLIST*	e_Segments;

		EBML_Matroska*		e_Main;
		SEGMENT_INFO**		SegmentInfo;
		SEGMENT_INFO*		pActiveSegInfo;
		TRACK_INFO*			pActiveTrackInfo;
		QUEUE**				queue;
		int*				iStreams2Queue;
	
		STREAM*				stream;
		bool				bAllowObfuscatedFiles;

		MATROSKA_INFO*		info;
		int					iSingleStream;
		int					iDebugLevel;
		__int64				iEnqueueCount;
		int					iMaxBlockGapFactor;
		
		int					StreamListLen(int*	piList);
	// writing
		int							iTrackCount;
		EBMLMSegmentInfo_Writer*	e_SegInfo;
		TRACK_DESCRIPTOR**			tracks;
		EBMLHeader_Writer*			e_Header;
		EBMLElement_Writer*			e_Segment;
		EBMLMTrackInfo_Writer*		e_Tracks;
		EBMLMSeekhead_Writer*		e_Seekhead;
		EBMLMSeekhead_Writer*		e_PrimarySeekhead;
		EBMLMSeekhead_Writer*		e_SecondarySeekhead;
		EBMLMCluster_Writer*		e_Cluster;
		EBMLMCue_Writer*			e_Cues;
		EBMLElement_Writer*         e_ReservedSpace;
		CChapters*					chapters;
		__int64						max_chapter_duration;
		
		WRITE_STATE					ws;
		WRITE_BUFFER				write_buffer;
		
	protected:
		void			FlushQueues();
		STREAM*			GetDest();
		int				GetActiveTrack();
		__int64			GetMinTimecode();
		void			SetMinTimecode(__int64 iTimecode);
		int				TrackNumber2Index(int iNbr);
	// reads next block and adds it to the corresponding queue
		int				ReadBlock();
		int				AddCuepoint(int iTrack, __int64 iClusterPosition, __int64 iTimecode, __int64 iBlock);
		float			GetTrackTimecodeScale(int iTrack = -1);
		int				MapT(int iIndex);
		int				MapS(int iIndex);
		int				StoreBlock(ADDBLOCK* a);
		int				PrebufferBlock(ADDBLOCK* a);
		int				FindEmptyBufferIndex(int s);
		int				FindEarliestBlockIndex();
		int				FindEarliestBlockIndexOfStream(int s);
		int				StoreEarliestBlock();
		int				FlushWriteBuffer();
		int				CopyAddBlock(int i, ADDBLOCK* a);
		int				GetTracksCopiesCount();
		int				FillQueue(int i);

		void			RenderChapterSegmentUIDTags(EBMLElement_Writer* pParent, CChapters* c);
		void*			GetTrackCompressionPrivate(int iTrack, int index);
	public:
		virtual ITitleSet* GetTitleSet();
		STREAM*			GetSource();
	// blocks (read)
		int				Read(READ_INFO* pInfo, int iFlags = MRF_CURRENT);
		bool			IsKeyframe();
		bool			IsEndOfStream(int iTrack = -1);
	// blocks (write)
		int				Write(ADDBLOCK* a);
		int				IsStreamQueued(int i);
		
		MATROSKA();
		virtual ~MATROSKA();
		int		virtual Open(STREAM* s,int iMode);
		int				Close();
	// if bAllow => do not assume logical file structure; allow obfuscated ordering of elements
		void			AllowObfuscatedFiles(bool bAllow = true);
	// global (read)
		int				GetSegmentCount();
		int				GetActiveSegment();
		__int64			GetDuration();
		__int64			GetSize();
	// global (write)
		int				BeginWrite();
	// choose segment and track
		int				SetActiveSegment(int iSegment);
		int				SetActiveTrack(int iTrack, int iType = SAT_ALL);
	// segment info (read):
		int				EnableQueue(int iStream, int iEnable = 1);
		char*			GetSegmentMuxingApp(int iSegment = -1);
		char*			GetSegmentTitle(int iSegment = -1);
		char*			GetSegmentWritingApp(int iSegment = -1);
		__int64			GetSegmentDuration();
		__int64			GetSegmentSize();
		__int64			GetSegmentFilePos();

		int				GetMaxBlockGapFactor();
		void			SetMaxBlockGapFactor(int iFactor);
	// segment info (write)
		void			Deb0rkReferences(bool bDeb0rk = true); // not yet implemented
//		void			EnablePrevClusterSize(int bEnable);
//		void			EnableClusterPosition(int bEnable);
//		void			EnableClusterIndex(int bEnable);
		void			EnableDisplayWidth_Height(int bEnable);
//		void			EnableCueBlockNumber(int bEnable);
		void			EnableCues(int iStreamType, int bEnable);
		void			EnableCueAutosize(int enabled);
//		void			EnableWriteFlagEnabled(int bEnable);
//		void			EnableWriteFlagDefault(int bEnable);
//		void			EnableWriteFlagLacing(int bEnable);
		void			EnableShiftFirstClusterTimecode2Zero(int bEnable = true);
		void			EnableRandomizeElementOrder(int bEnable = true);

		bool			Enable(unsigned __int64 flag, int additonal_info, int action);

		int				GetLaceStyle();
		__int64			GetMaxClusterSize();
		__int64			GetMaxClusterTime();
		__int64			GetOverhead();
		void			GetClusterStats(CLUSTER_STATS* lpInfo);
		int				GetCueCount(int flag = 2); // 1 = created, 2 = written
		__int64			GetSeekheadSize();
		bool			Is1stClusterLimited();
//		bool			IsClusterPositionEnabled();
		bool			IsDisplayWidth_HeightEnabled();
//		bool			IsPrevClusterSizeEnabled();
		bool			IsCuesEnabled(int iStreamType);
		bool			IsCueAutoSizeEnabled(void);
//		int				IsClusterIndexEnabled();
//		int 			IsEnabled_WriteFlagEnabled();
//		int 			IsEnabled_WriteFlagDefault();
//		int 			IsEnabled_WriteFlagLacing();
		int				IsEndOfSegment();
		void			SetLaceStyle(int iStyle);
		void			SetMaxClusterSize(__int64 iSize); // kByte
		void			SetMaxClusterTime(__int64 iSize, int bLimit1stCluster); // millisec
		void			SetNonclusterIndexMode(int mode);
		void			SetInitialHeaderSize(int size);
		void			SetSegmentDuration(float fDuration);
		void			SetSegmentTitle(char* cTitle);
		void			SetTrackCount(int iCount);
		void			SetAppName(const char* cName);
		void			SetChapters(CChapters* c, __int64 iDuration = -1);
		void			SetTimecodeScale(__int64 iScale);
		void			SetTracksCopiesCount(int iCount);
		void			SetMinimumCueInterval(__int64 interval_ns); // set interval in nanoseconds
		void			SetCueTargetSizeRatio(double ratio);
		double			GetCueTargetSizeRatio(void);
		void			SetUID(int uid_type, char* cUID);
		void			SetMatroskaVersion(int version);
		int				GetMatroskaVersion();

	// segment control
		void			Seek(__int64 iTimecode);
		bool			VerifyCuePoint(int index);

	// segment info (read/write)
		__int64			GetTimecodeScale();
		int				GetTrackCount(int segment = -1, int iType = GTC_ALL);
	// track info (read)
		int				GetAspectRatioType(int iTrack = -1);
		int				GetBitDepth(int iTrack = -1);
		int				GetChannelCount(int iTrack = -1);
		void			GetChannelPositions(unsigned char* pos);
		CHAPTERS*		GetChapterInfo();
		CUES*			GetCues();
		char*			GetCodecID(int iTrack = -1);
		char*			GetCodecName(int iTrack = -1);
		void*			GetCodecPrivate(int iTrack = -1);
		int				GetCodecPrivateSize(int iTrack = -1);
		int				GetColorSpace(int iTrack = -1);
		__int64			GetDefaultDuration(int iTrack = -1);
		float			GetGamma(int iTrack = -1);
		__int64			GetQueuedDataSize(int iTrack = -1);
		float			GetAvgFramesize(int iTrack = -1);
		char*			GetLanguage(int iTrack = -1);
		__int64 virtual GetMasterTrackDuration();
		int				GetMaxCache(int iTrack = -1);
		int				GetMinCache(int iTrack = -1);
		__int64			GetNextTimecode(int iTrack = -1);
		int				GetResolution(int* iPX,int* iPY,int* iDX,int* iDY, int* iDU);
		int				GetCropping(RECT* cropping);
		float			GetSamplingFrequency(int iTrack = -1);
		float			GetOutputSamplingFrequency(int iTrack = -1);
		char*			GetUID(int uid_type);
		char*			GetSegmentUID();
		TAG_INDEX_LIST& GetGlobalTags();
		int				GetTag(uint iIndex, char* cTagName, char* cTagValue, char* cTagLng);

		int				GetTrackCompressionDescriptorCount(int iTrack = -1);
		int				GetTrackCompression(int iTrack, int index);
		int				GetTrackCompressionPrivate(int iTrack, int index, void* pDest);
		int				GetTrackCompressionPrivate(int iTrack, int index, void** pDest);
		int				GetTrackCompressionPrivateSize(int iTrack, int index);
		int				GetTrackCompression(int iTrack, TRACK_COMPRESSION& target);
		int				GetTrackCompressionOrder(int iTrack, std::vector<int>& order);

		__int64			GetTrackDuration(int iTrack = -1);
		char*			GetTrackName(int iTrack = -1);
		ITitleSet*		GetTrackTitleSet(int iTrack = -1);
		int				GetTrackNumber(int iTrack = -1);
		int				GetTrackType(int iTrack = -1);
		__int64			GetTrackUID(int iTrack = -1);
		float			GetTrackBitrate(int iTrack = -1);
		__int64			GetTrackSize(int iTrack = -1);
		TAG_INDEX_LIST& GetTrackTags(int iTrack = -1);
		int				IsBitrateIndicated(int iTrack = -1);
		int				IsDefault(int iTrack = -1);
		int				IsEnabled(int iTrack = -1);
		int				IsLaced(int iTrack = -1);
		int				IsSparse(int iTrack = -1);
		int				IsForced(int iTrack = -1);
//		int				IsCueBlockNumberEnabled();
		void			SelectSingleStream(int iStream);
		void			SelectStreams(int* iStreams); // -1 - terminated!!
		int 			SetSparseFlag(int iTrack, int bFlag);
	// track info (write)
		__int64			GetLaceStatistics(int iTrack, int iIndex, LACE_STATS* lpData = NULL);
		void			SetBitDepth(int iTrack, int iDepth);
		void			SetCacheData(int iTrack, int iMin, int iMax);
		void			SetChannelCount(int iTrack, int iCount);
		void			SetCodecID(int iTrack, char* cID);
		void			SetCodecPrivate(int iTrack,void* pData,int iSize);
		void			SetCropping(int iTrack, RECT* r);
		void			SetDefaultDuration(int iTrack, __int64 iDuration);
		void			SetFlags(int iTrack,int iEnabled, int iLacing, int iDefault);
		void			SetResolution(int iTrack, int X, int Y, int X2 = -1, int Y2 = -1);
		void			SetSamplingFrequency(int iTrack, float iFreq, float iOutFreq);
//		void			SetTrackCompression(int iTrack, int iCompression, void* compression_private, int compression_private_size);
		void			AddTrackCompression(int iTrack, int iCompression, void* compression_private,
							size_t compression_private_size);

		void			SetTrackInfo(int iTrack, MATROSKA* m = NULL, int iSourceTrack = NULL);
		void			SetTrackLanguageCode(int iTrack,char* cName);
		void			SetTrackName(int iTrack, char* cName, char* cLanguage = "");
		void			SetTrackNumber(int iTrack, int iNbr);
		void			SetTrackType(int iTrack, int iType);

	// attachment functions
		__int64			GetAttachmentFlags(int index);
		int				GetAttachmentCount();
		int				GetAttachmentIndex(__int64 uid);
		int				GetAttachmentMimeType(int index, char* pDest, int max_len = 65535);
		int				GetAttachmentFilename(int index, char* pDest, int max_len = 65535);
		int				GetAttachmentFileDescription(int index, char* pDest, int max_len = 65535);
		__int64			GetAttachmentUID(int index);
		__int64			GetAttachmentFileSize(int index);
		__int64			GetAttachmentFilePosition(int index);
		int				GetAttachmentBinaryData(int index, char* pDest, int max_len);
};
char* matroska_GetCompileDate();

const int MGOF_CLUSTERS_BYSIZE	=	0x00000001;
const int MGOF_CLUSTERS_BYTIME	=	0x00000002;
const int MGOF_CLUSTERS_PREVSIZE=   0x00000004;
const int MGOF_CLUSTERS_POSITION=   0x00000008;
const int MGOF_CLUSTERS_NOINDEX =   0x00000010;
const int MGOF_NOCUEOVERHEAD    =   0x00000020;

const int MGOSF_LACE			=	0x00000001;
const int MGOSF_LACEDUR_IND		=	0x00000010;

const int MGOSF_FRAMESIZE_IND	=	0x00000002;
const int MGOSF_FRAMEDUR_IND	=   0x00000004;
const int MGOSF_FRAMECOUNT_IND  =   0x00000008;
const int MGOSF_CBR	            =   0x00000020;



typedef struct
{
	int		iFlags;              // flags: laced? frame size indicated? etc
	int		iLaceStyle;          // xiph, ebml/fixed, auto
	int		iFramesize;          // avg size of one frame
	float	fFrameDuration;      // duration of one frame in milliseconds
	float	fFrameCountPerLace;  // number of frames per lace
	float	fDurPerLace;         // duration of one lace in ms

} MGO_STREAMDESCR;

typedef struct
{
	int		iFlags;              // flags
	__int64	iDuration;           // duration of output file in seconds
	float	fFPS;                // avg fps
	__int64 iFinalSize;          // roughly estimated final size in kByte; needed for clusters-by-size
	int		iClusterSize;        // size of clusters in kilobytes
	int		iClusterTime;        // time of clusters in milliseconds
	int		iKeyframeInterval;   // keyframe interval; needed for cue size estimation
	int		iMatroskaVersion;

	int                 iStreamCount; // number of streams
	MGO_STREAMDESCR*    pStreams;     // descriptor for each stream

} MGO_DESCR;

int matroska_guess_overhead(MGO_DESCR* lpMGO);



#endif