/**
 *
 * 文 件 名：CScrollBar.h
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

#ifndef __CSCROLLBAR_H__
#define __CSCROLLBAR_H__

#include "../go.h"



/*
*
* 名称：ROLLINGARG
*/
typedef struct TAG_ROLLINGARG
{
	long    lrs1;  
	long    lrs2;  
	long    lrs3;  
}ROLLINGARG;

/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_CSCROLLBAR
*/
typedef struct TAG_INIT_CSCROLLBAR
{
	int         nRB1LMargin;
	int         nRB1TMargin;
	int         nRB2RMargin;
	int         nRB2BMargin;
	int         nRGMargin;
	int         nRB1Width;
	int         nRB1Height;
	int         nRB2Width;
	int         nRB2Height;
	int         nRGThickness;
	HBITMAP     hBmpRB1Normal;
	HBITMAP     hBmpRB1FocusOver; 
	HBITMAP     hBmpRB1FocusOn;
	HBITMAP     hBmpRB2Normal;
	HBITMAP     hBmpRB2FocusOver; 
	HBITMAP     hBmpRB2FocusOn;   
	HBITMAP     hBmpRGNormal;
	HBITMAP     hBmpRGFocusOver; 
	HBITMAP     hBmpRGFocusOn;  
}INIT_CSCROLLBAR;


/*
*
* 名称：INIT2_CSCROLLBAR
*/
typedef struct TAG_INIT2_CSCROLLBAR
{
	INIT_CSCROLLBAR    iscb;
	HBITMAP     hBmpNormal;
	HBITMAP     hBmpFocusOver; 
	HBITMAP     hBmpFocusOn;
	int         nThickness;
}INIT2_CSCROLLBAR;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_CSCROLLBAR
*/
typedef struct TAG_EM_CSCROLLBAR
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pCObject;
	int         nRB1LMargin;
	int         nRB1TMargin;
	int         nRB2RMargin;
	int         nRB2BMargin;
	int         nRGMargin;
	int         nRB1Width;
	int         nRB1Height;
	int         nRB2Width;
	int         nRB2Height;
	int         nRGThickness;
	HBITMAP     hBmpRB1Normal;
	HBITMAP     hBmpRB1FocusOver; 
	HBITMAP     hBmpRB1FocusOn;
	HBITMAP     hBmpRB2Normal;
	HBITMAP     hBmpRB2FocusOver; 
	HBITMAP     hBmpRB2FocusOn;   
	HBITMAP     hBmpRGNormal;
	HBITMAP     hBmpRGFocusOver; 
	HBITMAP     hBmpRGFocusOn;  
}EM_CSCROLLBAR;


#endif		/* #ifndef __CSCROLLBAR_H__ */
