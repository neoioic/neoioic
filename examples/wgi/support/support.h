

#ifndef NEOIOIC_WGIDEMO_SE_H
#define NEOIOIC_WGIDEMO_SE_H

#include "../host.h"
#include "wgi.h"

enum ebitmap {
	/* - TRCClose - */
	TRC_CLOSE_NORMAL_BMP,
	TRC_CLOSE_FOCUS_OVER_BMP,
	TRC_CLOSE_FOCUS_ON_BMP,

	/* - Button2 - */
	BUTTON2_NORMAL_BMP,
	BUTTON2_FOCUS_OVER_BMP,
	BUTTON2_FOCUS_ON_BMP,
	BUTTON2_ACTIVE_BMP,
	BUTTON2_ABS_INACTIVE_BMP,

	/* - number of enum - */
	NUM_BMP
};

#ifdef _DEBUG

extern void _Debug_OutputString(TCHAR *str1, int val, TCHAR *str2);

#endif

#endif /* #ifndef NEOIOIC_WGIDEMO_SE_H */
