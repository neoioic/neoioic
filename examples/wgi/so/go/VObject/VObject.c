

#include "VObject.h"

int v_object_i_open(struct object *self, const struct vr *caller_context);
int v_object__cmd_initialize(struct object *self,
			     const struct init_vobject *pivob,
			     const struct vr *caller_context);
int v_object__cmd_wgi_refreshdcllpfirstiirsbdt(struct object *self,
					       const struct vr *caller_context);
int v_object__mak_wgi_currentbitmap0(struct object *self,
				     const struct vr *caller_context);
int v_object__mak_wgi_currentbitmap2(struct object *self,
				     const HBITMAP h_bmp_bkgd,
				     const struct vr *caller_context);
int v_object__cmd_wgi_paint(struct object *self,
			    const struct vr *caller_context);
int v_object__cmd_wgi_repaint(struct object *self,
			      const struct vr *caller_context);
int v_object__msg_wgi_focusoverleave(struct object *self,
				     const struct vr *caller_context);
int v_object__msg_wgi_focusonleave(struct object *self,
				   const struct vr *caller_context);
int v_object__msg_wgi_focusover(struct object *self, const POINT pt,
				const struct vr *caller_context);
int v_object__msg_wgi_focuson(struct object *self, const POINT pt,
			      const struct vr *caller_context);
int v_object__msg_wgi_focusovermove(struct object *self, const POINT pt,
				    const struct vr *caller_context);
int v_object__msg_wgi_focusdown(struct object *self, const POINT pt,
				const struct vr *caller_context);
int v_object__msg_wgi_focusup(struct object *self, const POINT pt,
			      const struct vr *caller_context);
int v_object__msg_wgi_focusonmove(struct object *self, const POINT pt,
				  const struct vr *caller_context);
int v_object__msg_wgi_activate(struct object *self,
			       const struct vr *caller_context);
int v_object__msg_wgi_deactivate(struct object *self,
				 const struct vr *caller_context);
int v_object__cmd_prepare(struct object *self, const struct vr *caller_context);
int v_object_i_close(struct object *self, const struct vr *caller_context);
int v_object__cmd_wgi_repaintsuperior(struct object *self,
				      const struct vr *caller_context);
int v_object__cmd_wgi_rollir(struct object *self,
			     const struct irrollingdelta delta,
			     const struct vr *caller_context);

static void make_current_bitmap(struct object *self,
				const HBITMAP h_bmp_background);
static void Deactivate(struct object *self, const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> OIOIC </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int v_object_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return v_object_i_open(self, &caller);
}

