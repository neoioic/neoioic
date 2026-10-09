/**
 *
 * 文 件 名：MyDialog_InitSub.c
 *
 * 描    述：初始化 MyDialog 的各级下级对象的 .c 文件。
 *
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 *
 * 创建日期：
 *
 * 备    注：InitSub - initialize subordinate
 *
 *
 * * 维护历史 *
 *
 *   <日期>                <修改者>
 *   <修改内容...>
 *
 **/


#include "MyDialog_InitSub.h"
#include "../CObject/CObject.h"
#include "../CEdit/CEdit.h"


extern  HBITMAP     g_ArrHBITMAP[eNum_BMP];


/**
*
* NAME: MyDialog_InitSub_Button
*/
void  MyDialog_InitSub_Button(OBJECT* This, ESMYDIALOG  es, const VR* pCaller)
{
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	ivob.pSuperior = This;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = eVOBState_Normal;

	switch(es)
	{
	case eTRCClose_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = g_ArrHBITMAP[eTRCClose_Normal_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = g_ArrHBITMAP[eTRCClose_FocusOver_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = g_ArrHBITMAP[eTRCClose_FocusOn_BMP];
		ivob.ArrHBITMAP[eVOBState_Active] = g_ArrHBITMAP[eTRCClose_Normal_BMP];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_TRCCLOSE_L;
		ivob.rsc.rcouter.top = MYDIALOG_TRCCLOSE_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eEdit_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eMRControl_MyDialog];
		break;
	case eMRControl_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eMRControl_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eMRControl_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eMRControl_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eMRControl_FocusOn_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRCONTROL_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRCONTROL_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eTRCClose_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eMRMenuDemo_MyDialog];
		break;
	case eMRMenuDemo_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eMRMenuDemo_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eMRMenuDemo_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eMRMenuDemo_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eMRMenuDemo_FocusOn_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRMENUDEMO_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRMENUDEMO_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eMRControl_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eMRHelp_MyDialog];
		break;
	case eMRHelp_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eMRHelp_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eMRHelp_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eMRHelp_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eMRHelp_FocusOn_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRHELP_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRHELP_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eMRMenuDemo_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton1_MyDialog];
		break;
	case eButton1_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eButton1_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eButton1_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog];//pem->ArrHBITMAP[eButton1_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_SemiActive] = pem->ArrHBITMAP[eButton1_ABSInactive_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON1_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON1_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eMRHelp_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton2_MyDialog];
		break;
	case eButton2_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = g_ArrHBITMAP[eButton2_Normal_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = g_ArrHBITMAP[eButton2_FocusOver_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = g_ArrHBITMAP[eButton2_Active_BMP];//g_ArrHBITMAP[eButton2_FocusOn_BMP];
		ivob.ArrHBITMAP[eVOBState_Active] = g_ArrHBITMAP[eButton2_Active_BMP];
		ivob.ArrHBITMAP[eVOBState_SemiActive] = g_ArrHBITMAP[eButton2_ABSInactive_BMP];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON2_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON2_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 4;
		ivob.rsc.rcinner.top = 4;
		ivob.rsc.rcinner.right = bm.bmWidth - 4;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 4;
		ivob.pPrevCodt = pem->ArrSUB[eButton1_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton3_MyDialog];
		break;
	case eButton3_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eButton3_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eButton3_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog];//pem->ArrHBITMAP[eButton3_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_SemiActive] = pem->ArrHBITMAP[eButton3_ABSInactive_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON3_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON3_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 6;
		ivob.rsc.rcinner.top = 6;
		ivob.rsc.rcinner.right = bm.bmWidth - 6;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 6;
		ivob.pPrevCodt = pem->ArrSUB[eButton2_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eEdit_MyDialog];
		break;
	default:
		assert(0);
		break;
	}

	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.pWndHandle = &pem_wob->hWnd;

	VO_Open(pem->ArrSUB[es], pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
	VO_Interact0(pem->ArrSUB[es], CMD_PREPARE, pCaller);

	return;
}


/**
*
* NAME: MyDialog_InitSub_Edit
*/
void  MyDialog_InitSub_Edit(OBJECT* This, ESMYDIALOG  es, const VR* pCaller)
{
	EM_MYDIALOG*        pem = (EM_MYDIALOG*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	INIT_CEDIT          iced;
	BITMAP              bm;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));
	memset(&iced, 0, sizeof(INIT_CEDIT));

	ivob.pSuperior = This;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = eVOBState_Normal;

	switch(es)
	{
	case eEdit_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eEdit_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eEdit_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eEdit_Active_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eEdit_Active_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_EDIT_L;
		ivob.rsc.rcouter.top = MYDIALOG_EDIT_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 6;
		ivob.rsc.rcinner.top = 7;
		ivob.rsc.rcinner.right = bm.bmWidth - 9;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 6;
		ivob.pPrevCodt = pem->ArrSUB[eButton3_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eTRCClose_MyDialog];
		wcscpy(pem->edttext, TEXT("0\n1\n2"));
		iced.ti.text = pem->edttext;
		iced.ti.cpty = sizeof(pem->edttext) / sizeof(TCHAR);
		iced.ti.clen = wcslen(pem->edttext);
		iced.format |= ETF_LEFT;//ETF_HCENTER | ETF_VCENTER;
		break;
	default:
		assert(0);
		break;
	}

	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.pWndHandle = &pem_wob->hWnd;

	VO_Open(pem->ArrSUB[es], pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
	VO_Interact2(pem->ArrSUB[es], CMD_INITIALIZE, (BYTE*)&iced, sizeof(INIT_CEDIT), pCaller);
	VO_Interact0(pem->ArrSUB[es], CMD_PREPARE, pCaller);

	return;
}