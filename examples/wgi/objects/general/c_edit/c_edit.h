

#ifndef NEOIOIC_CEDIT_H
#define NEOIOIC_CEDIT_H

#include "../general.h"
#include "../c_scroll_bar/c_scroll_bar.h"

/* 控件风格 */
#define EDTS_AUTOWRAP 0x00000001L /* 1 - 自动换行, 0 - 不自动换行。 */
#define EDTS_SCROLLBAR \
	0x00000002L /* 1 - 有滚动条（自动添加）, 0 - 没有滚动条。 */

/* 文本对齐风格（即文本格式化方式） */
#define ETF_LEFT 0x00000001L	/* 1 - 左靠齐, 0 - 不左靠齐。 */
#define ETF_RIGHT 0x00000002L	/* 1 - 右靠齐, 0 - 不右靠齐。 */
#define ETF_HCENTER 0x00000004L /* 1 - 水平居中, 0 - 不水平居中。 */
#define ETF_TOP 0x00000008L	/* 1 - 顶靠齐, 0 - 不顶靠齐。 */
#define ETF_BOTTOM 0x00000010L	/* 1 - 底靠齐, 0 - 不底靠齐。 */
#define ETF_VCENTER 0x00000020L /* 1 - 垂直居中, 0 - 不垂直居中。 */

/* 字符宽度和位置 */
struct cwxy {
	int w;
	long x;
	long y;
};

/* 文本信息 */
struct edittextinfo {
	TCHAR *text;
	long cpty;
	long clen;
	HFONT font;
	COLORREF crnor;
	COLORREF crsel;
	COLORREF crbgsel;
	int n_spc_row;
	int n_spc_clm;
};

/* 插入符位置 */
struct caretpos {
	long i_char;
	char b_to_right;
};

/* INIT */

struct init_cedit {
	struct init2_cscrollbar i2hscb;
	struct init2_cscrollbar i2vscb;
	struct edittextinfo ti;
	unsigned int format;
	unsigned int style;
	int caret_width;
	HBITMAP h_bmp_int_area_vh_scrbar;
};

/* Extended Member */

struct em_cedit {
	struct object *neoioic_node;
	struct object *visual_node;
	struct object *control_node;
	struct edittextinfo ti;
	int vpw;
	int vph;
	long text_width;
	long text_height;
	unsigned int format;
	unsigned int style;
	int caret_width;
	int char_height;
	struct cwxy *p_arr_cwxy;
	struct caretpos cp;
	struct init2_cscrollbar i2hscb;
	struct init2_cscrollbar i2vscb;
	struct object *p_h_scr_bar;
	struct object *p_v_scr_bar;
	HBITMAP h_bmp_int_area_vh_scrbar;
};

#endif /* #ifndef NEOIOIC_CEDIT_H */
