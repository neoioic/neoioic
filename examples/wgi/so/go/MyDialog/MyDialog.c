/**
 *
 * 文 件 名：MyDialog.c
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
#include "MyDialog.h"
#include "MyDialog_InitSub.h"
#include "../WMenu/WMenu.h"
#include "../CObject/CObject.h"


extern   const  TCHAR    g_szMyDialogClass[]; 
extern   const  TCHAR    g_szMyDialogName[]; 
extern   HINSTANCE       g_hInstance;


const  TCHAR   g_szMenuClass[] = TEXT("Menu"); 
const  TCHAR   g_szMenuName[] = TEXT("Menu"); 


void  TOG_MyDialog(OBJECT* pObj);

static ATOM  MyRegisterClass(OBJECT* This);
static LRESULT CALLBACK CBF_MyDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static void  LoadBitmaps(OBJECT*  This);
static void  UnloadBitmaps(OBJECT*  This);
static void  PopMenuForMRControl(OBJECT* This, const VR* pCaller);
static void  PopMenuForMRMenuDemo(OBJECT* This, const VR* pCaller);
static OIOIC_BOOL  CBF_CreateMenuItemsForMRControl(OBJECT* pMenu, const VR* pCaller);
static OIOIC_BOOL  CBF_DestroyMenuItemsForMRControl(OBJECT* pMenu, const VR* pCaller);
static OIOIC_BOOL  CBF_CreateMenuItemsForMRMenuDemo(OBJECT* pMenu, const VR* pCaller);
static OIOIC_BOOL  CBF_DestroyMenuItemsForMRMenuDemo(OBJECT* pMenu, const VR* pCaller);
static OIOIC_BOOL  CBF_CreateMenuItemsForMIItem3(OBJECT* pMenu, const VR* pCaller);
static OIOIC_BOOL  CBF_DestroyMenuItemsForMIItem3(OBJECT* pMenu, const VR* pCaller);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> WPanel </ibn>*/
/*<crt>*/
RESULT  CRT_MyDialog(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  void  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  void  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  void  TOG_WPanel(OBJECT* pObj);
	extern  void  TOG_WObject(OBJECT* pObj);
	extern  void  TOG_VObject(OBJECT* pObj);
	extern  void  TOG_OIOIC(OBJECT* pObj);


	size_t   ux_ND = 5; 	/* ND数量。*/
	size_t   ux_BN = 10; 	/* 各ND的BN数量之和。*/
	size_t   ux_IB = 4; 	/* 各ND的IBN数量之和。*/
	size_t   ux_CS = NumCR * 15; 	/* 各ND的最少CS数量之和。*/
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_MYDIALOG) + OIOIC_ALIGNED_SIZE(EM_WPANEL) + OIOIC_ALIGNED_SIZE(EM_WOBJECT)
		 + OIOIC_ALIGNED_SIZE(EM_VOBJECT) + OIOIC_ALIGNED_SIZE(EM_OIOIC); 	/* 各ND的EM尺寸之和。*/

	size_t  sum = ux_ND * sizeof(OBJECT) 	/* for AND. */
		 + ux_BN * sizeof(OBJECT*) 	/* for "ppo_ABN". */
		 + ux_IB * sizeof(OBJECT*) 	/* for "ppo_AIB". */
		 + ux_CS * sizeof(VR) + ux_EM; 	/* for "pvr_ACS" and "pEM". */


	BYTE*  pIC = NULL;

	if(NULL == pExotic)
	{
		*ppObj = NULL;
		pIC = (BYTE*)calloc(sum, 1);
	}else
	{
		pIC = pExotic;
	}


	if( pIC != NULL )
	{
		OBJECT*  pND;
		MLDSN    ArrMsn[4];
		BYTE*    p = pIC + sizeof(OBJECT) * ux_ND;


		/***  确定AND各元素  ***/

		/** MyDialog **/
		pND = (OBJECT*)pIC;
		TOG_MyDialog(pND);
		pND->MSN = MSN_MYDIALOG;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** WPanel **/
		TOG_WPanel(++pND);
		pND->MSN = MSN_WPANEL;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** WObject **/
		TOG_WObject(++pND);
		pND->MSN = MSN_WOBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** VObject **/
		TOG_VObject(++pND);
		pND->MSN = MSN_VOBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** OIOIC **/
		TOG_OIOIC(++pND);
		pND->MSN = MSN_OIOIC;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;


		/***  初始化各ND  ***/

		/** MyDialog **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_WPANEL;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_WPANEL;
		ArrMsn[1] = MSN_WOBJECT;
		ArrMsn[2] = MSN_VOBJECT;
		ArrMsn[3] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 4);
		p += sizeof(OBJECT*) * 4;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_MYDIALOG);

		/** WPanel **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_WOBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_WOBJECT;
		ArrMsn[1] = MSN_VOBJECT;
		ArrMsn[2] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 3);
		p += sizeof(OBJECT*) * 3;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_WPANEL);

		/** WObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		ArrMsn[1] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 2);
		p += sizeof(OBJECT*) * 2;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 3;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_WOBJECT);

		/** VObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 4;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_VOBJECT);

		/** OIOIC **/
		++pND;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 5;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		if( IQCty > 0 )
		{
			/* - IQ - */
			((EM_OIOIC*)(pND->pEM))->IQ.Dtrm = (BYTE*)calloc(IQCty, 1);
			if( NULL == ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm)
			{
				/* 分配IQ的容量失败！*/
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->IQ.Front = ((EM_OIOIC*)(pND->pEM))->IQ.Rear = ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->IQ.Cty = IQCty;
			((EM_OIOIC*)(pND->pEM))->IQ.Qty = ((EM_OIOIC*)(pND->pEM))->IQ.Lost = 0;
		}

		if( OQCty > 0 )
 		{
			/* - OQ - */
			((EM_OIOIC*)(pND->pEM))->OQ.Dtrm = (BYTE*)calloc(OQCty, 1);
			if(NULL == ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm)
			{
				/* 分配OQ的容量失败！*/
				if( ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm != NULL )
					free(((EM_OIOIC*)(pND->pEM))->IQ.Dtrm);
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->OQ.Front = ((EM_OIOIC*)(pND->pEM))->OQ.Rear = ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->OQ.Cty = OQCty;
			((EM_OIOIC*)(pND->pEM))->OQ.Qty = ((EM_OIOIC*)(pND->pEM))->OQ.Lost = 0;
		}
		p += OIOIC_ALIGNED_SIZE(EM_OIOIC);
	}else
	{
		return R_N;
	}


	if(NULL == pExotic)
		*ppObj = (OBJECT*)pIC;


	return R_P;
}
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：MyDialog_Open
*/
static  RESULT  MyDialog_Open(OBJECT* This, const VR* pCaller)
{
	EM_MYDIALOG*      pem;


	OBS_OBJECT_OPEN_;


	/* 在下面完成接口自己的任务。*/

	if(1 == This->RefCnt)
	{
		pem = (EM_MYDIALOG*)This->pEM;
		pem->pOIOIC = GetBN(This, MSN_OIOIC); 
		pem->pVObject = GetBN(This, MSN_VOBJECT); 
		pem->pWObject = GetBN(This, MSN_WOBJECT); 
		pem->pWPanel = GetBN(This, MSN_WPANEL);

		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eTRCClose_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eMRControl_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eMRMenuDemo_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eMRHelp_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eButton1_MyDialog]);
		CreateObject(MSN_MYBUTTON, 0, 0, 1, &pem->ArrSUB[eButton2_MyDialog]);
		CreateObject(MSN_MYBUTTON2, 0, 0, 1, &pem->ArrSUB[eButton3_MyDialog]);
		CreateObject(MSN_CEDIT, 0, 0, 1, &pem->ArrSUB[eEdit_MyDialog]);

		LoadBitmaps(This);

		return RP_RCONE;
	}


	return R_P;
}