static int v_object_input(struct object *self, unsigned char *input_stream,
			  unsigned int quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int v_object_output(struct object *self, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int v_object_io_put(struct object *self, unsigned char *input_stream,
			   unsigned int quantity, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int v_object_interact0(struct object *self, unsigned int action,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_PREPARE:
		return v_object__cmd_prepare(self, &caller);
	case CMD_WGI_REFRESHDCLLPFIRSTIIRSBDT:
		return v_object__cmd_wgi_refreshdcllpfirstiirsbdt(self,
								  &caller);
	case MAK_WGI_CURRENTBITMAP0:
		return v_object__mak_wgi_currentbitmap0(self, &caller);
	case CMD_WGI_PAINT:
		return v_object__cmd_wgi_paint(self, &caller);
	case CMD_WGI_REPAINT:
		return v_object__cmd_wgi_repaint(self, &caller);
	case MSG_WGI_FOCUSOVERLEAVE:
		return v_object__msg_wgi_focusoverleave(self, &caller);
	case MSG_WGI_FOCUSONLEAVE:
		return v_object__msg_wgi_focusonleave(self, &caller);
	case MSG_WGI_ACTIVATE:
		return v_object__msg_wgi_activate(self, &caller);
	case MSG_WGI_DEACTIVATE:
		return v_object__msg_wgi_deactivate(self, &caller);
	case CMD_WGI_REPAINTSUPERIOR:
		return v_object__cmd_wgi_repaintsuperior(self, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int v_object_interact1(struct object *self, unsigned int action,
			      unsigned char *output_stream,
			      unsigned int capacity,
			      unsigned int *output_quantity,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int v_object_interact2(struct object *self, unsigned int action,
			      unsigned char *input_stream,
			      unsigned int quantity,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_INITIALIZE:
		assert(sizeof(struct init_vobject) == quantity);
		return v_object__cmd_initialize(
			self, (struct init_vobject *)input_stream, &caller);
	case MAK_WGI_CURRENTBITMAP2:
		assert(sizeof(HBITMAP) == quantity);
		return v_object__mak_wgi_currentbitmap2(
			self, *(HBITMAP *)input_stream, &caller);
	case MSG_WGI_FOCUSOVER:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focusover(self, *(POINT *)input_stream,
						   &caller);
	case MSG_WGI_FOCUSON:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focuson(self, *(POINT *)input_stream,
						 &caller);
	case MSG_WGI_FOCUSOVERMOVE:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focusovermove(
			self, *(POINT *)input_stream, &caller);
	case MSG_WGI_FOCUSUP:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focusup(self, *(POINT *)input_stream,
						 &caller);
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focusdown(self, *(POINT *)input_stream,
						   &caller);
	case MSG_WGI_FOCUSONMOVE:
		assert(sizeof(POINT) == quantity);
		return v_object__msg_wgi_focusonmove(
			self, *(POINT *)input_stream, &caller);
	case CMD_WGI_ROLLIR:
		assert(sizeof(struct irrollingdelta) == quantity);
		return v_object__cmd_wgi_rollir(
			self, *(struct irrollingdelta *)input_stream, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int v_object_interact3(struct object *self, unsigned int action,
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

static int v_object_close(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	return v_object_i_close(self, &caller);
}

/* TOG */

void tog_v_object(struct object *object)
{
	object->open = v_object_open;
	object->input = v_object_input;
	object->output = v_object_output;
	object->io_put = v_object_io_put;
	object->interact0 = v_object_interact0;
	object->interact1 = v_object_interact1;
	object->interact2 = v_object_interact2;
	object->interact3 = v_object_interact3;
	object->close = v_object_close;
}

/* Function(s) */

/*
 * 刷新p_first_iir_sbdt所指的双向循环链表。
 * 刷新p_first_iir_sbdt所指的双向循环链表。VObject节点函数。
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 * 备    注：	DCLL - Doubly Circularly Linked List，双向循环链表。
 */
static void refresh_dcll_p_first_iir_sbdt(struct object *self)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct object *p_sbdt;
	struct object *p_iir_sbdt;
	struct em_vobject *pem_sbdt;
	struct em_vobject *pem_ii_rsbdt;
	RECT rc;

	if (NULL == members->p_first_sbdt)
		return;

	p_sbdt = members->p_first_sbdt;
	p_iir_sbdt = members->p_first_iir_sbdt = NULL;
	do {
		pem_sbdt = (struct em_vobject *)get_base_members(p_sbdt,
								 MSN_VOBJECT);

		rc = pem_sbdt->rsc.rcouter;
		rc.left += members->rsc.rcinner.left;
		rc.top += members->rsc.rcinner.top;
		rc.right += members->rsc.rcinner.left;
		rc.bottom += members->rsc.rcinner.top;

		if (is_inter2_rects(&members->rsc.rcinner, &rc, NULL)) {
			if (NULL == pem_sbdt->h_bmp_current) {
				/* 没有当前位图，有可能是因为这个下级对象之前不在显示区而被销毁，所以现在需要重新生成当前位图。 */
				make_current_bitmap(
					get_base_node(p_sbdt, MSN_VOBJECT),
					NULL);
			}

			if (NULL == p_iir_sbdt) {
				members->p_first_iir_sbdt = p_iir_sbdt = p_sbdt;
			} else {
				pem_ii_rsbdt =
					(struct em_vobject *)get_base_members(
						p_iir_sbdt, MSN_VOBJECT);
				pem_ii_rsbdt->p_next_isir_codt = p_sbdt;
				pem_ii_rsbdt =
					(struct em_vobject *)get_base_members(
						p_sbdt, MSN_VOBJECT);
				pem_ii_rsbdt->p_prev_isir_codt = p_iir_sbdt;
				p_iir_sbdt = p_sbdt;
			}
		} else if (pem_sbdt->h_bmp_current != NULL) {
			/* 为了节省内存空间，销毁不在显示区的下级对象的当前位图。 */
			DeleteObject(pem_sbdt->h_bmp_current);
			pem_sbdt->h_bmp_current = NULL;
		}

		p_sbdt = pem_sbdt->p_next_codt;

	} while (p_sbdt != members->p_first_sbdt);

	if (p_iir_sbdt != NULL) {
		pem_ii_rsbdt = (struct em_vobject *)get_base_members(
			p_iir_sbdt, MSN_VOBJECT);
		pem_ii_rsbdt->p_next_isir_codt = members->p_first_iir_sbdt;
		pem_ii_rsbdt = (struct em_vobject *)get_base_members(
			members->p_first_iir_sbdt, MSN_VOBJECT);
		pem_ii_rsbdt->p_prev_isir_codt = p_iir_sbdt;
	}

	return;
}

/*
 * 做好内部矩形滚动前的一些数值计算。
 * 做好内部矩形滚动前的一些数值计算。节点函数，VObject。
 * 参    数：	self - [IN] 对象自己；
 *               dx - [IN] 沿X坐标轴的滚动增量，可以为负值；
 *               dy - [IN] 沿Y坐标轴的滚动增量，可以为负值。
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 * 备    注：	IR - Inner Rectangle。
 */
static void calcu_ir_roll(struct object *self, long dx, long dy)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct object *p_sbdt;
	struct em_vobject *pem_sbdt;
	int adx, ady; /* a: actual */
	int w, h, n;

	w = members->rsc.rcinner.right - members->rsc.rcinner.left;
	h = members->rsc.rcinner.bottom - members->rsc.rcinner.top;

	if (dx >= 0) {
		n = -members->ox_irr;
		adx = dx < n ? dx : n;
	} else {
		n = w - members->scenew - members->ox_irr;
		adx = dx > n ? dx : n;
	}

	if (dy >= 0) {
		n = -members->oy_irr;
		ady = dy < n ? dy : n;
	} else {
		n = h - members->sceneh - members->oy_irr;
		ady = dy > n ? dy : n;
	}

	if ((0 == adx && 0 == ady) || NULL == members->p_first_sbdt)
		return;

	p_sbdt = members->p_first_sbdt;
	do {
		pem_sbdt = (struct em_vobject *)get_base_members(p_sbdt,
								 MSN_VOBJECT);
		if (!(pem_sbdt->style & VOBS_XIRROLLABLE)) {
			pem_sbdt->rsc.rcouter.left += adx;
			pem_sbdt->rsc.rcouter.right += adx;
		}
		if (!(pem_sbdt->style & VOBS_YIRROLLABLE)) {
			pem_sbdt->rsc.rcouter.top += ady;
			pem_sbdt->rsc.rcouter.bottom += ady;
		}
		p_sbdt = pem_sbdt->p_next_codt;
	} while (p_sbdt != members->p_first_sbdt);

	refresh_dcll_p_first_iir_sbdt(self);

	members->ox_irr += adx;
	members->oy_irr += ady;

	return;
}

/*
 * 生成当前位图 struct em_vobject.h_bmp_current。
 * 生成当前位图 struct em_vobject.h_bmp_current。节点函数，VObject。
 * 参    数：	self - [IN] 对象自己；
 *               h_bmp_background - [IN] 背景位图，背景位图即没有绘制下级对象的干净位图。
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */

static void make_current_bitmap(struct object *self,
				const HBITMAP h_bmp_background)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	struct object *p_sbdt;
	HDC hdc, memdc1, memdc2, memdc3;
	HBITMAP h_bmp_bkgd;
	HBITMAP h_bmp_inner_rect; /* the bitmap of inner rectangle */
	HBITMAP h_orig_bmp1, h_orig_bmp2, h_orig_bmp3; /* original bitmap */
	HFONT h_old_font = NULL;
	COLORREF cr_old_color;
	BITMAP bm;
	int w, h;

	h_bmp_bkgd = h_bmp_inner_rect = h_orig_bmp1 = h_orig_bmp2 = NULL;

	hdc = GetDC(*members->p_wnd_handle);
	memdc1 = CreateCompatibleDC(hdc);
	memdc2 = CreateCompatibleDC(hdc);

	h_orig_bmp1 = GetCurrentObject(memdc1, OBJ_BITMAP);
	h_orig_bmp2 = GetCurrentObject(memdc2, OBJ_BITMAP);

	h_bmp_bkgd = (NULL == h_bmp_background)
			     ? members->arr_hbitmap[members->state]
			     : h_bmp_background;

	if (members->h_bmp_current != NULL)
		DeleteObject(members->h_bmp_current);
	w = members->rsc.rcouter.right - members->rsc.rcouter.left;
	h = members->rsc.rcouter.bottom - members->rsc.rcouter.top;
	members->h_bmp_current = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(memdc1, members->h_bmp_current);

	if (h_bmp_bkgd != NULL) {
		GetObject(h_bmp_bkgd, sizeof(bm), &bm);
		SelectObject(memdc2, h_bmp_bkgd);
		StretchBlt(memdc1, 0, 0, w, h, memdc2, 0, 0, bm.bmWidth,
			   bm.bmHeight, SRCCOPY);
	}

	SetBkMode(memdc1, TRANSPARENT);

	if (members->onmcb.p_customer != NULL)
		members->onmcb.on_make_current_bitmap(members->onmcb.p_customer,
						      memdc1);

	if (members->ci.clen > 0) {
		if (members->ci.font)
			h_old_font = SelectObject(memdc1, members->ci.font);
		cr_old_color = SetTextColor(memdc1, members->ci.color);

		DrawText(memdc1, members->ci.text, members->ci.clen,
			 &members->ci.rect, members->ci.format);

		if (h_old_font != NULL)
			SelectObject(memdc1, h_old_font);
		SetTextColor(memdc1, cr_old_color);
	}

	if (members->p_first_iir_sbdt != NULL) {
		if (NULL !=
		    get_base_node(members->p_first_iir_sbdt, MSN_COBJECT)) {
			w = members->rsc.rcinner.right -
			    members->rsc.rcinner.left;
			h = members->rsc.rcinner.bottom -
			    members->rsc.rcinner.top;
			h_bmp_inner_rect = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(memdc2, h_bmp_inner_rect);
			BitBlt(memdc2, 0, 0, w, h, memdc1,
			       members->rsc.rcinner.left,
			       members->rsc.rcinner.top, SRCCOPY);

			memdc3 = CreateCompatibleDC(hdc);
			h_orig_bmp3 = GetCurrentObject(memdc3, OBJ_BITMAP);

			p_sbdt = members->p_first_iir_sbdt;
			do {
				pem_sbdt =
					(struct em_vobject *)get_base_members(
						p_sbdt, MSN_VOBJECT);
				GetObject(pem_sbdt->h_bmp_current, sizeof(bm),
					  &bm);
				SelectObject(memdc3, pem_sbdt->h_bmp_current);
				w = pem_sbdt->rsc.rcouter.right -
				    pem_sbdt->rsc.rcouter.left;
				h = pem_sbdt->rsc.rcouter.bottom -
				    pem_sbdt->rsc.rcouter.top;
				StretchBlt(memdc2, pem_sbdt->rsc.rcouter.left,
					   pem_sbdt->rsc.rcouter.top, w, h,
					   memdc3, 0, 0, bm.bmWidth,
					   bm.bmHeight, SRCCOPY);

				p_sbdt = pem_sbdt->p_next_isir_codt;
			} while (p_sbdt != members->p_first_iir_sbdt);

			w = members->rsc.rcinner.right -
			    members->rsc.rcinner.left;
			h = members->rsc.rcinner.bottom -
			    members->rsc.rcinner.top;
			BitBlt(memdc1, members->rsc.rcinner.left,
			       members->rsc.rcinner.top, w, h, memdc2, 0, 0,
			       SRCCOPY);

			SelectObject(memdc3, h_orig_bmp3);
			DeleteDC(memdc3);
		}
	}

	ReleaseDC(*members->p_wnd_handle, hdc);
	SelectObject(memdc1, h_orig_bmp1);
	DeleteDC(memdc1);
	SelectObject(memdc2, h_orig_bmp2);
	DeleteDC(memdc2);

	if (h_bmp_inner_rect != NULL)
		DeleteObject(h_bmp_inner_rect);

	return;
}

/*
 * 显示当前位图struct em_vobject.h_bmp_current。
 * 显示当前位图struct em_vobject.h_bmp_current。节点函数，VObject。
 * 参    数：	self - [IN] 对象自己。
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
static void paint(struct object *self)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_super;
	HDC hdc, memdc;
	HBITMAP h_orig_bmp; /* original bitmap */
	RECT rc1, rc2;
	int w, h, x, y, dx, dy;

	hdc = GetDC(*members->p_wnd_handle);
	memdc = CreateCompatibleDC(hdc);
	h_orig_bmp = GetCurrentObject(memdc, OBJ_BITMAP);

	do {
		if (members->p_superior != NULL) {
			if (NULL != get_base_node(members->p_superior,
						  MSN_COBJECT) ||
			    NULL != get_base_node(members->p_superior,
						  MSN_WPANEL))
				break;
		}

		SelectObject(memdc, members->h_bmp_current);
		w = members->rsc.rcouter.right - members->rsc.rcouter.left;
		h = members->rsc.rcouter.bottom - members->rsc.rcouter.top;
		BitBlt(hdc, 0, 0, w, h, memdc, 0, 0, SRCCOPY);
		ReleaseDC(*members->p_wnd_handle, hdc);
		SelectObject(memdc, h_orig_bmp);
		DeleteDC(memdc);
		return;
	} while (0);

	rc1 = members->rsc.rcouter;
	dx = rc1.left;
	dy = rc1.top;
	pem_super = (struct em_vobject *)get_base_members(members->p_superior,
							  MSN_VOBJECT);

	/* 计算对象的显示区域，dx和dy保存外部矩形左上角到Panel对象的外部矩形左上角的距离。 */
	while (1) {
		dx += pem_super->rsc.rcinner.left;
		dy += pem_super->rsc.rcinner.top;
		rc1.left += pem_super->rsc.rcinner.left;
		rc1.top += pem_super->rsc.rcinner.top;
		rc1.right += pem_super->rsc.rcinner.left;
		rc1.bottom += pem_super->rsc.rcinner.top;

		/* 在此永远不会出现不相交的情况，因为如果对象不在显示区就不会调用paint函数。 */
		is_inter2_rects(&pem_super->rsc.rcinner, &rc1, &rc2);

		if (NULL == pem_super->p_superior)
			break;

		if (NULL == get_base_node(pem_super->p_superior, MSN_COBJECT) &&
		    NULL == get_base_node(pem_super->p_superior, MSN_WPANEL))
			break;

		dx += pem_super->rsc.rcouter.left;
		dy += pem_super->rsc.rcouter.top;
		rc1 = rc2;
		rc1.left += pem_super->rsc.rcouter.left;
		rc1.top += pem_super->rsc.rcouter.top;
		rc1.right += pem_super->rsc.rcouter.left;
		rc1.bottom += pem_super->rsc.rcouter.top;

		pem_super = (struct em_vobject *)get_base_members(
			pem_super->p_superior, MSN_VOBJECT);
	}

	x = rc2.left - dx;
	y = rc2.top - dy;
	w = rc2.right - rc2.left;
	h = rc2.bottom - rc2.top;
	SelectObject(memdc, members->h_bmp_current);
	BitBlt(hdc, rc2.left, rc2.top, w, h, memdc, x, y, SRCCOPY);

	ReleaseDC(*members->p_wnd_handle, hdc);
	SelectObject(memdc, h_orig_bmp);
	DeleteDC(memdc);

	return;
}

/*
 * 重新绘制上级对象。
 * 重新绘制上级对象。节点函数，VObject。
 * 参    数：	self - [IN] 对象自己；
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
static void repaint_superior(struct object *self)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct object *p_v_object_super =
		get_base_node(members->p_superior, MSN_VOBJECT);

	assert(members->p_superior != NULL);

	refresh_dcll_p_first_iir_sbdt(p_v_object_super);
	make_current_bitmap(p_v_object_super, NULL);
	paint(p_v_object_super);

	return;
}

/*
 * 激活对象
 * 激活对象，MSG_WGI_ACTIVATE行为调用。VObject节点函数。
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
static void Activate(struct object *self, const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct object *pvob1;
	struct object *pvob2;
	struct em_vobject *pem_vob1;
	struct em_vobject *pem_vob2;
	enum evobstate state;

	if (VOB_STATE_ACTIVE == members->state)
		return;

	state = members->state;
	members->state = VOB_STATE_ACTIVE;
	if (members->arr_hbitmap[state] != members->arr_hbitmap[members->state])
		make_current_bitmap(self, NULL);

	pvob1 = self;
	pvob2 = NULL;
	pem_vob1 = (struct em_vobject *)pvob1->members;
	while (pem_vob1->p_superior != NULL) {
		pvob2 = get_base_node(pem_vob1->p_superior, MSN_VOBJECT);
		pem_vob2 = (struct em_vobject *)pvob2->members;

		if (pem_vob2->p_active_sbdt != pvob1->nodes) {
			if (pem_vob2->p_active_sbdt != NULL)
				/* Deactivate(get_base_node(pem_vob2->p_active_sbdt, MSN_VOBJECT), caller_context); */
				vo_interact0(pem_vob2->p_active_sbdt,
					     MSG_WGI_DEACTIVATE,
					     caller_context);
			pem_vob2->p_active_sbdt = pvob1->nodes;
		}

		if (pem_vob2->state != VOB_STATE_ACTIVE) {
			pem_vob2->state = VOB_STATE_ACTIVE;
			make_current_bitmap(pvob2, NULL);
			pvob1 = pvob2;
			pem_vob1 = pem_vob2;
		} else {
			make_current_bitmap(pvob2, NULL);
			break;
		}
	}

	paint((NULL == pvob2) ? pvob1 : pvob2);

	return;
}

/*
 * 使对象退出激活状态
 * 使对象退出激活状态，MSG_WGI_DEACTIVATE行为调用。VObject节点函数。
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
static void Deactivate(struct object *self, const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_super;

	if (members->state != VOB_STATE_ACTIVE)
		return;

	if (members->p_active_sbdt != NULL)
		vo_interact0(members->p_active_sbdt, MSG_WGI_DEACTIVATE,
			     caller_context);

	if (members->p_superior != NULL) {
		pem_super = get_base_members(members->p_superior, MSN_VOBJECT);

		if (members->style & VOBS_NOSEMIACTIVE ||
		    pem_super->state == VOB_STATE_ACTIVE) {
			if (pem_super->p_cf_over_sbdt ==
			    self->nodes) /* pem_super->p_active_sbdt) */
				members->state = VOB_STATE_FOCUS_OVER;
			else if (pem_super->p_cf_on_sbdt ==
				 self->nodes) /* pem_super->p_active_sbdt) */
				members->state = VOB_STATE_FOCUS_ON;
			else
				members->state = VOB_STATE_NORMAL;
		} else {
			members->state = VOB_STATE_SEMI_ACTIVE;
		}

		pem_super->p_active_sbdt = NULL;
	} else {
		members->state = VOB_STATE_NORMAL;
	}

	make_current_bitmap(self, NULL);
	paint(self);

	return;
}

