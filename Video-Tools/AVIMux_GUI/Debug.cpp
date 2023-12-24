#include "stdafx.h"
#include "Debug.h"

#ifdef DEBUG_ON
#include "resource.h"
#include "math.h"
#endif

__int64 QW_div(__int64 x, __int64 y, char* lpName)
{
#ifdef DEBUG_ON
	if (!y)
	{
		//	CString cStr;
		//	cStr.LoadString(IDS_ERROR);
		char	Buffer[100];
		wsprintf(Buffer,"Division by Zero: %c%c%s",13,10,lpName);
		MessageBox(NULL,Buffer,"Internal Error",MB_OK | MB_ICONERROR);
		return 0;
	}
#endif
	return x/y;
}

double d_div(double x, double y, char* lpName)
{
#ifdef DEBUG_ON
	if (fabs(y)<0.001)
	{
		//	CString cStr;
		//	cStr.LoadString(IDS_ERROR);
		char	Buffer[100];
		wsprintf(Buffer,"Division by Zero: %c%c%s",13,10,lpName);
		MessageBox(NULL,Buffer,"Internal Error",MB_OK | MB_ICONERROR);
		return 0;
	}
#endif
	return x/y;

}