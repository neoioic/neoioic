

#ifndef OIOIC_WMENU_H
#define OIOIC_WMENU_H

#include "../go.h"
#include "../WPanel/WPanel.h"

/* 菜单与不能遮盖区域的位置关系 */
#define MNUT_TBLEFT 0
#define MNUT_TBRIGHT 1
#define MNUT_LRTOP 2
#define MNUT_LRBOTTOM 3

/* INIT */

struct init_wmenu {
	struct init_vobject ivob;
	struct init_wobject iwob;
	struct object *p_parent;
	int n_rb_height;
	RECT uca;
	int type;
	int width;
	HBITMAP h_bmp_trb_normal;
	HBITMAP h_bmp_trb_focus_over;
	HBITMAP h_bmp_trb_focus_on;
	HBITMAP h_bmp_brb_normal;
	HBITMAP h_bmp_brb_focus_over;
	HBITMAP h_bmp_brb_focus_on;
	UINT timertov;
	int rollstep;
	char (*create_items)(struct object *pWMenu,
			     const struct vr *caller_context);
	char (*destroy_items)(struct object *pWMenu,
			      const struct vr *caller_context);
};

/* Extended Member */

struct em_wmenu {
	struct object *oioic_node;
	struct object *visual_node;
	struct object *window_node;
	struct object *panel_node;
	struct object *p_parent;
	struct object *p_cf_over_sbdt;
	struct object *p_sub_menu;
	struct object *p_tr_button;
	struct object *p_br_button;
	int n_rb_height;
	RECT uca;
	int type;
	int width;
	HBITMAP h_bmp_trb_normal;
	HBITMAP h_bmp_trb_focus_over;
	HBITMAP h_bmp_trb_focus_on;
	HBITMAP h_bmp_brb_normal;
	HBITMAP h_bmp_brb_focus_over;
	HBITMAP h_bmp_brb_focus_on;
	UINT timerid;
	UINT timertov;
	int rollstep;
	char (*create_items)(struct object *self,
			     const struct vr *caller_context);
	char (*destroy_items)(struct object *self,
			      const struct vr *caller_context);
};

extern struct object *pop_menu(const struct init_wmenu *piwmu,
			       const struct vr *caller_context);

#endif /* #ifndef OIOIC_WMENU_H */
