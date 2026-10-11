

#include "WMenu.h"
#include "../CObject/CObject.h"

void tog_w_menu(struct object *object);
int w_menu_i_open(struct object *self, const struct vr *caller_context);
int w_menu_i_close(struct object *self, const struct vr *caller_context);
int w_menu__cmd_prepare(struct object *self, const struct vr *caller_context);
int w_menu__cmd_initialize(struct object *self, const struct init_wmenu *piwmu,
			   const struct vr *caller_context);
int w_menu__cmd_run(struct object *self, const struct vr *caller_context);

static ATOM my_register_class(struct object *self);
static LRESULT CALLBACK cbf_w_menu_proc(HWND window_handle, UINT message,
					WPARAM wparam, LPARAM lparam);

/* OICC label */

/* <oicc> */
/* <ibn> WPanel </ibn> */
/* <crt> */
int crt_w_menu(uint64_t *object_id, unsigned int input_capacity,
	       unsigned int output_capacity, int caller_capacity,
	       struct object **object_out, unsigned char *exotic_memory)
{
	extern void init_direct_bases(struct object * node,
				      unsigned short *base_msns,
				      unsigned short nib);
	extern void init_base_nodes(struct object * node,
				    unsigned short *base_msns,
				    unsigned short nbn);
	extern void tog_w_panel(struct object * object);
	extern void tog_w_object(struct object * object);
	extern void tog_v_object(struct object * object);
	extern void tog_oioic(struct object * object);

	size_t ux_nd = 5;		     /* ND数量。 */
	size_t ux_bn = 10;		     /* 各ND的BN数量之和。 */
	size_t ux_ib = 4;		     /* 各ND的IBN数量之和。 */
	if (caller_capacity < 1 || (size_t)caller_capacity > USHRT_MAX / 5)
		return RN_INVALIDARG;
	size_t ux_cs = (size_t)caller_capacity * 15; /* 各ND的最少CS数量之和。 */
	size_t ux_em =
		OIOIC_ALIGNED_SIZE(struct em_wmenu) +
		OIOIC_ALIGNED_SIZE(struct em_wpanel) +
		OIOIC_ALIGNED_SIZE(struct em_wobject) +
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

		/* WMenu * */
		node = (struct object *)p_ic;
		tog_w_menu(node);
		node->model_id = MSN_WMENU;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* WPanel * */
		tog_w_panel(++node);
		node->model_id = MSN_WPANEL;
		node->oid = (*object_id)++;
		node->nodes = (struct object *)p_ic;
		node->node_count = ux_nd;

		/* WObject * */
		tog_w_object(++node);
		node->model_id = MSN_WOBJECT;
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

		/* WMenu * */
		node = (struct object *)p_ic;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_WPANEL;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_WPANEL;
		base_msns[1] = MSN_WOBJECT;
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
		p += OIOIC_ALIGNED_SIZE(struct em_wmenu);

		/* WPanel * */
		++node;

		/* - AIB - */
		node->direct_bases = (struct object **)p;
		base_msns[0] = MSN_WOBJECT;
		init_direct_bases(node, base_msns, 1);
		p += sizeof(struct object *) * 1;

		/* - ABN - */
		node->bases = (struct object **)p;
		base_msns[0] = MSN_WOBJECT;
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
		p += OIOIC_ALIGNED_SIZE(struct em_wpanel);

		/* WObject * */
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
		p += OIOIC_ALIGNED_SIZE(struct em_wobject);

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

static int w_menu_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return w_menu_i_open(self, &caller);
}

