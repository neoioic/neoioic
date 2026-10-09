/**
 *
 * 文 件 名：WMenu.h
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

#ifndef __WMENU_H__
#define __WMENU_H__

#include "../go.h"
#include "../WPanel/WPanel.h"


/*
*
* 菜单与不能遮盖区域的位置关系
*/
#define   MNUT_TBLEFT          0  
#define   MNUT_TBRIGHT         1  
#define   MNUT_LRTOP           2
#define   MNUT_LRBOTTOM        3


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_WMENU
*/
typedef struct TAG_INIT_WMENU
{
	INIT_VOBJECT     ivob;
	INIT_WOBJECT     iwob;
	OBJECT*          pParent;
	int              nRBHeight;
    RECT             uca;
	int              type;                    
	int              width;  
	HBITMAP          hBmpTRBNormal;
	HBITMAP          hBmpTRBFocusOver; 
	HBITMAP          hBmpTRBFocusOn;
	HBITMAP          hBmpBRBNormal;
	HBITMAP          hBmpBRBFocusOver; 
	HBITMAP          hBmpBRBFocusOn;
	UINT             timertov;
	int              rollstep; 
	OIOIC_BOOL             (*CreateItems)(OBJECT* pWMenu, const VR* pCaller);
	OIOIC_BOOL             (*DestroyItems)(OBJECT* pWMenu, const VR* pCaller);
}INIT_WMENU;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_WMENU
*/
typedef struct TAG_EM_WMENU
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pWObject;
	OBJECT*     pWPanel;
    OBJECT*     pParent;
	OBJECT*     pCFOverSbdt;
	OBJECT*     pSubMenu;
	OBJECT*     pTRButton;
	OBJECT*     pBRButton;
	int         nRBHeight;
    RECT        uca;
	int         type;                    
	int         width; 
	HBITMAP     hBmpTRBNormal;
	HBITMAP     hBmpTRBFocusOver; 
	HBITMAP     hBmpTRBFocusOn;
	HBITMAP     hBmpBRBNormal;
	HBITMAP     hBmpBRBFocusOver; 
	HBITMAP     hBmpBRBFocusOn;
	UINT        timerid;
	UINT        timertov;
	int         rollstep;
	OIOIC_BOOL        (*CreateItems)(OBJECT* This, const VR* pCaller);
	OIOIC_BOOL        (*DestroyItems)(OBJECT* This, const VR* pCaller);
}EM_WMENU;


/*=======================================================*/

extern  OBJECT*  PopMenu(const INIT_WMENU* piwmu, const VR* pCaller);


#endif		/* #ifndef __WMENU_H__ */
