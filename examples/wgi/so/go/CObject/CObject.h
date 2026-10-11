

#ifndef OIOIC_COBJECT_H
#define OIOIC_COBJECT_H

#include "../go.h"
#include "../VObject/VObject.h"

/* INIT */

struct init_cobject {
	const HWND *p_wnd_handle;
};

/* Extended Member */

struct em_cobject {
	struct object *oioic_node;
	struct object *visual_node;
};

#endif /* #ifndef OIOIC_COBJECT_H */