/**
*
* 名称：MyDialog_Input
*/
static  RESULT  MyDialog_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：MyDialog_Output
*/
static  RESULT  MyDialog_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：MyDialog_IOput
*/
static  RESULT  MyDialog_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：MyDialog_Interact0
*/
static  RESULT  MyDialog_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR                  caller;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
    EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	RESULT              r;
	int                 i;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		if(0 == MyRegisterClass(This))
			return R_N;

		r = VO_Interact0(pem->pWObject, CRT_WGI_WINDOW, &caller);
		if(!RP(r))
			return r;

		for(i = 0; i<eNum_SUB_MyDialog; i++)
		{
			switch(i)
			{
			case eTRCClose_MyDialog:
			case eMRControl_MyDialog:
			case eMRMenuDemo_MyDialog:
			case eMRHelp_MyDialog:
			case eButton1_MyDialog:
			case eButton2_MyDialog:
			case eButton3_MyDialog:
				MyDialog_InitSub_Button(This, i, &caller);
				break;
			case eEdit_MyDialog:
				MyDialog_InitSub_Edit(This,  i, &caller);
				break;
			default:
				break;
			}
		}

		pem_vob->pFirstSbdt = pem->ArrSUB[eTRCClose_MyDialog];
		VO_Interact0(pem->pVObject, CMD_PREPARE, &caller);
		return R_P;
	case CMD_RUN:
		//SendMessage(pem_wob->hWnd, WM_INITDIALOG, 0, 0);
		ShowWindow(pem_wob->hWnd, SW_SHOW);
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：MyDialog_Interact1
*/
static  RESULT  MyDialog_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：MyDialog_Interact2
*/
static  RESULT  MyDialog_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：MyDialog_Interact3
*/
static  RESULT  MyDialog_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	VR                  caller;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)This->pEM;
	INIT_WMENU          iwmu;
	OBJECT*             pObj;
	BITMAP			    bm;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case MSG_WGI_MENUITEMFOCUSOVER:
		assert(sizeof(OBJECT*) == Qty);
		assert(Cty >= sizeof(OBJECT*));
		pObj = *(OBJECT**)IStrm;
		//_Debug_OutputString(TEXT("\nMSG_WGI_MENUITEMFOCUSOVER"), 123, NULL);
		if(pObj == pem->ArrMI[eMIItem3_MyDialog])
		{
			memset(&iwmu, 0, sizeof(INIT_WMENU));
			iwmu.ivob.state = eVOBState_Active;
			iwmu.iwob.hInstance = g_hInstance;
			iwmu.iwob.pClassName = g_szMenuClass;
			iwmu.iwob.pWindowName = g_szMenuName;
			iwmu.hBmpBRBNormal = pem->ArrHBITMAP[eBottomRB_Normal_BMP_MyDialog];
			iwmu.hBmpBRBFocusOn = pem->ArrHBITMAP[eBottomRB_FocusOver_BMP_MyDialog];
			iwmu.hBmpBRBFocusOver = pem->ArrHBITMAP[eBottomRB_FocusOver_BMP_MyDialog];
			iwmu.hBmpTRBNormal = pem->ArrHBITMAP[eTopRB_Normal_BMP_MyDialog];
			iwmu.hBmpTRBFocusOn = pem->ArrHBITMAP[eTopRB_FocusOver_BMP_MyDialog];
			iwmu.hBmpTRBFocusOver = pem->ArrHBITMAP[eTopRB_FocusOver_BMP_MyDialog];
			GetObject(iwmu.hBmpBRBNormal, sizeof(bm), &bm);
			iwmu.nRBHeight = bm.bmHeight;
			iwmu.CreateItems = CBF_CreateMenuItemsForMIItem3;
			iwmu.DestroyItems = CBF_DestroyMenuItemsForMIItem3;
			iwmu.pParent = This;
			iwmu.type = MNUT_LRBOTTOM;
			iwmu.width = 135;
			CalcuORACoord(pObj, &iwmu.uca);
			pObj = PopMenu(&iwmu, &caller);
			assert(pObj);
			*(OBJECT**)OStrm = pObj;
			*pQty = sizeof(OBJECT*);
		}else
		{
		}
		return R_P;
	case MSG_WGI_MENUITEMFOCUSON:
		assert(sizeof(OBJECT*) == Qty);
		assert(Cty >= sizeof(OBJECT*));
		return R_P;
	case MSG_WGI_MENUITEMFOCUSDOWN:
		assert(sizeof(OBJECT*) == Qty);
		assert(Cty >= sizeof(OBJECT*));
		return R_P;
	case MSG_WGI_MENUITEMFOCUSUP:
		assert(sizeof(OBJECT*) == Qty);
		assert(Cty >= sizeof(OBJECT*));
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：MyDialog_Close
*/
static  RESULT  MyDialog_Close(OBJECT* This, const VR* pCaller)
{
	VR                  caller;
	EM_MYDIALOG*          pem = (EM_MYDIALOG*)This->pEM;
	int                 i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	if(0 == This->RefCnt)
	{
		UnloadBitmaps(This);
		
		for(i = 0; i<eNum_SUB_MyDialog; i++)
		{
			VO_Close(pem->ArrSUB[i], &caller);
			DestroyObject(pem->ArrSUB[i]); 
		}

		return RP_RCZERO;
	}


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_MyDialog
*/
void  TOG_MyDialog(OBJECT* pObj)
{
	pObj->Open = MyDialog_Open;
	pObj->Input = MyDialog_Input;
	pObj->Output = MyDialog_Output;
	pObj->IOput = MyDialog_IOput;
	pObj->Interact0 = MyDialog_Interact0;
	pObj->Interact1 = MyDialog_Interact1;
	pObj->Interact2 = MyDialog_Interact2;
	pObj->Interact3 = MyDialog_Interact3;
	pObj->Close = MyDialog_Close;
}

/*====================+ Function(s) +====================*/

/**
*
* 名称：MyRegisterClass
* 描述：
*/
static ATOM  MyRegisterClass(OBJECT* This)
{
	EM_MYDIALOG*          pem = (EM_MYDIALOG*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	WNDCLASS wc;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	    = (WNDPROC)CBF_MyDialogProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= pem_wob->hInstance;
	wc.hIcon			= LoadIcon(pem_wob->hInstance, MAKEINTRESOURCE(IDI_WGIDEMO));
	wc.hCursor		    = NULL;//LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName	    = NULL;
	wc.lpszClassName	= pem_wob->pClassName;

	return RegisterClass(&wc);
}

/**
*
* 名称：CBF_MyDialogProc
* 描述：Mesage handler for dialog.
*/
static LRESULT CALLBACK CBF_MyDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static OBJECT*    s_pSubToMove = NULL;
	static  POINT     s_pt = {0,0};

	VR                caller;
	OBJECT*           This;
	EM_MYDIALOG*      pem;
	EM_VOBJECT*       pem_vob;
	EM_VOBJECT*       pem_vob_sbdt;     
	PAINTSTRUCT       ps;
	POINT             pt;
	MOVE              mv;
	TCHAR             ch;
	int               n;


	caller.cr = OID_MAIN;

	switch (message)
	{
	case WM_INITDIALOG:
		//This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	case WM_PAINT:	
		if(NULL == (This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA))) 
			break;
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		BeginPaint(hWnd, &ps);
		VO_Interact0(pem->pWPanel, CMD_WGI_PAINT, &caller);
		EndPaint(hWnd, &ps);
		break;
	case WM_ACTIVATE:   /* MSDN：如果应用程序处理了此消息，应该返回FALSE。所以没用“break”。*/
		if(NULL == (This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA))) 
			return FALSE; 
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
	
		if(WA_INACTIVE == LOWORD(wParam))
		{		
			if(pem->pMenu)
			{
				/* 被激活的窗口不是菜单，就要关闭和销毁菜单。*/
				VO_Close(pem->pMenu, &caller);
				DestroyObject(pem->pMenu);
				pem->pPoppingMR = NULL;
			}

			VO_Interact0(pem->pWPanel, MSG_WGI_DEACTIVATE, &caller);
		}else
		{
			VO_Interact0(pem->pWPanel, MSG_WGI_ACTIVATE, &caller);
		}
		
		return FALSE;
	case WM_MOUSEMOVE:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		if(wParam != MK_LBUTTON)
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSOVERMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
			if(pem->pMenu != NULL)
			{
				if(pem_vob->pCFOverSbdt == pem->ArrSUB[eMRControl_MyDialog] && 
					pem->pPoppingMR != pem->ArrSUB[eMRControl_MyDialog])
				{
					VO_Close(pem->pMenu, &caller);
					DestroyObject(pem->pMenu);
					pem->pPoppingMR = NULL;

					PopMenuForMRControl(This, &caller);

				}else if(pem_vob->pCFOverSbdt == pem->ArrSUB[eMRMenuDemo_MyDialog] && 
					pem->pPoppingMR != pem->ArrSUB[eMRMenuDemo_MyDialog])
				{
					VO_Close(pem->pMenu, &caller);
					DestroyObject(pem->pMenu);
					pem->pPoppingMR = NULL;

					PopMenuForMRMenuDemo(This, &caller);
				}
			}
		}else
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSONMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
			if(NULL == pem_vob->pCFOnSbdt && NULL == s_pSubToMove)
			{
				PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			}else if(s_pSubToMove != NULL)
			{
					memset(&mv, 0, sizeof(MOVE));
					mv.dxLR = mv.dxUL = GET_X_LPARAM(lParam) - s_pt.x;
					mv.dyLR = mv.dyUL = GET_Y_LPARAM(lParam) - s_pt.y;
					VO_Interact2(s_pSubToMove, CMD_WGI_MOVE, (BYTE*)&mv, sizeof(MOVE), &caller);
			}

			s_pt.x = GET_X_LPARAM(lParam);
			s_pt.y = GET_Y_LPARAM(lParam);
		}
		break;
	case WM_MOVE:
		if(NULL == (This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA))) 
			break;
		pem = (EM_MYDIALOG*)This->pEM;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		n = pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left;
		pem_vob->rsc.rcouter.left = GET_X_LPARAM(lParam); 
		pem_vob->rsc.rcouter.right = pem_vob->rsc.rcouter.left + n;
		n = pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top;
		pem_vob->rsc.rcouter.top = GET_Y_LPARAM(lParam); 
		pem_vob->rsc.rcouter.bottom = pem_vob->rsc.rcouter.top + n;
		break;
	case WM_LBUTTONDOWN:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);

		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		
		s_pt.x = GET_X_LPARAM(lParam);
		s_pt.y = GET_Y_LPARAM(lParam);

		if(pem->pMenu)
		{
			VO_Close(pem->pMenu, &caller);
			DestroyObject(pem->pMenu);
			pem->pPoppingMR = NULL;
			break;
		}

		// VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSOVER, (BYTE*)&pt, sizeof(POINT), &caller); /* 触摸屏需要先执行焦点OVER行为 */

		if(pem_vob->pCFOverSbdt != NULL)
			VO_Interact0(pem_vob->pCFOverSbdt, MSG_WGI_ACTIVATE, &caller);

		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSDOWN, (BYTE*)&pt, sizeof(POINT), &caller);
		if(pem_vob->pCFDownSbdt != NULL)
		{
			pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pCFDownSbdt, MSN_VOBJECT);
			s_pSubToMove = (NULL == pem_vob_sbdt->pCFDownSbdt) ? pem_vob->pCFDownSbdt : NULL;
		}else
		{
			s_pSubToMove = NULL;
		}

		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSON, (BYTE*)&pt, sizeof(POINT), &caller);
		
		if(pem_vob->pCFOnSbdt != NULL)
		{
			if(pem_vob->pCFOnSbdt == pem->ArrSUB[eTRCClose_MyDialog])
			{
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}

			if(pem_vob->pCFOnSbdt == pem->ArrSUB[eMRControl_MyDialog])
			{
				PopMenuForMRControl(This, &caller);
			}else if(pem_vob->pCFOnSbdt == pem->ArrSUB[eMRMenuDemo_MyDialog])
			{
				PopMenuForMRMenuDemo(This, &caller);
			}else if(pem_vob->pCFOnSbdt == pem->ArrSUB[eMRHelp_MyDialog])
			{
			}
		}

		break;
	case WM_LBUTTONUP:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		s_pSubToMove = NULL;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSUP, (BYTE*)&pt, sizeof(POINT), &caller);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSOVER, (BYTE*)&pt, sizeof(POINT), &caller);
		break;
	case WM_KEYDOWN:
		//This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	case WM_CHAR:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		pem = (EM_MYDIALOG*)This->pEM;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		caller.mr = This->OID;
		if(pem_vob->pActiveSbdt ==  pem->ArrSUB[eEdit_MyDialog])
		{
			ch = (0x0D == wParam) ? 0x0A : wParam; /* 0x0D 是回车符，0x0A 是换行符。*/ 
			VO_Interact2(pem_vob->pActiveSbdt, CMD_WGI_INSERTCHARATCP, (BYTE*)&ch, sizeof(TCHAR), &caller);
		}
		break;
	case WM_ERASEBKGND:
		return TRUE; // 消除移动窗口闪烁。
	case WM_CLOSE:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		VO_Interact0(pem->pWObject, DTR_WGI_WINDOW, &caller);
		break;
	case WM_DESTROY:
		PostQuitMessage (0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return TRUE; 
}


