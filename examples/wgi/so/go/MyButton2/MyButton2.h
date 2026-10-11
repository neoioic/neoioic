

#ifndef OIOIC_MYBUTTON2_H
#define OIOIC_MYBUTTON2_H

#include "../go.h"

/*
 *  subordinates' coordinates.
 *  L - left, T - top.
 */

#define MYBUTTON2_BUTTON_L 80
#define MYBUTTON2_BUTTON_T 80

/* DESC: enumerate subordinates of MyButton2 */
enum esmybutton2 {
	BUTTON_MY_BUTTON2,

	/* - number of enum - */
	NUM_SUB_MY_BUTTON2
};

enum ebitmap_mybutton2 {
	/* - Button - */
	BUTTON_NORMAL_BMP_MY_BUTTON2,
	BUTTON_FOCUS_OVER_BMP_MY_BUTTON2,
	BUTTON_FOCUS_ON_BMP_MY_BUTTON2,
	BUTTON_ACTIVE_BMP_MY_BUTTON2,
	BUTTON_ABS_INACTIVE_BMP_MY_BUTTON2,

	/* - number of enum - */
	NUM_BMP_MY_BUTTON2
};

/* INIT */

/* Extended Member */

struct em_mybutton2 {
	struct object *oioic_node;
	struct object *visual_node;
	struct object *control_node;
	struct object *p_c_button;
	HBITMAP arr_hbitmap[NUM_BMP_MY_BUTTON2];
	struct object *arr_sub[NUM_SUB_MY_BUTTON2];
	POINT lastpt;
};

#endif /* #ifndef OIOIC_MYBUTTON2_H */
