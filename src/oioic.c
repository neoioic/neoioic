/*
 * OIOIC 节点的 .c 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 版权(C)2005-2011 赵平智。保留所有权利。
 */

#include <stdlib.h>
#include <string.h>
#include "oioic.h"

/* Interface */

/*
 * open接口。
 * 参数：caller_context --- [IN] 来访者。
 */
static int oioic_open(struct object *self, const struct vr *caller_context)
{
	self->ref_count++;
	return R_P;
}

/*
 * input接口。
 * 参数：input_stream --- [IN] 输入流；
 *       quantity --- [IN] 输入的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_input(struct object *self, unsigned char *input_stream,
		       unsigned int quantity, const struct vr *caller_context)
{
	return RO_SBOOIX;
}

/*
 * output接口。
 * 参数：output_stream --- [OUT] 输出流的流向；
 *       capacity --- [IN] output_stream所指存储空间的容量；
 *       output_quantity --- [OUT] 指向实际输出的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_output(struct object *self, unsigned char *output_stream,
			unsigned int capacity, unsigned int *output_quantity,
			const struct vr *caller_context)
{
	return RO_SBOOIX;
}

/*
 * io_put接口。
 * 参数：input_stream --- [IN] 输入流；
 *       quantity --- [IN] 输入的Byte数量；
 *       output_stream --- [OUT] 输出流的流向；
 *       capacity --- [IN] output_stream所指存储空间的容量；
 *       output_quantity --- [OUT] 指向实际输出的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_io_put(struct object *self, unsigned char *input_stream,
			unsigned int quantity, unsigned char *output_stream,
			unsigned int capacity, unsigned int *output_quantity,
			const struct vr *caller_context)
{
	return RO_SBOOIX;
}

/*
 * interact0接口。
 * 参数：action --- [IN] 交互行为；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_interact0(struct object *self, unsigned int action,
			   const struct vr *caller_context)
{
	struct em_oioic *members = (struct em_oioic *)self->members;

	switch (action) {
	case ASK_SHARED: /* 问共享么。 */
		if (members->mds & MOD_SHARED)
			return R_N;
		return R_P;
	case SET_SHARED: /* 设置共享。 */
		members->mds &= ~MOD_SHARED;
		return R_P;
	case SET_UNSHARED: /* 设置非共享。 */
		members->mds |= MOD_SHARED;
		return R_P;
	case SET_BLOCKI: /* 设置阻断输入。 */
		members->mds &= ~MOD_BLOCKI;
		return R_P;
	case SET_UNBLOCKI: /* 设置非阻断输入。 */
		members->mds |= MOD_BLOCKI;
		return R_P;
	case SET_BLOCKO: /* 设置阻断输出。 */
		members->mds &= ~MOD_BLOCKO;
		return R_P;
	case SET_UNBLOCKO: /* 设置非阻断输出。 */
		members->mds |= MOD_BLOCKO;
		return R_P;
	case CMD_RESET: /* 重置。 */
		members->iq.front = members->iq.rear = members->iq.data - 1;
		members->iq.quantity = members->iq.lost = 0;
		members->oq.front = members->oq.rear = members->oq.data - 1;
		members->oq.quantity = members->oq.lost = 0;
		return R_P;
	default:
		break;
	}

	return RO_SBOOIX;
}

/*
 * interact1接口。
 * 参数：action --- [IN] 交互行为；
 *       output_stream --- [OUT] 输出流的流向；
 *       capacity --- [IN] output_stream所指存储空间的容量；
 *       output_quantity --- [OUT] 指向实际输出的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_interact1(struct object *self, unsigned int action,
			   unsigned char *output_stream, unsigned int capacity,
			   unsigned int *output_quantity,
			   const struct vr *caller_context)
{
	struct em_oioic *members = (struct em_oioic *)(self->members);

	switch (action) {
	case GET_IQCTY: /* 获取iq容量。 */
		assert(capacity >= sizeof(unsigned int));
		*((unsigned int *)output_stream) = members->iq.capacity;
		*output_quantity = sizeof(unsigned int);
		return R_P;
	case GET_OQCTY: /* 获取oq容量。 */
		assert(capacity >= sizeof(unsigned int));
		*((unsigned int *)output_stream) = members->oq.capacity;
		*output_quantity = sizeof(unsigned int);
		return R_P;
	default:
		break;
	}

	return RO_SBOOIX;
}

/*
 * interact2接口。
 * 参数：action --- [IN] 交互行为；
 *       input_stream --- [IN] 输入流；
 *       quantity --- [IN] 输入的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_interact2(struct object *self, unsigned int action,
			   unsigned char *input_stream, unsigned int quantity,
			   const struct vr *caller_context)
{
	struct em_oioic *members = (struct em_oioic *)(self->members);

	switch (action) {
	case SET_IQCTY: /* 设置iq容量。 */
		assert(sizeof(unsigned int) == quantity);
		if (members->iq.data != NULL)
			free(members->iq.data);
		members->iq.data = (unsigned char *)calloc(
			*((unsigned int *)input_stream), 1);
		if (members->iq.data != NULL) {
			members->iq.front = members->iq.rear =
				members->iq.data - 1;
			members->iq.capacity = *((unsigned int *)input_stream);
			members->iq.quantity = members->iq.lost = 0;
			return R_P;
		} else {
			return R_N;
		}
	case SET_OQCTY: /* 设置oq容量。 */
		assert(sizeof(unsigned int) == quantity);
		if (members->oq.data != NULL)
			free(members->oq.data);
		members->oq.data = (unsigned char *)calloc(
			*((unsigned int *)input_stream), 1);
		if (members->oq.data != NULL) {
			members->oq.front = members->oq.rear =
				members->oq.data - 1;
			members->oq.capacity = *((unsigned int *)input_stream);
			members->oq.quantity = members->oq.lost = 0;
			return R_P;
		} else {
			return R_N;
		}
	default:
		break;
	}

	return RO_SBOOIX;
}

/*
 * interact3接口。
 * 参数：action --- [IN] 交互行为；
 *       input_stream --- [IN] 输入流；
 *       quantity --- [IN] 输入的Byte数量；
 *       output_stream --- [OUT] 输出流的流向；
 *       capacity --- [IN] output_stream所指存储空间的容量；
 *       output_quantity --- [OUT] 指向实际输出的Byte数量；
 *       caller_context --- [IN] 来访者。
 */
static int oioic_interact3(struct object *self, unsigned int action,
			   unsigned char *input_stream, unsigned int quantity,
			   unsigned char *output_stream, unsigned int capacity,
			   unsigned int *output_quantity,
			   const struct vr *caller_context)
{
	return RO_SBOOIX;
}

/*
 * close接口。
 * 参数：caller_context --- [IN] 来访者。
 */
static int oioic_close(struct object *self, const struct vr *caller_context)
{
	self->ref_count--;
	return R_P;
}

/* TOG */

void tog_oioic(struct object *object)
{
	object->open = oioic_open;
	object->input = oioic_input;
	object->output = oioic_output;
	object->io_put = oioic_io_put;
	object->interact0 = oioic_interact0;
	object->interact1 = oioic_interact1;
	object->interact2 = oioic_interact2;
	object->interact3 = oioic_interact3;
	object->close = oioic_close;
}

/* IRF(s) */

/* Function(s) */