static int w_menu_input(struct object *self, unsigned char *input_stream,
			unsigned int quantity, const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int w_menu_output(struct object *self, unsigned char *output_stream,
			 unsigned int capacity, unsigned int *output_quantity,
			 const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int w_menu_io_put(struct object *self, unsigned char *input_stream,
			 unsigned int quantity, unsigned char *output_stream,
			 unsigned int capacity, unsigned int *output_quantity,
			 const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int w_menu_interact0(struct object *self, unsigned int action,
			    const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		return w_menu__cmd_prepare(self, &caller);
	case CMD_RUN:
		return w_menu__cmd_run(self, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int w_menu_interact1(struct object *self, unsigned int action,
			    unsigned char *output_stream, unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int w_menu_interact2(struct object *self, unsigned int action,
			    unsigned char *input_stream, unsigned int quantity,
			    const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_INITIALIZE:
		assert(sizeof(struct init_wmenu) == quantity);
		return w_menu__cmd_initialize(
			self, (struct init_wmenu *)input_stream, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int w_menu_interact3(struct object *self, unsigned int action,
			    unsigned char *input_stream, unsigned int quantity,
			    unsigned char *output_stream, unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int w_menu_close(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	return w_menu_i_close(self, &caller);
}

/* TOG */

void tog_w_menu(struct object *object)
{
	object->open = w_menu_open;
	object->input = w_menu_input;
	object->output = w_menu_output;
	object->io_put = w_menu_io_put;
	object->interact0 = w_menu_interact0;
	object->interact1 = w_menu_interact1;
	object->interact2 = w_menu_interact2;
	object->interact3 = w_menu_interact3;
	object->close = w_menu_close;
}

/* Function(s) */

static ATOM my_register_class(struct object *self)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)cbf_w_menu_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = pem_wob->instance;
	wc.hIcon = LoadIcon(pem_wob->instance, MAKEINTRESOURCE(IDI_WGIDEMO));
	wc.hCursor = NULL; /* LoadCursor(NULL, IDC_ARROW); */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = pem_wob->p_class_name;

	return RegisterClass(&wc);
}

/* Initialize Top Rolling Button */
static void init_tr_button(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	struct em_vobject *pem_vob_sbdt;
	struct init_vobject ivob;
	struct init_cobject icob;
	int n;

	assert(members->p_tr_button != NULL);

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	ivob.p_superior = self;
	ivob.style |= VOBS_NOSEMIACTIVE | VOBS_YIRROLLABLE;
	ivob.state = VOB_STATE_NORMAL;

	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	ivob.rsc.rcouter.right = n;
	ivob.rsc.rcinner.right = n;
	ivob.rsc.rcinner.bottom = members->n_rb_height;
	ivob.scenew = n;
	ivob.sceneh = members->n_rb_height;
	icob.p_wnd_handle = &pem_wob->window_handle;

	ivob.rsc.rcouter.bottom = members->n_rb_height;
	ivob.arr_hbitmap[VOB_STATE_NORMAL] = members->h_bmp_trb_normal;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] = members->h_bmp_trb_focus_over;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] = members->h_bmp_trb_focus_on;

	pem_vob_sbdt = (struct em_vobject *)get_base_members(
		pem_vob->p_first_sbdt, MSN_VOBJECT);
	ivob.p_prev_codt = pem_vob_sbdt->p_prev_codt;
	pem_vob_sbdt->p_prev_codt = members->p_tr_button;
	ivob.p_next_codt = pem_vob->p_first_sbdt;
	pem_vob_sbdt = (struct em_vobject *)get_base_members(ivob.p_prev_codt,
							     MSN_VOBJECT);
	pem_vob_sbdt->p_next_codt = members->p_tr_button;

	vo_open(members->p_tr_button, caller_context);
	vo_interact2(get_base_node(members->p_tr_button, MSN_VOBJECT),
		     CMD_INITIALIZE, (unsigned char *)&ivob,
		     sizeof(struct init_vobject), caller_context);
	vo_interact2(get_base_node(members->p_tr_button, MSN_COBJECT),
		     CMD_INITIALIZE, (unsigned char *)&icob,
		     sizeof(struct init_cobject), caller_context);
	vo_interact0(members->p_tr_button, CMD_PREPARE, caller_context);

	return;
}

/* Initialize Bottom Rolling Button */
static void init_br_button(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	struct em_vobject *pem_vob_sbdt;
	struct init_vobject ivob;
	struct init_cobject icob;
	int n;

	assert(members->p_br_button != NULL);

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	ivob.p_superior = self;
	ivob.style |= VOBS_NOSEMIACTIVE | VOBS_YIRROLLABLE;
	ivob.state = VOB_STATE_NORMAL;

	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	ivob.rsc.rcouter.right = n;
	ivob.rsc.rcinner.right = n;
	ivob.rsc.rcinner.bottom = members->n_rb_height;
	ivob.scenew = n;
	ivob.sceneh = members->n_rb_height;
	icob.p_wnd_handle = &pem_wob->window_handle;

	ivob.rsc.rcouter.top =
		pem_vob->rsc.rcinner.bottom - members->n_rb_height;
	ivob.rsc.rcouter.bottom = pem_vob->rsc.rcinner.bottom;
	ivob.arr_hbitmap[VOB_STATE_NORMAL] = members->h_bmp_brb_normal;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] = members->h_bmp_brb_focus_over;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] = members->h_bmp_brb_focus_on;

	if (members->p_tr_button != NULL) {
		ivob.p_next_codt = members->p_tr_button;
		pem_vob_sbdt = (struct em_vobject *)get_base_members(
			members->p_tr_button, MSN_VOBJECT);
	} else {
		ivob.p_next_codt = pem_vob->p_first_sbdt;
		pem_vob_sbdt = (struct em_vobject *)get_base_members(
			pem_vob->p_first_sbdt, MSN_VOBJECT);
	}
	ivob.p_prev_codt = pem_vob_sbdt->p_prev_codt;
	pem_vob_sbdt->p_prev_codt = members->p_br_button;
	pem_vob_sbdt = (struct em_vobject *)get_base_members(ivob.p_prev_codt,
							     MSN_VOBJECT);
	pem_vob_sbdt->p_next_codt = members->p_br_button;

	vo_open(members->p_br_button, caller_context);
	vo_interact2(get_base_node(members->p_br_button, MSN_VOBJECT),
		     CMD_INITIALIZE, (unsigned char *)&ivob,
		     sizeof(struct init_vobject), caller_context);
	vo_interact2(get_base_node(members->p_br_button, MSN_COBJECT),
		     CMD_INITIALIZE, (unsigned char *)&icob,
		     sizeof(struct init_cobject), caller_context);
	vo_interact0(members->p_br_button, CMD_PREPARE, caller_context);

	return;
}

/* Destroy Top Rolling Button */
static void destroy_tr_button(struct object *self,
			      const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_vobject *pem_vob_sbdt;
	struct em_vobject *pem_vob_sbdt2;

	assert(members->p_tr_button != NULL);

	if (pem_vob->p_active_sbdt == members->p_tr_button)
		pem_vob->p_active_sbdt = NULL;
	if (pem_vob->p_cf_down_sbdt == members->p_tr_button)
		pem_vob->p_cf_down_sbdt = NULL;
	if (pem_vob->p_cf_on_sbdt == members->p_tr_button)
		pem_vob->p_cf_on_sbdt = NULL;
	if (pem_vob->p_cf_over_sbdt == members->p_tr_button)
		pem_vob->p_cf_over_sbdt = NULL;
	if (pem_vob->p_cf_up_sbdt == members->p_tr_button)
		pem_vob->p_cf_up_sbdt = NULL;

	pem_vob_sbdt = (struct em_vobject *)get_base_members(
		members->p_tr_button, MSN_VOBJECT);
	pem_vob_sbdt2 = (struct em_vobject *)get_base_members(
		pem_vob_sbdt->p_prev_codt, MSN_VOBJECT);
	pem_vob_sbdt2->p_next_codt = pem_vob_sbdt->p_next_codt;
	pem_vob_sbdt2 = (struct em_vobject *)get_base_members(
		pem_vob_sbdt->p_next_codt, MSN_VOBJECT);
	pem_vob_sbdt2->p_prev_codt = pem_vob_sbdt->p_prev_codt;
	vo_close(members->p_tr_button, caller_context);
	destroy_object(members->p_tr_button);

	return;
}

/* Destroy Bottom Rolling Button */
static void destroy_br_button(struct object *self,
			      const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_vobject *pem_vob_sbdt;
	struct em_vobject *pem_vob_sbdt2;

	assert(members->p_br_button != NULL);

	if (pem_vob->p_active_sbdt == members->p_br_button)
		pem_vob->p_active_sbdt = NULL;
	if (pem_vob->p_cf_down_sbdt == members->p_br_button)
		pem_vob->p_cf_down_sbdt = NULL;
	if (pem_vob->p_cf_on_sbdt == members->p_br_button)
		pem_vob->p_cf_on_sbdt = NULL;
	if (pem_vob->p_cf_over_sbdt == members->p_br_button)
		pem_vob->p_cf_over_sbdt = NULL;
	if (pem_vob->p_cf_up_sbdt == members->p_br_button)
		pem_vob->p_cf_up_sbdt = NULL;

	pem_vob_sbdt = (struct em_vobject *)get_base_members(
		members->p_br_button, MSN_VOBJECT);
	pem_vob_sbdt2 = (struct em_vobject *)get_base_members(
		pem_vob_sbdt->p_prev_codt, MSN_VOBJECT);
	pem_vob_sbdt2->p_next_codt = pem_vob_sbdt->p_next_codt;
	pem_vob_sbdt2 = (struct em_vobject *)get_base_members(
		pem_vob_sbdt->p_next_codt, MSN_VOBJECT);
	pem_vob_sbdt2->p_prev_codt = pem_vob_sbdt->p_prev_codt;
	vo_close(members->p_br_button, caller_context);
	destroy_object(members->p_br_button);

	return;
}

/* Mesage handler for WMenu. */
static LRESULT CALLBACK cbf_w_menu_proc(HWND window_handle, UINT message,
					WPARAM wparam, LPARAM lparam)
{
	struct vr caller;
	struct object *self;
	struct em_wmenu *members;
	struct em_vobject *pem_vob;
	struct em_vobject *pem_vob_sbdt;
	struct em_vobject *pem_vob_sbdt2;
	PAINTSTRUCT ps;
	POINT pt;
	struct irrollingdelta irrd;
	unsigned int qty;
	int n;

	caller.cr = OID_MAIN;

	switch (message) {
	case WM_INITDIALOG:
		/* self = (struct object*)GetWindowLongPtr(window_handle, GWLP_USERDATA); */
		break;
	case WM_PAINT:
		if (NULL == (self = (struct object *)GetWindowLongPtr(
				     window_handle, GWLP_USERDATA)))
			break;
		members = (struct em_wmenu *)self->members;
		caller.mr = self->oid;
		BeginPaint(window_handle, &ps);
		vo_interact0(members->panel_node, CMD_WGI_PAINT, &caller);
		EndPaint(window_handle, &ps);
		break;
	case WM_MOUSEACTIVATE:
		return MA_NOACTIVATEANDEAT; /* 不激活菜单。 */
	case WM_MOUSEMOVE:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_wmenu *)self->members;
		caller.mr = self->oid;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);
		if (wparam != MK_LBUTTON) {
			vo_interact2(members->panel_node, MSG_WGI_FOCUSOVERMOVE,
				     (unsigned char *)&pt, sizeof(POINT),
				     &caller);
			if (pem_vob->p_cf_over_sbdt !=
			    members->p_cf_over_sbdt) {
				if (members->p_sub_menu) {
					vo_close(members->p_sub_menu, &caller);
					destroy_object(members->p_sub_menu);
				}

				if (pem_vob->p_cf_over_sbdt != NULL) {
					if (pem_vob->p_cf_over_sbdt ==
					    members->p_tr_button) {
						/* _Debug_OutputString(TEXT("\nif(pem_vob->p_cf_over_sbdt == pem->p_tr_button)"), 123, NULL); */
						if (members->timerid != 0) {
							if (members->rollstep <
							    0) /* 当前的定时器是底端滚动按钮的？ */
							{
								KillTimer(
									window_handle,
									members->timerid);
								members->rollstep =
									-members->rollstep;
								members->timerid = SetTimer(
									window_handle,
									1,
									members->timertov,
									NULL); /* nIDEvent参数为1，表示是顶端滚动按钮的定时器。 */
							}
						} else {
							if (members->rollstep <
							    0)
								members->rollstep =
									-members->rollstep;

							if (NULL ==
							    members->p_br_button) {
								create_object(
									MSN_CBUTTON,
									0, 0, 1,
									&members->p_br_button);
								init_br_button(
									self,
									&caller);
								vo_interact0(
									members->panel_node,
									CMD_WGI_REPAINT,
									&caller);
							}

							members->timerid = SetTimer(
								window_handle,
								1,
								members->timertov,
								NULL); /* nIDEvent参数为1，表示是顶端滚动按钮的定时器。 */
						}
					} else if (pem_vob->p_cf_over_sbdt ==
						   members->p_br_button) {
						if (members->timerid != 0) {
							if (members->rollstep >
							    0) /* 当前的定时器是顶端滚动按钮的？ */
							{
								KillTimer(
									window_handle,
									members->timerid);
								members->rollstep =
									-members->rollstep;
								members->timerid = SetTimer(
									window_handle,
									2,
									members->timertov,
									NULL); /* nIDEvent参数为2，表示是底端滚动按钮的定时器。 */
							}
						} else {
							if (members->rollstep >
							    0)
								members->rollstep =
									-members->rollstep;

							if (NULL ==
							    members->p_tr_button) {
								create_object(
									MSN_CBUTTON,
									0, 0, 1,
									&members->p_tr_button);
								init_tr_button(
									self,
									&caller);
								vo_interact0(
									members->panel_node,
									CMD_WGI_REPAINT,
									&caller);
							}
							members->timerid = SetTimer(
								window_handle,
								2,
								members->timertov,
								NULL); /* nIDEvent参数为2，表示是底端滚动按钮的定时器。 */
						}
					} else {
						if (members->timerid != 0) {
							KillTimer(
								window_handle,
								members->timerid);
							members->timerid = 0;
						}

						if (members->p_tr_button !=
							    NULL ||
						    members->p_br_button !=
							    NULL) {
							irrd.dx = 0;
							pem_vob_sbdt = (struct
									em_vobject
										*)
								get_base_members(
									pem_vob->p_cf_over_sbdt,
									MSN_VOBJECT);
							if (members->p_tr_button !=
							    NULL) {
								pem_vob_sbdt2 = (struct
										 em_vobject
											 *)
									get_base_members(
										members->p_tr_button,
										MSN_VOBJECT);
								if (is_inter2_rects(
									    &pem_vob_sbdt
										     ->rsc
										     .rcouter,
									    &pem_vob_sbdt2
										     ->rsc
										     .rcouter,
									    NULL)) {
									if (NULL ==
									    members->p_br_button) {
										create_object(
											MSN_CBUTTON,
											0,
											0,
											1,
											&members->p_br_button);
										init_br_button(
											self,
											&caller);
									}
									irrd.dy =
										pem_vob_sbdt2
											->rsc
											.rcouter
											.bottom -
										pem_vob_sbdt
											->rsc
											.rcouter
											.top;
									vo_interact2(
										members->visual_node,
										CMD_WGI_ROLLIR,
										(unsigned char
											 *)&irrd,
										sizeof(struct
										       irrollingdelta),
										&caller);
									if (0 ==
									    pem_vob->oy_irr) {
										destroy_tr_button(
											self,
											&caller);
										vo_interact0(
											members->panel_node,
											CMD_WGI_REPAINT,
											&caller);
									}
								} else if (
									members->p_br_button !=
									NULL) {
									pem_vob_sbdt2 = (struct
											 em_vobject
												 *)
										get_base_members(
											members->p_br_button,
											MSN_VOBJECT);
									if (is_inter2_rects(
										    &pem_vob_sbdt
											     ->rsc
											     .rcouter,
										    &pem_vob_sbdt2
											     ->rsc
											     .rcouter,
										    NULL)) {
										irrd.dy =
											pem_vob_sbdt2
												->rsc
												.rcouter
												.top -
											pem_vob_sbdt
												->rsc
												.rcouter
												.bottom;
										vo_interact2(
											members->visual_node,
											CMD_WGI_ROLLIR,
											(unsigned char
												 *)&irrd,
											sizeof(struct
											       irrollingdelta),
											&caller);
									}
								}
							} else /* members->p_br_button != NULL */
							{
								pem_vob_sbdt2 = (struct
										 em_vobject
											 *)
									get_base_members(
										members->p_br_button,
										MSN_VOBJECT);
								if (is_inter2_rects(
									    &pem_vob_sbdt
										     ->rsc
										     .rcouter,
									    &pem_vob_sbdt2
										     ->rsc
										     .rcouter,
									    NULL)) {
									irrd.dy =
										pem_vob_sbdt2
											->rsc
											.rcouter
											.top -
										pem_vob_sbdt
											->rsc
											.rcouter
											.bottom;
									create_object(
										MSN_CBUTTON,
										0,
										0,
										1,
										&members->p_tr_button);
									init_tr_button(
										self,
										&caller);
									vo_interact2(
										members->visual_node,
										CMD_WGI_ROLLIR,
										(unsigned char
											 *)&irrd,
										sizeof(struct
										       irrollingdelta),
										&caller);
								}
							}
						}
						vo_interact3(
							members->p_parent,
							MSG_WGI_MENUITEMFOCUSOVER,
							(unsigned char
								 *)&pem_vob
								->p_cf_over_sbdt,
							sizeof(struct object *),
							(unsigned char
								 *)&members
								->p_sub_menu,
							sizeof(struct object *),
							&qty, &caller);
					}
				}

				members->p_cf_over_sbdt =
					pem_vob->p_cf_over_sbdt;
			}
		} else {
			vo_interact2(members->panel_node, MSG_WGI_FOCUSONMOVE,
				     (unsigned char *)&pt, sizeof(POINT),
				     &caller);
		}
		break;
	case WM_LBUTTONDOWN:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_wmenu *)self->members;

		caller.mr = self->oid;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);

		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);

		vo_interact2(members->panel_node, MSG_WGI_FOCUSDOWN,
			     (unsigned char *)&pt, sizeof(POINT), &caller);
		vo_interact2(members->panel_node, MSG_WGI_FOCUSON,
			     (unsigned char *)&pt, sizeof(POINT), &caller);

		if (pem_vob->p_cf_down_sbdt != NULL) {
		}

		break;
	case WM_LBUTTONUP:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_wmenu *)self->members;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		caller.mr = self->oid;
		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);
		vo_interact2(members->panel_node, MSG_WGI_FOCUSUP,
			     (unsigned char *)&pt, sizeof(POINT), &caller);
		break;
	case WM_KEYDOWN:
		/* self = (struct object*)GetWindowLongPtr(window_handle, GWLP_USERDATA); */
		break;
	case WM_CHAR:
		/* self = (struct object*)GetWindowLongPtr(window_handle, GWLP_USERDATA); */
		break;
	case WM_TIMER:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_wmenu *)self->members;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		caller.mr = self->oid;

		irrd.dx = 0;
		irrd.dy = members->rollstep;
		n = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top -
		    pem_vob->sceneh;

		if (members->rollstep > 0) /* 顶端滚动按钮的定时器？ */
		{
			if (pem_vob->oy_irr + irrd.dy >= 0) {
				destroy_tr_button(self, &caller);
				KillTimer(window_handle, members->timerid);
				members->timerid = 0;

				vo_interact2(
					members->visual_node, CMD_WGI_ROLLIR,
					(unsigned char *)&irrd,
					sizeof(struct irrollingdelta), &caller);
				/*
				 *  因为之前的一些当前焦点事件下级对象（如当前焦点OVER下级对象、当前焦点ON下级对象等等）
				 * 				就是这个滚动按钮对象，所以销毁滚动按钮后，需要触发一次焦点移动事件，更新当前焦点事件下级对象。
				 */
				GetCursorPos(&pt);
				SetCursorPos(pt.x, pt.y);
				break;
			}
		} else if (pem_vob->oy_irr + irrd.dy <=
			   n) /* 否则就是底端滚动按钮的定时器。 */
		{
			destroy_br_button(self, &caller);
			KillTimer(window_handle, members->timerid);
			members->timerid = 0;

			vo_interact2(members->visual_node, CMD_WGI_ROLLIR,
				     (unsigned char *)&irrd,
				     sizeof(struct irrollingdelta), &caller);
			/*
			 *  因为之前的一些当前焦点事件下级对象（如当前焦点OVER下级对象、当前焦点ON下级对象等等）
			 * 			就是这个滚动按钮对象，所以销毁滚动按钮后，需要触发一次焦点移动事件，更新当前焦点事件下级对象。
			 */
			GetCursorPos(&pt);
			SetCursorPos(pt.x, pt.y);
			break;
		}

		vo_interact2(members->visual_node, CMD_WGI_ROLLIR,
			     (unsigned char *)&irrd,
			     sizeof(struct irrollingdelta), &caller);
		break;
	case WM_ERASEBKGND:
		return TRUE; /* 消除移动窗口闪烁。 */
	case WM_CLOSE:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_wmenu *)self->members;
		caller.mr = self->oid;
		if (members->timerid != 0)
			KillTimer(window_handle, members->timerid);
		vo_interact0(members->window_node, DTR_WGI_WINDOW, &caller);
		break;
	default:
		return DefWindowProc(window_handle, message, wparam, lparam);
	}

	return TRUE;
}

