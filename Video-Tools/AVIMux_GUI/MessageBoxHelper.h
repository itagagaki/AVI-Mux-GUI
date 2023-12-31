#pragma once

#include <wtypes.h>
#include "../../Common/utf-8.h"

class MessageBoxHelper
{
public:
	static DWORD ShowByID(HWND parent, DWORD titleID, DWORD messageID, UINT uType);
	static DWORD Show(const CUTF8& title, const CUTF8& message);

	static DWORD CouldNotOpenFileForWrite(const CUTF8& fileName);
};