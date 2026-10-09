/**
 *
 * 文 件 名：wgi.c
 *
 * 描    述：
 *
 * 创 建 者：
 *
 * 创建日期：
 *
 * 版    本：1.0.8
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

#include <olectl.h>
#include "wgi.h"
#include "../so/go/VObject/VObject.h"


/**
*
* 需求编号：	
* 需求功能：	加载图片文件。
* 函    数：	HBITMAP  LoadPictureFile(const TCHAR* adrame)
* 描    述：	加载图片文件，SE函数。
* 参    数：	adrame - [IN] address and name，图片地址和名称。
* 返    回：	非NULL - 加载成功；NULL - 加载失败。
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：		
*/
HBITMAP  LoadPictureFile(const TCHAR* adrame)
{
    IPicture* picture = NULL;
    OLE_HANDLE handle;
    HBITMAP bitmap = NULL;
    HRESULT result = OleLoadPicturePath((LPOLESTR)adrame, NULL, 0, 0,
                                       &IID_IPicture, (void**)&picture);
    if (FAILED(result))
        return NULL;
    if (SUCCEEDED(picture->lpVtbl->get_Handle(picture, &handle)))
        bitmap = CopyImage((HANDLE)(uintptr_t)(uint32_t)handle, IMAGE_BITMAP, 0, 0, 0);
    picture->lpVtbl->Release(picture);
    return bitmap;
}


/**
*
* 需求编号：	
* 需求功能：	判断一点是否在一个多边形内。
* 函    数：	OIOIC_BOOL  IsPointInPolygon(int x, int y, const POLYGON*  pplg)
* 描    述：	判断一点是否在一个多边形内，SE函数。
* 参    数：	x - [IN] 点的X轴坐标； 
*               y - [IN] 点的Y轴坐标；
*               pplg - [IN] 指向多边形。
* 返    回：	TRUE - 点在多边形内，FALSE - 点不在多边形内。
* 定 义 者：	赵平智
* 设 计 者：	尹斌
* 实 现 者：	尹斌
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
OIOIC_BOOL  IsPointInPolygon(int x, int y, const POLYGON*  pplg)
{
	return TRUE;
}

/**
*
* 需求编号：	
* 需求功能：	判断两个在同一平面的矩形是否相交。
* 函    数：	OIOIC_BOOL  IsInter2Rects(const RECT* pSrcRect1, const RECT* pSrcRect2, RECT*  pDstRect)
* 描    述：	判断两个在同一平面的矩形是否相交（包括内含），SE函数。
* 参    数：	pSrcRect1 - [IN] 第一个平面多边形。
*               pSrcRect2 - [IN] 第二个平面多边形。
*               pDstRect - [OUT] 这个参数可以为NULL，如果不为NULL,输出两个矩形相交的部分（也是矩形）,如果两个矩形不相交,就把这个结构体置空。
* 返    回：	TRUE - 两平面矩形相交，FALSE - 两平面矩形不相交。
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
OIOIC_BOOL  IsInter2Rects(const RECT* pSrcRect1, const RECT* pSrcRect2, RECT*  pDstRect)
{
	if(NULL == pDstRect)
	{
		RECT  rc;
		return IntersectRect(&rc, pSrcRect1, pSrcRect2);
	}else
	{
		return IntersectRect(pDstRect, pSrcRect1, pSrcRect2);
	}
}


/**
*
* 需求编号：	
* 需求功能：	计算可视对象外部矩形的绝对坐标值。
* 函    数：	void CalcuORACoord(OBJECT* pObj, RECT* pAOR)
* 描    述：	计算可视对象外部矩形的绝对坐标值，SE函数。
* 参    数：	pObj - [IN] 对象指针，必须是VObject节点的派生对象；
                pAOR - [OUT] 接收外部矩形的绝对坐标值（AOR,Absolute Outer Rectangle（绝对外部矩形，
				即坐标值转换为相对于桌面左上角后的外部矩形））。
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.0
* 更新日期：	20111222
* 备    注：	Calcu - Calculate
* 修改记录：	
* 测试要点：	
*/
void  CalcuORACoord(OBJECT* pObj, RECT* pAOR)
{
	EM_VOBJECT*      pem_vob = (EM_VOBJECT*)GetEMofBN(pObj, MSN_VOBJECT);

	assert(pem_vob != NULL);

	*pAOR = pem_vob->rsc.rcouter;

	while(pem_vob->pSuperior)
	{			
		pem_vob = (EM_VOBJECT*)GetEMofBN(pem_vob->pSuperior, MSN_VOBJECT);
		pAOR->top += pem_vob->rsc.rcinner.top + pem_vob->rsc.rcouter.top;
		pAOR->bottom += pem_vob->rsc.rcinner.top + pem_vob->rsc.rcouter.top;
		pAOR->left += pem_vob->rsc.rcinner.left + pem_vob->rsc.rcouter.left;
		pAOR->right += pem_vob->rsc.rcinner.left + pem_vob->rsc.rcouter.left;
	}

	return;
}
