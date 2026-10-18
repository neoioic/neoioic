

#include <wchar.h>
#include "my_button.h"
#include "my_button_init_sub.h"
#include "../c_object/c_object.h"
#include "../c_button/c_button.h"

void tog_my_button(struct object *object);
static void load_bitmaps(struct object *self);
static void unload_bitmaps(struct object *self);

/* OICC label */

/* <oicc> */
/* <ibn> c_button </ibn> */
/* <crt> */
int crt_my_button(uint64_t *object_id, unsigned int input_capacity,
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
	extern void tog_neoioic(struct object * object);

	size_t ux_nd = 5;		     /* ND数量。 */
	size_t ux_bn = 10;		     /* 各ND的BN数量之和。 */
	size_t ux_ib = 4;		     /* 各ND的IBN数量之和。 */
	if (caller_capacity < 1 || (size_t)caller_capacity > USHRT_MAX / 5)
		return RN_INVALIDARG;
	size_t ux_cs = (size_t)caller_capacity * 15; /* 各ND的最少CS数量之和。 */
	size_t ux_em =
		NEOIOIC_ALIGNED_SIZE(struct em_mybutton) +
		NEOIOIC_ALIGNED_SIZE(struct em_cbutton) +
		NEOIOIC_ALIGNED_SIZE(struct em_cobject) +
		NEOIOIC_ALIGNED_SIZE(struct em_vobject) +
		NEOIOIC_ALIGNED_SIZE(struct em_neoioic); /* 各ND的void尺寸之和。 */

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

		/* my_button * */
		node = (struct object *)p_ic;
		tog_my_button(node);
		node->model_id = MSN_MYBUTTON;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* c_button * */
		tog_c_button(++node);
		node->model_id = MSN_CBUTTON;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* c_object * */
		tog_c_object(++node);
		node->model_id = MSN_COBJECT;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* v_object * */
		tog_v_object(++node);
		node->model_id = MSN_VOBJECT;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* NEOioic * */
		tog_neoioic(++node);
		node->model_id = MSN_NEOIOIC;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* 初始化各ND  ** */

		/* my_button * */
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
		base_msns[3] = MSN_NEOIOIC;
		init_base_nodes(node, base_msns, 4);
		p += sizeof(struct object *) * 4;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 1;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += NEOIOIC_ALIGNED_SIZE(struct em_mybutton);

		/* c_button * */
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
		base_msns[2] = MSN_NEOIOIC;
		init_base_nodes(node, base_msns, 3);
		p += sizeof(struct object *) * 3;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 2;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += NEOIOIC_ALIGNED_SIZE(struct em_cbutton);

		/* c_object * */
		++node;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_VOBJECT;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_VOBJECT;
		base_msns[1] = MSN_NEOIOIC;
		init_base_nodes(node, base_msns, 2);
		p += sizeof(struct object *) * 2;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 3;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += NEOIOIC_ALIGNED_SIZE(struct em_cobject);

		/* v_object * */
		++node;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_NEOIOIC;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_NEOIOIC;
		init_base_nodes(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 4;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		p += NEOIOIC_ALIGNED_SIZE(struct em_vobject);

		/* NEOioic * */
		++node;

		/* - ACS - */
		node->callers = (struct vr *)p;
		node->caller_count = caller_capacity * 5;
		p += sizeof(struct vr) * node->caller_count;

		/* - void - */
		node->members = (void *)p;
		if (input_capacity > 0) {
			/* - iq - */
			((struct em_neoioic *)(node->members))->iq.data =
				(unsigned char *)calloc(input_capacity, 1);
			if (NULL ==
			    ((struct em_neoioic *)(node->members))->iq.data) {
				/* 分配iq的容量失败！ */
				if (NULL == exotic_memory)
					free(p_ic);
				return R_N;
			}
			((struct em_neoioic *)(node->members))->iq.front =
				((struct em_neoioic *)(node->members))->iq.rear =
					NULL;
			((struct em_neoioic *)(node->members))->iq.capacity =
				input_capacity;
			((struct em_neoioic *)(node->members))->iq.quantity =
				((struct em_neoioic *)(node->members))->iq.lost =
					0;
		}

		if (output_capacity > 0) {
			/* - oq - */
			((struct em_neoioic *)(node->members))->oq.data =
				(unsigned char *)calloc(output_capacity, 1);
			if (NULL ==
			    ((struct em_neoioic *)(node->members))->oq.data) {
				/* 分配oq的容量失败！ */
				if (((struct em_neoioic *)(node->members))
					    ->iq.data != NULL)
					free(((struct em_neoioic
						       *)(node->members))
						     ->iq.data);
				if (NULL == exotic_memory)
					free(p_ic);
				return R_N;
			}
			((struct em_neoioic *)(node->members))->oq.front =
				((struct em_neoioic *)(node->members))->oq.rear =
					NULL;
			((struct em_neoioic *)(node->members))->oq.capacity =
				output_capacity;
			((struct em_neoioic *)(node->members))->oq.quantity =
				((struct em_neoioic *)(node->members))->oq.lost =
					0;
		}
		p += NEOIOIC_ALIGNED_SIZE(struct em_neoioic);
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

static int my_button_open(struct object *self, const struct vr *caller_context)
{
	struct em_mybutton *members;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	if (1 == self->ref_count) {
		members = (struct em_mybutton *)self->members;
		members->neoioic_node = get_base_node(self, MSN_NEOIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->control_node = get_base_node(self, MSN_COBJECT);
		members->p_c_button = get_base_node(self, MSN_CBUTTON);

		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON1_MY_BUTTON]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON2_MY_BUTTON]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON3_MY_BUTTON]);

		load_bitmaps(self);

		return RP_RCONE;
	}

	return R_P;
}

