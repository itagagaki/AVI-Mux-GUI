#ifndef I_FILEDIALOGS
#define I_FILEDIALOGS


#include <afxwin.h>
#include <tchar.h>

void PrepareSimpleDialog(void* lpopn, HWND m_hWnd, const TCHAR* cFilter);
int GetOpenSaveFileNameUTF8(void* lpofn, int open);


#endif