int v_object_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);

		return RP_RCONE;
	}

	return R_P;
}

int v_object_i_close(struct object *self, const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;

	if (0 == self->ref_count) {
		if (members->h_bmp_current != NULL) {
			DeleteObject(members->h_bmp_current);
			members->h_bmp_current = NULL;
		}

		return RP_RCZERO;
	}

	return R_P;
}

int v_object__cmd_prepare(struct object *self, const struct vr *caller_context)
{
	refresh_dcll_p_first_iir_sbdt(self);
	make_current_bitmap(self, NULL);
	return R_P;
}

int v_object__cmd_wgi_refreshdcllpfirstiirsbdt(struct object *self,
					       const struct vr *caller_context)
{
	refresh_dcll_p_first_iir_sbdt(self);
	return R_P;
}

int v_object__mak_wgi_currentbitmap0(struct object *self,
				     const struct vr *caller_context)
{
	make_current_bitmap(self, NULL);
	return R_P;
}

int v_object__cmd_wgi_paint(struct object *self,
			    const struct vr *caller_context)
{
	paint(self);
	return R_P;
}

int v_object__cmd_wgi_repaint(struct object *self,
			      const struct vr *caller_context)
{
	refresh_dcll_p_first_iir_sbdt(self);
	make_current_bitmap(self, NULL);
	paint(self);

	return R_P;
}

