/**
 *
 * 文 件 名：WMenu.c
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

#include "WMenu.h"
#include "../CObject/CObject.h"


void  TOG_WMenu(OBJECT* pObj);
RESULT  WMenu_I_Open(OBJECT* This, const VR* pCaller);
RESULT  WMenu_I_Close(OBJECT* This, const VR* pCaller);
RESULT WMenu__CMD_PREPARE(OBJECT* This, const VR* pCaller);
RESULT  WMenu__CMD_INITIALIZE(OBJECT* This, const INIT_WMENU* piwmu, const VR* pCaller);
RESULT WMenu__CMD_RUN(OBJECT* This, const VR* pCaller);


static ATOM  MyRegisterClass(OBJECT* This);
static LRESULT CALLBACK CBF_WMenuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> WPanel </ibn>*/
/*<crt>*/
RESULT  CRT_WMenu(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
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
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_WMENU) + OIOIC_ALIGNED_SIZE(EM_WPANEL) + OIOIC_ALIGNED_SIZE(EM_WOBJECT)
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

		/** WMenu **/
		pND = (OBJECT*)pIC;
		TOG_WMenu(pND);
		pND->MSN = MSN_WMENU;
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

		/** WMenu **/
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
		p += OIOIC_ALIGNED_SIZE(EM_WMENU);

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
* 名称：WMenu_Open
*/
static  RESULT  WMenu_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return WMenu_I_Open(This, &caller);
}

