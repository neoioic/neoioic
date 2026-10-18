

#include <wchar.h>
#include "support.h"

HBITMAP g_arr_hbitmap[NUM_BMP];

#ifdef _DEBUG

void _Debug_OutputString(TCHAR *str1, int val, TCHAR *str2)
{
	TCHAR str[1024];

	assert(str1 != NULL);

	if (str2 != NULL)
		swprintf(str, sizeof(str) / sizeof(str[0]), TEXT("%ls%d%ls"),
			 str1, val, str2);
	else
		swprintf(str, sizeof(str) / sizeof(str[0]), TEXT("%ls%d"), str1,
			 val);

	OutputDebugString(str);

	return;
}

#endif

/* DESC: load resource of bitmaps */
void load_bitmaps()
{
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));

	/* - TRCClose - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("trc_close_normal.jpg"));
	g_arr_hbitmap[TRC_CLOSE_NORMAL_BMP] = load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("trc_close_focus_over.jpg"));
	g_arr_hbitmap[TRC_CLOSE_FOCUS_OVER_BMP] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("trc_close_focus_on.jpg"));
	g_arr_hbitmap[TRC_CLOSE_FOCUS_ON_BMP] = load_picture_file(sz_file_path);

	/* - Button2 - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button2_normal.jpg"));
	g_arr_hbitmap[BUTTON2_NORMAL_BMP] = load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button2_focus_over.jpg"));
	g_arr_hbitmap[BUTTON2_FOCUS_OVER_BMP] = load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button2_focus_on.jpg"));
	g_arr_hbitmap[BUTTON2_FOCUS_ON_BMP] = load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button2_active.jpg"));
	g_arr_hbitmap[BUTTON2_ACTIVE_BMP] = load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button2_abs_inactive.jpg"));
	g_arr_hbitmap[BUTTON2_ABS_INACTIVE_BMP] =
		load_picture_file(sz_file_path);

	return;
}

/* DESC: unload resource of bitmap */
void unload_bitmaps()
{
	int i;

	for (i = 0; i < NUM_BMP; i++) {
		if (g_arr_hbitmap[i])
			DeleteObject(g_arr_hbitmap[i]);
	}

	return;
}