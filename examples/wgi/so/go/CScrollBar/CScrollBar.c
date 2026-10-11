

#include "CScrollBar.h"
#include "../CObject/CObject.h"

void tog_c_scroll_bar(struct object *object);

int c_scroll_bar_i_open(struct object *self, const struct vr *caller_context);
int c_scroll_bar_i_close(struct object *self, const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> CObject </ibn> */
/* <crt> */
int crt_c_scroll_bar(uint64_t *object_id, unsigned int input_capacity,
		     unsigned int output_capacity, int caller_capacity,
		     struct object **object_out, unsigned char *exotic_memory)
{
	extern void init_direct_bases(struct object * node,
				      unsigned short *base_msns,
				      unsigned short nib);
	extern void init_base_nodes(struct object * node,
				    unsigned short *base_msns,
				    unsigned short nbn);
	extern void tog_c_object(struct object * object);
	extern void tog_v_object(struct object * object);
	extern void tog_oioic(struct object * object);

	size_t ux_nd = 4;		     /* ND数量。 */
	size_t ux_bn = 6;		     /* 各ND的BN数量之和。 */
	size_t ux_ib = 3;		     /* 各ND的IBN数量之和。 */
	if (caller_capacity < 1 || (size_t)caller_capacity > USHRT_MAX / 4)
		return RN_INVALIDARG;
	size_t ux_cs = (size_t)caller_capacity * 10; /* 各ND的最少CS数量之和。 */
	size_t ux_em =
		OIOIC_ALIGNED_SIZE(struct em_cscrollbar) +
		OIOIC_ALIGNED_SIZE(struct em_cobject) +
		OIOIC_ALIGNED_SIZE(struct em_vobject) +
		OIOIC_ALIGNED_SIZE(struct em_oioic); /* 各ND的void尺寸之和。 */

	size_t sum = ux_nd * sizeof(struct object)     /* for AND. */
		     + ux_bn * sizeof(struct object *) /* for "bases". */
		     + ux_ib * sizeof(struct object *) /* for "direct_bases". */
		     + ux_cs * sizeof(struct vr) +
		     ux_em; /* for "callers" and "members". */

	unsigned char *p_ic = NULL;

	if (NULL == exotic_memory) {
		*object_out = NULL;
		p_ic = (unsigned char *)calloc(sum, 1);
	} else {
		p_ic = exotic_memory;
		memset(p_ic, 0, sum);
	}

	if (p_ic != NULL) {
		struct object *node;
		unsigned short base_msns[3];
		unsigned char *p = p_ic + sizeof(struct object) * ux_nd;

		/* 确定AND各元素  ** */

		/* CScrollBar * */
		node = (struct object *)p_ic;
		tog_c_scroll_bar(node);
		node->model_id = MSN_CSCROLLBAR;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* CObject * */
		tog_c_object(++node);
		node->model_id = MSN_COBJECT;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* VObject * */
		tog_v_object(++node);
		node->model_id = MSN_VOBJECT;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* OIOIC * */
		tog_oioic(++node);
		node->model_id = MSN_OIOIC;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* 初始化各ND  ** */

		/* CScrollBar * */
		node = (struct object *)p_ic;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_COBJECT;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_COBJECT;
		base_msns[1] = MSN_VOBJECT;
		base_msns[2] = MSN_OIOIC;
		init_base_nodes(node, base_msns, 3);
		p += sizeof(struct object *) * 3;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 1;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_cscrollbar);

		/* CObject * */
		++node;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_VOBJECT;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_VOBJECT;
		base_msns[1] = MSN_OIOIC;
		init_base_nodes(node, base_msns, 2);
		p += sizeof(struct object *) * 2;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 2;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_cobject);

		/* VObject * */
		++node;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_OIOIC;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_OIOIC;
		init_base_nodes(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 3;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_vobject);

		/* OIOIC * */
		++node;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 4;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		if (input_capacity > 0) {
			/* - iq - */
			((struct em_oioic *)(node->members))->iq.data =
				(unsigned char *)calloc(input_capacity, 1);
			if (NULL ==
			    ((struct em_oioic *)(node->members))->iq.data) {
				/* 分配iq的容量失败！ */
				if (NULL == exotic_memory)
					free(p_ic);
				return R_N;
			}
			((struct em_oioic *)(node->members))->iq.front =
				((struct em_oioic *)(node->members))->iq.rear =
					NULL;
			((struct em_oioic *)(node->members))->iq.capacity =
				input_capacity;
			((struct em_oioic *)(node->members))->iq.quantity =
				((struct em_oioic *)(node->members))->iq.lost =
					0;
		}

		if (output_capacity > 0) {
			/* - oq - */
			((struct em_oioic *)(node->members))->oq.data =
				(unsigned char *)calloc(output_capacity, 1);
			if (NULL ==
			    ((struct em_oioic *)(node->members))->oq.data) {
				/* 分配oq的容量失败！ */
				if (((struct em_oioic *)(node->members))
					    ->iq.data != NULL)
					free(((struct em_oioic
						       *)(node->members))
						     ->iq.data);
				if (NULL == exotic_memory)
					free(p_ic);
				return R_N;
			}
			((struct em_oioic *)(node->members))->oq.front =
				((struct em_oioic *)(node->members))->oq.rear =
					NULL;
			((struct em_oioic *)(node->members))->oq.capacity =
				output_capacity;
			((struct em_oioic *)(node->members))->oq.quantity =
				((struct em_oioic *)(node->members))->oq.lost =
					0;
		}
		p += OIOIC_ALIGNED_SIZE(struct em_oioic);
	} else {
		return R_N;
	}

	if (NULL == exotic_memory)
		*object_out = (struct object *)p_ic;

	return R_P;
}
/* </crt> */
/* </oicc> */