/**
*
* 名称：WMenu_Input
*/
static  RESULT  WMenu_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：WMenu_Output
*/
static  RESULT  WMenu_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：WMenu_IOput
*/
static  RESULT  WMenu_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：WMenu_Interact0
*/
static  RESULT  WMenu_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR   caller;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		return WMenu__CMD_PREPARE(This, &caller);
	case CMD_RUN:
		return WMenu__CMD_RUN(This, &caller);
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：WMenu_Interact1
*/
static  RESULT  WMenu_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：WMenu_Interact2
*/
static  RESULT  WMenu_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_INITIALIZE:
		assert(sizeof(INIT_WMENU) == Qty);
		return WMenu__CMD_INITIALIZE(This, (INIT_WMENU*)IStrm, &caller);
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：WMenu_Interact3
*/
static  RESULT  WMenu_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：WMenu_Close
*/
static  RESULT  WMenu_Close(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

	return WMenu_I_Close(This, &caller);
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_WMenu
*/
void  TOG_WMenu(OBJECT* pObj)
{
	pObj->Open = WMenu_Open;
	pObj->Input = WMenu_Input;
	pObj->Output = WMenu_Output;
	pObj->IOput = WMenu_IOput;
	pObj->Interact0 = WMenu_Interact0;
	pObj->Interact1 = WMenu_Interact1;
	pObj->Interact2 = WMenu_Interact2;
	pObj->Interact3 = WMenu_Interact3;
	pObj->Close = WMenu_Close;
}


/*====================+ Function(s) +====================*/

/**
*
* 名称：MyRegisterClass
* 描述：
*/
static ATOM  MyRegisterClass(OBJECT* This)
{
	EM_WMENU*           pem = (EM_WMENU*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	WNDCLASS wc;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	    = (WNDPROC)CBF_WMenuProc;
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
* 名称：InitTRButton
* 描述：Initialize Top Rolling Button
*/
static void  InitTRButton(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*           pem = (EM_WMENU*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	EM_VOBJECT*         pem_vob_sbdt;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	int                 n;

	assert(pem->pTRButton != NULL);

	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	ivob.pSuperior = This;
	ivob.style |= VOBS_NOSEMIACTIVE | VOBS_YIRROLLABLE;
	ivob.state = eVOBState_Normal;

	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	ivob.rsc.rcouter.right = n;
	ivob.rsc.rcinner.right = n;
	ivob.rsc.rcinner.bottom = pem->nRBHeight;
	ivob.scenew = n;
	ivob.sceneh =  pem->nRBHeight;
	icob.pWndHandle = &pem_wob->hWnd;

	ivob.rsc.rcouter.bottom = pem->nRBHeight;
	ivob.ArrHBITMAP[eVOBState_Normal] = pem->hBmpTRBNormal;
	ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->hBmpTRBFocusOver;
	ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->hBmpTRBFocusOn;

	pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pFirstSbdt, MSN_VOBJECT);
	ivob.pPrevCodt = pem_vob_sbdt->pPrevCodt;	
	pem_vob_sbdt->pPrevCodt = pem->pTRButton;
	ivob.pNextCodt = pem_vob->pFirstSbdt;
	pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(ivob.pPrevCodt, MSN_VOBJECT);
	pem_vob_sbdt->pNextCodt = pem->pTRButton;

	VO_Open(pem->pTRButton, pCaller);
	VO_Interact2(GetBN(pem->pTRButton, MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->pTRButton, MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
	VO_Interact0(pem->pTRButton, CMD_PREPARE, pCaller);

	return;
}

/**
*
* 名称：InitBRButton
* 描述：Initialize Bottom Rolling Button
*/
static void  InitBRButton(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*           pem = (EM_WMENU*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	EM_VOBJECT*         pem_vob_sbdt;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	int                 n;

	assert(pem->pBRButton != NULL);

	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	ivob.pSuperior = This;
	ivob.style |= VOBS_NOSEMIACTIVE | VOBS_YIRROLLABLE;
	ivob.state = eVOBState_Normal;

	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	ivob.rsc.rcouter.right = n;
	ivob.rsc.rcinner.right = n;
	ivob.rsc.rcinner.bottom = pem->nRBHeight;
	ivob.scenew = n;
	ivob.sceneh =  pem->nRBHeight;
	icob.pWndHandle = &pem_wob->hWnd;

	ivob.rsc.rcouter.top = pem_vob->rsc.rcinner.bottom - pem->nRBHeight;
	ivob.rsc.rcouter.bottom =  pem_vob->rsc.rcinner.bottom;
	ivob.ArrHBITMAP[eVOBState_Normal] = pem->hBmpBRBNormal;
	ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->hBmpBRBFocusOver;
	ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->hBmpBRBFocusOn;
	
	if(pem->pTRButton != NULL)
	{
		ivob.pNextCodt = pem->pTRButton;
		pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem->pTRButton, MSN_VOBJECT);
	}else
	{
		ivob.pNextCodt = pem_vob->pFirstSbdt;
		pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pFirstSbdt, MSN_VOBJECT);
	}
	ivob.pPrevCodt = pem_vob_sbdt->pPrevCodt;
	pem_vob_sbdt->pPrevCodt = pem->pBRButton;
	pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(ivob.pPrevCodt, MSN_VOBJECT);
	pem_vob_sbdt->pNextCodt = pem->pBRButton;

	VO_Open(pem->pBRButton, pCaller);
	VO_Interact2(GetBN(pem->pBRButton, MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->pBRButton, MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);
	VO_Interact0(pem->pBRButton, CMD_PREPARE, pCaller);

	return;
}

/**
*
* 名称：DestroyTRButton
* 描述：Destroy Top Rolling Button
*/
static void  DestroyTRButton(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*         pem = (EM_WMENU*)This->pEM;
	EM_VOBJECT*       pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_VOBJECT*       pem_vob_sbdt;
	EM_VOBJECT*       pem_vob_sbdt2;

	assert(pem->pTRButton != NULL);

	if(pem_vob->pActiveSbdt == pem->pTRButton)
		pem_vob->pActiveSbdt = NULL;
	if(pem_vob->pCFDownSbdt == pem->pTRButton)
		pem_vob->pCFDownSbdt = NULL;
	if(pem_vob->pCFOnSbdt == pem->pTRButton)
		pem_vob->pCFOnSbdt = NULL;
	if(pem_vob->pCFOverSbdt == pem->pTRButton)
		pem_vob->pCFOverSbdt = NULL;
	if(pem_vob->pCFUpSbdt == pem->pTRButton)
		pem_vob->pCFUpSbdt = NULL;

	pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem->pTRButton, MSN_VOBJECT);
	pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem_vob_sbdt->pPrevCodt, MSN_VOBJECT);
	pem_vob_sbdt2->pNextCodt = pem_vob_sbdt->pNextCodt;
	pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem_vob_sbdt->pNextCodt, MSN_VOBJECT);
	pem_vob_sbdt2->pPrevCodt = pem_vob_sbdt->pPrevCodt;
	VO_Close(pem->pTRButton, pCaller);
	DestroyObject(pem->pTRButton);
	
	return;
}

/**
*
* 名称：DestroyBRButton
* 描述：Destroy Bottom Rolling Button
*/
static void  DestroyBRButton(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*         pem = (EM_WMENU*)This->pEM;
	EM_VOBJECT*       pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_VOBJECT*       pem_vob_sbdt;
	EM_VOBJECT*       pem_vob_sbdt2;

	assert(pem->pBRButton != NULL);

	if(pem_vob->pActiveSbdt == pem->pBRButton)
		pem_vob->pActiveSbdt = NULL;
	if(pem_vob->pCFDownSbdt == pem->pBRButton)
		pem_vob->pCFDownSbdt = NULL;
	if(pem_vob->pCFOnSbdt == pem->pBRButton)
		pem_vob->pCFOnSbdt = NULL;
	if(pem_vob->pCFOverSbdt == pem->pBRButton)
		pem_vob->pCFOverSbdt = NULL;
	if(pem_vob->pCFUpSbdt == pem->pBRButton)
		pem_vob->pCFUpSbdt = NULL;

	pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem->pBRButton, MSN_VOBJECT);
	pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem_vob_sbdt->pPrevCodt, MSN_VOBJECT);
	pem_vob_sbdt2->pNextCodt = pem_vob_sbdt->pNextCodt;
	pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem_vob_sbdt->pNextCodt, MSN_VOBJECT);
	pem_vob_sbdt2->pPrevCodt = pem_vob_sbdt->pPrevCodt;
	VO_Close(pem->pBRButton, pCaller);
	DestroyObject(pem->pBRButton);

	
	return;
}