int w_menu_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->window_node = get_base_node(self, MSN_WOBJECT);
		members->panel_node = get_base_node(self, MSN_WPANEL);

		return RP_RCONE;
	}

	return R_P;
}

int w_menu_i_close(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;

	if (0 == self->ref_count) {
		if (members->p_sub_menu) {
			vo_close(members->p_sub_menu, caller_context);
			destroy_object(members->p_sub_menu);
		}

		if (members->p_tr_button)
			destroy_tr_button(self, caller_context);

		if (members->p_br_button)
			destroy_br_button(self, caller_context);

		SendMessage(pem_wob->window_handle, WM_CLOSE, 0, 0);
		members->destroy_items(self, caller_context);
		return RP_RCZERO;
	}

	return R_P;
}

int w_menu__cmd_initialize(struct object *self, const struct init_wmenu *piwmu,
			   const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct object *object;

	object = get_base_node(self, MSN_VOBJECT);
	vo_interact2(object, CMD_INITIALIZE, (unsigned char *)&piwmu->ivob,
		     sizeof(struct init_vobject), caller_context);
	object = get_base_node(self, MSN_WOBJECT);
	vo_interact2(object, CMD_INITIALIZE, (unsigned char *)&piwmu->iwob,
		     sizeof(struct init_wobject), caller_context);

	members->p_parent = piwmu->p_parent;
	members->n_rb_height = piwmu->n_rb_height;
	members->uca = piwmu->uca;
	members->type = piwmu->type;
	members->width = piwmu->width;
	members->h_bmp_brb_focus_on = piwmu->h_bmp_brb_focus_on;
	members->h_bmp_brb_focus_over = piwmu->h_bmp_brb_focus_over;
	members->h_bmp_brb_normal = piwmu->h_bmp_brb_normal;
	members->h_bmp_trb_focus_on = piwmu->h_bmp_trb_focus_on;
	members->h_bmp_trb_focus_over = piwmu->h_bmp_trb_focus_over;
	members->h_bmp_trb_normal = piwmu->h_bmp_trb_normal;
	members->timertov = piwmu->timertov != 0 ? piwmu->timertov : 100;
	members->rollstep = piwmu->rollstep != 0 ? piwmu->rollstep : 10;
	members->create_items = piwmu->create_items;
	members->destroy_items = piwmu->destroy_items;

	return R_P;
}

