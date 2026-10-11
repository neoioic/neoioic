

#ifndef OIOIC_WOBJECT_H
#define OIOIC_WOBJECT_H

#include "../go.h"
#include "../VObject/VObject.h"

/* INIT */

struct init_wobject {
	HINSTANCE instance;
	const TCHAR *p_class_name;
	const TCHAR *p_window_name;
};

/* Extended Member */

struct em_wobject {
	struct object *oioic_node;
	struct object *visual_node;
	HINSTANCE instance;
	HWND window_handle;
	const TCHAR *p_class_name;
	const TCHAR *p_window_name;
};

#endif /* #ifndef OIOIC_WOBJECT_H */
