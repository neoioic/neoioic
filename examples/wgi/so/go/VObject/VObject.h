

#ifndef OIOIC_VOBJECT_H
#define OIOIC_VOBJECT_H

#include "../go.h"

/* 文本格式化方式定义 */
#define CTF_LEFT DT_LEFT      /* aligns text to the left. */
#define CTF_RIGHT DT_RIGHT    /* aligns text to the right. */
#define CTF_HCENTER DT_CENTER /* horizontally centers text. */
#define CTF_VCENTER \
	DT_VCENTER /* vertically centeres text (single line only). */

/* 可视对象的风格定义 */
#define VOBS_IMMOVABLE 0x00000001L   /* 1: Immovable, 0: Movable */
#define VOBS_XIRROLLABLE 0x00000002L /* 1: Irrollable By X, 0: Rollable By X. */
#define VOBS_YIRROLLABLE 0x00000004L /* 1: Irrollable By Y, 0: Rollable By Y. */
#define VOBS_INACTIVABLE 0x00000008L /* 1: Inactivable, 0: Activable */
#define VOBS_NOSEMIACTIVE \
	0x00000020L /* 1: no the state of "VOB_STATE_SEMI_ACTIVE", 0: has the state of "VOB_STATE_SEMI_ACTIVE". */

/* 可视对象状态枚举 */
enum evobstate {
	VOB_STATE_NORMAL,
	VOB_STATE_FOCUS_OVER,
	VOB_STATE_FOCUS_ON,
	VOB_STATE_ACTIVE,
	VOB_STATE_SEMI_ACTIVE,
	VOB_STATE_SELECTED,
	VOB_STATE_DISABLE,
	VOB_STATE_HIDDEN,

	/* - number of state - */
	NUM_VOB_STATE
};

/* 标题信息 */
struct captioninfo {
	TCHAR *text;
	long cpty;
	long clen;
	RECT rect;
	UINT format;
	HFONT font;
	COLORREF color;
};

/* 矩形空间坐标结构体 */
struct rscoordinate {
	RECT rcouter;
	RECT rcinner;
	int z;
};

/* Z轴多边形单向链表（Singly Linked List）节点结构体 */
struct zpolygonsllnode {
	struct zpolygon zp;
	struct zpolygonsllnode *next;
};

/* 主动碰撞（active collision）单向链表节点结构体 */
struct atvcollisionsllnode {
	struct object *object;
	struct zpolygonsllnode *p_rgn;
	struct atvcollisionsllnode *next;
};

/* 对象移动时的输入流 */
struct move {
	int dx_ul;
	int dx_lr;
	int dy_ul;
	int dy_lr;
	int dz;
	struct atvcollisionsllnode *pacsn;
};

/* 被动碰撞（passive collision）结构体 */
struct psvcollision {
	struct object *object;
	struct zpolygonsllnode *p_rgn;
};

/* 内部矩形滚动偏移量结构体 */
struct irrollingdelta {
	long dx;
	long dy;
};

/*
 * 这个结构体让用户在VObject节点制作当前位图时定制当前位图的内容。
 *       比如Edit控件自己在当前位图上写文本内容，就是通过让VObject节点回调自己的函数来实现的。
 */
struct onmakecurrentbitmap {
	struct object *p_customer;
	void (*on_make_current_bitmap)(struct object *p_customer,
				       const HDC hDC);
};

/* INIT */

struct init_vobject {
	struct object *p_superior;
	/* struct object*          p_first_sbdt; */
	struct object *p_prev_codt;
	struct object *p_next_codt;
	/* struct object*          p_first_iir_sbdt; */
	/* struct object*          p_prev_isir_codt; */
	/* struct object*          p_next_isir_codt; */
	/* long             ox_irr; */
	/* long             oy_irr; */
	long scenew;
	long sceneh;
	HBITMAP arr_hbitmap[NUM_VOB_STATE];
	unsigned int style;
	enum evobstate state;
	struct captioninfo ci;
	struct rscoordinate rsc;
	struct zpolygonsllnode as;
	struct zpolygonsllnode rgn;
};

/* Extended Member */

struct em_vobject {
	struct object *oioic_node;
	struct object *p_superior;
	struct object *p_first_sbdt;
	struct object *p_prev_codt;
	struct object *p_next_codt;
	struct object *p_first_iir_sbdt;
	struct object *p_prev_isir_codt;
	struct object *p_next_isir_codt;
	struct object *p_active_sbdt;
	struct object *p_cf_over_sbdt;
	struct object *p_cf_down_sbdt;
	struct object *p_cf_on_sbdt;
	struct object *p_cf_up_sbdt;
	long ox_irr;
	long oy_irr;
	long scenew;
	long sceneh;
	const HWND *p_wnd_handle;
	HBITMAP arr_hbitmap[NUM_VOB_STATE];
	HBITMAP h_bmp_current;
	unsigned int style;
	enum evobstate state;
	struct captioninfo ci;
	struct rscoordinate rsc;
	struct zpolygonsllnode as;
	struct zpolygonsllnode rgn;
	POINT lastpt;
	struct onmakecurrentbitmap onmcb;
};

#endif /* #ifndef OIOIC_VOBJECT_H */
