

#ifndef NEOIOIC_WPANEL_H
#define NEOIOIC_WPANEL_H

#include "../general.h"
#include "../w_object/w_object.h"

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

/* INIT */

/* Extended Member */

struct em_wpanel {
	struct object *neoioic_node;
	struct object *visual_node;
	struct object *window_node;
};

#endif /* #ifndef NEOIOIC_WPANEL_H */