/**
*
* NAME: LoadBitmaps
*/
static void  LoadBitmaps(OBJECT*  This)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	TCHAR          szFilePath[MAX_PATH+1];
	TCHAR*         p;

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));

    /*- Menu Roots -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRControl_Normal.jpg"));
	pem->ArrHBITMAP[eMRControl_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRControl_FocusOver.jpg"));
	pem->ArrHBITMAP[eMRControl_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRControl_FocusOn.jpg"));
	pem->ArrHBITMAP[eMRControl_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRMenuDemo_Normal.jpg"));
	pem->ArrHBITMAP[eMRMenuDemo_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRMenuDemo_FocusOver.jpg"));
	pem->ArrHBITMAP[eMRMenuDemo_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRMenuDemo_FocusOn.jpg"));
	pem->ArrHBITMAP[eMRMenuDemo_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRHelp_Normal.jpg"));
	pem->ArrHBITMAP[eMRHelp_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRHelp_FocusOver.jpg"));
	pem->ArrHBITMAP[eMRHelp_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MRHelp_FocusOn.jpg"));
	pem->ArrHBITMAP[eMRHelp_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

    /*- Rolling Buttons for Menu -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("TopRB_Normal.jpg"));
	pem->ArrHBITMAP[eTopRB_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("TopRB_FocusOver.jpg"));
	pem->ArrHBITMAP[eTopRB_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("BottomRB_Normal.jpg"));
	pem->ArrHBITMAP[eBottomRB_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("BottomRB_FocusOver.jpg"));
	pem->ArrHBITMAP[eBottomRB_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- Button1 -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button1_Normal.jpg"));
	pem->ArrHBITMAP[eButton1_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button1_FocusOver.jpg"));
	pem->ArrHBITMAP[eButton1_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button1_FocusOn.jpg"));
	pem->ArrHBITMAP[eButton1_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button1_Active.jpg"));
	pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button1_ABSInactive.jpg"));
	pem->ArrHBITMAP[eButton1_ABSInactive_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- Button3 -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button3_Normal.jpg"));
	pem->ArrHBITMAP[eButton3_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button3_FocusOver.jpg"));
	pem->ArrHBITMAP[eButton3_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button3_FocusOn.jpg"));
	pem->ArrHBITMAP[eButton3_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button3_Active.jpg"));
	pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Button3_ABSInactive.jpg"));
	pem->ArrHBITMAP[eButton3_ABSInactive_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- Edit -*/
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Edit_Normal.jpg"));
	pem->ArrHBITMAP[eEdit_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("Edit_Active.jpg"));
	pem->ArrHBITMAP[eEdit_Active_BMP_MyDialog] = LoadPictureFile(szFilePath);


	return;
}

