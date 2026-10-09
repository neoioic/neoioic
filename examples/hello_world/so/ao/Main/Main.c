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

#include <stdio.h>
#include "Main.h"


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
static RESULT  Main_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


	return R_P;
}

/**
*
* 名称：Main_Input
*/
static RESULT  Main_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：Main_Output
*/
static RESULT  Main_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：Main_IOput
*/
static RESULT  Main_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：Main_Interact0
*/
static RESULT  Main_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：Main_Interact1
*/
static RESULT  Main_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：Main_Interact2
*/
static RESULT  Main_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：Main_Interact3
*/
static RESULT  Main_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：Main_Close
*/
static RESULT  Main_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	/* ... */


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
* 名称：Main
* 描述：主体函数。
*/
SI32  Main(SI32 argc, SI8 **argv)
{
	printf("Hello world!\n");
	return 0;
}


/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

