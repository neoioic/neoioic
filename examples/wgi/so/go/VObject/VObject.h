/**
 *
 * 文 件 名：VObject.h
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

#ifndef __VOBJECT_H__
#define __VOBJECT_H__

#include "../go.h"


/*
*
* 文本格式化方式定义
*/
#define   CTF_LEFT          DT_LEFT     // aligns text to the left.
#define   CTF_RIGHT         DT_RIGHT    // aligns text to the right.
#define   CTF_HCENTER       DT_CENTER   // horizontally centers text.
#define   CTF_VCENTER       DT_VCENTER   // vertically centeres text (single line only).


/*
*
* 可视对象的风格定义
*/
#define   VOBS_IMMOVABLE           0x00000001L  // 1: Immovable, 0: Movable
#define   VOBS_XIRROLLABLE         0x00000002L  // 1: Irrollable By X, 0: Rollable By X.
#define   VOBS_YIRROLLABLE         0x00000004L  // 1: Irrollable By Y, 0: Rollable By Y.
#define   VOBS_INACTIVABLE         0x00000008L  // 1: Inactivable, 0: Activable
#define   VOBS_NOSEMIACTIVE        0x00000020L  // 1: no the state of "eVOBState_SemiActive", 0: has the state of "eVOBState_SemiActive".

/*
*
* 名称：EVOBSTATE
* 描述：可视对象状态枚举
*/
typedef  enum  TAG_EVOBSTATE
{
	eVOBState_Normal,
	eVOBState_FocusOver,
	eVOBState_FocusOn,
	eVOBState_Active,
	eVOBState_SemiActive,
	eVOBState_Selected,
	eVOBState_Disable,
	eVOBState_Hidden,
	
	/*- number of state -*/
	eNumVOBState		
}EVOBSTATE;


/*
*
* 名称：CAPTIONINFO
* 描述：标题信息
*/
typedef struct TAG_CAPTIONINFO
{
	TCHAR*     text;
	long       cpty;
	long       clen;
    RECT       rect;
    UINT       format;
	HFONT      font;
	COLORREF   color;
}CAPTIONINFO;


/*
*
* 名称：RSCOORD
* 描述：矩形空间坐标结构体
*/
typedef  struct  TAG_RSCOORDINATE
{
	RECT        rcouter;
	RECT        rcinner;
	int         z;
}RSCOORD;


/*
*
* 名称：ZPLGSLLND
* 描述：Z轴多边形单向链表（Singly Linked List）节点结构体
*/
typedef struct TAG_ZPOLYGONSLLNODE
{
	ZPOLYGON                          zp;
	struct TAG_ZPOLYGONSLLNODE*       next;
}ZPLGSLLND;


/*
*
* 名称：ATVCLNSLLNODE
* 描述：主动碰撞（active collision）单向链表节点结构体
*/
typedef struct TAG_ATVCOLLISIONSLLNODE
{
	OBJECT*                                pObj;
	ZPLGSLLND*                             pRgn;
	struct TAG_ATVCOLLISIONSLLNODE*        next;
}ATVCLNSLLNODE;


/*
*
* 名称：MOVE
* 描述：对象移动时的输入流
*/
typedef struct TAG_MOVE
{
	int               dxUL;
	int               dxLR;
	int               dyUL;
	int               dyLR;
	int               dz;         
	ATVCLNSLLNODE*    pacsn;
}MOVE;


/*
*
* 名称：PSVCOLLISION
* 描述：被动碰撞（passive collision）结构体
*/
typedef struct TAG_PSVCOLLISION
{
	OBJECT*          pObj;
	ZPLGSLLND*       pRgn;
}PSVCOLLISION;

/*
*
* 名称：IRRDELTA
* 描述：内部矩形滚动偏移量结构体
*/
typedef struct TAG_IRROLLINGDELTA
{
	long       dx;
	long       dy;
}IRRDELTA;


/*
*
* 名称：ONMAKECURRENTBITMAP
* 描述：这个结构体让用户在VObject节点制作当前位图时定制当前位图的内容。
*       比如Edit控件自己在当前位图上写文本内容，就是通过让VObject节点回调自己的函数来实现的。
*/
typedef struct TAG_ONMAKECURRENTBITMAP
{
	OBJECT*    pCustomer;
	void      (*OnMakeCurrentBitmap)(OBJECT* pCustomer, const HDC  hDC);
}ONMAKECURRENTBITMAP;



/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_VOBJECT
*/
typedef struct TAG_INIT_VOBJECT
{
	OBJECT*          pSuperior;
//	OBJECT*          pFirstSbdt;
	OBJECT*          pPrevCodt;
	OBJECT*          pNextCodt; 
//	OBJECT*          pFirstIIRSbdt;
//	OBJECT*          pPrevISIRCodt;
//	OBJECT*          pNextISIRCodt;
//	long             ox_irr;
//	long             oy_irr;
	long             scenew;
	long             sceneh;
	HBITMAP          ArrHBITMAP[eNumVOBState];
	UI32             style;
	EVOBSTATE        state;
	CAPTIONINFO      ci;
	RSCOORD          rsc;
	ZPLGSLLND        as;
	ZPLGSLLND        rgn;
}INIT_VOBJECT;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_VOBJECT
*/
typedef struct TAG_EM_VOBJECT
{
	OBJECT*          pOIOIC;
	OBJECT*          pSuperior;
	OBJECT*          pFirstSbdt;
	OBJECT*          pPrevCodt;
	OBJECT*          pNextCodt; 
	OBJECT*          pFirstIIRSbdt;
	OBJECT*          pPrevISIRCodt;
	OBJECT*          pNextISIRCodt;
	OBJECT*          pActiveSbdt;
	OBJECT*          pCFOverSbdt;
	OBJECT*          pCFDownSbdt;
	OBJECT*          pCFOnSbdt;
	OBJECT*          pCFUpSbdt;
	long             ox_irr;
	long             oy_irr;
	long             scenew;
	long             sceneh;
	const HWND*      pWndHandle;
	HBITMAP          ArrHBITMAP[eNumVOBState];
	HBITMAP          hBmpCurrent;
	UI32             style;
	EVOBSTATE        state;
	CAPTIONINFO      ci;
	RSCOORD          rsc;
	ZPLGSLLND        as;
	ZPLGSLLND        rgn;
	POINT            lastpt;
	ONMAKECURRENTBITMAP    onmcb;
}EM_VOBJECT;


#endif		/* #ifndef __VOBJECT_H__ */
