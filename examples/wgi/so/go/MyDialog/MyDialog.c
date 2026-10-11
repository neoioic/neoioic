

#include <wchar.h>
#include "MyDialog.h"
#include "MyDialog_InitSub.h"
#include "../WMenu/WMenu.h"
#include "../CObject/CObject.h"

extern const TCHAR g_sz_my_dialog_class[];
extern const TCHAR g_sz_my_dialog_name[];
extern HINSTANCE g_h_instance;

const TCHAR g_sz_menu_class[] = TEXT("Menu");
const TCHAR g_sz_menu_name[] = TEXT("Menu");

void tog_my_dialog(struct object *object);

static ATOM my_register_class(struct object *self);
static LRESULT CALLBACK cbf_my_dialog_proc(HWND window_handle, UINT message,
					   WPARAM wparam, LPARAM lparam);
static void load_bitmaps(struct object *self);
static void unload_bitmaps(struct object *self);
static void pop_menu_for_mr_control(struct object *self,
				    const struct vr *caller_context);
static void pop_menu_for_mr_menu_demo(struct object *self,
				      const struct vr *caller_context);
static char
cbf_create_menu_items_for_mr_control(struct object *p_menu,
				     const struct vr *caller_context);
static char
cbf_destroy_menu_items_for_mr_control(struct object *p_menu,
				      const struct vr *caller_context);
static char
cbf_create_menu_items_for_mr_menu_demo(struct object *p_menu,
				       const struct vr *caller_context);
static char
cbf_destroy_menu_items_for_mr_menu_demo(struct object *p_menu,
					const struct vr *caller_context);
static char cbf_create_menu_items_for_mi_item3(struct object *p_menu,
					       const struct vr *caller_context);
static char
cbf_destroy_menu_items_for_mi_item3(struct object *p_menu,
				    const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> WPanel </ibn> */
/* <crt> */
int crt_my_dialog(uint64_t *object_id, unsigned int input_capacity,
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
		OIOIC_ALIGNED_SIZE(struct em_mydialog) +
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

		/* MyDialog * */
		node = (struct object *)p_ic;
		tog_my_dialog(node);
		node->model_id = MSN_MYDIALOG;
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

		/* MyDialog * */
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
		p += OIOIC_ALIGNED_SIZE(struct em_mydialog);

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

static int my_dialog_open(struct object *self, const struct vr *caller_context)
{
	struct em_mydialog *members;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	if (1 == self->ref_count) {
		members = (struct em_mydialog *)self->members;
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->window_node = get_base_node(self, MSN_WOBJECT);
		members->panel_node = get_base_node(self, MSN_WPANEL);

		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[TRC_CLOSE_MY_DIALOG]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[MR_CONTROL_MY_DIALOG]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[MR_MENU_DEMO_MY_DIALOG]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[MR_HELP_MY_DIALOG]);
		create_object(MSN_CBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON1_MY_DIALOG]);
		create_object(MSN_MYBUTTON, 0, 0, 1,
			      &members->arr_sub[BUTTON2_MY_DIALOG]);
		create_object(MSN_MYBUTTON2, 0, 0, 1,
			      &members->arr_sub[BUTTON3_MY_DIALOG]);
		create_object(MSN_CEDIT, 0, 0, 1,
			      &members->arr_sub[EDIT_MY_DIALOG]);

		load_bitmaps(self);

		return RP_RCONE;
	}

	return R_P;
}

