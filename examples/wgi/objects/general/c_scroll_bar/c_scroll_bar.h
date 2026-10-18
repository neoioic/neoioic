

#ifndef NEOIOIC_CSCROLLBAR_H
#define NEOIOIC_CSCROLLBAR_H

#include "../general.h"

struct rollingarg {
	long lrs1;
	long lrs2;
	long lrs3;
};

/* INIT */

struct init_cscrollbar {
	int n_rb1_l_margin;
	int n_rb1_t_margin;
	int n_rb2_r_margin;
	int n_rb2_b_margin;
	int n_rg_margin;
	int n_rb1_width;
	int n_rb1_height;
	int n_rb2_width;
	int n_rb2_height;
	int n_rg_thickness;
	HBITMAP h_bmp_rb1_normal;
	HBITMAP h_bmp_rb1_focus_over;
	HBITMAP h_bmp_rb1_focus_on;
	HBITMAP h_bmp_rb2_normal;
	HBITMAP h_bmp_rb2_focus_over;
	HBITMAP h_bmp_rb2_focus_on;
	HBITMAP h_bmp_rg_normal;
	HBITMAP h_bmp_rg_focus_over;
	HBITMAP h_bmp_rg_focus_on;
};

struct init2_cscrollbar {
	struct init_cscrollbar iscb;
	HBITMAP h_bmp_normal;
	HBITMAP h_bmp_focus_over;
	HBITMAP h_bmp_focus_on;
	int n_thickness;
};

/* Extended Member */

struct em_cscrollbar {
	struct object *neoioic_node;
	struct object *visual_node;
	struct object *control_node;
	int n_rb1_l_margin;
	int n_rb1_t_margin;
	int n_rb2_r_margin;
	int n_rb2_b_margin;
	int n_rg_margin;
	int n_rb1_width;
	int n_rb1_height;
	int n_rb2_width;
	int n_rb2_height;
	int n_rg_thickness;
	HBITMAP h_bmp_rb1_normal;
	HBITMAP h_bmp_rb1_focus_over;
	HBITMAP h_bmp_rb1_focus_on;
	HBITMAP h_bmp_rb2_normal;
	HBITMAP h_bmp_rb2_focus_over;
	HBITMAP h_bmp_rb2_focus_on;
	HBITMAP h_bmp_rg_normal;
	HBITMAP h_bmp_rg_focus_over;
	HBITMAP h_bmp_rg_focus_on;
};

#endif /* #ifndef NEOIOIC_CSCROLLBAR_H */
