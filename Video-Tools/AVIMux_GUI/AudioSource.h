/*

AUDIOSOURCE: abstract class

CBRSOURCE: generic source for constant bitrate streams
MP3SOURCE: handles MP3-VBR
AC3SOURCE: handles AC3-CBR
DTSSOURCE: handles DTS-CBR

*/


#ifndef F_AUDIOSOURCE_I
#define F_AUDIOSOURCE_I

//#include <windows.h>
#include "MessageLists.h"
#include "AudioSource_generic.h"
#include "AudioSource_DTS.h"
#include "AudioSource_AC3.h"
#include "AudioSource_MP3.h"
#include "AudioSource_Matroska.h"
#include "AudioSource_AVI.h"
#include "AudioSource_AAC.h"
#include "AudioSource_List.h"
#include "AudioSource_Vorbis.h"
#include "AudioSource_WAV.h"

#include "../BaseStreams.h"
#include "../multimedia_source.h"


/*

  non self-evident calls:
    - GetOffset(): reports the amount of crap data (in bytes) at the beginning of a stream

*/

// enough paramters for Read(). Further ones are collected here


// audio sources from a binary stream without any special container around,
// such as MP3, AC3 and DTS





#endif