static int my_dialog_input(struct object *self, unsigned char *input_stream,
			   unsigned int quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int my_dialog_output(struct object *self, unsigned char *output_stream,
			    unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int my_dialog_io_put(struct object *self, unsigned char *input_stream,
			    unsigned int quantity, unsigned char *output_stream,
			    unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int my_dialog_interact0(struct object *self, unsigned int action,
			       const struct vr *caller_context)
{
	struct vr caller;
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	int r;
	int i;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		if (0 == my_register_class(self))
			return R_N;

		r = vo_interact0(members->window_node, CRT_WGI_WINDOW, &caller);
		if (!RP(r))
			return r;

		for (i = 0; i < NUM_SUB_MY_DIALOG; i++) {
			switch (i) {
			case TRC_CLOSE_MY_DIALOG:
			case MR_CONTROL_MY_DIALOG:
			case MR_MENU_DEMO_MY_DIALOG:
			case MR_HELP_MY_DIALOG:
			case BUTTON1_MY_DIALOG:
			case BUTTON2_MY_DIALOG:
			case BUTTON3_MY_DIALOG:
				my_dialog_init_sub_button(self, i, &caller);
				break;
			case EDIT_MY_DIALOG:
				my_dialog_init_sub_edit(self, i, &caller);
				break;
			default:
				break;
			}
		}

		pem_vob->p_first_sbdt = members->arr_sub[TRC_CLOSE_MY_DIALOG];
		vo_interact0(members->visual_node, CMD_PREPARE, &caller);
		return R_P;
	case CMD_RUN:
		/* SendMessage(pem_wob->window_handle, WM_INITDIALOG, 0, 0); */
		ShowWindow(pem_wob->window_handle, SW_SHOW);
		return R_P;
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int my_dialog_interact1(struct object *self, unsigned int action,
			       unsigned char *output_stream,
			       unsigned int capacity,
			       unsigned int *output_quantity,
			       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int my_dialog_interact2(struct object *self, unsigned int action,
			       unsigned char *input_stream,
			       unsigned int quantity,
			       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int my_dialog_interact3(struct object *self, unsigned int action,
			       unsigned char *input_stream,
			       unsigned int quantity,
			       unsigned char *output_stream,
			       unsigned int capacity,
			       unsigned int *output_quantity,
			       const struct vr *caller_context)
{
	struct vr caller;
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct init_wmenu iwmu;
	struct object *object;
	BITMAP bm;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case MSG_WGI_MENUITEMFOCUSOVER:
		assert(sizeof(struct object *) == quantity);
		assert(capacity >= sizeof(struct object *));
		object = *(struct object **)input_stream;
		/* _Debug_OutputString(TEXT("\nMSG_WGI_MENUITEMFOCUSOVER"), 123, NULL); */
		if (object == members->arr_mi[MI_ITEM3_MY_DIALOG]) {
			memset(&iwmu, 0, sizeof(struct init_wmenu));
			iwmu.ivob.state = VOB_STATE_ACTIVE;
			iwmu.iwob.instance = g_h_instance;
			iwmu.iwob.p_class_name = g_sz_menu_class;
			iwmu.iwob.p_window_name = g_sz_menu_name;
			iwmu.h_bmp_brb_normal =
				members->arr_hbitmap
					[BOTTOM_RB_NORMAL_BMP_MY_DIALOG];
			iwmu.h_bmp_brb_focus_on =
				members->arr_hbitmap
					[BOTTOM_RB_FOCUS_OVER_BMP_MY_DIALOG];
			iwmu.h_bmp_brb_focus_over =
				members->arr_hbitmap
					[BOTTOM_RB_FOCUS_OVER_BMP_MY_DIALOG];
			iwmu.h_bmp_trb_normal =
				members->arr_hbitmap
					[TOP_RB_NORMAL_BMP_MY_DIALOG];
			iwmu.h_bmp_trb_focus_on =
				members->arr_hbitmap
					[TOP_RB_FOCUS_OVER_BMP_MY_DIALOG];
			iwmu.h_bmp_trb_focus_over =
				members->arr_hbitmap
					[TOP_RB_FOCUS_OVER_BMP_MY_DIALOG];
			GetObject(iwmu.h_bmp_brb_normal, sizeof(bm), &bm);
			iwmu.n_rb_height = bm.bmHeight;
			iwmu.create_items = cbf_create_menu_items_for_mi_item3;
			iwmu.destroy_items =
				cbf_destroy_menu_items_for_mi_item3;
			iwmu.p_parent = self;
			iwmu.type = MNUT_LRBOTTOM;
			iwmu.width = 135;
			calcu_ora_coord(object, &iwmu.uca);
			object = pop_menu(&iwmu, &caller);
			assert(object);
			*(struct object **)output_stream = object;
			*output_quantity = sizeof(struct object *);
		} else {
		}
		return R_P;
	case MSG_WGI_MENUITEMFOCUSON:
		assert(sizeof(struct object *) == quantity);
		assert(capacity >= sizeof(struct object *));
		return R_P;
	case MSG_WGI_MENUITEMFOCUSDOWN:
		assert(sizeof(struct object *) == quantity);
		assert(capacity >= sizeof(struct object *));
		return R_P;
	case MSG_WGI_MENUITEMFOCUSUP:
		assert(sizeof(struct object *) == quantity);
		assert(capacity >= sizeof(struct object *));
		return R_P;
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int my_dialog_close(struct object *self, const struct vr *caller_context)
{
	struct vr caller;
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	int i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	if (0 == self->ref_count) {
		unload_bitmaps(self);

		for (i = 0; i < NUM_SUB_MY_DIALOG; i++) {
			vo_close(members->arr_sub[i], &caller);
			destroy_object(members->arr_sub[i]);
		}

		return RP_RCZERO;
	}

	return R_P;
}

/* TOG */

void tog_my_dialog(struct object *object)
{
	object->open = my_dialog_open;
	object->input = my_dialog_input;
	object->output = my_dialog_output;
	object->io_put = my_dialog_io_put;
	object->interact0 = my_dialog_interact0;
	object->interact1 = my_dialog_interact1;
	object->interact2 = my_dialog_interact2;
	object->interact3 = my_dialog_interact3;
	object->close = my_dialog_close;
}

/* Function(s) */

static ATOM my_register_class(struct object *self)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)cbf_my_dialog_proc;
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

/* Mesage handler for dialog. */
static LRESULT CALLBACK cbf_my_dialog_proc(HWND window_handle, UINT message,
					   WPARAM wparam, LPARAM lparam)
{
	static struct object *s_p_sub_to_move = NULL;
	static POINT s_pt = { 0, 0 };

	struct vr caller;
	struct object *self;
	struct em_mydialog *members;
	struct em_vobject *pem_vob;
	struct em_vobject *pem_vob_sbdt;
	PAINTSTRUCT ps;
	POINT pt;
	struct move mv;
	TCHAR ch;
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
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;
		BeginPaint(window_handle, &ps);
		vo_interact0(members->panel_node, CMD_WGI_PAINT, &caller);
		EndPaint(window_handle, &ps);
		break;
	case WM_ACTIVATE: /* MSDN：如果应用程序处理了此消息，应该返回FALSE。所以没用“break”。 */
		if (NULL == (self = (struct object *)GetWindowLongPtr(
				     window_handle, GWLP_USERDATA)))
			return FALSE;
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;

		if (WA_INACTIVE == LOWORD(wparam)) {
			if (members->p_menu) {
				/* 被激活的窗口不是菜单，就要关闭和销毁菜单。 */
				vo_close(members->p_menu, &caller);
				destroy_object(members->p_menu);
				members->p_popping_mr = NULL;
			}

			vo_interact0(members->panel_node, MSG_WGI_DEACTIVATE,
				     &caller);
		} else {
			vo_interact0(members->panel_node, MSG_WGI_ACTIVATE,
				     &caller);
		}

		return FALSE;
	case WM_MOUSEMOVE:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);
		if (wparam != MK_LBUTTON) {
			vo_interact2(members->panel_node, MSG_WGI_FOCUSOVERMOVE,
				     (unsigned char *)&pt, sizeof(POINT),
				     &caller);
			if (members->p_menu != NULL) {
				if (pem_vob->p_cf_over_sbdt ==
					    members->arr_sub
						    [MR_CONTROL_MY_DIALOG] &&
				    members->p_popping_mr !=
					    members->arr_sub
						    [MR_CONTROL_MY_DIALOG]) {
					vo_close(members->p_menu, &caller);
					destroy_object(members->p_menu);
					members->p_popping_mr = NULL;

					pop_menu_for_mr_control(self, &caller);

				} else if (
					pem_vob->p_cf_over_sbdt ==
						members->arr_sub
							[MR_MENU_DEMO_MY_DIALOG] &&
					members->p_popping_mr !=
						members->arr_sub
							[MR_MENU_DEMO_MY_DIALOG]) {
					vo_close(members->p_menu, &caller);
					destroy_object(members->p_menu);
					members->p_popping_mr = NULL;

					pop_menu_for_mr_menu_demo(self,
								  &caller);
				}
			}
		} else {
			vo_interact2(members->panel_node, MSG_WGI_FOCUSONMOVE,
				     (unsigned char *)&pt, sizeof(POINT),
				     &caller);
			if (NULL == pem_vob->p_cf_on_sbdt &&
			    NULL == s_p_sub_to_move) {
				PostMessage(window_handle, WM_NCLBUTTONDOWN,
					    HTCAPTION, 0);
			} else if (s_p_sub_to_move != NULL) {
				memset(&mv, 0, sizeof(struct move));
				mv.dx_lr = mv.dx_ul =
					GET_X_LPARAM(lparam) - s_pt.x;
				mv.dy_lr = mv.dy_ul =
					GET_Y_LPARAM(lparam) - s_pt.y;
				vo_interact2(s_p_sub_to_move, CMD_WGI_MOVE,
					     (unsigned char *)&mv,
					     sizeof(struct move), &caller);
			}

			s_pt.x = GET_X_LPARAM(lparam);
			s_pt.y = GET_Y_LPARAM(lparam);
		}
		break;
	case WM_MOVE:
		if (NULL == (self = (struct object *)GetWindowLongPtr(
				     window_handle, GWLP_USERDATA)))
			break;
		members = (struct em_mydialog *)self->members;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		n = pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left;
		pem_vob->rsc.rcouter.left = GET_X_LPARAM(lparam);
		pem_vob->rsc.rcouter.right = pem_vob->rsc.rcouter.left + n;
		n = pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top;
		pem_vob->rsc.rcouter.top = GET_Y_LPARAM(lparam);
		pem_vob->rsc.rcouter.bottom = pem_vob->rsc.rcouter.top + n;
		break;
	case WM_LBUTTONDOWN:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);

		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);

		s_pt.x = GET_X_LPARAM(lparam);
		s_pt.y = GET_Y_LPARAM(lparam);

		if (members->p_menu) {
			vo_close(members->p_menu, &caller);
			destroy_object(members->p_menu);
			members->p_popping_mr = NULL;
			break;
		}

		/* 触摸屏可在此先分派焦点 OVER 行为。 */

		if (pem_vob->p_cf_over_sbdt != NULL)
			vo_interact0(pem_vob->p_cf_over_sbdt, MSG_WGI_ACTIVATE,
				     &caller);

		vo_interact2(members->panel_node, MSG_WGI_FOCUSDOWN,
			     (unsigned char *)&pt, sizeof(POINT), &caller);
		if (pem_vob->p_cf_down_sbdt != NULL) {
			pem_vob_sbdt = (struct em_vobject *)get_base_members(
				pem_vob->p_cf_down_sbdt, MSN_VOBJECT);
			s_p_sub_to_move = (NULL == pem_vob_sbdt->p_cf_down_sbdt)
						  ? pem_vob->p_cf_down_sbdt
						  : NULL;
		} else {
			s_p_sub_to_move = NULL;
		}

		vo_interact2(members->panel_node, MSG_WGI_FOCUSON,
			     (unsigned char *)&pt, sizeof(POINT), &caller);

		if (pem_vob->p_cf_on_sbdt != NULL) {
			if (pem_vob->p_cf_on_sbdt ==
			    members->arr_sub[TRC_CLOSE_MY_DIALOG]) {
				PostMessage(window_handle, WM_CLOSE, 0, 0);
				break;
			}

			if (pem_vob->p_cf_on_sbdt ==
			    members->arr_sub[MR_CONTROL_MY_DIALOG]) {
				pop_menu_for_mr_control(self, &caller);
			} else if (pem_vob->p_cf_on_sbdt ==
				   members->arr_sub[MR_MENU_DEMO_MY_DIALOG]) {
				pop_menu_for_mr_menu_demo(self, &caller);
			} else if (pem_vob->p_cf_on_sbdt ==
				   members->arr_sub[MR_HELP_MY_DIALOG]) {
			}
		}

		break;
	case WM_LBUTTONUP:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		s_p_sub_to_move = NULL;
		pt.x = GET_X_LPARAM(lparam);
		pt.y = GET_Y_LPARAM(lparam);
		vo_interact2(members->panel_node, MSG_WGI_FOCUSUP,
			     (unsigned char *)&pt, sizeof(POINT), &caller);
		vo_interact2(members->panel_node, MSG_WGI_FOCUSOVER,
			     (unsigned char *)&pt, sizeof(POINT), &caller);
		break;
	case WM_KEYDOWN:
		/* self = (struct object*)GetWindowLongPtr(window_handle, GWLP_USERDATA); */
		break;
	case WM_CHAR:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_mydialog *)self->members;
		pem_vob = (struct em_vobject *)get_base_members(self,
								MSN_VOBJECT);
		caller.mr = self->oid;
		if (pem_vob->p_active_sbdt ==
		    members->arr_sub[EDIT_MY_DIALOG]) {
			ch = (0x0D == wparam)
				     ? 0x0A
				     : wparam; /* 0x0D 是回车符，0x0A 是换行符。 */
			vo_interact2(
				pem_vob->p_active_sbdt, CMD_WGI_INSERTCHARATCP,
				(unsigned char *)&ch, sizeof(TCHAR), &caller);
		}
		break;
	case WM_ERASEBKGND:
		return TRUE; /* 消除移动窗口闪烁。 */
	case WM_CLOSE:
		self = (struct object *)GetWindowLongPtr(window_handle,
							 GWLP_USERDATA);
		members = (struct em_mydialog *)self->members;
		caller.mr = self->oid;
		vo_interact0(members->window_node, DTR_WGI_WINDOW, &caller);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message, wparam, lparam);
	}

	return TRUE;
}