/**
*
* NAME: UnloadBitmaps
*/
static void  UnloadBitmaps(OBJECT*  This)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	int            i;

	for(i = 0; i < eNum_BMP_MyDialog; i++)
	{
		if(pem->ArrHBITMAP[i])
			DeleteObject(pem->ArrHBITMAP[i]);
	}

	return;
}

/**
*
* NAME: PopMenuForMRControl
* DESC: Pop menu for MRControl
*/
static void  PopMenuForMRControl(OBJECT* This, const VR* pCaller)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	INIT_WMENU      iwmu;

	memset(&iwmu, 0, sizeof(INIT_WMENU));

	iwmu.ivob.state = eVOBState_Active;
	iwmu.iwob.hInstance = g_hInstance;
	iwmu.iwob.pClassName = g_szMenuClass;
	iwmu.iwob.pWindowName = g_szMenuName;
	iwmu.CreateItems = CBF_CreateMenuItemsForMRControl;
	iwmu.DestroyItems = CBF_DestroyMenuItemsForMRControl;
	iwmu.pParent = This;
	iwmu.type = MNUT_TBLEFT;
	iwmu.width = 201;
	CalcuORACoord(pem->ArrSUB[eMRControl_MyDialog], &iwmu.uca);
	pem->pMenu = PopMenu(&iwmu, pCaller);
	pem->pPoppingMR = pem->ArrSUB[eMRControl_MyDialog];

	assert(pem->pMenu);

	return;
}


