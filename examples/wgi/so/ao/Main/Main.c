/**
 *
 * 文 件 名：Main.c
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
#include "Main.h"
#include <stdio.h>
#include "../../go/VObject/VObject.h"
#include "../../go/WObject/WObject.h"

#define _CRTDBG_MAP_ALLOC



extern  OBJECT*   g_poMainWnd;
extern  void  LoadBitmaps();
extern  void  UnloadBitmaps();

// Global Variables:
const  TCHAR   g_szDialogClass[] = TEXT("Dialog"); // main window class name.
const  TCHAR   g_szDialogName[] = TEXT("Dialog"); // main window name.
HINSTANCE      g_hInstance = NULL;

/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：Main_Open
*/
static  RESULT  Main_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	if(1 == This->RefCnt)
		return RP_RCONE;


	return R_P;
}

/**
*
* 名称：Main_Input
*/
static  RESULT  Main_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：Main_Output
*/
static  RESULT  Main_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：Main_IOput
*/
static  RESULT  Main_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：Main_Interact0
*/
static  RESULT  Main_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：Main_Interact1
*/
static  RESULT  Main_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：Main_Interact2
*/
static  RESULT  Main_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：Main_Interact3
*/
static  RESULT  Main_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：Main_Close
*/
static  RESULT  Main_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	if(0 == This->RefCnt)
		return RP_RCZERO;


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_Main
*/
void  TOG_Main(OBJECT* pObj)
{
	pObj->Open = Main_Open;
	pObj->Input = Main_Input;
	pObj->Output = Main_Output;
	pObj->IOput = Main_IOput;
	pObj->Interact0 = Main_Interact0;
	pObj->Interact1 = Main_Interact1;
	pObj->Interact2 = Main_Interact2;
	pObj->Interact3 = Main_Interact3;
	pObj->Close = Main_Close;
}


/*=======================+ Main +========================*/


/**
*
* 名称：WinMain
* 描述：主体函数。
*/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	VR		             caller = {OID_MAIN, OID_WGIDEMO};
	HWND                 hWnd;
	MSG                  msg = {0};
	int                  exitCode = 0;
	OBJECT*              pObject;
	INIT_VOBJECT         ivob;
	INIT_WOBJECT         iwob;
	HCURSOR              hCursor;
	RESULT               r;
	BITMAP               bm;
	HBITMAP              hBmpNormal, hBmpFocusOver, hBmpFocusOn, hBmpActive;  // Dialog's bitmaps
	TCHAR                szFilePath[MAX_PATH+1];
	TCHAR*               p;


	hWnd = FindWindow(g_szDialogClass, g_szDialogName);
	if(hWnd != NULL)
	{
		SetForegroundWindow(hWnd);
		return  0;
	}

	g_hInstance = hInstance;
	if (FAILED(OleInitialize(NULL)))
		return -1;
				
	hCursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hCursor);

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));
	
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Dialog_Normal.jpg"));
	hBmpNormal = LoadPictureFile(szFilePath);
	assert(hBmpNormal);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Dialog_FocusOver.jpg"));
	hBmpFocusOver = LoadPictureFile(szFilePath);
	assert(hBmpFocusOver);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Dialog_FocusOn.jpg"));
	hBmpFocusOn = LoadPictureFile(szFilePath);
	assert(hBmpFocusOn);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Dialog_Active.jpg"));
	hBmpActive = LoadPictureFile(szFilePath);
	assert(hBmpActive);

	LoadBitmaps();

    // create and open object
	r = CreateObject(MSN_MYDIALOG, 0, 0, 1, &g_poMainWnd);
	if(RN(r))
	{
		OleUninitialize();
		return -1;
	}
    r = VO_Open(g_poMainWnd, &caller);
	assert(RP(r));

	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&iwob, 0, sizeof(INIT_WOBJECT));

	GetObject(hBmpNormal, sizeof(bm), &bm);

	ivob.ArrHBITMAP[eVOBState_Normal] = hBmpNormal;
	ivob.ArrHBITMAP[eVOBState_FocusOver] = hBmpFocusOver;
	ivob.ArrHBITMAP[eVOBState_FocusOn] = hBmpFocusOn;
	ivob.ArrHBITMAP[eVOBState_Active] = hBmpActive;
	ivob.rsc.rcouter.left = 50;
	ivob.rsc.rcouter.top = 50;
	ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
	ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
	ivob.rsc.rcinner.left = 5;
	ivob.rsc.rcinner.top = 5;
	ivob.rsc.rcinner.right = bm.bmWidth - 5;
	ivob.rsc.rcinner.bottom = bm.bmHeight - 5;
	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;
	ivob.state = eVOBState_Active;

	iwob.hInstance = hInstance;
	iwob.pClassName = g_szDialogClass;
	iwob.pWindowName = g_szDialogName;

	pObject = GetBN(g_poMainWnd, MSN_VOBJECT);
	r = VO_Interact2(pObject, CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), &caller);
	if(!RP(r)) goto initialization_failed;
	pObject = GetBN(g_poMainWnd, MSN_WOBJECT);
	r = VO_Interact2(pObject, CMD_INITIALIZE, (BYTE*)&iwob, sizeof(INIT_WOBJECT), &caller);
	if(!RP(r)) goto initialization_failed;
	r = VO_Interact0(g_poMainWnd, CMD_PREPARE, &caller);
	if(!RP(r)) goto initialization_failed;
	r = VO_Interact0(g_poMainWnd, CMD_RUN, &caller);
	if(!RP(r)) goto initialization_failed;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	exitCode = (int)msg.wParam;
	goto cleanup;

initialization_failed:
	fprintf(stderr, "WGI initialization failed: result=%d, Windows error=%lu\n", r, GetLastError());
	exitCode = 1;

cleanup:

	// close and destroy object
	r = VO_Close(g_poMainWnd, &caller);
	assert(RP_RCZERO == r);
	DestroyObject(g_poMainWnd); 

	DeleteObject(hBmpNormal);
	DeleteObject(hBmpFocusOver);
	DeleteObject(hBmpFocusOn);
	DeleteObject(hBmpActive);
	UnloadBitmaps();
	OleUninitialize();

	

	return exitCode;
}

/*====================+ Function(s) +====================*/
/* ... */