static void load_bitmaps(struct object *self)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));

	/* - Menu Roots - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRControl_Normal.jpg"));
	members->arr_hbitmap[MR_CONTROL_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRControl_FocusOver.jpg"));
	members->arr_hbitmap[MR_CONTROL_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRControl_FocusOn.jpg"));
	members->arr_hbitmap[MR_CONTROL_FOCUS_ON_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRMenuDemo_Normal.jpg"));
	members->arr_hbitmap[MR_MENU_DEMO_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRMenuDemo_FocusOver.jpg"));
	members->arr_hbitmap[MR_MENU_DEMO_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRMenuDemo_FocusOn.jpg"));
	members->arr_hbitmap[MR_MENU_DEMO_FOCUS_ON_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRHelp_Normal.jpg"));
	members->arr_hbitmap[MR_HELP_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRHelp_FocusOver.jpg"));
	members->arr_hbitmap[MR_HELP_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MRHelp_FocusOn.jpg"));
	members->arr_hbitmap[MR_HELP_FOCUS_ON_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	/* - Rolling Buttons for Menu - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("TopRB_Normal.jpg"));
	members->arr_hbitmap[TOP_RB_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("TopRB_FocusOver.jpg"));
	members->arr_hbitmap[TOP_RB_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("BottomRB_Normal.jpg"));
	members->arr_hbitmap[BOTTOM_RB_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("BottomRB_FocusOver.jpg"));
	members->arr_hbitmap[BOTTOM_RB_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	/* - Button1 - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button1_Normal.jpg"));
	members->arr_hbitmap[BUTTON1_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button1_FocusOver.jpg"));
	members->arr_hbitmap[BUTTON1_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button1_FocusOn.jpg"));
	members->arr_hbitmap[BUTTON1_FOCUS_ON_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button1_Active.jpg"));
	members->arr_hbitmap[BUTTON1_ACTIVE_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button1_ABSInactive.jpg"));
	members->arr_hbitmap[BUTTON1_ABS_INACTIVE_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	/* - Button3 - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button3_Normal.jpg"));
	members->arr_hbitmap[BUTTON3_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button3_FocusOver.jpg"));
	members->arr_hbitmap[BUTTON3_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button3_FocusOn.jpg"));
	members->arr_hbitmap[BUTTON3_FOCUS_ON_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button3_Active.jpg"));
	members->arr_hbitmap[BUTTON3_ACTIVE_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Button3_ABSInactive.jpg"));
	members->arr_hbitmap[BUTTON3_ABS_INACTIVE_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	/* - Edit - */
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Edit_Normal.jpg"));
	members->arr_hbitmap[EDIT_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Edit_Active.jpg"));
	members->arr_hbitmap[EDIT_ACTIVE_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	return;
}

static void unload_bitmaps(struct object *self)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	int i;

	for (i = 0; i < NUM_BMP_MY_DIALOG; i++) {
		if (members->arr_hbitmap[i])
			DeleteObject(members->arr_hbitmap[i]);
	}

	return;
}