int v_object__cmd_wgi_repaintsuperior(struct object *self,
				      const struct vr *caller_context)
{
	repaint_superior(self);
	return R_P;
}

int v_object__msg_wgi_focusoverleave(struct object *self,
				     const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	enum evobstate state;

	if (members->state != VOB_STATE_ACTIVE &&
	    members->state != VOB_STATE_SELECTED &&
	    members->state != VOB_STATE_DISABLE) {
		state = members->state;
		members->state = VOB_STATE_NORMAL;
		if (members->arr_hbitmap[state] !=
		    members->arr_hbitmap[members->state]) {
			make_current_bitmap(self, NULL);
			paint(self);
		}
	}

	return R_P;
}

int v_object__msg_wgi_focusonleave(struct object *self,
				   const struct vr *caller_context)
{
	return v_object__msg_wgi_focusoverleave(self, caller_context);
}

int v_object__msg_wgi_activate(struct object *self,
			       const struct vr *caller_context)
{
	Activate(self, caller_context);
	return R_P;
}

int v_object__msg_wgi_deactivate(struct object *self,
				 const struct vr *caller_context)
{
	Deactivate(self, caller_context);
	return R_P;
}

int v_object__cmd_initialize(struct object *self,
			     const struct init_vobject *pivob,
			     const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;

	members->p_superior = pivob->p_superior;
	/* pem->p_first_sbdt = pivob->p_first_sbdt; */
	members->p_prev_codt = pivob->p_prev_codt;
	members->p_next_codt = pivob->p_next_codt;
	/* pem->p_first_iir_sbdt = pivob->p_first_iir_sbdt; */
	/* pem->p_prev_isir_codt = pivob->p_prev_isir_codt; */
	/* pem->p_next_isir_codt = pivob->p_next_isir_codt; */
	/* pem->ox_irr = pivob->ox_irr; */
	/* pem->oy_irr = pivob->oy_irr; */
	members->scenew = pivob->scenew;
	members->sceneh = pivob->sceneh;
	/* pem->hDC = pivob->hDC; */
	memcpy(members->arr_hbitmap, pivob->arr_hbitmap,
	       sizeof(members->arr_hbitmap));
	members->style = pivob->style;
	members->state = pivob->state;
	members->ci = pivob->ci;
	members->rsc = pivob->rsc;
	members->as = pivob->as;
	members->rgn = pivob->rgn;

	return R_P;
}

