

#ifndef OIOIC_WPANEL_H
#define OIOIC_WPANEL_H

#include "../go.h"
#include "../WObject/WObject.h"

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

/* INIT */

/* Extended Member */

struct em_wpanel {
	struct object *oioic_node;
	struct object *visual_node;
	struct object *window_node;
};

#endif /* #ifndef OIOIC_WPANEL_H */