/* DESC: Pop menu for MRControl */
static void pop_menu_for_mr_control(struct object *self,
				    const struct vr *caller_context)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct init_wmenu iwmu;

	memset(&iwmu, 0, sizeof(struct init_wmenu));

	iwmu.ivob.state = VOB_STATE_ACTIVE;
	iwmu.iwob.instance = g_h_instance;
	iwmu.iwob.p_class_name = g_sz_menu_class;
	iwmu.iwob.p_window_name = g_sz_menu_name;
	iwmu.create_items = cbf_create_menu_items_for_mr_control;
	iwmu.destroy_items = cbf_destroy_menu_items_for_mr_control;
	iwmu.p_parent = self;
	iwmu.type = MNUT_TBLEFT;
	iwmu.width = 201;
	calcu_ora_coord(members->arr_sub[MR_CONTROL_MY_DIALOG], &iwmu.uca);
	members->p_menu = pop_menu(&iwmu, caller_context);
	members->p_popping_mr = members->arr_sub[MR_CONTROL_MY_DIALOG];

	assert(members->p_menu);

	return;
}

/* DESC: Pop menu for MRMenuDemo */
static void pop_menu_for_mr_menu_demo(struct object *self,
				      const struct vr *caller_context)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct init_wmenu iwmu;
	BITMAP bm;

	memset(&iwmu, 0, sizeof(struct init_wmenu));

	iwmu.ivob.state = VOB_STATE_ACTIVE;
	iwmu.iwob.instance = g_h_instance;
	iwmu.iwob.p_class_name = g_sz_menu_class;
	iwmu.iwob.p_window_name = g_sz_menu_name;
	iwmu.h_bmp_brb_normal =
		members->arr_hbitmap[BOTTOM_RB_NORMAL_BMP_MY_DIALOG];
	iwmu.h_bmp_brb_focus_on =
		members->arr_hbitmap[BOTTOM_RB_FOCUS_OVER_BMP_MY_DIALOG];
	iwmu.h_bmp_brb_focus_over =
		members->arr_hbitmap[BOTTOM_RB_FOCUS_OVER_BMP_MY_DIALOG];
	iwmu.h_bmp_trb_normal =
		members->arr_hbitmap[TOP_RB_NORMAL_BMP_MY_DIALOG];
	iwmu.h_bmp_trb_focus_on =
		members->arr_hbitmap[TOP_RB_FOCUS_OVER_BMP_MY_DIALOG];
	iwmu.h_bmp_trb_focus_over =
		members->arr_hbitmap[TOP_RB_FOCUS_OVER_BMP_MY_DIALOG];
	GetObject(iwmu.h_bmp_brb_normal, sizeof(bm), &bm);
	iwmu.n_rb_height = bm.bmHeight;
	iwmu.create_items = cbf_create_menu_items_for_mr_menu_demo;
	iwmu.destroy_items = cbf_destroy_menu_items_for_mr_menu_demo;
	iwmu.p_parent = self;
	iwmu.type = MNUT_TBLEFT;
	iwmu.width = 157;
	calcu_ora_coord(members->arr_sub[MR_MENU_DEMO_MY_DIALOG], &iwmu.uca);
	members->p_menu = pop_menu(&iwmu, caller_context);
	members->p_popping_mr = members->arr_sub[MR_MENU_DEMO_MY_DIALOG];

	assert(members->p_menu);

	return;
}