int v_object__mak_wgi_currentbitmap2(struct object *self,
				     const HBITMAP h_bmp_bkgd,
				     const struct vr *caller_context)
{
	make_current_bitmap(self, h_bmp_bkgd);
	return R_P;
}

int v_object__msg_wgi_focusover(struct object *self, const POINT pt,
				const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	struct object *p_iir_sbdt;
	struct object *p_prev_of_first_sbdt;
	enum evobstate state;
	int r;
	POINT pt1;

	members->p_cf_up_sbdt = NULL;

	if (members->state != VOB_STATE_ACTIVE &&
	    members->state != VOB_STATE_SELECTED &&
	    members->state != VOB_STATE_DISABLE) {
		state = members->state;
		members->state = VOB_STATE_FOCUS_OVER;
		if (members->arr_hbitmap[state] !=
		    members->arr_hbitmap[members->state]) {
			make_current_bitmap(self, NULL);
			paint(self);
		}
	}

	if (NULL == members->p_first_iir_sbdt)
		return R_P;

	if (!PtInRect(&members->rsc.rcinner, pt))
		return R_P;

	pem_sbdt = get_base_members(members->p_first_iir_sbdt, MSN_VOBJECT);
	p_prev_of_first_sbdt = pem_sbdt->p_prev_codt;
	p_iir_sbdt = p_prev_of_first_sbdt;

	while (1) {
		pt1 = pt;
		pt1.x -= members->rsc.rcinner.left;
		pt1.y -= members->rsc.rcinner.top;

		pem_sbdt = get_base_members(p_iir_sbdt, MSN_VOBJECT);

		if (0 == pem_sbdt->as.zp.plg.npt)
			r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
		else
			r = is_point_in_polygon(
				    pt1.x - pem_sbdt->rsc.rcouter.left,
				    pt1.y - pem_sbdt->rsc.rcouter.top,
				    &pem_sbdt->as.zp.plg)
				    ? R_P
				    : R_N;

		if (R_P == r && pem_sbdt->state != VOB_STATE_HIDDEN) {
			pt1.x -= pem_sbdt->rsc.rcouter.left;
			pt1.y -= pem_sbdt->rsc.rcouter.top;

			members->p_cf_over_sbdt = p_iir_sbdt;
			vo_interact2(members->p_cf_over_sbdt, MSG_WGI_FOCUSOVER,
				     (unsigned char *)&pt1, sizeof(POINT),
				     caller_context);
			break;
		} else if (pem_sbdt->p_prev_isir_codt != p_prev_of_first_sbdt) {
			p_iir_sbdt = pem_sbdt->p_prev_isir_codt;
		} else {
			members->p_cf_over_sbdt = NULL;
			break;
		}
	}

	return R_P;
}