int w_menu__cmd_prepare(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	struct em_wobject *pem_wob_par;
	struct em_vobject *pem_vob_sbdt;
	struct object *object;
	int n, m, k, w, h;

	my_register_class(self);

	/* >>> 不调用基节点 WObject 的 CRT_WGI_WINDOW 行为创建窗口，单独实现。 */

	pem_wob_par = (struct em_wobject *)get_base_members(members->p_parent,
							    MSN_WOBJECT);
	pem_wob->window_handle =
		CreateWindowEx(0, pem_wob->p_class_name, pem_wob->p_window_name,
			       WS_POPUP, 0, 0, 0, 0, pem_wob_par->window_handle,
			       NULL, pem_wob->instance, NULL);

	if (NULL == pem_wob->window_handle)
		return R_N;

	pem_vob->p_wnd_handle = &pem_wob->window_handle;
	SetWindowLongPtr(pem_wob->window_handle, GWLP_USERDATA,
			 (LONG_PTR)self->nodes);

	/* 不调用基节点 WObject 的 CRT_WGI_WINDOW 行为创建窗口，单独实现。<<< */

	members->create_items(self, caller_context);
	assert(pem_vob->p_first_sbdt);

	if (0 == pem_vob->rsc.rcouter.bottom &&
	    0 == pem_vob->rsc.rcouter.left && 0 == pem_vob->rsc.rcouter.right &&
	    0 == pem_vob->rsc.rcouter.top) {
		w = GetSystemMetrics(SM_CXSCREEN);
		h = GetSystemMetrics(SM_CYSCREEN);

		n = h - members->uca.bottom;
		m = n > members->uca.top ? n : members->uca.top;
		n = 0;
		object = pem_vob->p_first_sbdt;
		do {
			pem_vob_sbdt = (struct em_vobject *)get_base_members(
				object, MSN_VOBJECT);
			n += pem_vob_sbdt->rsc.rcouter.bottom -
			     pem_vob_sbdt->rsc.rcouter.top;
			if (MNUT_TBLEFT == members->type ||
			    MNUT_TBRIGHT == members->type) {
				if (n > m) {
					n = m;
					assert(NULL == members->p_br_button);
					create_object(MSN_CBUTTON, 0, 0, 1,
						      &members->p_br_button);
					break;
				}
			} else {
				if (n > h) {
					n = h;
					assert(NULL == members->p_br_button);
					create_object(MSN_CBUTTON, 0, 0, 1,
						      &members->p_br_button);
					break;
				}
			}
			object = pem_vob_sbdt->p_next_codt;
		} while (object != pem_vob->p_first_sbdt);

		if (MNUT_TBLEFT == members->type) {
			m = h - members->uca.bottom;
			if (n <= m)
				pem_vob->rsc.rcouter.top = members->uca.bottom;
			else
				pem_vob->rsc.rcouter.top = members->uca.top - n;

			pem_vob->rsc.rcouter.left = members->uca.left;
			pem_vob->rsc.rcouter.right =
				pem_vob->rsc.rcouter.left + members->width;
			pem_vob->rsc.rcouter.bottom =
				pem_vob->rsc.rcouter.top + n;

			if (pem_vob->rsc.rcouter.left <
			    0) /* 菜单超出桌面的左边缘？ */
			{
				m = -pem_vob->rsc.rcouter.left;
				pem_vob->rsc.rcouter.right += m;
				pem_vob->rsc.rcouter.left = 0;
			} else if (
				pem_vob->rsc.rcouter.right > w &&
				pem_vob->rsc.rcouter.left >
					0) /* 菜单超出桌面的右边缘，并且菜单左边距桌面左边缘还有一定距离？ */
			{
				k = pem_vob->rsc.rcouter.right - w;
				m = k > pem_vob->rsc.rcouter.left
					    ? pem_vob->rsc.rcouter.left
					    : k;
				pem_vob->rsc.rcouter.left -= m;
				pem_vob->rsc.rcouter.right -= m;
			}

		} else if (MNUT_TBRIGHT == members->type) {
			m = h - members->uca.bottom;
			if (n <= m)
				pem_vob->rsc.rcouter.top = members->uca.bottom;
			else
				pem_vob->rsc.rcouter.top = members->uca.top - n;

			pem_vob->rsc.rcouter.right = members->uca.right;
			pem_vob->rsc.rcouter.left =
				pem_vob->rsc.rcouter.right - members->width;
			pem_vob->rsc.rcouter.bottom =
				pem_vob->rsc.rcouter.top + n;

			if (pem_vob->rsc.rcouter.right >
			    w) /* 菜单超出桌面的右边缘？ */
			{
				m = pem_vob->rsc.rcouter.right - w;
				pem_vob->rsc.rcouter.right -= m;
				pem_vob->rsc.rcouter.left -= m;
			} else if (
				pem_vob->rsc.rcouter.left < 0 &&
				pem_vob->rsc.rcouter.right <
					w) /* 菜单超出桌面的左边缘，并且菜单右边距桌面右边缘还有一定距离？ */
			{
				k = w - pem_vob->rsc.rcouter.right;
				m = k > -pem_vob->rsc.rcouter.left
					    ? -pem_vob->rsc.rcouter.left
					    : k;
				pem_vob->rsc.rcouter.left += m;
				pem_vob->rsc.rcouter.right += m;
			}
		} else if (MNUT_LRTOP == members->type) {
			if (n <= h) {
				pem_vob->rsc.rcouter.top =
					h - members->uca.top > n
						? members->uca.top
						: h - n;
				pem_vob->rsc.rcouter.bottom = n;
			} else {
				pem_vob->rsc.rcouter.top = 0;
				pem_vob->rsc.rcouter.bottom = h;
			}

			m = w - members->uca.right;
			if (members->width < m ||
			    members->uca.left <
				    m) /* 判断是否需要改为左贴近。 */
			{
				pem_vob->rsc.rcouter.left = members->uca.right;
				pem_vob->rsc.rcouter.right =
					pem_vob->rsc.rcouter.left +
					members->width;
			} else /* 需要改为左贴近。 */
			{
				pem_vob->rsc.rcouter.left =
					members->uca.left - members->width;
				pem_vob->rsc.rcouter.right = members->uca.right;
			}
		} else if (MNUT_LRBOTTOM == members->type) {
			if (n <= h) {
				pem_vob->rsc.rcouter.top =
					members->uca.bottom > n
						? members->uca.bottom - n
						: 0;
				pem_vob->rsc.rcouter.bottom =
					pem_vob->rsc.rcouter.top + n;
			} else {
				pem_vob->rsc.rcouter.top = 0;
				pem_vob->rsc.rcouter.bottom = h;
			}

			m = w - members->uca.right;
			if (members->width < m ||
			    members->uca.left <
				    m) /* 判断是否需要改为左贴近。 */
			{
				pem_vob->rsc.rcouter.left = members->uca.right;
				pem_vob->rsc.rcouter.right =
					pem_vob->rsc.rcouter.left +
					members->width;
			} else /* 需要改为左贴近。 */
			{
				pem_vob->rsc.rcouter.left =
					members->uca.left - members->width;
				pem_vob->rsc.rcouter.right = members->uca.left;
			}
		}
	}

	if (0 == pem_vob->rsc.rcinner.bottom &&
	    0 == pem_vob->rsc.rcinner.left && 0 == pem_vob->rsc.rcinner.right &&
	    0 == pem_vob->rsc.rcinner.top) {
		pem_vob->rsc.rcinner.top = 0;
		pem_vob->rsc.rcinner.left = 0;
		pem_vob->rsc.rcinner.right =
			pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left;
		pem_vob->rsc.rcinner.bottom =
			pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top;
	}

	if (0 == pem_vob->scenew)
		pem_vob->scenew =
			pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	if (0 == pem_vob->sceneh)
		pem_vob->sceneh =
			pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;

	if (members->p_tr_button != NULL)
		init_tr_button(self, caller_context);
	if (members->p_br_button != NULL)
		init_br_button(self, caller_context);

	SetWindowPos(pem_wob->window_handle, HWND_TOPMOST,
		     pem_vob->rsc.rcouter.left, pem_vob->rsc.rcouter.top,
		     pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left,
		     pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top,
		     SWP_HIDEWINDOW | SWP_NOACTIVATE);

	vo_interact0(members->visual_node, CMD_PREPARE, caller_context);

	return R_P;
}

int w_menu__cmd_run(struct object *self, const struct vr *caller_context)
{
	struct em_wmenu *members = (struct em_wmenu *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;

	ShowWindow(pem_wob->window_handle, SW_SHOWNOACTIVATE);

	return R_P;
}

/*
 * 创建菜单
 * 创建菜单，SE函数。
 * 参    数：	piwmu - [IN] 菜单的初始化信息。
 * 返    回：	菜单对象指针
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
struct object *pop_menu(const struct init_wmenu *piwmu,
			const struct vr *caller_context)
{
	int r;
	struct object *p_menu;

	r = create_object(MSN_WMENU, 0, 0, 1, &p_menu);
	if (RN(r))
		return NULL;

	r = vo_open(p_menu, caller_context);
	assert(RP(r));

	vo_interact2(p_menu, CMD_INITIALIZE, (unsigned char *)piwmu,
		     sizeof(struct init_wmenu), caller_context);
	vo_interact0(p_menu, CMD_PREPARE, caller_context);
	vo_interact0(p_menu, CMD_RUN, caller_context);

	return p_menu;
}