/* DESC: Create menu items for MRControl */
static char
cbf_create_menu_items_for_mr_control(struct object *p_menu,
				     const struct vr *caller_context)
{
	static TCHAR s_str1[] = TEXT("Enable Button");
	static TCHAR s_str2[] = TEXT("Disable Button");

	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_vobject *pem_wmu_vob =
		(struct em_vobject *)pem_wmu->visual_node->members;
	struct em_wobject *pem_wmu_wob =
		(struct em_wobject *)pem_wmu->window_node->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;
	int i;
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	create_object(MSN_CBUTTON, 0, 0, 1,
		      &members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG]);
	create_object(MSN_CBUTTON, 0, 0, 1,
		      &members->arr_mi[MI_DISABLE_BUTTON_MY_DIALOG]);

	/* - load bitmaps - */
	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIEnableButton_Normal.jpg"));
	members->arr_mihbitmap[MI_ENABLE_BUTTON_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIEnableButton_FocusOver.jpg"));
	members->arr_mihbitmap[MI_ENABLE_BUTTON_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	ivob.p_superior = p_menu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;
	ivob.arr_hbitmap[VOB_STATE_NORMAL] =
		members->arr_mihbitmap[MI_ENABLE_BUTTON_NORMAL_BMP_MY_DIALOG];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
		members->arr_mihbitmap
			[MI_ENABLE_BUTTON_FOCUS_OVER_BMP_MY_DIALOG];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
		members->arr_mihbitmap
			[MI_ENABLE_BUTTON_FOCUS_OVER_BMP_MY_DIALOG];
	GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
	ivob.rsc.rcouter.right = bm.bmWidth;
	ivob.rsc.rcinner.right = bm.bmWidth;
	ivob.rsc.rcinner.bottom = bm.bmHeight;
	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;
	icob.p_wnd_handle = &pem_wmu_wob->window_handle;

	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0, 0, 0);

	for (i = MI_ENABLE_BUTTON_MY_DIALOG; i <= MI_DISABLE_BUTTON_MY_DIALOG;
	     i++) {
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.ci.rect.top = 5;
		ivob.ci.rect.right =
			ivob.rsc.rcouter.right - ivob.rsc.rcouter.left;
		ivob.ci.rect.bottom =
			ivob.rsc.rcouter.bottom - ivob.rsc.rcouter.top;
		switch (i) {
		case MI_ENABLE_BUTTON_MY_DIALOG:
			ivob.ci.text = s_str1;
			ivob.ci.cpty = ivob.ci.clen = wcslen(s_str1);
			ivob.p_prev_codt =
				members->arr_mi[MI_DISABLE_BUTTON_MY_DIALOG];
			ivob.p_next_codt =
				members->arr_mi[MI_DISABLE_BUTTON_MY_DIALOG];
			break;
		case MI_DISABLE_BUTTON_MY_DIALOG:
			ivob.ci.text = s_str2;
			ivob.ci.cpty = ivob.ci.clen = wcslen(s_str2);
			ivob.p_prev_codt =
				members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG];
			ivob.p_next_codt =
				members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG];
			break;
		default:
			assert(0);
			break;
		}

		vo_open(members->arr_mi[i], caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_VOBJECT),
			     CMD_INITIALIZE, (unsigned char *)&ivob,
			     sizeof(struct init_vobject), caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_COBJECT),
			     CMD_INITIALIZE, (unsigned char *)&icob,
			     sizeof(struct init_cobject), caller_context);
		vo_interact0(members->arr_mi[i], CMD_PREPARE, caller_context);
	}

	pem_wmu_vob->sceneh = 2 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;
	pem_wmu_vob->p_first_sbdt = members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG];

	return TRUE;
}