/* REMARK: 焦点ON与OVER的实现类似，修改时以OVER的实现为准。 */
int v_object__msg_wgi_focuson(struct object *self, const POINT pt,
			      const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	struct object *p_iir_sbdt;
	struct object *p_prev_of_first_sbdt;
	enum evobstate state;
	int r;
	POINT pt1;

	members->p_cf_down_sbdt = NULL;

	if (members->state != VOB_STATE_ACTIVE &&
	    members->state != VOB_STATE_SELECTED &&
	    members->state != VOB_STATE_DISABLE) {
		state = members->state;
		members->state = VOB_STATE_FOCUS_ON;
		if (members->arr_hbitmap[state] !=
		    members->arr_hbitmap[members->state]) {
			make_current_bitmap(self, NULL);
			paint(self);
		}
	}

	if (NULL == members->p_first_iir_sbdt)
		return R_P;

	if (!PtInRect(&members->rsc.rcinner, pt))
		return R_P;

	pem_sbdt = get_base_members(members->p_first_iir_sbdt, MSN_VOBJECT);
	p_prev_of_first_sbdt = pem_sbdt->p_prev_codt;
	p_iir_sbdt = p_prev_of_first_sbdt;

	while (1) {
		pt1 = pt;
		pt1.x -= members->rsc.rcinner.left;
		pt1.y -= members->rsc.rcinner.top;

		pem_sbdt = get_base_members(p_iir_sbdt, MSN_VOBJECT);

		if (0 == pem_sbdt->as.zp.plg.npt)
			r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
		else
			r = is_point_in_polygon(
				    pt1.x - pem_sbdt->rsc.rcouter.left,
				    pt1.y - pem_sbdt->rsc.rcouter.top,
				    &pem_sbdt->as.zp.plg)
				    ? R_P
				    : R_N;

		if (R_P == r && pem_sbdt->state != VOB_STATE_HIDDEN) {
			pt1.x -= pem_sbdt->rsc.rcouter.left;
			pt1.y -= pem_sbdt->rsc.rcouter.top;

			members->p_cf_on_sbdt = p_iir_sbdt;
			vo_interact2(members->p_cf_on_sbdt, MSG_WGI_FOCUSON,
				     (unsigned char *)&pt1, sizeof(POINT),
				     caller_context);
			break;
		} else if (pem_sbdt->p_prev_isir_codt != p_prev_of_first_sbdt) {
			p_iir_sbdt = pem_sbdt->p_prev_isir_codt;
		} else {
			members->p_cf_on_sbdt = NULL;
			break;
		}
	}

	return R_P;
}

