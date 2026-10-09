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
#include <stdlib.h>
#include "Main.h"


extern  OBJECT*		g_pCar;


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
	RESULT   ir;
	RESULT   fr;
	SR32	  sr32_Val;
	BYTKTY    qty;
	VR        caller = {OID_MAIN, OID_FACTORY};

	/* 动态创建car对象。*/
	fr = CreateObject(MSN_CAR, 0, 0, 1, &g_pCar);
	if(RN(fr))
	{
		printf("Can't create car object.\n");
		return -1;
	}

	/* 打开car对象。*/
    ir = VO_Open(g_pCar, &caller);
	if(RN(ir))
	{
		printf("Can't open car object.\n");
		DestroyObject(g_pCar); /* 销毁动态创建的car对象。*/
		return -1;
	}

	do{
		/* 输出car的重量。*/
		ir = VO_Interact1(g_pCar, GET_WEIGHT, (BYTE*)&sr32_Val, sizeof(sr32_Val), &qty, &caller);
		if(RP(ir))
		{
			printf("car's weight is %f ton.\n", sr32_Val);
		}else
		{
			printf("Can't get car's weight.\n");
			break;
		}

		/* 输出car的最大载重量。*/
		ir = VO_Interact1(g_pCar, GET_MAXLOAD, (BYTE*)&sr32_Val, sizeof(sr32_Val), &qty, &caller);
		if(RP(ir))
		{
			printf("car's max-load is %f ton.\n", sr32_Val);
		}else
		{
			printf("Can't get car's max-load.\n");
			break;
		}

		/* 输出car的最大速度。*/
		ir = VO_Interact1(g_pCar, GET_MAXVELOCITY, (BYTE*)&sr32_Val, sizeof(sr32_Val), &qty, &caller);
		if(RP(ir))
		{
			printf("car's max-velocity is %f km/h.\n", sr32_Val);
		}else
		{
			printf("Can't get car's max-velocity.\n");
			break;
		}
	}while(0);

	ir = VO_Close(g_pCar, &caller);
	if(RP_RCZERO == ir)
	{
		DestroyObject(g_pCar); /* 销毁动态创建的car对象。*/
	}else
	{
		/* 因为仅一次打开car对象，如果引用计数不是0，就是错误的。*/
		printf("Reference count is not zero, after close car.\n");
		return -1; 
	}

	return 0;
}


/*=======================+ IRF(s) +======================*/
/* ... */

/*====================+ Function(s) +====================*/
/* ... */