/**
*
* 名称：CBF_WMenuProc
* 描述：Mesage handler for WMenu.
*/
static LRESULT CALLBACK CBF_WMenuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	VR                caller;
	OBJECT*           This;
	EM_WMENU*         pem;
	EM_VOBJECT*       pem_vob;
	EM_VOBJECT*       pem_vob_sbdt;
	EM_VOBJECT*       pem_vob_sbdt2;
	PAINTSTRUCT       ps;
	POINT             pt;
	IRRDELTA          irrd;
	BYTKTY			  qty;
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
		pem = (EM_WMENU*)This->pEM;
		caller.mr = This->OID;
		BeginPaint(hWnd, &ps);
		VO_Interact0(pem->pWPanel, CMD_WGI_PAINT, &caller);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEACTIVATE:
		return MA_NOACTIVATEANDEAT; /* 不激活菜单。*/
	case WM_MOUSEMOVE:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_WMENU*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		if(wParam != MK_LBUTTON)
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSOVERMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
			if(pem_vob->pCFOverSbdt != pem->pCFOverSbdt)
			{
				if(pem->pSubMenu)
				{
					VO_Close(pem->pSubMenu, &caller);
					DestroyObject(pem->pSubMenu);
				}

				if(pem_vob->pCFOverSbdt != NULL)
				{
					if(pem_vob->pCFOverSbdt == pem->pTRButton)
					{
						//_Debug_OutputString(TEXT("\nif(pem_vob->pCFOverSbdt == pem->pTRButton)"), 123, NULL);
						if(pem->timerid != 0)  
						{
							if(pem->rollstep < 0) /* 当前的定时器是底端滚动按钮的？*/
							{
								KillTimer(hWnd, pem->timerid);
								pem->rollstep = -pem->rollstep;
								pem->timerid = SetTimer(hWnd, 1, pem->timertov, NULL); /* nIDEvent参数为1，表示是顶端滚动按钮的定时器。*/
							}
						}else
						{
							if(pem->rollstep < 0)
								pem->rollstep = -pem->rollstep;
							
							if(NULL == pem->pBRButton)
							{
								CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pBRButton);
								InitBRButton(This, &caller);
								VO_Interact0(pem->pWPanel, CMD_WGI_REPAINT, &caller);
							}
							
							pem->timerid = SetTimer(hWnd, 1, pem->timertov, NULL); /* nIDEvent参数为1，表示是顶端滚动按钮的定时器。*/
						}
					}else if(pem_vob->pCFOverSbdt == pem->pBRButton)
					{
						if(pem->timerid != 0)  
						{
							if(pem->rollstep > 0)/* 当前的定时器是顶端滚动按钮的？*/
							{
								KillTimer(hWnd, pem->timerid);
								pem->rollstep = -pem->rollstep;
								pem->timerid = SetTimer(hWnd, 2, pem->timertov, NULL); /* nIDEvent参数为2，表示是底端滚动按钮的定时器。*/
							}
						}else
						{
							if(pem->rollstep > 0)
								pem->rollstep = -pem->rollstep;
							
							if(NULL == pem->pTRButton)
							{
								CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pTRButton);
								InitTRButton(This, &caller);
								VO_Interact0(pem->pWPanel, CMD_WGI_REPAINT, &caller);
							}
							pem->timerid = SetTimer(hWnd, 2, pem->timertov, NULL); /* nIDEvent参数为2，表示是底端滚动按钮的定时器。*/
						}
					}else 
					{
						if(pem->timerid != 0)  
						{
							KillTimer(hWnd, pem->timerid);
							pem->timerid = 0;
						}
						
						if(pem->pTRButton != NULL || pem->pBRButton != NULL)
						{
							irrd.dx = 0;
							pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pCFOverSbdt, MSN_VOBJECT);
							if(pem->pTRButton != NULL)
							{
								pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem->pTRButton, MSN_VOBJECT);
								if(IsInter2Rects(&pem_vob_sbdt->rsc.rcouter, &pem_vob_sbdt2->rsc.rcouter, NULL))
								{
									if(NULL == pem->pBRButton)
									{
										CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pBRButton);
										InitBRButton(This, &caller);
									}
									irrd.dy = pem_vob_sbdt2->rsc.rcouter.bottom - pem_vob_sbdt->rsc.rcouter.top;
									VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
									if(0 == pem_vob->oy_irr)
									{
										DestroyTRButton(This, &caller);
										VO_Interact0(pem->pWPanel, CMD_WGI_REPAINT, &caller);
									}
								}else if(pem->pBRButton != NULL)
								{
									pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem->pBRButton, MSN_VOBJECT);
									if(IsInter2Rects(&pem_vob_sbdt->rsc.rcouter, &pem_vob_sbdt2->rsc.rcouter, NULL))
									{
										irrd.dy = pem_vob_sbdt2->rsc.rcouter.top - pem_vob_sbdt->rsc.rcouter.bottom;
										VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
									}
								}
							}else  /* pem->pBRButton != NULL */
							{
								pem_vob_sbdt2 = (EM_VOBJECT*)GetEMofBN(pem->pBRButton, MSN_VOBJECT);
								if(IsInter2Rects(&pem_vob_sbdt->rsc.rcouter, &pem_vob_sbdt2->rsc.rcouter, NULL))
								{
									irrd.dy = pem_vob_sbdt2->rsc.rcouter.top - pem_vob_sbdt->rsc.rcouter.bottom;
									CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pTRButton);
									InitTRButton(This, &caller);
									VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
								}
							}		
						}
						VO_Interact3(pem->pParent, MSG_WGI_MENUITEMFOCUSOVER, (BYTE*)&pem_vob->pCFOverSbdt, sizeof(OBJECT*), (BYTE*)&pem->pSubMenu, sizeof(OBJECT*), &qty, &caller);
					}
				}
				
				pem->pCFOverSbdt = pem_vob->pCFOverSbdt;
			}
		}else
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSONMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
		}
		break;
	case WM_LBUTTONDOWN:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_WMENU*)This->pEM;

		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);

		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSDOWN, (BYTE*)&pt, sizeof(POINT), &caller);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSON, (BYTE*)&pt, sizeof(POINT), &caller);

		if(pem_vob->pCFDownSbdt != NULL)
		{
		}

		break;
	case WM_LBUTTONUP:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_WMENU*)This->pEM;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		caller.mr = This->OID;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSUP, (BYTE*)&pt, sizeof(POINT), &caller);
		break;
	case WM_KEYDOWN:
		//This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	case WM_CHAR:
		//This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	case WM_TIMER:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_WMENU*)This->pEM;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		caller.mr = This->OID;

		irrd.dx = 0;
		irrd.dy = pem->rollstep;
		n = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top - pem_vob->sceneh;
	
		if(pem->rollstep > 0) /* 顶端滚动按钮的定时器？*/
		{
			if(pem_vob->oy_irr + irrd.dy >= 0)
			{
				DestroyTRButton(This, &caller);
				KillTimer(hWnd, pem->timerid);
				pem->timerid = 0;

				VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
				/* 因为之前的一些当前焦点事件下级对象（如当前焦点OVER下级对象、当前焦点ON下级对象等等）
				就是这个滚动按钮对象，所以销毁滚动按钮后，需要触发一次焦点移动事件，更新当前焦点事件下级对象。*/
				GetCursorPos(&pt);
				SetCursorPos(pt.x, pt.y);
				break;
			}
		}else if(pem_vob->oy_irr + irrd.dy <= n)  /* 否则就是底端滚动按钮的定时器。*/
		{
			DestroyBRButton(This, &caller);
			KillTimer(hWnd, pem->timerid);
			pem->timerid = 0;

			VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
            /* 因为之前的一些当前焦点事件下级对象（如当前焦点OVER下级对象、当前焦点ON下级对象等等）
			就是这个滚动按钮对象，所以销毁滚动按钮后，需要触发一次焦点移动事件，更新当前焦点事件下级对象。*/
			GetCursorPos(&pt);
			SetCursorPos(pt.x, pt.y);
			break;
		}

		VO_Interact2(pem->pVObject, CMD_WGI_ROLLIR, (BYTE*)&irrd, sizeof(IRRDELTA), &caller);
		break;
	case WM_ERASEBKGND:
		return TRUE; // 消除移动窗口闪烁。
	case WM_CLOSE:
		This = (OBJECT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);   
		pem = (EM_WMENU*)This->pEM;
		caller.mr = This->OID;
		if(pem->timerid != 0)
			KillTimer(hWnd, pem->timerid);
		VO_Interact0(pem->pWObject, DTR_WGI_WINDOW, &caller);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return TRUE; 
}

