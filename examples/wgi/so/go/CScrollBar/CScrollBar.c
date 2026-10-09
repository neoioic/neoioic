/**
 *
 * 文 件 名：CScrollBar.c
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

#include "CScrollBar.h"
#include "../CObject/CObject.h"


void  TOG_CScrollBar(OBJECT* pObj);

RESULT  CScrollBar_I_Open(OBJECT* This, const VR* pCaller);
RESULT  CScrollBar_I_Close(OBJECT* This, const VR* pCaller);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> CObject </ibn>*/
/*<crt>*/
RESULT  CRT_CScrollBar(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  void  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  void  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  void  TOG_CObject(OBJECT* pObj);
	extern  void  TOG_VObject(OBJECT* pObj);
	extern  void  TOG_OIOIC(OBJECT* pObj);


	size_t   ux_ND = 4; 	/* ND数量。*/
	size_t   ux_BN = 6; 	/* 各ND的BN数量之和。*/
	size_t   ux_IB = 3; 	/* 各ND的IBN数量之和。*/
	size_t   ux_CS = NumCR * 10; 	/* 各ND的最少CS数量之和。*/
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_CSCROLLBAR) + OIOIC_ALIGNED_SIZE(EM_COBJECT) + OIOIC_ALIGNED_SIZE(EM_VOBJECT)
		 + OIOIC_ALIGNED_SIZE(EM_OIOIC); 	/* 各ND的EM尺寸之和。*/

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
		MLDSN    ArrMsn[3];
		BYTE*    p = pIC + sizeof(OBJECT) * ux_ND;


		/***  确定AND各元素  ***/

		/** CScrollBar **/
		pND = (OBJECT*)pIC;
		TOG_CScrollBar(pND);
		pND->MSN = MSN_CSCROLLBAR;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** CObject **/
		TOG_CObject(++pND);
		pND->MSN = MSN_COBJECT;
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

		/** CScrollBar **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		ArrMsn[1] = MSN_VOBJECT;
		ArrMsn[2] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 3);
		p += sizeof(OBJECT*) * 3;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_CSCROLLBAR);

		/** CObject **/
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
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_COBJECT);

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
		pND->NCS = NumCR * 3;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_VOBJECT);

		/** OIOIC **/
		++pND;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 4;
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
* 名称：CScrollBar_Open
*/
static  RESULT  CScrollBar_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;


	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return CScrollBar_I_Open(This, &caller);
}

/**
*
* 名称：CScrollBar_Input
*/
static  RESULT  CScrollBar_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：CScrollBar_Output
*/
static  RESULT  CScrollBar_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：CScrollBar_IOput
*/
static  RESULT  CScrollBar_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：CScrollBar_Interact0
*/
static  RESULT  CScrollBar_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：CScrollBar_Interact1
*/
static  RESULT  CScrollBar_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：CScrollBar_Interact2
*/
static  RESULT  CScrollBar_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：CScrollBar_Interact3
*/
static  RESULT  CScrollBar_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：CScrollBar_Close
*/
static  RESULT  CScrollBar_Close(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;


	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

	return CScrollBar_I_Close(This, &caller);
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_CScrollBar
*/
void  TOG_CScrollBar(OBJECT* pObj)
{
	pObj->Open = CScrollBar_Open;
	pObj->Input = CScrollBar_Input;
	pObj->Output = CScrollBar_Output;
	pObj->IOput = CScrollBar_IOput;
	pObj->Interact0 = CScrollBar_Interact0;
	pObj->Interact1 = CScrollBar_Interact1;
	pObj->Interact2 = CScrollBar_Interact2;
	pObj->Interact3 = CScrollBar_Interact3;
	pObj->Close = CScrollBar_Close;
}


/*====================+ Function(s) +====================*/
/* ... */

/*=======================================================*/

/**
*
* NAME: CScrollBar_I_Open
*/
RESULT  CScrollBar_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_CSCROLLBAR*      pem = (EM_CSCROLLBAR*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC);
		pem->pVObject = GetBN(This, MSN_VOBJECT);
		pem->pCObject = GetBN(This, MSN_COBJECT);

		return RP_RCONE;
	}
	
	return R_P;
}

/**
*
* NAME: CScrollBar_I_Close
*/
RESULT  CScrollBar_I_Close(OBJECT* This, const VR* pCaller)
{
	
	if(0 == This->RefCnt)
	{
		return RP_RCZERO;
	}
	
	return R_P;
}