int v_object__msg_wgi_focusovermove(struct object *self, const POINT pt,
				    const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	struct object *p_iir_sbdt;
	struct object *p_prev_of_first_iir_sbdt;
	int r;
	POINT pt1;

	if (NULL == members->p_first_iir_sbdt ||
	    !PtInRect(&members->rsc.rcinner, pt))
		return R_P;

	pem_sbdt = get_base_members(members->p_first_iir_sbdt, MSN_VOBJECT);
	p_prev_of_first_iir_sbdt = pem_sbdt->p_prev_isir_codt;
	p_iir_sbdt = p_prev_of_first_iir_sbdt;

	while (1) {
		pt1 = pt;
		pt1.x -= members->rsc.rcinner.left;
		pt1.y -= members->rsc.rcinner.top;

		pem_sbdt = get_base_members(p_iir_sbdt, MSN_VOBJECT);

		if (0 == pem_sbdt->as.zp.plg.npt)
			r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
		else
			r = is_point_in_polygon(
				    pt1.x - pem_sbdt->rsc.rcouter.left,
				    pt1.y - pem_sbdt->rsc.rcouter.top,
				    &pem_sbdt->as.zp.plg)
				    ? R_P
				    : R_N;

		if (R_P == r && pem_sbdt->state != VOB_STATE_HIDDEN) {
			pt1.x -= pem_sbdt->rsc.rcouter.left;
			pt1.y -= pem_sbdt->rsc.rcouter.top;

			if (p_iir_sbdt == members->p_cf_over_sbdt) {
				vo_interact2(p_iir_sbdt, MSG_WGI_FOCUSOVERMOVE,
					     (unsigned char *)&pt1,
					     sizeof(POINT), caller_context);
				break;
			}

			if (NULL != members->p_cf_over_sbdt)
				vo_interact0(members->p_cf_over_sbdt,
					     MSG_WGI_FOCUSOVERLEAVE,
					     caller_context);
			members->p_cf_over_sbdt = p_iir_sbdt;
			vo_interact2(p_iir_sbdt, MSG_WGI_FOCUSOVER,
				     (unsigned char *)&pt1, sizeof(POINT),
				     caller_context);

			break;
		} else if (pem_sbdt->p_prev_isir_codt !=
			   p_prev_of_first_iir_sbdt) {
			p_iir_sbdt = pem_sbdt->p_prev_isir_codt;
		} else {
			if (NULL != members->p_cf_over_sbdt) {
				vo_interact0(members->p_cf_over_sbdt,
					     MSG_WGI_FOCUSOVERLEAVE,
					     caller_context);
				members->p_cf_over_sbdt = NULL;
			}

			break;
		}
	}

	return R_P;
}

