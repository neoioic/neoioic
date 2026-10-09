/**
 *
 * 文 件 名：car.h
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

#ifndef __CAR_H__
#define __CAR_H__

#include "../go.h"

/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_CAR
*/
typedef struct TAG_EM_CAR
{
	SR32	max_load; /* 最大负载量，以吨为单位。*/
	SR32	max_velocity; /* 最大速度，以千米/小时为单位。*/
}EM_CAR;


#endif		/* #ifndef __CAR_H__ */