/* DESC: Destroy menu items for MRControl */
static char
cbf_destroy_menu_items_for_mr_control(struct object *p_menu,
				      const struct vr *caller_context)
{
	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;

	vo_close(members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG], caller_context);
	destroy_object(members->arr_mi[MI_ENABLE_BUTTON_MY_DIALOG]);

	vo_close(members->arr_mi[MI_DISABLE_BUTTON_MY_DIALOG], caller_context);
	destroy_object(members->arr_mi[MI_DISABLE_BUTTON_MY_DIALOG]);

	/* - unload bitmaps - */
	DeleteObject(
		members->arr_mihbitmap[MI_ENABLE_BUTTON_NORMAL_BMP_MY_DIALOG]);
	DeleteObject(members->arr_mihbitmap
			     [MI_ENABLE_BUTTON_FOCUS_OVER_BMP_MY_DIALOG]);

	return TRUE;
}

/* DESC: Create menu items for MRMenuDemo */
static char
cbf_create_menu_items_for_mr_menu_demo(struct object *p_menu,
				       const struct vr *caller_context)
{
	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_vobject *pem_wmu_vob =
		(struct em_vobject *)pem_wmu->visual_node->members;
	struct em_wobject *pem_wmu_wob =
		(struct em_wobject *)pem_wmu->window_node->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;
	int i;
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	for (i = MI_ITEM0_MY_DIALOG; i <= MI_ITEM50_MY_DIALOG; i++)
		create_object(MSN_CBUTTON, 0, 0, 1, &members->arr_mi[i]);

	/* - load bitmaps - */
	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem0_Normal.jpg"));
	members->arr_mihbitmap[MI_ITEM0_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem0_FocusOver.jpg"));
	members->arr_mihbitmap[MI_ITEM0_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem3_Normal.jpg"));
	members->arr_mihbitmap[MI_ITEM3_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem3_FocusOver.jpg"));
	members->arr_mihbitmap[MI_ITEM3_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	assert(NULL == members->p_text_pool_mr_menu_demo);
	members->p_text_pool_mr_menu_demo = (TCHAR *)calloc(
		51 * 15,
		sizeof(TCHAR)); /* 共51个菜单项，每个菜单项的标题文本空间为15个TCHAR字节。 */
	for (i = 0; i < 51; i++)
		swprintf(members->p_text_pool_mr_menu_demo + i * 15, 15,
			 TEXT("%ls%d"), TEXT("Item "), i);

	ivob.p_superior = p_menu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;
	icob.p_wnd_handle = &pem_wmu_wob->window_handle;

	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0, 0, 0);
	ivob.ci.cpty = 15;

	for (i = MI_ITEM0_MY_DIALOG; i <= MI_ITEM50_MY_DIALOG; i++) {
		switch (i) {
		case MI_ITEM0_MY_DIALOG:
			ivob.p_prev_codt = members->arr_mi[MI_ITEM50_MY_DIALOG];
			ivob.p_next_codt = members->arr_mi[i + 1];
			break;
		default:
			ivob.p_prev_codt = members->arr_mi[i - 1];
			ivob.p_next_codt = members->arr_mi[i + 1];
			break;
		}

		if (MI_ITEM3_MY_DIALOG == i) {
			ivob.arr_hbitmap[VOB_STATE_NORMAL] =
				members->arr_mihbitmap
					[MI_ITEM3_NORMAL_BMP_MY_DIALOG];
			ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
				members->arr_mihbitmap
					[MI_ITEM3_FOCUS_OVER_BMP_MY_DIALOG];
			ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
				members->arr_mihbitmap
					[MI_ITEM3_FOCUS_OVER_BMP_MY_DIALOG];
		} else {
			ivob.arr_hbitmap[VOB_STATE_NORMAL] =
				members->arr_mihbitmap
					[MI_ITEM0_NORMAL_BMP_MY_DIALOG];
			ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
				members->arr_mihbitmap
					[MI_ITEM0_FOCUS_OVER_BMP_MY_DIALOG];
			ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
				members->arr_mihbitmap
					[MI_ITEM0_FOCUS_OVER_BMP_MY_DIALOG];
		}

		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);

		ivob.rsc.rcouter.right = bm.bmWidth;
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;

		ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
		ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

		ivob.ci.text = members->p_text_pool_mr_menu_demo +
			       (i - MI_ITEM0_MY_DIALOG) * 15;
		ivob.ci.clen = wcslen(members->p_text_pool_mr_menu_demo +
				      (i - MI_ITEM0_MY_DIALOG) * 15);
		ivob.ci.rect.top = 5;
		ivob.ci.rect.right =
			ivob.rsc.rcouter.right - ivob.rsc.rcouter.left;
		ivob.ci.rect.bottom =
			ivob.rsc.rcouter.bottom - ivob.rsc.rcouter.top;

		vo_open(members->arr_mi[i], caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_VOBJECT),
			     CMD_INITIALIZE, (unsigned char *)&ivob,
			     sizeof(struct init_vobject), caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_COBJECT),
			     CMD_INITIALIZE, (unsigned char *)&icob,
			     sizeof(struct init_cobject), caller_context);
		vo_interact0(members->arr_mi[i], CMD_PREPARE, caller_context);
	}

	GetObject(members->arr_mihbitmap[MI_ITEM0_NORMAL_BMP_MY_DIALOG],
		  sizeof(bm), &bm);
	pem_wmu_vob->sceneh = 51 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;
	pem_wmu_vob->p_first_sbdt = members->arr_mi[MI_ITEM0_MY_DIALOG];

	return TRUE;
}

