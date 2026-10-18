

#ifndef NEOIOIC_WOBJECT_H
#define NEOIOIC_WOBJECT_H

#include "../general.h"
#include "../v_object/v_object.h"

/* INIT */

struct init_wobject {
	HINSTANCE instance;
	const TCHAR *p_class_name;
	const TCHAR *p_window_name;
};

/* Extended Member */

struct em_wobject {
	struct object *neoioic_node;
	struct object *visual_node;
	HINSTANCE instance;
	HWND window_handle;
	const TCHAR *p_class_name;
	const TCHAR *p_window_name;
};

#endif /* #ifndef NEOIOIC_WOBJECT_H */