/*=======================================================*/

/**
*
* NAME: WMenu_I_Open
*/
RESULT  WMenu_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*      pem = (EM_WMENU*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC);
		pem->pVObject = GetBN(This, MSN_VOBJECT);
		pem->pWObject = GetBN(This, MSN_WOBJECT);
		pem->pWPanel = GetBN(This, MSN_WPANEL);

		return RP_RCONE;
	}
	
	return R_P;
}


/**
*
* NAME: WMenu_I_Close
*/
RESULT  WMenu_I_Close(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*      pem = (EM_WMENU*)This->pEM;
	EM_WOBJECT*    pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	
	if(0 == This->RefCnt)
	{
		if(pem->pSubMenu)
		{
			VO_Close(pem->pSubMenu, pCaller);
			DestroyObject(pem->pSubMenu);
		}

		if(pem->pTRButton)
			DestroyTRButton(This, pCaller);
		
		if(pem->pBRButton)
			DestroyBRButton(This, pCaller);

		SendMessage(pem_wob->hWnd, WM_CLOSE, 0, 0);
		pem->DestroyItems(This, pCaller);
		return RP_RCZERO;
	}


	return R_P;
}

/**
*
* NAME: WMenu__CMD_INITIALIZE
*/
RESULT  WMenu__CMD_INITIALIZE(OBJECT* This, const INIT_WMENU* piwmu, const VR* pCaller)
{
	EM_WMENU*        pem = (EM_WMENU*)This->pEM;
	OBJECT*          pObj;

	pObj = GetBN(This, MSN_VOBJECT);
	VO_Interact2(pObj, CMD_INITIALIZE, (BYTE*)&piwmu->ivob, sizeof(INIT_VOBJECT), pCaller);
	pObj = GetBN(This, MSN_WOBJECT);
	VO_Interact2(pObj, CMD_INITIALIZE, (BYTE*)&piwmu->iwob, sizeof(INIT_WOBJECT), pCaller);

	pem->pParent = piwmu->pParent;
	pem->nRBHeight = piwmu->nRBHeight;
	pem->uca = piwmu->uca;
	pem->type = piwmu->type;
	pem->width = piwmu->width;
	pem->hBmpBRBFocusOn = piwmu->hBmpBRBFocusOn;
	pem->hBmpBRBFocusOver = piwmu->hBmpBRBFocusOver;
	pem->hBmpBRBNormal = piwmu->hBmpBRBNormal;
	pem->hBmpTRBFocusOn = piwmu->hBmpTRBFocusOn;
	pem->hBmpTRBFocusOver = piwmu->hBmpTRBFocusOver;
	pem->hBmpTRBNormal = piwmu->hBmpTRBNormal;
	pem->timertov = piwmu->timertov != 0 ? piwmu->timertov : 100;
	pem->rollstep = piwmu->rollstep != 0 ? piwmu->rollstep : 10;
	pem->CreateItems = piwmu->CreateItems;
	pem->DestroyItems = piwmu->DestroyItems;
	
	return R_P;
}

