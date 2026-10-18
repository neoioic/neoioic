

#ifndef NEOIOIC_COBJECT_H
#define NEOIOIC_COBJECT_H

#include "../general.h"
#include "../v_object/v_object.h"

/* INIT */

struct init_cobject {
	const HWND *p_wnd_handle;
};

/* Extended Member */

struct em_cobject {
	struct object *neoioic_node;
	struct object *visual_node;
};

#endif /* #ifndef NEOIOIC_COBJECT_H */
