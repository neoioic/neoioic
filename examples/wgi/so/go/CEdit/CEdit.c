

#include "CEdit.h"
#include "../CObject/CObject.h"

void tog_c_edit(struct object *object);
int c_edit_i_open(struct object *self, const struct vr *caller_context);
int c_edit_i_close(struct object *self, const struct vr *caller_context);
int c_edit__cmd_prepare(struct object *self, const struct vr *caller_context);
int c_edit__cmd_initialize(struct object *self, const struct init_cedit *piced,
			   const struct vr *caller_context);
int c_edit__cmd_wgi_insertcharatcp(struct object *self, const TCHAR *archar,
				   long count, const struct vr *caller_context);
int c_edit__msg_wgi_activate(struct object *self,
			     const struct vr *caller_context);
int c_edit__msg_wgi_deactivate(struct object *self,
			       const struct vr *caller_context);
int c_edit__msg_wgi_focusdown(struct object *self, const POINT pt,
			      const struct vr *caller_context);
int c_edit__cmd_wgi_move(struct object *self, const struct move *pmove,
			 const struct vr *caller_context);

static long search_ll_char_by_char(struct object *self, long i_char);
static long search_lf_char_by_char(struct object *self, long i_char);
static void calcu_all_character_xy_lefttop_autowrap(struct object *self,
						    int max_length);
static void overcb_rdc_scroll_bar(struct object *self,
				  const struct vr *caller_context);
static long search_char_by_point(struct object *self, long x, long y);
static long search_text_line_by_y_coord(struct object *self, long y);

/* OICC label */

/* <oicc> */
/* <ibn> CObject </ibn> */
/* <crt> */
int crt_c_edit(uint64_t *object_id, unsigned int input_capacity,
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
		OIOIC_ALIGNED_SIZE(struct em_cedit) +
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

		/* CEdit * */
		node = (struct object *)p_ic;
		tog_c_edit(node);
		node->model_id = MSN_CEDIT;
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

		/* CEdit * */
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
		p += OIOIC_ALIGNED_SIZE(struct em_cedit);

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

static int c_edit_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return c_edit_i_open(self, &caller);
}

