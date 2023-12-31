#include "stdafx.h"
#include "Queue.h"

#ifdef DEBUG_NEW
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

void QUEUE_enter(QUEUE** q, CBuffer* pData)
{
	if (!*q) {
		*q = new QUEUE; ZeroMemory(*q,sizeof(QUEUE));
		(*q)->buffer = pData;
		pData->IncRefCount();
	} else 
		QUEUE_enter(&(*q)->pLast->pNext, pData);

	if ((*q)->pLast) {
		(*q)->pLast = (*q)->pLast->pNext;
	} else {
		(*q)->pLast = (*q);
	}

}

// read one element from the queue, and delete it if QR_DONTREMOVE is not set
CBuffer* QUEUE_read(QUEUE** q, int iFlags)
{
	if (!*q) return NULL;
	QUEUE*	n = (*q)->pNext;
	CBuffer* b;

	if (n) {
		b = (*q)->buffer;
		if (! (iFlags & QR_DONTREMOVE)) {
			n->pLast = (*q)->pLast;
			DecBufferRefCount(&(*q)->buffer);
			delete (*q);
			*q = n;
		}
	} else {
		b = (*q)->buffer;
		if (! (iFlags & QR_DONTREMOVE)) {
			DecBufferRefCount(&(*q)->buffer);
			delete (*q);
			*q = n;
		}
	}
	return b;
}

void QUEUE_kill(QUEUE** q)
{
	while (*q) {
		CBuffer*  b = QUEUE_read(q);
		DecBufferRefCount(&b);
	}
}

bool QUEUE_empty(QUEUE* q)
{
	return (!q);
}

