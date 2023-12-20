#ifndef I_IBITSTREAM
#define I_IBITSTREAM

#include "BaseStreams.h"

class IBitStream
{
protected:
	STREAM*		source;
protected:
	STREAM virtual*	GetSource() { return source; }
public:
	IBitStream();
	virtual ~IBitStream();

	int		virtual	Open(STREAM* lpStream) = 0;
	int		virtual Close() = 0;
	int		virtual Seek(__int64 qwPos) = 0;
	int		virtual GetBitPos() = 0;
	__int64 virtual GetPos() = 0;
	void	virtual SetBitPos(int pos) = 0;
	void    virtual FlushInputBuffer() = 0;
	int		virtual ReadBits(int n, int iFlag = 0) = 0;
	__int64	virtual	ReadBits64(int n, int iFlag = 0) = 0;
};

#endif