static int c_edit_input(struct object *self, unsigned char *input_stream,
			unsigned int quantity, const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int c_edit_output(struct object *self, unsigned char *output_stream,
			 unsigned int capacity, unsigned int *output_quantity,
			 const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int c_edit_io_put(struct object *self, unsigned char *input_stream,
			 unsigned int quantity, unsigned char *output_stream,
			 unsigned int capacity, unsigned int *output_quantity,
			 const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int c_edit_interact0(struct object *self, unsigned int action,
			    const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		return c_edit__cmd_prepare(self, &caller);
	case MSG_WGI_ACTIVATE:
		return c_edit__msg_wgi_activate(self, &caller);
	case MSG_WGI_DEACTIVATE:
		return c_edit__msg_wgi_deactivate(self, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int c_edit_interact1(struct object *self, unsigned int action,
			    unsigned char *output_stream, unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int c_edit_interact2(struct object *self, unsigned int action,
			    unsigned char *input_stream, unsigned int quantity,
			    const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_INITIALIZE:
		assert(sizeof(struct init_cedit) == quantity);
		return c_edit__cmd_initialize(
			self, (struct init_cedit *)input_stream, &caller);
	case CMD_WGI_INSERTCHARATCP:
		return c_edit__cmd_wgi_insertcharatcp(
			self, (TCHAR *)input_stream,
			(long)(quantity / sizeof(TCHAR)), &caller);
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == quantity);
		return c_edit__msg_wgi_focusdown(self, *(POINT *)input_stream,
						 &caller);
	case CMD_WGI_MOVE:
		assert(sizeof(struct move) == quantity);
		return c_edit__cmd_wgi_move(self, (struct move *)input_stream,
					    &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int c_edit_interact3(struct object *self, unsigned int action,
			    unsigned char *input_stream, unsigned int quantity,
			    unsigned char *output_stream, unsigned int capacity,
			    unsigned int *output_quantity,
			    const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int c_edit_close(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	return c_edit_i_close(self, &caller);
}

/* TOG */

void tog_c_edit(struct object *object)
{
	object->open = c_edit_open;
	object->input = c_edit_input;
	object->output = c_edit_output;
	object->io_put = c_edit_io_put;
	object->interact0 = c_edit_interact0;
	object->interact1 = c_edit_interact1;
	object->interact2 = c_edit_interact2;
	object->interact3 = c_edit_interact3;
	object->close = c_edit_close;
}

/* Function(s) */

/* DESC: 在当前位图上定制内容，绘制文本，由VObject节点回调。 */
static void cbf_on_make_current_bitmap(struct object *self, const HDC hDC)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	HFONT h_old_font = NULL;
	COLORREF cr_old_color;
	HBITMAP h_orig_bmp, h_new_bmp;
	HDC memdc;
	long x, y;
	long i, i1, i2;
	int n;

	if (0 == members->ti.clen)
		return;

	memdc = CreateCompatibleDC(hDC);
	h_new_bmp = CreateCompatibleBitmap(hDC, members->vpw, members->vph);
	h_orig_bmp = GetCurrentObject(memdc, OBJ_BITMAP);
	SelectObject(memdc, h_new_bmp);
	BitBlt(memdc, 0, 0, members->vpw, members->vph, hDC,
	       pem_vob->rsc.rcinner.left, pem_vob->rsc.rcinner.top, SRCCOPY);

	n = members->ti.n_spc_row / 2 + 1;
	x = -pem_vob->ox_irr;
	y = (members->p_arr_cwxy[0].y > -pem_vob->oy_irr)
		    ? members->p_arr_cwxy[0].y
		    : -pem_vob->oy_irr;

	if (members->ti.font)
		h_old_font = SelectObject(memdc, members->ti.font);
	cr_old_color = SetTextColor(memdc, members->ti.crnor);

	while (y + pem_vob->oy_irr < members->vph) {
		i1 = search_char_by_point(self, x, y);
		i2 = search_char_by_point(self, x + members->vpw, y);
		if (-1 == i1 && i2 != -1) {
			i1 = search_lf_char_by_char(self, i2);
		} else if (i1 != -1 && -1 == i2) {
			i2 = search_ll_char_by_char(self, i1);
		} else if (-1 == i1 && -1 == i2) {
			i = search_text_line_by_y_coord(self, y);
			if (i < 0)
				break;
			if (members->format & ETF_HCENTER) /* 水平居中？ */
			{
				i1 = search_lf_char_by_char(self, i);
				i2 = search_ll_char_by_char(self, i);
			} else {
				y = members->p_arr_cwxy[i].y +
				    members->char_height + n;
				continue;
			}
		}

		for (i = i1; i <= i2; i++) {
			if (0x0A == members->ti.text[i])
				continue; /* 换行符不需要显示。 */
			/* _Debug_OutputString(TEXT("\n TextOut  "), pem->ti.text[i], NULL); */
			TextOut(memdc,
				members->p_arr_cwxy[i].x + pem_vob->ox_irr,
				members->p_arr_cwxy[i].y + pem_vob->oy_irr,
				members->ti.text + i, 1);
		}

		if (i2 == members->ti.clen - 1)
			break;

		y = members->p_arr_cwxy[i1].y + members->char_height + n;
	}

	BitBlt(hDC, pem_vob->rsc.rcinner.left, pem_vob->rsc.rcinner.top,
	       members->vpw, members->vph, memdc, 0, 0, SRCCOPY);

	if (h_old_font != NULL)
		SelectObject(memdc, h_old_font);
	SetTextColor(memdc, cr_old_color);

	SelectObject(memdc, h_orig_bmp);
	DeleteDC(memdc);

	if (h_new_bmp != NULL)
		DeleteObject(h_new_bmp);

	return;
}

/*
 * DESC: 计算文本尺寸（宽度和高度）。
 * RETU: 根据文本高度和宽度的变化情况，返回不同的数值。
 *       0 - 宽度和高度都没变化；
 *       1 - 只有宽度变化了，高度没变化；
 *       2 - 只有高度变化了，宽度没变化；
 *       3 - 宽度和高度都变化了。
 */
static int calcu_text_size(struct object *self)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long n, w, h, i, j, i_last;

	if (0 == members->ti.clen) {
		w = 0;
		h = members->char_height;
	} else {
		w = 0;
		i = 0;
		i_last = members->ti.clen - 1;

		while (1) {
			j = search_ll_char_by_char(self, i);
			n = members->p_arr_cwxy[j].x +
			    members->p_arr_cwxy[j].w - members->p_arr_cwxy[i].x;
			if (n > w)
				w = n;

			i = j + 1;
			if (i >= i_last)
				break;
		}

		h = members->p_arr_cwxy[i_last].y + members->char_height -
		    members->p_arr_cwxy[0].y;
	}

	if (w != members->text_width && h != members->text_height) {
		members->text_width = w;
		members->text_height = h;
		return 3;
	} else if (h != members->text_height) {
		members->text_height = h;
		return 2;
	} else if (w != members->text_width) {
		members->text_width = w;
		return 1;
	}

	return 0;
}

/* DESC: 计算情景尺寸（宽度和高度）。 */
static void calcu_scene_size(struct object *self)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	int n;

	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	pem_vob->scenew = members->text_width > n ? members->text_width : n;
	n = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;
	pem_vob->sceneh = members->text_height > n ? members->text_height : n;

	return;
}

/* DESC: 计算视口尺寸（宽度和高度）。 */
static void calcu_viewport_size(struct object *self)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	int w, h;

	w = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	h = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;

	if (members->style & EDTS_SCROLLBAR) {
		members->vpw = w;
		members->vph = h;
		return;
	}

	if (pem_vob->scenew > w) {
		members->vph = h - members->i2hscb.n_thickness;
		members->vpw =
			(pem_vob->sceneh > h - members->i2hscb.n_thickness)
				? w - members->i2vscb.n_thickness
				: w;
	} else {
		if (pem_vob->sceneh > h) {
			members->vpw = w - members->i2vscb.n_thickness;
			members->vph = (pem_vob->scenew >
					w - members->i2vscb.n_thickness)
					       ? h - members->i2hscb.n_thickness
					       : h;
		} else {
			members->vpw = w;
			members->vph = h;
		}
	}

	return;
}

/* DESC: 格式化指定文本段的每一行。 */
static void format_text(struct object *self, long i_begin, long i_end)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	long i, j, k, n;
	int dx, dy;

	assert(i_begin < i_end);

	if (members->format & ETF_TOP) {
		dy = -members->p_arr_cwxy[0].y;
	} else if (members->format & ETF_BOTTOM) {
		dy = pem_vob->sceneh - members->text_height -
		     members->p_arr_cwxy[0].y;
	} else /* ETF_VCENTER */
	{
		dy = (pem_vob->sceneh - members->text_height) / 2 -
		     members->p_arr_cwxy[0].y;
	}

	i = i_begin;

	do {
		j = search_lf_char_by_char(self, i);
		k = search_ll_char_by_char(self, i);
		if (members->format & ETF_LEFT) {
			dx = -members->p_arr_cwxy[j].x;
		} else if (members->format & ETF_RIGHT) {
			dx = pem_vob->scenew - members->p_arr_cwxy[k].x -
			     members->p_arr_cwxy[k].w;
		} else /* ETF_HCENTER */
		{
			n = members->p_arr_cwxy[k].x +
			    members->p_arr_cwxy[k].w - members->p_arr_cwxy[j].x;
			dx = (pem_vob->scenew - n) / 2 -
			     members->p_arr_cwxy[j].x;
		}

		for (i = j; i <= k; i++) {
			members->p_arr_cwxy[i].x += dx;
			members->p_arr_cwxy[i].y += dy;
		}

		i = k + 1;
	} while (i < i_end);

	return;
}

/*
 * DESC: 根据参数i_char和b_to_right设置插入符位置。
 * RETU: 0 - 没重画；1 - 重画了。
 */
static int set_caret_position(struct object *self, long i_char, char b_to_right,
			      const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	long x, y, dx, dy;
	int rv, n1, n2, m1, m2;

	if (-1 == i_char) {
		n1 = members->vpw - members->caret_width;
		n2 = n1 / 2;
		m1 = members->vph - members->char_height;
		m2 = m1 / 2;

		x = pem_vob->rsc.rcinner.left;
		y = pem_vob->rsc.rcinner.top;

		if (members->format & ETF_RIGHT)
			x += n1;
		else if (members->format & ETF_HCENTER)
			x += n2;

		if (members->format & ETF_BOTTOM)
			y += m1;
		else if (members->format & ETF_VCENTER)
			y += m2;

		rv = 0;
	} else {
		dx = members->p_arr_cwxy[i_char].x + pem_vob->ox_irr;
		if (TRUE == b_to_right)
			dx += members->p_arr_cwxy[i_char].w;
		dy = members->p_arr_cwxy[i_char].y + pem_vob->oy_irr;

		if (dx > 0) {
			dx += members->caret_width - members->vpw;
			if (dx < 0)
				dx = 0;
		}

		if (dy > 0) {
			dy += members->char_height - members->vph;
			if (dy < 0)
				dy = 0;
		}

		if (dx != 0 ||
		    dy != 0) /* 插入符在新位置不能完全出现在视口内？ */
		{
			pem_vob->ox_irr -= dx;
			pem_vob->oy_irr -= dy;

			/* ........ 在这里用CMD_WGI_ROLLONCB行为访问滚动条。 */

			vo_interact0(members->visual_node, CMD_WGI_REPAINT,
				     caller_context);
			rv = 1;
		}

		rv = 0;

		x = members->p_arr_cwxy[i_char].x + pem_vob->ox_irr +
		    pem_vob->rsc.rcinner.left;
		if (TRUE == b_to_right)
			x += members->p_arr_cwxy[i_char].w;
		y = members->p_arr_cwxy[i_char].y + pem_vob->oy_irr +
		    pem_vob->rsc.rcinner.top;
	}

	do { /* 把坐标转换到窗口对象的外部矩形坐标。 */
		x += pem_vob->rsc.rcouter.left;
		y += pem_vob->rsc.rcouter.top;
		pem_vob = (struct em_vobject *)get_base_members(
			pem_vob->p_superior, MSN_VOBJECT);
		x += pem_vob->rsc.rcinner.left;
		y += pem_vob->rsc.rcinner.top;
	} while (pem_vob->p_superior != NULL);

	SetCaretPos(x, y);
	ShowCaret(*pem_vob->p_wnd_handle);

	members->cp.i_char = i_char;
	members->cp.b_to_right = b_to_right;

	return rv;
}

/* DESC: 给定情景区域内一个纵坐标值，确定该值属于哪个文本行的行定位区域的纵坐标区间。 */
static long search_text_line_by_y_coord(struct object *self, long y)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long i, n1, n2, left, middle, right;
	int m1, m2;

	left = 0;
	right = members->ti.clen - 1;
	i = -1;
	m1 = members->ti.n_spc_row / 2;
	m2 = members->char_height + m1;

	while (left <= right) {
		middle = (left + right) / 2;
		n1 = members->p_arr_cwxy[middle].y - m1;
		n2 = members->p_arr_cwxy[middle].y + m2;

		if (y >= n1 && y <= n2) {
			i = middle;
			break;
		} else if (y < n1)
			right = middle - 1;
		else
			left = middle + 1;
	}

	return i;
}

/* DESC: 给定最大滚动区域内一个点的坐标，确定该点左哪个字符的定位区域。 */
static long search_char_by_point(struct object *self, long x, long y)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long i, n1, n2, left, middle, right;
	int m;

	/* 先确定属于哪一行： */
	i = search_text_line_by_y_coord(self, y);
	if (-1 == i)
		return -1;

	/* 确定属于哪一个字符： */
	m = members->ti.n_spc_clm / 2;
	n1 = members->p_arr_cwxy[i].x - m;
	n2 = members->p_arr_cwxy[i].x + members->p_arr_cwxy[i].w + m;

	if (x >= n1 && x <= n2) {
		return i;
	} else {
		left = search_lf_char_by_char(self, i);
		right = search_ll_char_by_char(self, i);
	}

	while (left <= right) {
		middle = (left + right) / 2;
		n1 = members->p_arr_cwxy[middle].x - m;
		n2 = members->p_arr_cwxy[middle].x +
		     members->p_arr_cwxy[middle].w + m;
		if (x >= n1 && x <= n2)
			return middle;
		else if (x < n1)
			right = middle - 1;
		else
			left = middle + 1;
	}

	return -1;
}

/* DESC: 给定一个字符的索引，确定该字符所在文本行的第一个字符的索引。 */
static long search_lf_char_by_char(struct object *self, long i_char)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long y, left, middle = i_char, right;
	assert(i_char >= 0 && i_char < members->ti.clen);

	left = 0;
	right = i_char;
	y = members->p_arr_cwxy[i_char].y;

	while (left <= right) {
		middle = (left + right) / 2;
		if (members->p_arr_cwxy[middle].y == y) {
			right = middle - 1;
			if (right == -1)
				break;
			else if (members->p_arr_cwxy[right].y < y)
				break;
		} else {
			left = middle + 1;
		}
	}

	return middle;
}