/* REMARK: 焦点ON-struct move与OVER-struct move的实现类似，修改时以OVER-struct move的实现为准。 */
int v_object__msg_wgi_focusonmove(struct object *self, const POINT pt,
				  const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	struct object *p_iir_sbdt;
	struct object *p_prev_of_first_iir_sbdt;
	int r;
	POINT pt1;

	if (NULL == members->p_first_iir_sbdt ||
	    !PtInRect(&members->rsc.rcinner, pt))
		return R_P;

	pem_sbdt = get_base_members(members->p_first_iir_sbdt, MSN_VOBJECT);
	p_prev_of_first_iir_sbdt = pem_sbdt->p_prev_isir_codt;
	p_iir_sbdt = p_prev_of_first_iir_sbdt;

	while (1) {
		pt1 = pt;
		pt1.x -= members->rsc.rcinner.left;
		pt1.y -= members->rsc.rcinner.top;

		pem_sbdt = get_base_members(p_iir_sbdt, MSN_VOBJECT);

		if (0 == pem_sbdt->as.zp.plg.npt)
			r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
		else
			r = is_point_in_polygon(
				    pt1.x - pem_sbdt->rsc.rcouter.left,
				    pt1.y - pem_sbdt->rsc.rcouter.top,
				    &pem_sbdt->as.zp.plg)
				    ? R_P
				    : R_N;

		if (R_P == r && pem_sbdt->state != VOB_STATE_HIDDEN) {
			pt1.x -= pem_sbdt->rsc.rcouter.left;
			pt1.y -= pem_sbdt->rsc.rcouter.top;

			if (p_iir_sbdt == members->p_cf_on_sbdt) {
				vo_interact2(p_iir_sbdt, MSG_WGI_FOCUSONMOVE,
					     (unsigned char *)&pt1,
					     sizeof(POINT), caller_context);
				break;
			}

			if (NULL != members->p_cf_on_sbdt)
				vo_interact0(members->p_cf_on_sbdt,
					     MSG_WGI_FOCUSONLEAVE,
					     caller_context);
			members->p_cf_on_sbdt = p_iir_sbdt;
			vo_interact2(p_iir_sbdt, MSG_WGI_FOCUSON,
				     (unsigned char *)&pt1, sizeof(POINT),
				     caller_context);

			break;
		} else if (pem_sbdt->p_prev_isir_codt !=
			   p_prev_of_first_iir_sbdt) {
			p_iir_sbdt = pem_sbdt->p_prev_isir_codt;
		} else {
			if (NULL != members->p_cf_on_sbdt) {
				vo_interact0(members->p_cf_on_sbdt,
					     MSG_WGI_FOCUSONLEAVE,
					     caller_context);
				members->p_cf_on_sbdt = NULL;
			}

			break;
		}
	}

	return R_P;
}

int v_object__msg_wgi_focusdown(struct object *self, const POINT pt,
				const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	POINT pt1;

	members->p_cf_down_sbdt = members->p_cf_over_sbdt;

	if (members->p_cf_down_sbdt != NULL) {
		pt1 = pt;
		pem_sbdt =
			get_base_members(members->p_cf_down_sbdt, MSN_VOBJECT);
		pt1.x -= members->rsc.rcinner.left + pem_sbdt->rsc.rcouter.left;
		pt1.y -= members->rsc.rcinner.top + pem_sbdt->rsc.rcouter.top;
		vo_interact2(members->p_cf_down_sbdt, MSG_WGI_FOCUSDOWN,
			     (unsigned char *)&pt1, sizeof(POINT),
			     caller_context);
		members->p_cf_over_sbdt = NULL;
	}

	return R_P;
}

/* REMARK: 焦点UP与DOWN的实现类似，修改时要参考DOWN的实现。 */
int v_object__msg_wgi_focusup(struct object *self, const POINT pt,
			      const struct vr *caller_context)
{
	struct em_vobject *members = (struct em_vobject *)self->members;
	struct em_vobject *pem_sbdt;
	POINT pt1;

	members->p_cf_up_sbdt = members->p_cf_on_sbdt;

	if (members->p_cf_up_sbdt != NULL) {
		pt1 = pt;
		pem_sbdt = get_base_members(members->p_cf_up_sbdt, MSN_VOBJECT);
		pt1.x -= members->rsc.rcinner.left + pem_sbdt->rsc.rcouter.left;
		pt1.y -= members->rsc.rcinner.top + pem_sbdt->rsc.rcouter.top;
		vo_interact2(members->p_cf_up_sbdt, MSG_WGI_FOCUSUP,
			     (unsigned char *)&pt1, sizeof(POINT),
			     caller_context);
		members->p_cf_on_sbdt = NULL;
	}

	return R_P;
}

int v_object__cmd_wgi_rollir(struct object *self,
			     const struct irrollingdelta delta,
			     const struct vr *caller_context)
{
	calcu_ir_roll(self, delta.dx, delta.dy);
	make_current_bitmap(self, NULL);
	paint(self);
	return R_P;
}
