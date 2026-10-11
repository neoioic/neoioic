

#include <wchar.h>
#include "MyButton2.h"
#include "MyButton2_InitSub.h"
#include "../CObject/CObject.h"
#include "../CButton/CButton.h"

void tog_my_button2(struct object *object);

/* OICC label */

/* <oicc> */
/* <ibn> CButton </ibn> */
/* <crt> */
int crt_my_button2(uint64_t *object_id, unsigned int input_capacity,
		   unsigned int output_capacity, int caller_capacity,
		   struct object **object_out, unsigned char *exotic_memory)
{
	extern void init_direct_bases(struct object * node,
				      unsigned short *base_msns,
				      unsigned short nib);
	extern void init_base_nodes(struct object * node,
				    unsigned short *base_msns,
				    unsigned short nbn);
	extern void tog_c_button(struct object * object);
	extern void tog_c_object(struct object * object);
	extern void tog_v_object(struct object * object);
	extern void tog_oioic(struct object * object);

	size_t ux_nd = 5;		     /* ND数量。 */
	size_t ux_bn = 10;		     /* 各ND的BN数量之和。 */
	size_t ux_ib = 4;		     /* 各ND的IBN数量之和。 */
	if (caller_capacity < 1 || (size_t)caller_capacity > USHRT_MAX / 5)
		return RN_INVALIDARG;
	size_t ux_cs = (size_t)caller_capacity * 15; /* 各ND的最少CS数量之和。 */
	size_t ux_em =
		OIOIC_ALIGNED_SIZE(struct em_mybutton2) +
		OIOIC_ALIGNED_SIZE(struct em_cbutton) +
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
		unsigned short base_msns[4];
		unsigned char *p = p_ic + sizeof(struct object) * ux_nd;

		/* 确定AND各元素  ** */

		/* MyButton2 * */
		node = (struct object *)p_ic;
		tog_my_button2(node);
		node->model_id = MSN_MYBUTTON2;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* CButton * */
		tog_c_button(++node);
		node->model_id = MSN_CBUTTON;
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

		/* MyButton2 * */
		node = (struct object *)p_ic;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_CBUTTON;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_CBUTTON;
		base_msns[1] = MSN_COBJECT;
		base_msns[2] = MSN_VOBJECT;
		base_msns[3] = MSN_OIOIC;
		init_base_nodes(node, base_msns, 4);
		p += sizeof(struct object *) * 4;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 1;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_mybutton2);

		/* CButton * */
		++node;

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
		node->caller_count = caller_capacity * 2;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_cbutton);

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
		node->caller_count = caller_capacity * 3;
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
		node->caller_count = caller_capacity * 4;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += OIOIC_ALIGNED_SIZE(struct em_vobject);

		/* OIOIC * */
		++node;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 5;
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

static int my_button2_open(struct object *self, const struct vr *caller_context)
{
	struct em_mybutton2 *members;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	if (1 == self->ref_count) {
		members = (struct em_mybutton2 *)self->members;
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->control_node = get_base_node(self, MSN_COBJECT);
		members->p_c_button = get_base_node(self, MSN_CBUTTON);

		create_object(MSN_MYBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON_MY_BUTTON2]);

		return RP_RCONE;
	}

	return R_P;
}