/* DESC: 给定一个字符的索引，确定该字符所在文本行的最后一个字符的索引。 */
static long search_ll_char_by_char(struct object *self, long i_char)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long n, y, left, middle = i_char, right;
	assert(i_char >= 0 && i_char < members->ti.clen);

	n = members->ti.clen;
	y = members->p_arr_cwxy[i_char].y;
	right = n - 1;
	left = i_char;

	while (left <= right) {
		middle = (left + right) / 2;
		if (members->p_arr_cwxy[middle].y == y) {
			left = middle + 1;
			if (left == n)
				break;
			else if (members->p_arr_cwxy[left].y > y)
				break;
		} else {
			right = middle - 1;
		}
	}

	return middle;
}

/*
 * DESC: 在当前位图上方（不是上面）插入初始化的文本，计算字符宽度和
 *       坐标以及判断是否需要创建滚动条。只在CMD_PREPARE行为中调用。
 */
static void overcb_insert_initial_text(struct object *self,
				       const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	HDC hdc;
	SIZE size;
	long i, n, x, y;
	int vpw, vph;

	if (0 == members->ti.clen)
		return;

	n = members->ti.clen;

	/* 计算每个新字符的宽度 */

	hdc = GetDC(*pem_vob->p_wnd_handle);
	for (i = 0; i < n; i++) {
		if (0x0A == members->ti.text[i]) {
			/* 换行符也有宽度，但不需显示换行符，所以记录换行符的宽度为0。 */
			members->p_arr_cwxy[i].w = 0;
		} else {
			GetTextExtentPoint32(hdc, members->ti.text + i, 1,
					     &size);
			members->p_arr_cwxy[i].w = size.cx;
		}
	}
	ReleaseDC(*pem_vob->p_wnd_handle, hdc);

	/* 计算字符的位置 */

	vpw = members->vpw;
	vph = members->vph;
	x = y = 0;

	if (members->style & EDTS_AUTOWRAP) /* 自动换行？ */
	{
		if ((members->p_v_scr_bar != NULL) ||
		    !(members->style &
		      EDTS_SCROLLBAR)) /* 有纵向滚动条，或者，控件没有滚动条风格？ */
		{
			for (i = 0; i < n; i++) {
				if (0x0A ==
				    members->ti.text[i]) /* 是换行符？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				} else if (x + members->p_arr_cwxy[i].w >
					   vpw) /* 超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}
		} else /* 没有纵向滚动条，并且，控件有滚动条风格。 */
		{
			for (i = 0; i < n; i++) {
				if (0x0A ==
				    members->ti.text[i]) /* 是换行符？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (y + members->char_height -
						    members->p_arr_cwxy[0].y >
					    vph) /* 需要加纵向滚动条？ */
					{
						calcu_all_character_xy_lefttop_autowrap(
							self,
							vpw - members->i2vscb
									.n_thickness);
						break;
					} else {
						members->p_arr_cwxy[i].x = 0;
						members->p_arr_cwxy[i].y = y;
						x = members->p_arr_cwxy[i].w +
						    members->ti.n_spc_clm;
					}
				} else if (x + members->p_arr_cwxy[i].w >
					   vpw) /* 超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (y + members->char_height -
						    members->p_arr_cwxy[0].y >
					    vph) /* 需要加纵向滚动条？ */
					{
						calcu_all_character_xy_lefttop_autowrap(
							self,
							vpw - members->i2vscb
									.n_thickness);
						break;
					} else {
						members->p_arr_cwxy[i].x = 0;
						members->p_arr_cwxy[i].y = y;
						x = members->p_arr_cwxy[i].w +
						    members->ti.n_spc_clm;
					}
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}
		}
	} else /* 不是自动换行。 */
	{
		for (i = 0; i < n; i++) {
			if (0x0A == members->ti.text[i]) /* 是换行符？ */
			{
				y += members->char_height +
				     members->ti.n_spc_row;
				members->p_arr_cwxy[i].x = 0;
				members->p_arr_cwxy[i].y = y;
				x = members->p_arr_cwxy[i].w +
				    members->ti.n_spc_clm;
			} else {
				members->p_arr_cwxy[i].x = x;
				members->p_arr_cwxy[i].y = y;
				x += members->p_arr_cwxy[i].w +
				     members->ti.n_spc_clm;
			}
		}
	}

	calcu_text_size(self);
	calcu_scene_size(self);
	calcu_viewport_size(self);

	if (!((members->format & ETF_LEFT) && (members->format & ETF_TOP)))
		format_text(self, 0, members->ti.clen - 1);

	overcb_rdc_scroll_bar(self, caller_context);

	return;
}

/* DESC: 在插入符位置插入一个或多个字符。 */
static void insert_character(struct object *self, long iat, const TCHAR *archar,
			     long count, const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	HDC hdc;
	SIZE size;
	long i, j, n, x, y;
	long i_ncb, i_nce,
		n_ncn; /* NCB: New Character Begin, NCE: New Character End, NCN : New Character Number */
	int vpw, vph, r;

	n = members->ti.cpty - members->ti.clen;
	n_ncn = count < n ? count : n;

	if (0 == n_ncn)
		return;

	i_ncb = iat;

	if (members->ti.clen > 0) {
		memmove(members->ti.text + i_ncb + n_ncn,
			members->ti.text + i_ncb,
			(members->ti.clen - i_ncb) * sizeof(TCHAR));
		memmove(members->p_arr_cwxy + i_ncb + n_ncn,
			members->p_arr_cwxy + i_ncb,
			(members->ti.clen - i_ncb) * sizeof(struct cwxy));
	}
	memcpy(members->ti.text + i_ncb, archar, n_ncn * sizeof(TCHAR));
	members->ti.clen += n_ncn;

	i_nce = i_ncb + n_ncn - 1;

	/* 计算每个新字符的宽度 */

	hdc = GetDC(*pem_vob->p_wnd_handle);
	for (i = 0; i < n_ncn; i++) {
		if (0x0A == archar[i]) {
			/* 换行符也有宽度，但不需显示换行符，所以记录换行符的宽度为0。 */
			members->p_arr_cwxy[i_ncb + i].w = 0;
		} else {
			GetTextExtentPoint32(hdc, archar + i, 1, &size);
			members->p_arr_cwxy[i_ncb + i].w = size.cx;
		}
	}
	ReleaseDC(*pem_vob->p_wnd_handle, hdc);

	/* 计算字符的位置 */

	vpw = members->vpw;
	vph = members->vph;

	if (0 == i_ncb) {
		x = 0;
		y = 0;
	} else {
		x = members->p_arr_cwxy[i_ncb - 1].x +
		    members->p_arr_cwxy[i_ncb - 1].w + members->ti.n_spc_clm;
		y = members->p_arr_cwxy[i_ncb - 1].y;
	}

	i = i_ncb;
	j = i_ncb + n_ncn;

	if (members->style & EDTS_AUTOWRAP) /* 自动换行？ */
	{
		if ((members->p_v_scr_bar != NULL) ||
		    !(members->style &
		      EDTS_SCROLLBAR)) /* 有纵向滚动条，或者，控件没有滚动条风格？ */
		{
			/* 先计算新字符的位置 */

			for (; i < j; i++) {
				if (0x0A == members->ti.text[i] ||
				    x + members->p_arr_cwxy[i].w >
					    vpw) /* 是换行符，或者，超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}

			/* 再计算后面字符的位置 */

			j = members->ti.clen;

			for (; i < j; i++) {
				if (0x0A ==
				    members->ti.text[i]) /* 是换行符？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (members->p_arr_cwxy[i].y ==
					    y) /* 满足中途结束条件？ */
					{
						break;
					} else {
						members->p_arr_cwxy[i].x = 0;
						members->p_arr_cwxy[i].y = y;
						x = members->p_arr_cwxy[i].w +
						    members->ti.n_spc_clm;
					}
				} else if (x + members->p_arr_cwxy[i].w >
					   vpw) /* 超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}
		} else /* 没有纵向滚动条，并且，控件有滚动条风格。 */
		{
			/* 先计算新字符的位置 */

			for (; i < j; i++) {
				if (0x0A == members->ti.text[i] ||
				    x + members->p_arr_cwxy[i].w >
					    vpw) /* 是换行符，或者，超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (y + members->char_height -
						    members->p_arr_cwxy[0].y >
					    vph) /* 需要加纵向滚动条？ */
					{
						calcu_all_character_xy_lefttop_autowrap(
							self,
							vpw - members->i2vscb
									.n_thickness);
						goto INSERTCHAR_GT;
					}
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}

			/* 再计算后面字符的位置 */

			j = members->ti.clen;

			for (; i < j; i++) {
				if (0x0A ==
				    members->ti.text[i]) /* 是换行符？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (members->p_arr_cwxy[i].y ==
					    y) /* 满足中途结束条件。 */
					{
						if (members->p_arr_cwxy
								    [members->ti
									     .clen -
								     1]
									    .y +
							    members->char_height -
							    members->p_arr_cwxy
								    [0]
									    .y >
						    vph) /* 需要加纵向滚动条？ */
						{
							calcu_all_character_xy_lefttop_autowrap(
								self,
								vpw - members->i2vscb
										.n_thickness);
							goto INSERTCHAR_GT;
						} else {
							break;
						}
					} else {
						if (y + members->char_height -
							    members->p_arr_cwxy
								    [0]
									    .y >
						    vph) /* 需要加纵向滚动条？ */
						{
							calcu_all_character_xy_lefttop_autowrap(
								self,
								vpw - members->i2vscb
										.n_thickness);
							goto INSERTCHAR_GT;
						} else {
							members->p_arr_cwxy[i]
								.x = 0;
							members->p_arr_cwxy[i]
								.y = y;
							x = members->p_arr_cwxy
								    [i]
									    .w +
							    members->ti
								    .n_spc_clm;
						}
					}
				} else if (x + members->p_arr_cwxy[i].w >
					   vpw) /* 超过最大行长度？ */
				{
					y += members->char_height +
					     members->ti.n_spc_row;
					if (y + members->char_height -
						    members->p_arr_cwxy[0].y >
					    vph) /* 需要加纵向滚动条？ */
					{
						calcu_all_character_xy_lefttop_autowrap(
							self,
							vpw - members->i2vscb
									.n_thickness);
						goto INSERTCHAR_GT;
					} else {
						members->p_arr_cwxy[i].x = 0;
						members->p_arr_cwxy[i].y = y;
						x = members->p_arr_cwxy[i].w +
						    members->ti.n_spc_clm;
					}
				} else {
					members->p_arr_cwxy[i].x = x;
					members->p_arr_cwxy[i].y = y;
					x += members->p_arr_cwxy[i].w +
					     members->ti.n_spc_clm;
				}
			}
		}
	} else /* 不是自动换行。 */
	{
		/* 先计算新字符的位置 */

		for (; i < j; i++) {
			if (0x0A == members->ti.text[i]) /* 是换行符？ */
			{
				y += members->char_height +
				     members->ti.n_spc_row;
				members->p_arr_cwxy[i].x = 0;
				members->p_arr_cwxy[i].y = y;
				x = members->p_arr_cwxy[i].w +
				    members->ti.n_spc_clm;
			} else {
				members->p_arr_cwxy[i].x = x;
				members->p_arr_cwxy[i].y = y;
				x += members->p_arr_cwxy[i].w +
				     members->ti.n_spc_clm;
			}
		}

		/* 再计算后面字符的位置 */

		j = members->ti.clen;

		for (; i < j; i++) {
			if (0x0A == members->ti.text[i]) /* 是换行符？ */
			{
				y += members->char_height +
				     members->ti.n_spc_row;
				if (members->p_arr_cwxy[i].y ==
				    y) /* 满足中途结束条件？ */
				{
					break;
				} else {
					members->p_arr_cwxy[i].x = 0;
					members->p_arr_cwxy[i].y = y;
					x = members->p_arr_cwxy[i].w +
					    members->ti.n_spc_clm;
				}
			} else {
				members->p_arr_cwxy[i].x = x;
				members->p_arr_cwxy[i].y = y;
				x += members->p_arr_cwxy[i].w +
				     members->ti.n_spc_clm;
			}
		}
	}

INSERTCHAR_GT:

	r = calcu_text_size(self);
	calcu_scene_size(self);
	calcu_viewport_size(self);

	if (!((members->format & ETF_LEFT) && (members->format & ETF_TOP))) {
		if (0 == r)
			format_text(self, i_ncb, i_nce);
		else
			format_text(self, 0, members->ti.clen - 1);
	}

	overcb_rdc_scroll_bar(self, caller_context);
	if (0 == set_caret_position(self, i_nce, TRUE, caller_context))
		vo_interact0(members->visual_node, CMD_WGI_REPAINT,
			     caller_context);

	return;
}

/* DESC: 初始化横向滚动条。 */
static void init_h_scroll_bar(struct object *self,
			      const struct vr *caller_context)
{
	return;
}

/* DESC: 初始化纵向滚动条。 */
static void init_v_scroll_bar(struct object *self,
			      const struct vr *caller_context)
{
	return;
}

/* DESC: 销毁横向滚动条。 */
static void destroy_h_scroll_bar(struct object *self,
				 const struct vr *caller_context)
{
	return;
}

/* DESC: 销毁纵向滚动条。 */
static void destroy_v_scroll_bar(struct object *self,
				 const struct vr *caller_context)
{
	return;
}

/* DESC: 在当前位图的上方（不是上面）重置或销毁或创建滚动条。 */
static void overcb_rdc_scroll_bar(struct object *self,
				  const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct rollingarg rarg;
	int w, h;

	w = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	h = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;

	if (!(members->style & EDTS_SCROLLBAR)) {
		if (members->p_h_scr_bar != NULL)
			destroy_h_scroll_bar(self, caller_context);
		if (members->p_v_scr_bar != NULL)
			destroy_v_scroll_bar(self, caller_context);
		return;
	} else {
		if (members->vpw < w && members->vph < h) {
			if (members->p_h_scr_bar != NULL &&
			    members->p_v_scr_bar != NULL) {
				vo_interact2(members->p_h_scr_bar,
					     CMD_WGI_ROLLONCB,
					     (unsigned char *)&rarg,
					     sizeof(struct rollingarg),
					     caller_context);
				vo_interact2(members->p_v_scr_bar,
					     CMD_WGI_ROLLONCB,
					     (unsigned char *)&rarg,
					     sizeof(struct rollingarg),
					     caller_context);
				return;
			}
		} else if (members->vpw < w) {
			if (NULL == members->p_h_scr_bar &&
			    members->p_v_scr_bar != NULL) {
				vo_interact2(members->p_v_scr_bar,
					     CMD_WGI_ROLLONCB,
					     (unsigned char *)&rarg,
					     sizeof(struct rollingarg),
					     caller_context);
				return;
			}
		} else if (members->vph < h) {
			if (members->p_h_scr_bar != NULL &&
			    NULL == members->p_v_scr_bar) {
				vo_interact2(members->p_h_scr_bar,
					     CMD_WGI_ROLLONCB,
					     (unsigned char *)&rarg,
					     sizeof(struct rollingarg),
					     caller_context);
				return;
			}
		} else /* 视口宽度和高度等于内部矩形宽度和高度。 */
		{
			if (members->p_h_scr_bar != NULL)
				destroy_h_scroll_bar(self, caller_context);
			if (members->p_v_scr_bar != NULL)
				destroy_v_scroll_bar(self, caller_context);
			return;
		}

		if (members->p_h_scr_bar != NULL)
			destroy_h_scroll_bar(self, caller_context);
		if (members->p_v_scr_bar != NULL)
			destroy_v_scroll_bar(self, caller_context);

		if (members->vpw < w) {
			create_object(MSN_CSCROLLBAR, 0, 0, 1,
				      &members->p_h_scr_bar);
			init_h_scroll_bar(self, caller_context);
		}

		if (members->vph < h) {
			create_object(MSN_CSCROLLBAR, 0, 0, 1,
				      &members->p_v_scr_bar);
			init_v_scroll_bar(self, caller_context);
		}
	}

	return;
}

/*
 * DESC: 按左靠齐和顶靠齐格式化方式及自动换行风格，计算所有字符的位置。
 * PARA: max_length-行的最大长度。
 */
static void calcu_all_character_xy_lefttop_autowrap(struct object *self,
						    int max_length)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long i, j, x, y;

	x = y = 0;
	j = members->ti.clen;

	for (i = 0; i < j; i++) {
		if (0x0A == members->ti.text[i] ||
		    x + members->p_arr_cwxy[i].w >
			    max_length) /* 是换行符，或者，超过最大行长度？ */
		{
			y += members->char_height + members->ti.n_spc_row;
			members->p_arr_cwxy[i].x = 0;
			members->p_arr_cwxy[i].y = y;
			x = members->p_arr_cwxy[i].w + members->ti.n_spc_clm;
		} else {
			members->p_arr_cwxy[i].x = x;
			members->p_arr_cwxy[i].y = y;
			x += members->p_arr_cwxy[i].w + members->ti.n_spc_clm;
		}
	}

	return;
}

int c_edit_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->control_node = get_base_node(self, MSN_COBJECT);

		return RP_RCONE;
	}

	return R_P;
}

