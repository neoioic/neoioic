/**
 *
 * 文 件 名：ship.c
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

#include <stdlib.h>
#include "../vehicle/vehicle.h"
#include "ship.h"


void  TOG_ship(OBJECT* pObj);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> vehicle </ibn>*/
/*<crt>*/
RESULT  CRT_ship(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  void  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  void  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  void  TOG_vehicle(OBJECT* pObj);
	extern  void  TOG_OIOIC(OBJECT* pObj);


	size_t   ux_ND = 3; 	/* ND数量。*/
	size_t   ux_BN = 3; 	/* 各ND的BN数量之和。*/
	size_t   ux_IB = 2; 	/* 各ND的IBN数量之和。*/
	size_t   ux_CS = NumCR * 6; 	/* 各ND的最少CS数量之和。*/
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_SHIP) + OIOIC_ALIGNED_SIZE(EM_VEHICLE) + OIOIC_ALIGNED_SIZE(EM_OIOIC); 	/* 各ND的EM尺寸之和。*/

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
		MLDSN    ArrMsn[2];
		BYTE*    p = pIC + sizeof(OBJECT) * ux_ND;


		/***  确定AND各元素  ***/

		/** ship **/
		pND = (OBJECT*)pIC;
		TOG_ship(pND);
		pND->MSN = MSN_SHIP;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** vehicle **/
		TOG_vehicle(++pND);
		pND->MSN = MSN_VEHICLE;
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

		/** ship **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_VEHICLE;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_VEHICLE;
		ArrMsn[1] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 2);
		p += sizeof(OBJECT*) * 2;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_SHIP);

		/** vehicle **/
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
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_VEHICLE);

		/** OIOIC **/
		++pND;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 3;
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
* 名称：ship_Open
*/
static RESULT  ship_Open(OBJECT* This, const VR* pCaller)
{
	EM_VEHICLE*		pvem = GetEMofBN(This, MSN_VEHICLE); 
	EM_SHIP*        pem = (EM_SHIP*)This->pEM;
	
	OBS_OBJECT_OPEN_;
	
	/* 在下面完成接口自己的任务。*/
	
	
	pvem->weight = 2.33f;
	pem->max_load = 5.87f;
	pem->max_velocity = 105.35f;


	return R_P;
}

/**
*
* 名称：ship_Input
*/
static RESULT  ship_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：ship_Output
*/
static RESULT  ship_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：ship_IOput
*/
static RESULT  ship_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：ship_Interact0
*/
static RESULT  ship_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：ship_Interact1
*/
static RESULT  ship_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	EM_SHIP*   pem = (EM_SHIP*)This->pEM;

	switch(Act)
	{
	case GET_MAXLOAD:
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = pem->max_load; 
		*pQty = sizeof(SR32); 
		return R_P;
	case GET_MAXVELOCITY:
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = pem->max_velocity; 
		*pQty = sizeof(SR32); 
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：ship_Interact2
*/
static RESULT  ship_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：ship_Interact3
*/
static RESULT  ship_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：ship_Close
*/
static RESULT  ship_Close(OBJECT* This, const VR* pCaller)
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
* 名称：TOG_ship
*/
void  TOG_ship(OBJECT* pObj)
{
	pObj->Open = ship_Open;
	pObj->Input = ship_Input;
	pObj->Output = ship_Output;
	pObj->IOput = ship_IOput;
	pObj->Interact0 = ship_Interact0;
	pObj->Interact1 = ship_Interact1;
	pObj->Interact2 = ship_Interact2;
	pObj->Interact3 = ship_Interact3;
	pObj->Close = ship_Close;
}

/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

