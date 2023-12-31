#ifndef I_BITSTREAM
#define I_BITSTREAM

#include <wtypes.h>
#include "IBitStream.h"
#include "types.h"
#include <deque>

class BITSTREAM : public virtual IBitStream
{
	protected:
		DWORD		dwCurrBitPos;
		void	virtual LoadWord(void);
		WORD		wData;
		int			ReadBit(int iFlag = 0);
    public:
		BITSTREAM(void)	{ source=NULL; dwCurrBitPos=0; }
		virtual ~BITSTREAM() {};
		int		virtual GetBitPos() { return dwCurrBitPos; }
		void	virtual SetBitPos(int pos) { dwCurrBitPos = pos; } 

		int		virtual	Open(STREAM* lpStream);
		int		virtual Close(void) { source=NULL; return STREAM_OK; }
		bool	virtual	IsEndOfStream(void) { return (source->IsEndOfStream()&&(dwCurrBitPos==15)); }
		int		virtual Seek(__int64	qwPos);
		void    virtual FlushInputBuffer() {};

		// Flag == 0 -> begin reading at bit 7
		// Flag == 1 -> begin reading at bit 0
		int	virtual		ReadBits(int n, int iFlag = 0);
		__int64	virtual	ReadBits64(int n, int iFlag = 0);
		__int64			GetPos();
};

class CBitStream2 : public virtual BITSTREAM
{
private:
	std::deque<uint8> m_InputBuffer;
	int m_PrebufferSize;

	/** \brief Reads data into the input buffer
	 *
	 * This function reads as many bytes as indicated \a m_PrebufferSize into \a m_InputBuffer.
	 * \returns 'true' if at least one byte was read, 'false' if no data could be read
	 */
	bool	virtual FillInputBuffer();
public:
	CBitStream2();
	virtual ~CBitStream2();
	int		virtual Seek(__int64	qwPos);
	__int64	virtual	ReadBits64(int n, int iFlag = 0);
	void    virtual FlushInputBuffer() { 
		m_InputBuffer.clear(); 
		dwCurrBitPos = 16;
	}
};

#endif