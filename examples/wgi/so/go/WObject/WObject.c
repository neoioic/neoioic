

#include "WObject.h"

int w_object_i_open(struct object *self, const struct vr *caller_context);
int w_object__crt_wgi_window(struct object *self,
			     const struct vr *caller_context);
int w_object__dtr_wgi_window(struct object *self,
			     const struct vr *caller_context);
int w_object__cmd_initialize(struct object *self,
			     const struct init_wobject *piwob,
			     const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> VObject </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int w_object_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return w_object_i_open(self, &caller);
}

static int w_object_input(struct object *self, unsigned char *input_stream,
			  unsigned int quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int w_object_output(struct object *self, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int w_object_io_put(struct object *self, unsigned char *input_stream,
			   unsigned int quantity, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int w_object_interact0(struct object *self, unsigned int action,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CRT_WGI_WINDOW:
		return w_object__crt_wgi_window(self, &caller);
	case DTR_WGI_WINDOW:
		return w_object__dtr_wgi_window(self, &caller);
	default:
		break;
	}
	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int w_object_interact1(struct object *self, unsigned int action,
			      unsigned char *output_stream,
			      unsigned int capacity,
			      unsigned int *output_quantity,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int w_object_interact2(struct object *self, unsigned int action,
			      unsigned char *input_stream,
			      unsigned int quantity,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_INITIALIZE:
		assert(sizeof(struct init_wobject) == quantity);
		return w_object__cmd_initialize(
			self, (struct init_wobject *)input_stream, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int w_object_interact3(struct object *self, unsigned int action,
			      unsigned char *input_stream,
			      unsigned int quantity,
			      unsigned char *output_stream,
			      unsigned int capacity,
			      unsigned int *output_quantity,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int w_object_close(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	if (0 == self->ref_count)
		return RP_RCZERO;

	return R_P;
}

/* TOG */

void tog_w_object(struct object *object)
{
	object->open = w_object_open;
	object->input = w_object_input;
	object->output = w_object_output;
	object->io_put = w_object_io_put;
	object->interact0 = w_object_interact0;
	object->interact1 = w_object_interact1;
	object->interact2 = w_object_interact2;
	object->interact3 = w_object_interact3;
	object->close = w_object_close;
}

/* Function(s) */

int w_object_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_wobject *members = (struct em_wobject *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);

		return RP_RCONE;
	}

	return R_P;
}

int w_object__crt_wgi_window(struct object *self,
			     const struct vr *caller_context)
{
	struct em_wobject *members = (struct em_wobject *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct em_wobject *pem_wob_sup = NULL;
	HWND hWndParent;

	if (members->window_handle != NULL)
		return RO_VAINLY;

	if (pem_vob->p_superior != NULL)
		pem_wob_sup = (struct em_wobject *)get_base_members(
			pem_vob->p_superior, MSN_WOBJECT);

	hWndParent = (pem_wob_sup != NULL) ? pem_wob_sup->window_handle : NULL;

	members->window_handle = CreateWindowEx(
		WS_EX_APPWINDOW, members->p_class_name, members->p_window_name,
		WS_POPUP | WS_VISIBLE, pem_vob->rsc.rcouter.left,
		pem_vob->rsc.rcouter.top,
		pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left,
		pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top,
		hWndParent, NULL, members->instance, NULL);

	if (NULL == members->window_handle)
		return R_N;

	pem_vob->p_wnd_handle = &members->window_handle;
	SetWindowLongPtr(members->window_handle, GWLP_USERDATA,
			 (LONG_PTR)self->nodes);

	return R_P;
}

int w_object__dtr_wgi_window(struct object *self,
			     const struct vr *caller_context)
{
	struct em_wobject *members = (struct em_wobject *)self->members;

	if (NULL == members->window_handle)
		return RO_VAINLY;

	if (!DestroyWindow(members->window_handle))
		return R_N;

	members->window_handle = NULL;
	return R_P;
}

int w_object__cmd_initialize(struct object *self,
			     const struct init_wobject *piwob,
			     const struct vr *caller_context)
{
	struct em_wobject *members = (struct em_wobject *)self->members;

	members->instance = piwob->instance;
	members->p_class_name = piwob->p_class_name;
	members->p_window_name = piwob->p_window_name;

	return R_P;
}
