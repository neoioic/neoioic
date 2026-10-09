/**
 *
 * 文 件 名：MyDialog.h
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

#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__

#include "../go.h"
#include "../WPanel/WPanel.h"


/*
*
*  subordinates' coordinates.
*  L - left, T - top. 
*/

#define   MYDIALOG_TRCCLOSE_L                965   
#define   MYDIALOG_TRCCLOSE_T                10  

#define   MYDIALOG_MRCONTROL_L               50   
#define   MYDIALOG_MRCONTROL_T               40 

#define   MYDIALOG_MRMENUDEMO_L              130   
#define   MYDIALOG_MRMENUDEMO_T              40 

#define   MYDIALOG_MRHELP_L                  260   
#define   MYDIALOG_MRHELP_T                  40 

#define   MYDIALOG_BUTTON1_L                 50   
#define   MYDIALOG_BUTTON1_T                 120  

#define   MYDIALOG_BUTTON2_L                 -200 
#define   MYDIALOG_BUTTON2_T                 230 

#define   MYDIALOG_BUTTON3_L                 780   
#define   MYDIALOG_BUTTON3_T                 200 

#define   MYDIALOG_EDIT_L                    450   
#define   MYDIALOG_EDIT_T                    200 



/*
*
* NAME: ESMYDIALOG
* DESC: enumerate subordinates of MyDialog
*/
typedef  enum  TAG_ESMYDIALOG
{
    eTRCClose_MyDialog,  // Close button at top right corner 

	/*- menu roots -*/
	eMRControl_MyDialog,
	eMRMenuDemo_MyDialog,
	eMRHelp_MyDialog,

	/*- other cobs -*/
    eButton1_MyDialog,
	eButton2_MyDialog,
	eButton3_MyDialog,
	eEdit_MyDialog,

	/*- number of enum - */
    eNum_SUB_MyDialog
}ESMYDIALOG;

/*
*
* NAME: EMIMYDIALOG
* DESC: enumerate menuitems of MyDialog
*/
typedef enum  TAG_EMIMYDIALOG
{
	/*- for MR Control - */
	eMIEnableButton_MyDialog,
	eMIDisableButton_MyDialog,

	/*- for MR MenuDemo - */
	eMIItem0_MyDialog,
	eMIItem1_MyDialog,
	eMIItem2_MyDialog,
	eMIItem3_MyDialog,
	eMIItem4_MyDialog,
	eMIItem5_MyDialog,
	eMIItem6_MyDialog,
	eMIItem7_MyDialog,
	eMIItem8_MyDialog,
	eMIItem9_MyDialog,
	eMIItem10_MyDialog,
	eMIItem11_MyDialog,
	eMIItem12_MyDialog,
	eMIItem13_MyDialog,
	eMIItem14_MyDialog,
	eMIItem15_MyDialog,
	eMIItem16_MyDialog,
	eMIItem17_MyDialog,
	eMIItem18_MyDialog,
	eMIItem19_MyDialog,
	eMIItem20_MyDialog,
	eMIItem21_MyDialog,
	eMIItem22_MyDialog,
	eMIItem23_MyDialog,
    eMIItem24_MyDialog,
	eMIItem25_MyDialog,
	eMIItem26_MyDialog,
	eMIItem27_MyDialog,
	eMIItem28_MyDialog,
	eMIItem29_MyDialog,
	eMIItem30_MyDialog,
	eMIItem31_MyDialog,
	eMIItem32_MyDialog,
	eMIItem33_MyDialog,
	eMIItem34_MyDialog,
	eMIItem35_MyDialog,
	eMIItem36_MyDialog,
	eMIItem37_MyDialog,
	eMIItem38_MyDialog,
	eMIItem39_MyDialog,
	eMIItem40_MyDialog,
	eMIItem41_MyDialog,
	eMIItem42_MyDialog,
	eMIItem43_MyDialog,
	eMIItem44_MyDialog,
	eMIItem45_MyDialog,
	eMIItem46_MyDialog,
	eMIItem47_MyDialog,
	eMIItem48_MyDialog,
	eMIItem49_MyDialog,
	eMIItem50_MyDialog,

	/*- for MR Help - */
	eMIAbout_MyDialog,

	/*- for MI Item1 - */
	eMIItem3_0_MyDialog,
	eMIItem3_1_MyDialog,
	eMIItem3_2_MyDialog,
	eMIItem3_3_MyDialog,
	eMIItem3_4_MyDialog,
	eMIItem3_5_MyDialog,
	eMIItem3_6_MyDialog,
	eMIItem3_7_MyDialog,
	eMIItem3_8_MyDialog,
	eMIItem3_9_MyDialog,
	eMIItem3_10_MyDialog,
	eMIItem3_11_MyDialog,
	eMIItem3_12_MyDialog,
	eMIItem3_13_MyDialog,
	eMIItem3_14_MyDialog,
	eMIItem3_15_MyDialog,
	eMIItem3_16_MyDialog,
	eMIItem3_17_MyDialog,
	eMIItem3_18_MyDialog,
	eMIItem3_19_MyDialog,
	eMIItem3_20_MyDialog,
	eMIItem3_21_MyDialog,
	eMIItem3_22_MyDialog,
	eMIItem3_23_MyDialog,
	eMIItem3_24_MyDialog,
	eMIItem3_25_MyDialog,
	eMIItem3_26_MyDialog,
	eMIItem3_27_MyDialog,
	eMIItem3_28_MyDialog,
	eMIItem3_29_MyDialog,
	eMIItem3_30_MyDialog,
	eMIItem3_31_MyDialog,
	eMIItem3_32_MyDialog,
	eMIItem3_33_MyDialog,
	eMIItem3_34_MyDialog,
	eMIItem3_35_MyDialog,
	eMIItem3_36_MyDialog,
	eMIItem3_37_MyDialog,
	eMIItem3_38_MyDialog,
	eMIItem3_39_MyDialog,
	eMIItem3_40_MyDialog,
	eMIItem3_41_MyDialog,
	eMIItem3_42_MyDialog,
	eMIItem3_43_MyDialog,
	eMIItem3_44_MyDialog,
	eMIItem3_45_MyDialog,
	eMIItem3_46_MyDialog,
	eMIItem3_47_MyDialog,
	eMIItem3_48_MyDialog,
	eMIItem3_49_MyDialog,
	eMIItem3_50_MyDialog,
	eMIItem3_51_MyDialog,
	eMIItem3_52_MyDialog,
	eMIItem3_53_MyDialog,
	eMIItem3_54_MyDialog,
	eMIItem3_55_MyDialog,

	/*- number of enum - */
	eNum_MI_MyDialog
}EMIMYDIALOG;