int c_edit_i_close(struct object *self, const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;

	if (0 == self->ref_count) {
		if (members->p_arr_cwxy)
			free(members->p_arr_cwxy);
		return RP_RCZERO;
	}

	return R_P;
}

int c_edit__cmd_initialize(struct object *self, const struct init_cedit *piced,
			   const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;

	pem_vob->onmcb.p_customer = self;
	pem_vob->onmcb.on_make_current_bitmap = cbf_on_make_current_bitmap;
	members->h_bmp_int_area_vh_scrbar = piced->h_bmp_int_area_vh_scrbar;
	members->i2hscb = piced->i2hscb;
	members->i2vscb = piced->i2vscb;
	members->ti = piced->ti;
	members->style = piced->style;
	members->format = piced->format;
	members->caret_width = piced->caret_width;

	return R_P;
}

int c_edit__cmd_prepare(struct object *self, const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	HFONT h_old_font = NULL;
	HDC hdc;
	TEXTMETRIC tm;

	if (!(0x00000007L & members->format))
		members->format |= ETF_LEFT;

	if (!(0x00000038L & members->format))
		members->format |= ETF_TOP;

	if (0 == members->caret_width)
		members->caret_width = 1;

	if (members->ti.cpty > 0) {
		members->p_arr_cwxy = (struct cwxy *)calloc(
			members->ti.cpty, sizeof(struct cwxy));
		if (NULL == members->p_arr_cwxy)
			return R_N;
	}

	hdc = GetDC(*pem_vob->p_wnd_handle);
	if (members->ti.font)
		h_old_font = SelectObject(hdc, members->ti.font);
	GetTextMetrics(hdc, &tm);
	if (h_old_font != NULL)
		SelectObject(hdc, h_old_font);
	ReleaseDC(*pem_vob->p_wnd_handle, hdc);

	members->char_height = tm.tmHeight;

	overcb_insert_initial_text(self, caller_context);
	vo_interact0(members->visual_node, CMD_PREPARE, caller_context);

	return R_P;
}

