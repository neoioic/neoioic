/**
 *
 * 文 件 名：ho.h
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

#ifndef __HO_FACTORY_H__
#define __HO_FACTORY_H__

#include "oioic.h"

/*==================+ OID(s) and OID_ +==================*/

/* 注意：在目前操作系统下，尽管大多情况不需要创建HO和AO，但它
*  们的OID是必需的！不需要创建的HO或AO就在这里为它们定义OID。*/

#define   OID_HO			(0x0000000000020000 | OID_OS)  /* HO的OID。*/
#define   OID_FACTORY		(OID_HO + 0) /* Factory的OID。HO */
#define   OID_MAIN			(OID_HO + 1) /* Main的OID。AO */
/* #define   OID_XXX3		(OID_HO + 2) /-* xxx3的OID。.. *-/ */
/* ...     ...     ...     ...     ...     ... */
#define   OID_				(OID_HO + 3) /* 其它OID的起点。*/


/*========================+ MSN +========================*/

/* #define   MSN_XXX1      (MSN_ + 0)  /-* xxx1的MSN。HO *-/ */
/* #define   MSN_XXX2      (MSN_ + 1)  /-* xxx2的MSN。AO *-/ */
/* #define   MSN_XXX3      (MSN_ + 2)  /-* xxx3的MSN。.. *-/ */
#define   MSN_VEHICLE		(MSN_ + 3)  /* vehicle的MSN。GO */
#define   MSN_CAR			(MSN_ + 4)  /* car的MSN。GO */
#define   MSN_SHIP			(MSN_ + 5)  /* ship的MSN。GO */
#define   MSN_AMPHICAR		(MSN_ + 6)  /* amphicar的MSN。GO */
/* ...     ...     ...     ...     ...     ... */


/*=======================+ Action +======================*/

/** 非一个对象模专用的AC0交互行为：**/
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC1_PVT_          (AC1_ + 0)  /* 非一个对象模专用的AC1交互行为起点。*/

/** 非一个对象模专用的AC1交互行为：**/
#define     GET_MAXLOAD          (AC1 | (AC1_PVT_  + 0)) /* car，ship，获取最大载重量。TSO: SR32 */
#define     GET_MAXVELOCITY      (AC1 | (AC1_PVT_  + 1)) /* car，ship，获取最大速度。TSO: SR32 */
/* ...     ...     ...     ...     ...     ... */
#define     AC2_PVT_          (AC1_PVT_ + 2)  /* 非一个对象模专用的AC2交互行为起点。*/

/** 非一个对象模专用的AC2交互行为：**/
/* #define     XXX_YYYYY         (AC2 | (AC2_PVT_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC3_PVT_          (AC2_PVT_ + 0)  /* 非一个对象模专用的AC3交互行为起点。*/

/** 非一个对象模专用的AC3交互行为：**/
/* #define     XXX_YYYYY         (AC3 | (AC3_PVT_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC0_PVT_VEHICLE_      (AC3_PVT_ + 0)  /* vehicle的私有AC0交互行为起点。*/


/** vehicle对象模的私有AC0交互行为：**/
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_VEHICLE_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC1_PVT_VEHICLE_      (AC0_PVT_VEHICLE_ + 0)  /* vehicle的私有AC1交互行为起点。*/

/** vehicle对象模的私有AC1交互行为：**/
#define     GET_WEIGHT			 (AC1 | (AC1_PVT_VEHICLE_  + 0)) /* 获取重量。TSO: SR32 */
/* ...     ...     ...     ...     ...     ... */
#define     AC2_PVT_VEHICLE_      (AC1_PVT_VEHICLE_ + 1)  /* vehicle的私有AC2交互行为起点。*/

/** vehicle对象模的私有AC2交互行为：**/
/* #define     XXX_YYYYY         (AC2 | (AC2_PVT_VEHICLE_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC3_PVT_VEHICLE_      (AC2_PVT_VEHICLE_ + 0)  /* vehicle的私有AC3交互行为起点。*/

/** vehicle对象模的私有AC3交互行为：**/
/* #define     XXX_YYYYY         (AC3 | (AC3_PVT_VEHICLE_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC0_PVT_AMPHICAR_      (AC3_PVT_VEHICLE_ + 0)  /* amphicar的私有AC0交互行为起点。*/


/** amphicar对象模的私有AC0交互行为：**/
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_AMPHICAR_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC1_PVT_AMPHICAR_      (AC0_PVT_AMPHICAR_ + 0)  /* amphicar的私有AC1交互行为起点。*/

/** amphicar对象模的私有AC1交互行为：**/
#define     GET_TMAXLOAD          (AC1 | (AC1_PVT_AMPHICAR_  + 0)) /* 获取陆上（terrestrial）最大载重量。TSO: SR32 */
#define     GET_TMAXVELOCITY      (AC1 | (AC1_PVT_AMPHICAR_  + 1)) /* 获取陆上最大速度。TSO: SR32 */
#define     GET_AMAXLOAD          (AC1 | (AC1_PVT_AMPHICAR_  + 2)) /* 获取水上（aquatic）最大载重量。TSO: SR32 */
#define     GET_AMAXVELOCITY      (AC1 | (AC1_PVT_AMPHICAR_  + 3)) /* 获取水上最大速度。TSO: SR32 */
/* ...     ...     ...     ...     ...     ... */
#define     AC2_PVT_AMPHICAR_      (AC1_PVT_AMPHICAR_ + 4)  /* amphicar的私有AC2交互行为起点。*/

/** amphicar对象模的私有AC2交互行为：**/
/* #define     XXX_YYYYY         (AC2 | (AC2_PVT_AMPHICAR_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC3_PVT_AMPHICAR_      (AC2_PVT_AMPHICAR_ + 0)  /* amphicar的私有AC3交互行为起点。*/

/** amphicar对象模的私有AC3交互行为：**/
/* #define     XXX_YYYYY         (AC3 | (AC3_PVT_AMPHICAR_  + 0)) */
/* ...     ...     ...     ...     ...     ... */
#define     AC0_PVT_YYY_      (AC3_PVT_AMPHICAR_ + 0)  /* X3的私有AC0交互行为起点。*/


/** X3对象模的私有AC0交互行为：**/
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_YYY_  + 0)) */
/* ...     ...     ...     ...     ...     ... */

/* ...     ...     ...     ...     ...     ... */


/*=======================================================*/


#endif		/* #ifndef __HO_FACTORY_H__ */