/**
*
* NAME: PopMenuForMRMenuDemo
* DESC: Pop menu for MRMenuDemo
*/
static void  PopMenuForMRMenuDemo(OBJECT* This, const VR* pCaller)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	INIT_WMENU      iwmu;
	BITMAP          bm;

	memset(&iwmu, 0, sizeof(INIT_WMENU));

	iwmu.ivob.state = eVOBState_Active;
	iwmu.iwob.hInstance = g_hInstance;
	iwmu.iwob.pClassName = g_szMenuClass;
	iwmu.iwob.pWindowName = g_szMenuName;
	iwmu.hBmpBRBNormal = pem->ArrHBITMAP[eBottomRB_Normal_BMP_MyDialog];
	iwmu.hBmpBRBFocusOn = pem->ArrHBITMAP[eBottomRB_FocusOver_BMP_MyDialog];
	iwmu.hBmpBRBFocusOver = pem->ArrHBITMAP[eBottomRB_FocusOver_BMP_MyDialog];
	iwmu.hBmpTRBNormal = pem->ArrHBITMAP[eTopRB_Normal_BMP_MyDialog];
	iwmu.hBmpTRBFocusOn = pem->ArrHBITMAP[eTopRB_FocusOver_BMP_MyDialog];
	iwmu.hBmpTRBFocusOver = pem->ArrHBITMAP[eTopRB_FocusOver_BMP_MyDialog];
	GetObject(iwmu.hBmpBRBNormal, sizeof(bm), &bm);
	iwmu.nRBHeight = bm.bmHeight;
	iwmu.CreateItems = CBF_CreateMenuItemsForMRMenuDemo;
	iwmu.DestroyItems = CBF_DestroyMenuItemsForMRMenuDemo;
	iwmu.pParent = This;
	iwmu.type = MNUT_TBLEFT;
	iwmu.width = 157;
	CalcuORACoord(pem->ArrSUB[eMRMenuDemo_MyDialog], &iwmu.uca);
	pem->pMenu = PopMenu(&iwmu, pCaller);
	pem->pPoppingMR = pem->ArrSUB[eMRMenuDemo_MyDialog];

	assert(pem->pMenu);
	
	return;
}

