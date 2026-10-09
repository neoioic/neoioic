/**
 *
 * 文 件 名：se.c
 *
 * 描    述：
 *
 * 创 建 者：
 *
 * 创建日期：
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>                <修改者>
 *   <修改内容...>
 *
 **/

#include <wchar.h>
#include "se.h"


HBITMAP     g_ArrHBITMAP[eNum_BMP];



#ifdef _DEBUG 

/**
*
* NAME: _Debug_OutputString
*/
void _Debug_OutputString(TCHAR* str1, int val, TCHAR* str2)
{
	TCHAR   str[1024];

	assert(str1 != NULL);

	if(str2 != NULL)
		swprintf(str, sizeof(str) / sizeof(str[0]), TEXT("%ls%d%ls"), str1, val, str2);
	else
		swprintf(str, sizeof(str) / sizeof(str[0]), TEXT("%ls%d"), str1, val);

	OutputDebugString(str);
	
	return;
}

#endif



/**
*
* NAME: LoadBitmaps
* DESC: load resource of bitmaps
*/
void  LoadBitmaps()
{
	TCHAR                szFilePath[MAX_PATH+1];
	TCHAR*               p;

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));

	/*- TRCClose -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("TRCClose_Normal.jpg"));
	g_ArrHBITMAP[eTRCClose_Normal_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("TRCClose_FocusOver.jpg"));
	g_ArrHBITMAP[eTRCClose_FocusOver_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("TRCClose_FocusOn.jpg"));
	g_ArrHBITMAP[eTRCClose_FocusOn_BMP] = LoadPictureFile(szFilePath);

    /*- Button2 -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button2_Normal.jpg"));
	g_ArrHBITMAP[eButton2_Normal_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button2_FocusOver.jpg"));
	g_ArrHBITMAP[eButton2_FocusOver_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button2_FocusOn.jpg"));
	g_ArrHBITMAP[eButton2_FocusOn_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button2_Active.jpg"));
	g_ArrHBITMAP[eButton2_Active_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button2_ABSInactive.jpg"));
	g_ArrHBITMAP[eButton2_ABSInactive_BMP] = LoadPictureFile(szFilePath);

	return;
}

/**
*
* NAME: UnloadBitmaps
* DESC: unload resource of bitmap
*/
void  UnloadBitmaps()
{
	int i;

	for(i = 0; i < eNum_BMP; i++)
	{
		if(g_ArrHBITMAP[i])
			DeleteObject(g_ArrHBITMAP[i]);
	}

	return;
}