/* Interface */

static int c_scroll_bar_open(struct object *self,
			     const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return c_scroll_bar_i_open(self, &caller);
}

static int c_scroll_bar_input(struct object *self, unsigned char *input_stream,
			      unsigned int quantity,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int c_scroll_bar_output(struct object *self,
			       unsigned char *output_stream,
			       unsigned int capacity,
			       unsigned int *output_quantity,
			       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int c_scroll_bar_io_put(struct object *self, unsigned char *input_stream,
			       unsigned int quantity,
			       unsigned char *output_stream,
			       unsigned int capacity,
			       unsigned int *output_quantity,
			       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int c_scroll_bar_interact0(struct object *self, unsigned int action,
				  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int c_scroll_bar_interact1(struct object *self, unsigned int action,
				  unsigned char *output_stream,
				  unsigned int capacity,
				  unsigned int *output_quantity,
				  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int c_scroll_bar_interact2(struct object *self, unsigned int action,
				  unsigned char *input_stream,
				  unsigned int quantity,
				  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int c_scroll_bar_interact3(struct object *self, unsigned int action,
				  unsigned char *input_stream,
				  unsigned int quantity,
				  unsigned char *output_stream,
				  unsigned int capacity,
				  unsigned int *output_quantity,
				  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int c_scroll_bar_close(struct object *self,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	return c_scroll_bar_i_close(self, &caller);
}

/* TOG */

void tog_c_scroll_bar(struct object *object)
{
	object->open = c_scroll_bar_open;
	object->input = c_scroll_bar_input;
	object->output = c_scroll_bar_output;
	object->io_put = c_scroll_bar_io_put;
	object->interact0 = c_scroll_bar_interact0;
	object->interact1 = c_scroll_bar_interact1;
	object->interact2 = c_scroll_bar_interact2;
	object->interact3 = c_scroll_bar_interact3;
	object->close = c_scroll_bar_close;
}

/* Function(s) */

int c_scroll_bar_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_cscrollbar *members = (struct em_cscrollbar *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->control_node = get_base_node(self, MSN_COBJECT);

		return RP_RCONE;
	}

	return R_P;
}

int c_scroll_bar_i_close(struct object *self, const struct vr *caller_context)
{

	if (0 == self->ref_count) {
		return RP_RCZERO;
	}

	return R_P;
}