/**
*
* NAME: CBF_CreateMenuItemsForMRControl
* DESC: Create menu items for MRControl
*/
static OIOIC_BOOL  CBF_CreateMenuItemsForMRControl(OBJECT* pMenu, const VR* pCaller)
{
	static  TCHAR		s_str1[] = TEXT("Enable Button");
	static  TCHAR		s_str2[] = TEXT("Disable Button");

	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_VOBJECT*         pem_wmu_vob = (EM_VOBJECT*)pem_wmu->pVObject->pEM;
	EM_WOBJECT*         pem_wmu_wob = (EM_WOBJECT*)pem_wmu->pWObject->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;
	int                 i;
	TCHAR               szFilePath[MAX_PATH+1];
	TCHAR*              p;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrMI[eMIEnableButton_MyDialog]);
	CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrMI[eMIDisableButton_MyDialog]);
	
	/*- load bitmaps -*/
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIEnableButton_Normal.jpg"));
	pem->ArrMIHBITMAP[eMIEnableButton_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIEnableButton_FocusOver.jpg"));
	pem->ArrMIHBITMAP[eMIEnableButton_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);


	ivob.pSuperior = pMenu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = eVOBState_Normal;
	ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrMIHBITMAP[eMIEnableButton_Normal_BMP_MyDialog];
	ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrMIHBITMAP[eMIEnableButton_FocusOver_BMP_MyDialog];
	ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrMIHBITMAP[eMIEnableButton_FocusOver_BMP_MyDialog];
	GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
	ivob.rsc.rcouter.right = bm.bmWidth;
	ivob.rsc.rcinner.right = bm.bmWidth;
	ivob.rsc.rcinner.bottom = bm.bmHeight;
	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;
	icob.pWndHandle = &pem_wmu_wob->hWnd;

	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0,0,0);

	for(i = eMIEnableButton_MyDialog; i <= eMIDisableButton_MyDialog; i++)
	{
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.ci.rect.top = 5;
		ivob.ci.rect.right = ivob.rsc.rcouter.right - ivob.rsc.rcouter.left;
		ivob.ci.rect.bottom = ivob.rsc.rcouter.bottom - ivob.rsc.rcouter.top;
		switch(i)
		{
		case eMIEnableButton_MyDialog:
			ivob.ci.text = s_str1;
			ivob.ci.cpty = ivob.ci.clen = wcslen(s_str1);
			ivob.pPrevCodt = pem->ArrMI[eMIDisableButton_MyDialog];
			ivob.pNextCodt = pem->ArrMI[eMIDisableButton_MyDialog];
			break;
		case eMIDisableButton_MyDialog:
			ivob.ci.text = s_str2;
			ivob.ci.cpty = ivob.ci.clen = wcslen(s_str2);
			ivob.pPrevCodt = pem->ArrMI[eMIEnableButton_MyDialog];
			ivob.pNextCodt = pem->ArrMI[eMIEnableButton_MyDialog];
			break;
		default:
			assert(0);
			break;
		}

		VO_Open(pem->ArrMI[i], pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
		VO_Interact0(pem->ArrMI[i], CMD_PREPARE, pCaller);
	}
	
	pem_wmu_vob->sceneh = 2 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;
	pem_wmu_vob->pFirstSbdt = pem->ArrMI[eMIEnableButton_MyDialog];

	return TRUE;
}

/**
*
* NAME: CBF_DestroyMenuItemsForMRControl
* DESC: Destroy menu items for MRControl
*/
static OIOIC_BOOL  CBF_DestroyMenuItemsForMRControl(OBJECT* pMenu, const VR* pCaller)
{
	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;


	VO_Close(pem->ArrMI[eMIEnableButton_MyDialog], pCaller);
	DestroyObject(pem->ArrMI[eMIEnableButton_MyDialog]); 
	
	VO_Close(pem->ArrMI[eMIDisableButton_MyDialog], pCaller);
	DestroyObject(pem->ArrMI[eMIDisableButton_MyDialog]); 

	/*- unload bitmaps -*/
	DeleteObject(pem->ArrMIHBITMAP[eMIEnableButton_Normal_BMP_MyDialog]);
	DeleteObject(pem->ArrMIHBITMAP[eMIEnableButton_FocusOver_BMP_MyDialog]);

	return TRUE;
}