static int my_button_input(struct object *self, unsigned char *input_stream,
			   unsigned int quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int my_button_output(struct object *self, unsigned char *output_stream,
			    unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int my_button_io_put(struct object *self, unsigned char *input_stream,
			    unsigned int quantity, unsigned char *output_stream,
			    unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int my_button_interact0(struct object *self, unsigned int action,
			       const struct vr *caller_context)
{
	struct vr caller;
	struct em_mybutton *members = (struct em_mybutton *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	int i;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		for (i = 0; i < NUM_SUB_MY_BUTTON; i++) {
			switch (i) {
			case BUTTON1_MY_BUTTON:
			case BUTTON2_MY_BUTTON:
			case BUTTON3_MY_BUTTON:
				my_button_init_sub_button(self, i, &caller);
				break;
			default:
				break;
			}
		}

		pem_vob->p_first_sbdt = members->arr_sub[BUTTON1_MY_BUTTON];
		vo_interact0(members->visual_node, CMD_PREPARE, &caller);
		return R_P;
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int my_button_interact1(struct object *self, unsigned int action,
			       unsigned char *output_stream,
			       unsigned int capacity,
			       unsigned int *output_quantity,
			       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int my_button_interact2(struct object *self, unsigned int action,
			       unsigned char *input_stream,
			       unsigned int quantity,
			       const struct vr *caller_context)
{
	static struct object *s_p_sub_to_move = NULL;

	struct vr caller;
	struct em_mybutton *members = (struct em_mybutton *)self->members;
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
	case MSG_WGI_FOCUSOVER:
		/* _Debug_OutputString(TEXT("\nMSG_WGI_FOCUSOVER"), 123, NULL); */
		break;
	case MSG_WGI_FOCUSON:
		assert(sizeof(POINT) == quantity);
		vo_interact2(members->visual_node, MSG_WGI_FOCUSON,
			     input_stream, sizeof(POINT), &caller);
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

static int my_button_interact3(struct object *self, unsigned int action,
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

static int my_button_close(struct object *self, const struct vr *caller_context)
{
	struct vr caller;
	struct em_mybutton *members = (struct em_mybutton *)self->members;
	int i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	if (0 == self->ref_count) {
		unload_bitmaps(self);

		for (i = 0; i < NUM_SUB_MY_BUTTON; i++) {
			vo_close(members->arr_sub[i], &caller);
			destroy_object(members->arr_sub[i]);
		}

		return RP_RCZERO;
	}

	return R_P;
}

/* TOG */

void tog_my_button(struct object *object)
{
	object->open = my_button_open;
	object->input = my_button_input;
	object->output = my_button_output;
	object->io_put = my_button_io_put;
	object->interact0 = my_button_interact0;
	object->interact1 = my_button_interact1;
	object->interact2 = my_button_interact2;
	object->interact3 = my_button_interact3;
	object->close = my_button_close;
}

/* Function(s) */

static void load_bitmaps(struct object *self)
{
	struct em_mybutton *members = (struct em_mybutton *)self->members;
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));

	/* - Button - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button_normal.jpg"));
	members->arr_hbitmap[BUTTON_NORMAL_BMP_MY_BUTTON] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button_focus_over.jpg"));
	members->arr_hbitmap[BUTTON_FOCUS_OVER_BMP_MY_BUTTON] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button_focus_on.jpg"));
	members->arr_hbitmap[BUTTON_FOCUS_ON_BMP_MY_BUTTON] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button_active.jpg"));
	members->arr_hbitmap[BUTTON_ACTIVE_BMP_MY_BUTTON] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("button_abs_inactive.jpg"));
	members->arr_hbitmap[BUTTON_ABS_INACTIVE_BMP_MY_BUTTON] =
		load_picture_file(sz_file_path);

	return;
}

static void unload_bitmaps(struct object *self)
{
	struct em_mybutton *members = (struct em_mybutton *)self->members;
	int i;

	for (i = 0; i < NUM_BMP_MY_BUTTON; i++) {
		if (members->arr_hbitmap[i])
			DeleteObject(members->arr_hbitmap[i]);
	}

	return;
}