/*
*
* NAME: EBITMAP_MYDIALOG
*/
typedef  enum  TAG_EBITMAP_MYDIALOG
{
	/*- Menu Roots -*/
	eMRControl_Normal_BMP_MyDialog,
	eMRControl_FocusOver_BMP_MyDialog,
	eMRControl_FocusOn_BMP_MyDialog,
	eMRMenuDemo_Normal_BMP_MyDialog,
	eMRMenuDemo_FocusOver_BMP_MyDialog,
	eMRMenuDemo_FocusOn_BMP_MyDialog,
	eMRHelp_Normal_BMP_MyDialog,
	eMRHelp_FocusOver_BMP_MyDialog,
	eMRHelp_FocusOn_BMP_MyDialog,

	/*- Rolling Buttons for Menu -*/
	eTopRB_Normal_BMP_MyDialog,
	eTopRB_FocusOver_BMP_MyDialog,	
	eBottomRB_Normal_BMP_MyDialog,
	eBottomRB_FocusOver_BMP_MyDialog,

	/*- Button1 -*/
	eButton1_Normal_BMP_MyDialog,
	eButton1_FocusOver_BMP_MyDialog,
	eButton1_FocusOn_BMP_MyDialog,
	eButton1_Active_BMP_MyDialog,
	eButton1_ABSInactive_BMP_MyDialog,

	/*- Button3 -*/
	eButton3_Normal_BMP_MyDialog,
	eButton3_FocusOver_BMP_MyDialog,
	eButton3_FocusOn_BMP_MyDialog,
	eButton3_Active_BMP_MyDialog,
	eButton3_ABSInactive_BMP_MyDialog,

	/*- Edit -*/
	eEdit_Normal_BMP_MyDialog,
	eEdit_Active_BMP_MyDialog,

	/*- number of enum -*/
    eNum_BMP_MyDialog
}EBITMAP_MYDIALOG;



/*
*
* NAME: EMIBITMAP_MYDIALOG
* DESC: enumerate BITMAP for menu items.
*/
typedef  enum  TAG_EMIBITMAP_MYDIALOG
{
	eMIEnableButton_Normal_BMP_MyDialog,
	eMIEnableButton_FocusOver_BMP_MyDialog,
	
	eMIDisableButton_Normal_BMP_MyDialog,
	eMIDisableButton_FocusOver_BMP_MyDialog,

	eMIItem0_Normal_BMP_MyDialog,
	eMIItem0_FocusOver_BMP_MyDialog,

	eMIItem3_Normal_BMP_MyDialog,
	eMIItem3_FocusOver_BMP_MyDialog,

	eMIItem3_0_Normal_BMP_MyDialog,
	eMIItem3_0_FocusOver_BMP_MyDialog,

	eMIAbout_Normal_BMP_MyDialog,
	eMIAbout_FocusOver_BMP_MyDialog,

	/*- number of enum -*/
    eNum_MIBMP_MyDialog
}EMIBITMAP_MYDIALOG;


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_MYDIALOG
*/
/*typedef struct TAG_INIT_MYDIALOG
{
}INIT_MYDIALOG;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_MYDIALOG
*/
typedef struct TAG_EM_MYDIALOG
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pWObject;
	OBJECT*     pWPanel;
	OBJECT*     pMenu;
	OBJECT*     pPoppingMR;  /* 记录当前弹出菜单的菜单根对象。*/
	OBJECT*     ArrSUB[eNum_SUB_MyDialog];
	OBJECT*     ArrMI[eNum_MI_MyDialog];
	HBITMAP     ArrHBITMAP[eNum_BMP_MyDialog];
	HBITMAP     ArrMIHBITMAP[eNum_MIBMP_MyDialog];
	TCHAR*      pTextPool_MRMenuDemo; 
	TCHAR*      pTextPool_MIItem3; 
	TCHAR       edttext[256];
}EM_MYDIALOG;


#endif		/* #ifndef __MYDIALOG_H__ */