int c_edit__msg_wgi_activate(struct object *self,
			     const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_vobject *pem_wob_sup;
	char flag;

	pem_wob_sup = (struct em_vobject *)get_base_members(pem_vob->p_superior,
							    MSN_VOBJECT);
	flag = (self->nodes != pem_wob_sup->p_active_sbdt)
		       ? TRUE
		       : FALSE; /* 标记是否需要创建插入符。 */

	vo_interact0(members->visual_node, MSG_WGI_ACTIVATE, caller_context);

	if (TRUE == flag) /* 需要创建插入符？ */
	{
		CreateCaret(*pem_vob->p_wnd_handle, NULL, members->caret_width,
			    members->char_height);
		/* _Debug_OutputString(TEXT("\nCreateCaret"), 123, NULL); */
	}

	return R_P;
}

int c_edit__msg_wgi_deactivate(struct object *self,
			       const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;

	DestroyCaret(); /* 销毁插入符。 */
	vo_interact0(members->visual_node, MSG_WGI_DEACTIVATE, caller_context);

	return R_P;
}

int c_edit__cmd_wgi_insertcharatcp(struct object *self, const TCHAR *archar,
				   long count, const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	long i;

	if (-1 == members->cp.i_char)
		return R_N;

	if (0 == members->ti.clen)
		i = 0;
	else
		i = (TRUE == members->cp.b_to_right) ? members->cp.i_char + 1
						     : members->cp.i_char;

	insert_character(self, i, archar, count, caller_context);

	return R_P;
}

