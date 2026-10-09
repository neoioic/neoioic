/**
 *
 * 文 件 名：CEdit.h
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

#ifndef __CEDIT_H__
#define __CEDIT_H__

#include "../go.h"
#include "../CScrollBar/CScrollBar.h"


/*
*
* 控件风格
*/
#define   EDTS_AUTOWRAP      0x00000001L  // 1 - 自动换行, 0 - 不自动换行。
#define   EDTS_SCROLLBAR     0x00000002L  // 1 - 有滚动条（自动添加）, 0 - 没有滚动条。

/*
*
* 文本对齐风格（即文本格式化方式）
*/
#define   ETF_LEFT         0x00000001L  // 1 - 左靠齐, 0 - 不左靠齐。
#define   ETF_RIGHT        0x00000002L  // 1 - 右靠齐, 0 - 不右靠齐。
#define   ETF_HCENTER      0x00000004L  // 1 - 水平居中, 0 - 不水平居中。
#define   ETF_TOP          0x00000008L  // 1 - 顶靠齐, 0 - 不顶靠齐。
#define   ETF_BOTTOM       0x00000010L  // 1 - 底靠齐, 0 - 不底靠齐。
#define   ETF_VCENTER      0x00000020L  // 1 - 垂直居中, 0 - 不垂直居中。


/*
*
* 名称：CWXY
* 描述：字符宽度和位置
*/
typedef struct TAG_CWXY
{
	int   w;
	long  x;
	long  y;
}CWXY;


/*
*
* 名称：EDITTEXTINFO
* 描述：文本信息
*/
typedef struct TAG_EDITTEXTINFO
{
	TCHAR*     text;
	long       cpty;
	long       clen;
	HFONT      font;
	COLORREF   crnor;
	COLORREF   crsel;
	COLORREF   crbgsel;
	int        nSpcRow;
	int        nSpcClm;
}EDITTEXTINFO;


/*
*
* 名称：CARETPOS
* 描述：插入符位置
*/
typedef struct TAG_CARETPOS
{
	long    iChar;
	OIOIC_BOOL    bToRight;  
}CARETPOS;


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_CEDIT
*/
typedef struct TAG_INIT_CEDIT
{
	INIT2_CSCROLLBAR   i2hscb;
	INIT2_CSCROLLBAR   i2vscb;
	EDITTEXTINFO       ti;
	UI32               format;
	UI32               style;
	int                CaretWidth;
	HBITMAP            hBmpIntAreaVHScrbar;
}INIT_CEDIT;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_CEDIT
*/
typedef struct TAG_EM_CEDIT
{
	OBJECT*             pOIOIC;
	OBJECT*             pVObject;
	OBJECT*             pCObject;
	EDITTEXTINFO        ti;
	int                 vpw;
	int                 vph;
	long                textWidth;
	long                textHeight;
	UI32                format;
	UI32                style;
	int                 CaretWidth;
	int                 CharHeight;
	CWXY*               pArrCWXY;
	CARETPOS            cp;
	INIT2_CSCROLLBAR    i2hscb;
	INIT2_CSCROLLBAR    i2vscb;
	OBJECT*             pHScrBar;
	OBJECT*             pVScrBar;
	HBITMAP             hBmpIntAreaVHScrbar;
}EM_CEDIT;


#endif		/* #ifndef __CEDIT_H__ */
