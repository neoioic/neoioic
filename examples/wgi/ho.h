

#ifndef OIOIC_HO_WGIDEMO_H
#define OIOIC_HO_WGIDEMO_H

#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <string.h>
#include "resource.h"
#include "oioic.h"

/* oid */

/*
 *  注意：在目前操作系统下，尽管大多情况不需要创建HO和AO，但它
 *  们的oid是必需的！不需要创建的HO或AO就在这里为它们定义oid。
 */

#define OID_HO (0x0000000000010000 | OID_OS) /* HO的oid。 */
#define OID_WGIDEMO (OID_HO + 0)	     /* wgidemo的oid。HO */
#define OID_MAIN (OID_HO + 1)		     /* main的oid。AO */
/* #define   OID_XXX3      (OID_HO + 2) /-* xxx3的oid。.. *-/ */

#define OID_ (OID_HO + 3) /* 其它oid的起点。 */

/* model_id */

#define MSN_WGIDEMO (MSN_ + 0)	   /* wgidemo的model_id。HO */
#define MSN_MAIN (MSN_ + 1)	   /* main的model_id。AO */
#define MSN_VOBJECT (MSN_ + 2)	   /* VObject的model_id。GO */
#define MSN_WOBJECT (MSN_ + 3)	   /* WObject的model_id。GO */
#define MSN_COBJECT (MSN_ + 4)	   /* CObject的model_id。GO */
#define MSN_WPANEL (MSN_ + 5)	   /* WPanel的model_id。GO */
#define MSN_CBUTTON (MSN_ + 6)	   /* CButton的model_id。GO */
#define MSN_MYDIALOG (MSN_ + 7)	   /* MyDialog的model_id。GO */
#define MSN_MYBUTTON (MSN_ + 8)	   /* MyButton的model_id。GO */
#define MSN_MYBUTTON2 (MSN_ + 9)   /* MyButton2的model_id。GO */
#define MSN_WMENU (MSN_ + 10)	   /* WMenu的model_id。GO */
#define MSN_CEDIT (MSN_ + 11)	   /* CEdit的model_id。GO */
#define MSN_CSCROLLBAR (MSN_ + 12) /* CScrollBar的model_id。GO */

/* Result */

/* #define     RN_XXXXX              (RN_ - 1) */
/* #define     RN_XXXXX              (RN_ - 0) */
/* N 结果（上）：* */

/* #define     RO_XXXXX             (RON_ - 1) */
/* #define     RO_XXXXX             (RON_ - 0) */

/* #define     RO_XXXXX             (ROP_ + 0) */
/* #define     RO_XXXXX             (ROP_ + 1) */

/* P 结果（下）：* */
/* #define     RP_XXXXX              (RP_ + 0) */
/* #define     RP_XXXXX              (RP_ + 1) */

/* Action */

/* AC0 行为：* */
#define CMD_WGI_PAINT (AC0_ + 0)
#define CMD_RUN (AC0_ + 11)
#define MSG_WGI_FOCUSOVERLEAVE (AC0_ + 1)
#define MSG_WGI_FOCUSONLEAVE (AC0_ + 2)
#define MSG_WGI_ACTIVATE (AC0_ + 3)
#define MSG_WGI_DEACTIVATE (AC0_ + 4)
#define MAK_WGI_CURRENTBITMAP0 (AC0_ + 5)
#define CRT_WGI_WINDOW (AC0_ + 6)
#define DTR_WGI_WINDOW (AC0_ + 7)
#define CMD_WGI_REPAINT (AC0_ + 8)
#define CMD_WGI_REPAINTSUPERIOR (AC0_ + 9)
#define CMD_WGI_REFRESHDCLLPFIRSTIIRSBDT (AC0_ + 10)

/* AC1 行为：* */
/* #define     XXX_YYYYY            (AC1_ + 0) */
/* #define     XXX_YYYYY            (AC1_ + 1) */

/* AC2 行为：* */
#define MSG_WGI_FOCUSOVER (AC2_ + 0)
#define MSG_WGI_FOCUSON (AC2_ + 1)
#define MSG_WGI_FOCUSOVERMOVE (AC2_ + 2)
#define MSG_WGI_FOCUSONMOVE (AC2_ + 3)
#define MSG_WGI_FOCUSDOWN (AC2_ + 4)
#define MSG_WGI_FOCUSUP (AC2_ + 5)
#define MAK_WGI_CURRENTBITMAP2 (AC2_ + 6)
#define CMD_WGI_MOVE (AC2_ + 7)
#define CMD_WGI_ROLLIR (AC2_ + 8)
#define CMD_WGI_INSERTCHARATCP (AC2_ + 9)
#define CMD_WGI_ROLL (AC2_ + 10)
#define CMD_WGI_ROLLONCB (AC2_ + 11)

/* AC3 行为：* */
#define MSG_WGI_MENUITEMFOCUSOVER (AC3_ + 0)
#define MSG_WGI_MENUITEMFOCUSON (AC3_ + 1)
#define MSG_WGI_MENUITEMFOCUSDOWN (AC3_ + 2)
#define MSG_WGI_MENUITEMFOCUSUP (AC3_ + 3)

#endif /* #ifndef OIOIC_HO_WGIDEMO_H */