/**
*
* NAME: CBF_CreateMenuItemsForMRMenuDemo
* DESC: Create menu items for MRMenuDemo
*/
static OIOIC_BOOL  CBF_CreateMenuItemsForMRMenuDemo(OBJECT* pMenu, const VR* pCaller)
{
	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_VOBJECT*         pem_wmu_vob = (EM_VOBJECT*)pem_wmu->pVObject->pEM;
	EM_WOBJECT*         pem_wmu_wob = (EM_WOBJECT*)pem_wmu->pWObject->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;
	int                 i;
	TCHAR               szFilePath[MAX_PATH+1];
	TCHAR*              p;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	for(i = eMIItem0_MyDialog; i <= eMIItem50_MyDialog; i++)
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrMI[i]);
	
	/*- load bitmaps -*/
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem0_Normal.jpg"));
	pem->ArrMIHBITMAP[eMIItem0_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem0_FocusOver.jpg"));
	pem->ArrMIHBITMAP[eMIItem0_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem3_Normal.jpg"));
	pem->ArrMIHBITMAP[eMIItem3_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem3_FocusOver.jpg"));
	pem->ArrMIHBITMAP[eMIItem3_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	assert(NULL == pem->pTextPool_MRMenuDemo);
	pem->pTextPool_MRMenuDemo = (TCHAR*)calloc(51 * 15, sizeof(TCHAR)); /* 共51个菜单项，每个菜单项的标题文本空间为15个TCHAR字节。*/
	for(i = 0; i < 51; i++)
		swprintf(pem->pTextPool_MRMenuDemo+i*15, 15, TEXT("%ls%d"), TEXT("Item "), i);

	ivob.pSuperior = pMenu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = eVOBState_Normal;
	icob.pWndHandle = &pem_wmu_wob->hWnd;


	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0,0,0);
	ivob.ci.cpty = 15;

	for(i = eMIItem0_MyDialog; i <= eMIItem50_MyDialog; i++)
	{
		switch(i)
		{
		case eMIItem0_MyDialog:
			ivob.pPrevCodt = pem->ArrMI[eMIItem50_MyDialog];
			ivob.pNextCodt = pem->ArrMI[i+1];
			break;
		default:
			ivob.pPrevCodt = pem->ArrMI[i-1];
			ivob.pNextCodt = pem->ArrMI[i+1];
			break;
		}

		if(eMIItem3_MyDialog == i)
		{
			ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrMIHBITMAP[eMIItem3_Normal_BMP_MyDialog];
			ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrMIHBITMAP[eMIItem3_FocusOver_BMP_MyDialog];
			ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrMIHBITMAP[eMIItem3_FocusOver_BMP_MyDialog];
		}else
		{
			ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrMIHBITMAP[eMIItem0_Normal_BMP_MyDialog];
			ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrMIHBITMAP[eMIItem0_FocusOver_BMP_MyDialog];
			ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrMIHBITMAP[eMIItem0_FocusOver_BMP_MyDialog];
		}

		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		
		ivob.rsc.rcouter.right = bm.bmWidth;
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		
		ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
		ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

		ivob.ci.text = pem->pTextPool_MRMenuDemo + (i-eMIItem0_MyDialog)*15;
		ivob.ci.clen = wcslen(pem->pTextPool_MRMenuDemo + (i-eMIItem0_MyDialog)*15);
		ivob.ci.rect.top = 5;
		ivob.ci.rect.right = ivob.rsc.rcouter.right - ivob.rsc.rcouter.left;
		ivob.ci.rect.bottom = ivob.rsc.rcouter.bottom - ivob.rsc.rcouter.top;

		VO_Open(pem->ArrMI[i], pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
		VO_Interact0(pem->ArrMI[i], CMD_PREPARE, pCaller);
	}
	
	GetObject(pem->ArrMIHBITMAP[eMIItem0_Normal_BMP_MyDialog], sizeof(bm), &bm);
	pem_wmu_vob->sceneh = 51 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;
	pem_wmu_vob->pFirstSbdt = pem->ArrMI[eMIItem0_MyDialog];

	return TRUE;
}

/**
*
* NAME: CBF_DestroyMenuItemsForMRMenuDemo
* DESC: Destroy menu items for MRMenuDemo
*/
static OIOIC_BOOL  CBF_DestroyMenuItemsForMRMenuDemo(OBJECT* pMenu, const VR* pCaller)
{
	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;
	int                 i;

	for(i = eMIItem0_MyDialog; i <= eMIItem50_MyDialog; i++)
	{
		VO_Close(pem->ArrMI[i], pCaller);
		DestroyObject(pem->ArrMI[i]); 
	}

	/*- unload bitmaps -*/
	DeleteObject(pem->ArrMIHBITMAP[eMIItem0_Normal_BMP_MyDialog]);
	DeleteObject(pem->ArrMIHBITMAP[eMIItem0_FocusOver_BMP_MyDialog]);
	DeleteObject(pem->ArrMIHBITMAP[eMIItem3_Normal_BMP_MyDialog]);
	DeleteObject(pem->ArrMIHBITMAP[eMIItem3_FocusOver_BMP_MyDialog]);

	if(pem->pTextPool_MRMenuDemo != NULL)
	{
		free(pem->pTextPool_MRMenuDemo);
		pem->pTextPool_MRMenuDemo = NULL;
	}

	return TRUE;
}



/**
*
* NAME: CBF_CreateMenuItemsForMIItem3
* DESC: Create menu items for MIItem3
*/
static OIOIC_BOOL  CBF_CreateMenuItemsForMIItem3(OBJECT* pMenu, const VR* pCaller)
{
	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_VOBJECT*         pem_wmu_vob = (EM_VOBJECT*)pem_wmu->pVObject->pEM;
	EM_WOBJECT*         pem_wmu_wob = (EM_WOBJECT*)pem_wmu->pWObject->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;
	int                 i;
	TCHAR               szFilePath[MAX_PATH+1];
	TCHAR*              p;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	for(i = eMIItem3_0_MyDialog; i <= eMIItem3_55_MyDialog; i++)
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrMI[i]);
	
	/*- load bitmaps -*/
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem3_0_Normal.jpg"));
	pem->ArrMIHBITMAP[eMIItem3_0_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - szFilePath), TEXT("%ls"), TEXT("MIItem3_0_FocusOver.jpg"));
	pem->ArrMIHBITMAP[eMIItem3_0_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);


	assert(NULL == pem->pTextPool_MIItem3);
	pem->pTextPool_MIItem3 = (TCHAR*)calloc(56 * 15, sizeof(TCHAR)); /* 共56个菜单项，每个菜单项的标题文本空间为15个TCHAR字节。*/
	for(i = 0; i < 56; i++)
		swprintf(pem->pTextPool_MIItem3+i*15, 15, TEXT("%ls%d"), TEXT("Item3_ "), i);

	ivob.pSuperior = pMenu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = eVOBState_Normal;
	icob.pWndHandle = &pem_wmu_wob->hWnd;

	ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrMIHBITMAP[eMIItem3_0_Normal_BMP_MyDialog];
	ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrMIHBITMAP[eMIItem3_0_FocusOver_BMP_MyDialog];
	ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrMIHBITMAP[eMIItem3_0_FocusOver_BMP_MyDialog];

	GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);

	pem_wmu_vob->sceneh = 56 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;

	ivob.rsc.rcouter.right = bm.bmWidth;
	ivob.rsc.rcinner.right = bm.bmWidth;
	ivob.rsc.rcinner.bottom = bm.bmHeight;
	ivob.scenew = bm.bmWidth;
	ivob.sceneh = bm.bmHeight;
	ivob.ci.rect.right = bm.bmWidth;
	ivob.ci.rect.bottom = bm.bmHeight;
	ivob.ci.rect.top = 5;
	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0,0,0);
	ivob.ci.cpty = 15;

	for(i = eMIItem3_0_MyDialog; i <= eMIItem3_55_MyDialog; i++)
	{
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.ci.text = pem->pTextPool_MIItem3 + (i-eMIItem3_0_MyDialog)*15;
		ivob.ci.clen = wcslen(pem->pTextPool_MIItem3 + (i-eMIItem3_0_MyDialog)*15);

		switch(i)
		{
		case eMIItem3_0_MyDialog:
			ivob.pPrevCodt = pem->ArrMI[eMIItem3_55_MyDialog];
			ivob.pNextCodt = pem->ArrMI[i+1];
			break;
		default:
			ivob.pPrevCodt = pem->ArrMI[i-1];
			ivob.pNextCodt = pem->ArrMI[i+1];
			break;
		}

		VO_Open(pem->ArrMI[i], pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
		VO_Interact2(GetBN(pem->ArrMI[i], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
		VO_Interact0(pem->ArrMI[i], CMD_PREPARE, pCaller);
	}
	
	pem_wmu_vob->pFirstSbdt = pem->ArrMI[eMIItem3_0_MyDialog];

	return TRUE;
}


/**
*
* NAME: CBF_DestroyMenuItemsForMIItem3
* DESC: Destroy menu items for MIItem3
*/
static OIOIC_BOOL  CBF_DestroyMenuItemsForMIItem3(OBJECT* pMenu, const VR* pCaller)
{
	EM_WMENU*           pem_wmu = (EM_WMENU*)pMenu->pEM;
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)pem_wmu->pParent->pEM;
	int                 i;

	for(i = eMIItem3_0_MyDialog; i <= eMIItem3_55_MyDialog; i++)
	{
		VO_Close(pem->ArrMI[i], pCaller);
		DestroyObject(pem->ArrMI[i]); 
	}

	/*- unload bitmaps -*/
	DeleteObject(pem->ArrMIHBITMAP[eMIItem3_0_Normal_BMP_MyDialog]);
	DeleteObject(pem->ArrMIHBITMAP[eMIItem3_0_FocusOver_BMP_MyDialog]);

	if(pem->pTextPool_MIItem3 != NULL)
	{
		free(pem->pTextPool_MIItem3);
		pem->pTextPool_MIItem3 = NULL;
	}

	return TRUE;
}