/* DESC: Destroy menu items for MRMenuDemo */
static char
cbf_destroy_menu_items_for_mr_menu_demo(struct object *p_menu,
					const struct vr *caller_context)
{
	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;
	int i;

	for (i = MI_ITEM0_MY_DIALOG; i <= MI_ITEM50_MY_DIALOG; i++) {
		vo_close(members->arr_mi[i], caller_context);
		destroy_object(members->arr_mi[i]);
	}

	/* - unload bitmaps - */
	DeleteObject(members->arr_mihbitmap[MI_ITEM0_NORMAL_BMP_MY_DIALOG]);
	DeleteObject(members->arr_mihbitmap[MI_ITEM0_FOCUS_OVER_BMP_MY_DIALOG]);
	DeleteObject(members->arr_mihbitmap[MI_ITEM3_NORMAL_BMP_MY_DIALOG]);
	DeleteObject(members->arr_mihbitmap[MI_ITEM3_FOCUS_OVER_BMP_MY_DIALOG]);

	if (members->p_text_pool_mr_menu_demo != NULL) {
		free(members->p_text_pool_mr_menu_demo);
		members->p_text_pool_mr_menu_demo = NULL;
	}

	return TRUE;
}

/* DESC: Create menu items for MIItem3 */
static char cbf_create_menu_items_for_mi_item3(struct object *p_menu,
					       const struct vr *caller_context)
{
	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_vobject *pem_wmu_vob =
		(struct em_vobject *)pem_wmu->visual_node->members;
	struct em_wobject *pem_wmu_wob =
		(struct em_wobject *)pem_wmu->window_node->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;
	int i;
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	for (i = MI_ITEM3_0_MY_DIALOG; i <= MI_ITEM3_55_MY_DIALOG; i++)
		create_object(MSN_CBUTTON, 0, 0, 1, &members->arr_mi[i]);

	/* - load bitmaps - */
	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem3_0_Normal.jpg"));
	members->arr_mihbitmap[MI_ITEM3_0_NORMAL_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);
	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("MIItem3_0_FocusOver.jpg"));
	members->arr_mihbitmap[MI_ITEM3_0_FOCUS_OVER_BMP_MY_DIALOG] =
		load_picture_file(sz_file_path);

	assert(NULL == members->p_text_pool_mi_item3);
	members->p_text_pool_mi_item3 = (TCHAR *)calloc(
		56 * 15,
		sizeof(TCHAR)); /* 共56个菜单项，每个菜单项的标题文本空间为15个TCHAR字节。 */
	for (i = 0; i < 56; i++)
		swprintf(members->p_text_pool_mi_item3 + i * 15, 15,
			 TEXT("%ls%d"), TEXT("Item3_ "), i);

	ivob.p_superior = p_menu;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;
	icob.p_wnd_handle = &pem_wmu_wob->window_handle;

	ivob.arr_hbitmap[VOB_STATE_NORMAL] =
		members->arr_mihbitmap[MI_ITEM3_0_NORMAL_BMP_MY_DIALOG];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
		members->arr_mihbitmap[MI_ITEM3_0_FOCUS_OVER_BMP_MY_DIALOG];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
		members->arr_mihbitmap[MI_ITEM3_0_FOCUS_OVER_BMP_MY_DIALOG];

	GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);

	pem_wmu_vob->sceneh = 56 * bm.bmHeight;
	pem_wmu_vob->scenew = bm.bmWidth;

	ivob.rsc.rcouter.right = bm.bmWidth;
	ivob.rsc.rcinner.right = bm.bmWidth;
	ivob.rsc.rcinner.bottom = bm.bmHeight;
	ivob.scenew = bm.bmWidth;
	ivob.sceneh = bm.bmHeight;
	ivob.ci.rect.right = bm.bmWidth;
	ivob.ci.rect.bottom = bm.bmHeight;
	ivob.ci.rect.top = 5;
	ivob.ci.format = CTF_HCENTER | DT_END_ELLIPSIS;
	ivob.ci.color = RGB(0, 0, 0);
	ivob.ci.cpty = 15;

	for (i = MI_ITEM3_0_MY_DIALOG; i <= MI_ITEM3_55_MY_DIALOG; i++) {
		ivob.rsc.rcouter.top = ivob.rsc.rcouter.bottom;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.ci.text = members->p_text_pool_mi_item3 +
			       (i - MI_ITEM3_0_MY_DIALOG) * 15;
		ivob.ci.clen = wcslen(members->p_text_pool_mi_item3 +
				      (i - MI_ITEM3_0_MY_DIALOG) * 15);

		switch (i) {
		case MI_ITEM3_0_MY_DIALOG:
			ivob.p_prev_codt =
				members->arr_mi[MI_ITEM3_55_MY_DIALOG];
			ivob.p_next_codt = members->arr_mi[i + 1];
			break;
		default:
			ivob.p_prev_codt = members->arr_mi[i - 1];
			ivob.p_next_codt = members->arr_mi[i + 1];
			break;
		}

		vo_open(members->arr_mi[i], caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_VOBJECT),
			     CMD_INITIALIZE, (unsigned char *)&ivob,
			     sizeof(struct init_vobject), caller_context);
		vo_interact2(get_base_node(members->arr_mi[i], MSN_COBJECT),
			     CMD_INITIALIZE, (unsigned char *)&icob,
			     sizeof(struct init_cobject), caller_context);
		vo_interact0(members->arr_mi[i], CMD_PREPARE, caller_context);
	}

	pem_wmu_vob->p_first_sbdt = members->arr_mi[MI_ITEM3_0_MY_DIALOG];

	return TRUE;
}

/* DESC: Destroy menu items for MIItem3 */
static char cbf_destroy_menu_items_for_mi_item3(struct object *p_menu,
						const struct vr *caller_context)
{
	struct em_wmenu *pem_wmu = (struct em_wmenu *)p_menu->members;
	struct em_mydialog *members =
		(struct em_mydialog *)pem_wmu->p_parent->members;
	int i;

	for (i = MI_ITEM3_0_MY_DIALOG; i <= MI_ITEM3_55_MY_DIALOG; i++) {
		vo_close(members->arr_mi[i], caller_context);
		destroy_object(members->arr_mi[i]);
	}

	/* - unload bitmaps - */
	DeleteObject(members->arr_mihbitmap[MI_ITEM3_0_NORMAL_BMP_MY_DIALOG]);
	DeleteObject(
		members->arr_mihbitmap[MI_ITEM3_0_FOCUS_OVER_BMP_MY_DIALOG]);

	if (members->p_text_pool_mi_item3 != NULL) {
		free(members->p_text_pool_mi_item3);
		members->p_text_pool_mi_item3 = NULL;
	}

	return TRUE;
}