/**
*
* NAME: WMenu__CMD_PREPARE
*/
RESULT WMenu__CMD_PREPARE(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*        pem = (EM_WMENU*)This->pEM;
	EM_VOBJECT*      pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_WOBJECT*      pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	EM_WOBJECT*      pem_wob_par;
	EM_VOBJECT*      pem_vob_sbdt;
	OBJECT*          pObj;
	int              n, m, k, w, h;


	MyRegisterClass(This);


/*>>> 不调用基节点 WObject 的 CRT_WGI_WINDOW 行为创建窗口，单独实现。*/

	pem_wob_par = (EM_WOBJECT*)GetEMofBN(pem->pParent, MSN_WOBJECT);
	pem_wob->hWnd = CreateWindowEx(0, pem_wob->pClassName, pem_wob->pWindowName, WS_POPUP, 0, 0, 0, 0, 
		pem_wob_par->hWnd, NULL, pem_wob->hInstance, NULL);
	
	if(NULL == pem_wob->hWnd)
		return R_N;
	
	pem_vob->pWndHandle = &pem_wob->hWnd;
	SetWindowLongPtr(pem_wob->hWnd, GWLP_USERDATA, (LONG_PTR)This->po_AND);

/* 不调用基节点 WObject 的 CRT_WGI_WINDOW 行为创建窗口，单独实现。<<<*/

	
	pem->CreateItems(This, pCaller);
	assert(pem_vob->pFirstSbdt);


	if(0 == pem_vob->rsc.rcouter.bottom
		&& 0 == pem_vob->rsc.rcouter.left
		&& 0 == pem_vob->rsc.rcouter.right
		&& 0 == pem_vob->rsc.rcouter.top)
	{
		w = GetSystemMetrics(SM_CXSCREEN); 
		h = GetSystemMetrics(SM_CYSCREEN);
		
	
		/* 计算菜单高度（用变量n保存）：*/

		n = h - pem->uca.bottom;
		m = n > pem->uca.top ? n : pem->uca.top;
		n = 0;
		pObj = pem_vob->pFirstSbdt;
		do{
			pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pObj, MSN_VOBJECT);
			n += pem_vob_sbdt->rsc.rcouter.bottom - pem_vob_sbdt->rsc.rcouter.top;
			if(MNUT_TBLEFT == pem->type || MNUT_TBRIGHT == pem->type)
			{
				if(n > m)
				{
					n = m;
					assert(NULL == pem->pBRButton);
					CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pBRButton);
					break;
				}
			}else
			{
				if(n > h)
				{
					n = h;
					assert(NULL == pem->pBRButton);
					CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->pBRButton);
					break;
				}
			}
			pObj = pem_vob_sbdt->pNextCodt;
		}while(pObj != pem_vob->pFirstSbdt);
		
	
		/* 确定菜单的位置：*/

		if(MNUT_TBLEFT == pem->type)
		{
			m = h - pem->uca.bottom;
			if(n <= m)
				pem_vob->rsc.rcouter.top = pem->uca.bottom;	
			else
				pem_vob->rsc.rcouter.top = pem->uca.top - n;

			pem_vob->rsc.rcouter.left = pem->uca.left;
			pem_vob->rsc.rcouter.right = pem_vob->rsc.rcouter.left + pem->width;
			pem_vob->rsc.rcouter.bottom = pem_vob->rsc.rcouter.top + n;
			
			if(pem_vob->rsc.rcouter.left < 0) /* 菜单超出桌面的左边缘？*/
			{
				m = -pem_vob->rsc.rcouter.left;
				pem_vob->rsc.rcouter.right += m;
				pem_vob->rsc.rcouter.left = 0;
			}else if(pem_vob->rsc.rcouter.right > w && pem_vob->rsc.rcouter.left > 0) /* 菜单超出桌面的右边缘，并且菜单左边距桌面左边缘还有一定距离？*/
			{
				k = pem_vob->rsc.rcouter.right - w;
				m = k > pem_vob->rsc.rcouter.left ? pem_vob->rsc.rcouter.left : k;
				pem_vob->rsc.rcouter.left -= m;
				pem_vob->rsc.rcouter.right -= m;
			}

		}else if(MNUT_TBRIGHT == pem->type)
		{
			m = h - pem->uca.bottom;
			if(n <= m)
				pem_vob->rsc.rcouter.top = pem->uca.bottom;	
			else
				pem_vob->rsc.rcouter.top = pem->uca.top - n;

			pem_vob->rsc.rcouter.right = pem->uca.right;
			pem_vob->rsc.rcouter.left = pem_vob->rsc.rcouter.right - pem->width;
			pem_vob->rsc.rcouter.bottom = pem_vob->rsc.rcouter.top + n;
			
			if(pem_vob->rsc.rcouter.right > w) /* 菜单超出桌面的右边缘？*/
			{
				m = pem_vob->rsc.rcouter.right - w;
				pem_vob->rsc.rcouter.right -= m;
				pem_vob->rsc.rcouter.left -= m;
			}else if(pem_vob->rsc.rcouter.left < 0 && pem_vob->rsc.rcouter.right < w) /* 菜单超出桌面的左边缘，并且菜单右边距桌面右边缘还有一定距离？*/
			{
				k = w - pem_vob->rsc.rcouter.right;
				m = k > -pem_vob->rsc.rcouter.left ? -pem_vob->rsc.rcouter.left : k;
				pem_vob->rsc.rcouter.left += m;
				pem_vob->rsc.rcouter.right += m;
			}
		}else if(MNUT_LRTOP == pem->type)
		{
			if(n <= h)
			{
				pem_vob->rsc.rcouter.top = 	h - pem->uca.top > n ? pem->uca.top : h - n;
				pem_vob->rsc.rcouter.bottom = n;
			}else
			{
				pem_vob->rsc.rcouter.top = 0;
				pem_vob->rsc.rcouter.bottom = h;
			}

			m = w - pem->uca.right;
			if(pem->width < m || pem->uca.left < m) /* 判断是否需要改为左贴近。*/
			{
				pem_vob->rsc.rcouter.left = pem->uca.right;
				pem_vob->rsc.rcouter.right = pem_vob->rsc.rcouter.left + pem->width;
			}else /* 需要改为左贴近。*/
			{
				pem_vob->rsc.rcouter.left = pem->uca.left - pem->width;
				pem_vob->rsc.rcouter.right = pem->uca.right;
			}
		}else if(MNUT_LRBOTTOM == pem->type)
		{
			if(n <= h)
			{
				pem_vob->rsc.rcouter.top = pem->uca.bottom > n ? pem->uca.bottom - n : 0;
				pem_vob->rsc.rcouter.bottom = pem_vob->rsc.rcouter.top + n;
			}else
			{
				pem_vob->rsc.rcouter.top = 0;
				pem_vob->rsc.rcouter.bottom = h;
			}

			m = w - pem->uca.right;
			if(pem->width < m || pem->uca.left < m) /* 判断是否需要改为左贴近。*/
			{
				pem_vob->rsc.rcouter.left = pem->uca.right;
				pem_vob->rsc.rcouter.right = pem_vob->rsc.rcouter.left + pem->width;
			}else /* 需要改为左贴近。*/
			{
				pem_vob->rsc.rcouter.left = pem->uca.left - pem->width;
				pem_vob->rsc.rcouter.right = pem->uca.left;
			}
		}
	}
	
	if(0 == pem_vob->rsc.rcinner.bottom
		&& 0 == pem_vob->rsc.rcinner.left
		&& 0 == pem_vob->rsc.rcinner.right
		&& 0 == pem_vob->rsc.rcinner.top)
	{
		pem_vob->rsc.rcinner.top = 0;
		pem_vob->rsc.rcinner.left = 0;
		pem_vob->rsc.rcinner.right = pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left;
		pem_vob->rsc.rcinner.bottom = pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top;
	}
	
	if(0 == pem_vob->scenew)
		pem_vob->scenew = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	if(0 == pem_vob->sceneh)
		pem_vob->sceneh = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;


	if(pem->pTRButton != NULL)
		InitTRButton(This, pCaller);
	if(pem->pBRButton != NULL)
		InitBRButton(This, pCaller);

	SetWindowPos(pem_wob->hWnd, HWND_TOPMOST, 
		pem_vob->rsc.rcouter.left, pem_vob->rsc.rcouter.top, 
		pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left, 
		pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top,
		SWP_HIDEWINDOW | SWP_NOACTIVATE);

	VO_Interact0(pem->pVObject, CMD_PREPARE, pCaller);
	
	return R_P;
}


