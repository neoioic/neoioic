/**
 *
 * 文 件 名：Factory.c
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

#include "Factory.h"


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：Factory_Open
*/
static RESULT  Factory_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/**
*
* 名称：Factory_Input
*/
static RESULT  Factory_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：Factory_Output
*/
static RESULT  Factory_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：Factory_IOput
*/
static RESULT  Factory_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：Factory_Interact0
*/
static RESULT  Factory_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：Factory_Interact1
*/
static RESULT  Factory_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：Factory_Interact2
*/
static RESULT  Factory_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：Factory_Interact3
*/
static RESULT  Factory_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：Factory_Close
*/
static RESULT  Factory_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_Factory
*/
void  TOG_Factory(OBJECT* pObj)
{
	pObj->Open = Factory_Open;
	pObj->Input = Factory_Input;
	pObj->Output = Factory_Output;
	pObj->IOput = Factory_IOput;
	pObj->Interact0 = Factory_Interact0;
	pObj->Interact1 = Factory_Interact1;
	pObj->Interact2 = Factory_Interact2;
	pObj->Interact3 = Factory_Interact3;
	pObj->Close = Factory_Close;
}

/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

