/**
 *
 * 文 件 名：vehicle.c
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

#include "vehicle.h"


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：vehicle_Open
*/
static RESULT  vehicle_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/**
*
* 名称：vehicle_Input
*/
static RESULT  vehicle_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：vehicle_Output
*/
static RESULT  vehicle_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：vehicle_IOput
*/
static RESULT  vehicle_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：vehicle_Interact0
*/
static RESULT  vehicle_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：vehicle_Interact1
*/
static RESULT  vehicle_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	EM_VEHICLE*   pem = (EM_VEHICLE*)This->pEM;

	switch(Act)
	{
	case GET_WEIGHT:
		assert(Cty >= sizeof(SR32)); /* 判断输出流容量够不够。*/
		*(SR32*)OStrm = pem->weight; /* 输出重量值。*/
		*pQty = sizeof(SR32); /* 输出的字节数。*/
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：vehicle_Interact2
*/
static RESULT  vehicle_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：vehicle_Interact3
*/
static RESULT  vehicle_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：vehicle_Close
*/
static RESULT  vehicle_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_vehicle
*/
void  TOG_vehicle(OBJECT* pObj)
{
	pObj->Open = vehicle_Open;
	pObj->Input = vehicle_Input;
	pObj->Output = vehicle_Output;
	pObj->IOput = vehicle_IOput;
	pObj->Interact0 = vehicle_Interact0;
	pObj->Interact1 = vehicle_Interact1;
	pObj->Interact2 = vehicle_Interact2;
	pObj->Interact3 = vehicle_Interact3;
	pObj->Close = vehicle_Close;
}

/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

