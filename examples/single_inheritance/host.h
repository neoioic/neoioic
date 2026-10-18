

#ifndef NEOIOIC_HO_FACTORY_H
#define NEOIOIC_HO_FACTORY_H

#include "neoioic.h"

/* oid(s) and OID_ */

/*
 *  注意：在目前操作系统下，尽管大多情况不需要创建HO和AO，但它
 *  们的oid是必需的！不需要创建的HO或AO就在这里为它们定义oid。
 */

#define OID_HO (0x0000000000020000 | OID_OS) /* HO的oid。 */
#define OID_FACTORY (OID_HO + 0)	     /* Factory的oid。HO */
#define OID_MAIN (OID_HO + 1)		     /* main的oid。AO */
/* #define   OID_XXX3		(OID_HO + 2) /-* xxx3的oid。.. *-/ */

#define OID_ (OID_HO + 3) /* 其它oid的起点。 */

/* model_id */

/* #define   MSN_XXX1      (MSN_ + 0)  /-* xxx1的model_id。HO *-/ */
/* #define   MSN_XXX2      (MSN_ + 1)  /-* xxx2的model_id。AO *-/ */
/* #define   MSN_XXX3      (MSN_ + 2)  /-* xxx3的model_id。.. *-/ */
#define MSN_CAR (MSN_ + 3)     /* car的model_id。GO */
#define MSN_VEHICLE (MSN_ + 4) /* vehicle的model_id。GO */

/* Action */

/* 非一个对象模专用的AC0交互行为：* */
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_  + 0)) */

#define AC1_PVT_ (AC1_ + 0) /* 非一个对象模专用的AC1交互行为起点。 */

/* 非一个对象模专用的AC1交互行为：* */
#define GET_MAXLOAD (AC1 | (AC1_PVT_ + 0)) /* car，获取最大载重量。TSO: float */
#define GET_MAXVELOCITY \
	(AC1 | (AC1_PVT_ + 1)) /* car，获取最大速度。TSO: float */

#define AC2_PVT_ (AC1_PVT_ + 2) /* 非一个对象模专用的AC2交互行为起点。 */

/* 非一个对象模专用的AC2交互行为：* */
/* #define     XXX_YYYYY         (AC2 | (AC2_PVT_  + 0)) */

#define AC3_PVT_ (AC2_PVT_ + 0) /* 非一个对象模专用的AC3交互行为起点。 */

/* 非一个对象模专用的AC3交互行为：* */
/* #define     XXX_YYYYY         (AC3 | (AC3_PVT_  + 0)) */

#define AC0_PVT_VEHICLE_ (AC3_PVT_ + 0) /* vehicle的私有AC0交互行为起点。 */

/* vehicle对象模的私有AC0交互行为：* */
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_VEHICLE_  + 0)) */

#define AC1_PVT_VEHICLE_ \
	(AC0_PVT_VEHICLE_ + 0) /* vehicle的私有AC1交互行为起点。 */

/* vehicle对象模的私有AC1交互行为：* */
#define GET_WEIGHT (AC1 | (AC1_PVT_VEHICLE_ + 0)) /* 获取重量。TSO: float */

/* #define     AC2_PVT_VEHICLE_      (AC1_PVT_VEHICLE_ + x)  /-* vehicle的私有AC2交互行为起点。*-/ */

/* vehicle对象模的私有AC2交互行为：* */
/* #define     XXX_YYYYY         (AC2 | (AC2_PVT_VEHICLE_  + 0)) */

#define AC3_PVT_VEHICLE_ \
	(AC2_PVT_VEHICLE_ + 0) /* vehicle的私有AC3交互行为起点。 */

/* vehicle对象模的私有AC3交互行为：* */
/* #define     XXX_YYYYY         (AC3 | (AC3_PVT_VEHICLE_  + 0)) */

#define AC0_PVT_YYY_ (AC3_PVT_VEHICLE_ + 0) /* X2的私有AC0交互行为起点。 */

/* X2对象模的私有AC0交互行为：* */
/* #define     XXX_YYYYY         (AC0 | (AC0_PVT_YYY_  + 0)) */

#endif /* #ifndef NEOIOIC_HO_FACTORY_H */