static int my_button2_input(struct object *self, unsigned char *input_stream,
			    unsigned int quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int my_button2_output(struct object *self, unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int my_button2_io_put(struct object *self, unsigned char *input_stream,
			     unsigned int quantity,
			     unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int my_button2_interact0(struct object *self, unsigned int action,
				const struct vr *caller_context)
{
	struct vr caller;
	struct em_mybutton2 *members = (struct em_mybutton2 *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	int i;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		for (i = 0; i < NUM_SUB_MY_BUTTON2; i++) {
			switch (i) {
			case BUTTON_MY_BUTTON2:
				my_button2_init_sub_button(self, i, &caller);
				break;
			default:
				break;
			}
		}

		pem_vob->p_first_sbdt = members->arr_sub[BUTTON_MY_BUTTON2];
		vo_interact0(members->visual_node, CMD_PREPARE, &caller);
		return R_P;
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int my_button2_interact1(struct object *self, unsigned int action,
				unsigned char *output_stream,
				unsigned int capacity,
				unsigned int *output_quantity,
				const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int my_button2_interact2(struct object *self, unsigned int action,
				unsigned char *input_stream,
				unsigned int quantity,
				const struct vr *caller_context)
{
	static struct object *s_p_sub_to_move = NULL;

	struct vr caller;
	struct em_mybutton2 *members = (struct em_mybutton2 *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_vobject *pem_vob_sbdt;
	POINT pt;
	struct move mv;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == quantity);

		if (pem_vob->p_cf_over_sbdt != NULL)
			vo_interact0(pem_vob->p_cf_over_sbdt, MSG_WGI_ACTIVATE,
				     &caller);

		vo_interact2(members->visual_node, MSG_WGI_FOCUSDOWN,
			     input_stream, sizeof(POINT), &caller);

		/* if(pem_vob->p_cf_down_sbdt != NULL) */
		/* pem->lastpt = *(POINT*)input_stream; */

		if (pem_vob->p_cf_down_sbdt != NULL) {
			pem_vob_sbdt = (struct em_vobject *)get_base_members(
				pem_vob->p_cf_down_sbdt, MSN_VOBJECT);
			if (NULL == pem_vob_sbdt->p_cf_down_sbdt) {
				s_p_sub_to_move = pem_vob->p_cf_down_sbdt;
				members->lastpt = *(POINT *)input_stream;
			} else {
				s_p_sub_to_move = NULL;
			}
		} else {
			s_p_sub_to_move = NULL;
		}

		return R_P;
	case MSG_WGI_FOCUSUP:
		assert(sizeof(POINT) == quantity);
		vo_interact2(members->visual_node, MSG_WGI_FOCUSUP,
			     input_stream, sizeof(POINT), &caller);
		s_p_sub_to_move = NULL;
		return R_P;
	case MSG_WGI_FOCUSONMOVE:
		assert(sizeof(POINT) == quantity);
		vo_interact2(members->visual_node, MSG_WGI_FOCUSONMOVE,
			     input_stream, sizeof(POINT), &caller);
		if (s_p_sub_to_move != NULL) {
			memset(&mv, 0, sizeof(struct move));
			pt = *(POINT *)input_stream;
			mv.dx_lr = mv.dx_ul = pt.x - members->lastpt.x;
			mv.dy_lr = mv.dy_ul = pt.y - members->lastpt.y;
			vo_interact2(s_p_sub_to_move, CMD_WGI_MOVE,
				     (unsigned char *)&mv, sizeof(struct move),
				     &caller);

			members->lastpt = pt;
		}
		return R_P;
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int my_button2_interact3(struct object *self, unsigned int action,
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

static int my_button2_close(struct object *self,
			    const struct vr *caller_context)
{
	struct vr caller;
	struct em_mybutton2 *members = (struct em_mybutton2 *)self->members;
	int i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	if (0 == self->ref_count) {
		for (i = 0; i < NUM_SUB_MY_BUTTON2; i++) {
			vo_close(members->arr_sub[i], &caller);
			destroy_object(members->arr_sub[i]);
		}

		return RP_RCZERO;
	}

	return R_P;
}

/* TOG */

void tog_my_button2(struct object *object)
{
	object->open = my_button2_open;
	object->input = my_button2_input;
	object->output = my_button2_output;
	object->io_put = my_button2_io_put;
	object->interact0 = my_button2_interact0;
	object->interact1 = my_button2_interact1;
	object->interact2 = my_button2_interact2;
	object->interact3 = my_button2_interact3;
	object->close = my_button2_close;
}

/* Function(s) */
