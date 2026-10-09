/**
 *
 * 文 件 名：amphicar.c
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
#include "../car/car.h"
#include "../ship/ship.h"
#include "amphicar.h"


void  TOG_amphicar(OBJECT* pObj);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> car, ship </ibn>*/
/*<crt>*/
RESULT  CRT_amphicar(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  void  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  void  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  void  TOG_car(OBJECT* pObj);
	extern  void  TOG_vehicle(OBJECT* pObj);
	extern  void  TOG_OIOIC(OBJECT* pObj);
	extern  void  TOG_ship(OBJECT* pObj);


	size_t   ux_ND = 5; 	/* ND数量。*/
	size_t   ux_BN = 9; 	/* 各ND的BN数量之和。*/
	size_t   ux_IB = 5; 	/* 各ND的IBN数量之和。*/
	size_t   ux_CS = NumCR * 12; 	/* 各ND的最少CS数量之和。*/
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_CAR) + OIOIC_ALIGNED_SIZE(EM_VEHICLE) + OIOIC_ALIGNED_SIZE(EM_OIOIC)
		 + OIOIC_ALIGNED_SIZE(EM_SHIP); 	/* 各ND的EM尺寸之和。*/

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

		/** amphicar **/
		pND = (OBJECT*)pIC;
		TOG_amphicar(pND);
		pND->MSN = MSN_AMPHICAR;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** car **/
		TOG_car(++pND);
		pND->MSN = MSN_CAR;
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

		/** ship **/
		TOG_ship(++pND);
		pND->MSN = MSN_SHIP;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;


		/***  初始化各ND  ***/

		/** amphicar **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_CAR;
		ArrMsn[1] = MSN_SHIP;
		InitAIBofND(pND, ArrMsn, 2);
		p += sizeof(OBJECT*) * 2;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_CAR;
		ArrMsn[1] = MSN_VEHICLE;
		ArrMsn[2] = MSN_OIOIC;
		ArrMsn[3] = MSN_SHIP;
		InitABNofND(pND, ArrMsn, 4);
		p += sizeof(OBJECT*) * 4;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/** car **/
		++pND;

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
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_CAR);

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
		pND->NCS = NumCR * 3;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_VEHICLE);

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

		/** ship **/
		++pND;

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
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_SHIP);
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
* 名称：amphicar_Open
*/
static RESULT  amphicar_Open(OBJECT* This, const VR* pCaller)
{
	EM_VEHICLE*		pvem = GetEMofBN(This, MSN_VEHICLE); 
	EM_CAR*			pcem = GetEMofBN(This, MSN_CAR); 
	EM_SHIP*		psem = GetEMofBN(This, MSN_SHIP); 

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	pvem->weight = 4.06f;
	pcem->max_load = 10.93f;
	pcem->max_velocity = 215.00f;
	psem->max_load = 12.5f;
	psem->max_velocity = 138.00f;


	return R_P;
}

/**
*
* 名称：amphicar_Input
*/
static RESULT  amphicar_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：amphicar_Output
*/
static RESULT  amphicar_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：amphicar_IOput
*/
static RESULT  amphicar_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：amphicar_Interact0
*/
static RESULT  amphicar_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：amphicar_Interact1
*/
static RESULT  amphicar_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	EM_CAR*			pcem = GetEMofBN(This, MSN_CAR); 
	EM_SHIP*		psem = GetEMofBN(This, MSN_SHIP); 

	switch(Act)
	{
	case GET_TMAXLOAD: /* 获取陆上（terrestrial）最大载重量。*/
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = pcem->max_load; 
		*pQty = sizeof(SR32); 
		return R_P;
	case GET_TMAXVELOCITY: /* 获取陆上最大速度。*/
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = pcem->max_velocity; 
		*pQty = sizeof(SR32); 
		return R_P;
	case GET_AMAXLOAD: /* 获取水上（aquatic）最大载重量。*/
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = psem->max_load; 
		*pQty = sizeof(SR32); 
		return R_P;
	case GET_AMAXVELOCITY: /* 获取水上最大速度。*/
		assert(Cty >= sizeof(SR32));
		*(SR32*)OStrm = psem->max_velocity; 
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
* 名称：amphicar_Interact2
*/
static RESULT  amphicar_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：amphicar_Interact3
*/
static RESULT  amphicar_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：amphicar_Close
*/
static RESULT  amphicar_Close(OBJECT* This, const VR* pCaller)
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
* 名称：TOG_amphicar
*/
void  TOG_amphicar(OBJECT* pObj)
{
	pObj->Open = amphicar_Open;
	pObj->Input = amphicar_Input;
	pObj->Output = amphicar_Output;
	pObj->IOput = amphicar_IOput;
	pObj->Interact0 = amphicar_Interact0;
	pObj->Interact1 = amphicar_Interact1;
	pObj->Interact2 = amphicar_Interact2;
	pObj->Interact3 = amphicar_Interact3;
	pObj->Close = amphicar_Close;
}

/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

