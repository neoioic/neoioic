

#ifndef NEOIOIC_MYBUTTON_H
#define NEOIOIC_MYBUTTON_H

#include "../general.h"

/*
 *  subordinates' coordinates.
 *  L - left, T - top.
 */

#define MYBUTTON_BUTTON1_L 130
#define MYBUTTON_BUTTON1_T 20

#define MYBUTTON_MYBUTTON_L 130
#define MYBUTTON_MYBUTTON_T 100

#define MYBUTTON_BUTTON3_L 130
#define MYBUTTON_BUTTON3_T 260

/* DESC: enumerate subordinates of my_button */
enum esmybutton {
	BUTTON1_MY_BUTTON,
	BUTTON2_MY_BUTTON,
	BUTTON3_MY_BUTTON,

	/* - number of enum - */
	NUM_SUB_MY_BUTTON
};

enum ebitmap_mybutton {
	/* - Button - */
	BUTTON_NORMAL_BMP_MY_BUTTON,
	BUTTON_FOCUS_OVER_BMP_MY_BUTTON,
	BUTTON_FOCUS_ON_BMP_MY_BUTTON,
	BUTTON_ACTIVE_BMP_MY_BUTTON,
	BUTTON_ABS_INACTIVE_BMP_MY_BUTTON,

	/* - number of enum - */
	NUM_BMP_MY_BUTTON
};

/* INIT */

/* Extended Member */

struct em_mybutton {
	struct object *neoioic_node;
	struct object *visual_node;
	struct object *control_node;
	struct object *p_c_button;
	HBITMAP arr_hbitmap[NUM_BMP_MY_BUTTON];
	struct object *arr_sub[NUM_SUB_MY_BUTTON];
	POINT lastpt;
};

#endif /* #ifndef NEOIOIC_MYBUTTON_H */
