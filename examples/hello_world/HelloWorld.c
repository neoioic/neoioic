/**
 *
 * 文 件 名：HelloWorld.c
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

#include "HelloWorld.h"


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：HelloWorld_Open
*/
static RESULT  HelloWorld_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/**
*
* 名称：HelloWorld_Input
*/
static RESULT  HelloWorld_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：HelloWorld_Output
*/
static RESULT  HelloWorld_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：HelloWorld_IOput
*/
static RESULT  HelloWorld_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：HelloWorld_Interact0
*/
static RESULT  HelloWorld_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：HelloWorld_Interact1
*/
static RESULT  HelloWorld_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：HelloWorld_Interact2
*/
static RESULT  HelloWorld_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：HelloWorld_Interact3
*/
static RESULT  HelloWorld_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：HelloWorld_Close
*/
static RESULT  HelloWorld_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_HelloWorld
*/
void  TOG_HelloWorld(OBJECT* pObj)
{
	pObj->Open = HelloWorld_Open;
	pObj->Input = HelloWorld_Input;
	pObj->Output = HelloWorld_Output;
	pObj->IOput = HelloWorld_IOput;
	pObj->Interact0 = HelloWorld_Interact0;
	pObj->Interact1 = HelloWorld_Interact1;
	pObj->Interact2 = HelloWorld_Interact2;
	pObj->Interact3 = HelloWorld_Interact3;
	pObj->Close = HelloWorld_Close;
}

/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