int c_edit__msg_wgi_focusdown(struct object *self, const POINT pt,
			      const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	long x, y, i, j;

	vo_interact2(members->visual_node, MSG_WGI_FOCUSDOWN,
		     (unsigned char *)&pt, sizeof(POINT), caller_context);

	x = pt.x - pem_vob->rsc.rcinner.left;
	y = pt.y - pem_vob->rsc.rcinner.top;
	if (!(x > 0 && x < members->vpw && y > 0 && y < members->vph))
		return R_P; /* 不在视口内就返回。 */

	if (0 == members->ti.clen) {
		set_caret_position(self, -1, TRUE, caller_context);
		return R_P;
	}

	x -= pem_vob->ox_irr;
	y -= pem_vob->oy_irr;
	j = members->ti.clen - 1;

	if (y > members->p_arr_cwxy[0].y &&
	    y < members->p_arr_cwxy[j].y + members->char_height) {
		i = search_char_by_point(self, x, y);
		if (-1 == i) {
			i = search_text_line_by_y_coord(self, y);
			i = search_lf_char_by_char(self, i);
			if (x < members->p_arr_cwxy[i].x) /* 在行首字符前面？ */
			{
				if (0x0A ==
				    members->ti.text[i]) /* 是换行符？ */
					set_caret_position(self, i, TRUE,
							   caller_context);
				else
					set_caret_position(self, i, FALSE,
							   caller_context);
			} else {
				i = search_ll_char_by_char(self, i);
				set_caret_position(self, i, TRUE,
						   caller_context);
			}
		} else if (
			x <
			members->p_arr_cwxy[i].x +
				members->p_arr_cwxy[i].w /
					2) /* 在i所指字符的定位区域的左半部？ */
		{
			if (0x0A == members->ti.text[i]) /* 是换行符？ */
				set_caret_position(self, i, TRUE,
						   caller_context);
			else if (0 == i)
				set_caret_position(self, i, FALSE,
						   caller_context);
			else if (members->p_arr_cwxy[i - 1].y <
				 members->p_arr_cwxy[i]
					 .y) /* “i-1”所指的字符在上一行？ */
				set_caret_position(self, i, FALSE,
						   caller_context);
			else
				set_caret_position(self, i - 1, TRUE,
						   caller_context);
		} else {
			set_caret_position(self, i, TRUE, caller_context);
		}
	} else if (y <= members->p_arr_cwxy[0].y) {
		set_caret_position(self, 0, FALSE, caller_context);
	} else {
		set_caret_position(self, j, TRUE, caller_context);
	}

	return R_P;
}

int c_edit__cmd_wgi_move(struct object *self, const struct move *pmove,
			 const struct vr *caller_context)
{
	struct em_cedit *members = (struct em_cedit *)self->members;
	POINT pt;

	vo_interact2(members->control_node, CMD_WGI_MOVE,
		     (unsigned char *)pmove, sizeof(struct move),
		     caller_context);

	GetCaretPos(&pt);

	pt.x += pmove->dx_ul;
	pt.y += pmove->dy_ul;
	SetCaretPos(pt.x, pt.y);

	return R_P;
}