/**
*
* NAME: WMenu__CMD_RUN
*/
RESULT WMenu__CMD_RUN(OBJECT* This, const VR* pCaller)
{
	EM_WMENU*        pem = (EM_WMENU*)This->pEM;
    EM_WOBJECT*      pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	
	ShowWindow(pem_wob->hWnd, SW_SHOWNOACTIVATE);

	return R_P;
}

/*=======================================================*/

/**
*
* 需求编号：	
* 需求功能：	创建菜单
* 函    数：	OBJECT*  PopMenu(const INIT_WMENU* piwmu, const VR* pCaller)
* 描    述：	创建菜单，SE函数。
* 参    数：	piwmu - [IN] 菜单的初始化信息。
* 返    回：	菜单对象指针
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.0
* 更新日期：	20111222
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
OBJECT*  PopMenu(const INIT_WMENU* piwmu, const VR* pCaller)
{
	RESULT       r;
    OBJECT*      pMenu;

	r = CreateObject(MSN_WMENU, 0, 0, 1, &pMenu);
	if(RN(r))
		return  NULL;

    r = VO_Open(pMenu, pCaller);
	assert(RP(r));

	VO_Interact2(pMenu, CMD_INITIALIZE, (BYTE*)piwmu, sizeof(INIT_WMENU), pCaller);
	VO_Interact0(pMenu, CMD_PREPARE, pCaller);
	VO_Interact0(pMenu, CMD_RUN, pCaller);

	return pMenu;
}

