

#include "w_panel.h"

int w_panel_i_open(struct object *self, const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> w_object </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int w_panel_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return w_panel_i_open(self, &caller);
}

static int w_panel_input(struct object *self, unsigned char *input_stream,
			 unsigned int quantity, const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int w_panel_output(struct object *self, unsigned char *output_stream,
			  unsigned int capacity, unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int w_panel_io_put(struct object *self, unsigned char *input_stream,
			  unsigned int quantity, unsigned char *output_stream,
			  unsigned int capacity, unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int w_panel_interact0(struct object *self, unsigned int action,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int w_panel_interact1(struct object *self, unsigned int action,
			     unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int w_panel_interact2(struct object *self, unsigned int action,
			     unsigned char *input_stream, unsigned int quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int w_panel_interact3(struct object *self, unsigned int action,
			     unsigned char *input_stream, unsigned int quantity,
			     unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int w_panel_close(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	if (0 == self->ref_count)
		return RP_RCZERO;

	return R_P;
}

/* TOG */

void tog_w_panel(struct object *object)
{
	object->open = w_panel_open;
	object->input = w_panel_input;
	object->output = w_panel_output;
	object->io_put = w_panel_io_put;
	object->interact0 = w_panel_interact0;
	object->interact1 = w_panel_interact1;
	object->interact2 = w_panel_interact2;
	object->interact3 = w_panel_interact3;
	object->close = w_panel_close;
}

/* Function(s) */

int w_panel_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_wpanel *members = (struct em_wpanel *)self->members;

	if (1 == self->ref_count) {
		members->neoioic_node = get_base_node(self, MSN_NEOIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);
		members->window_node = get_base_node(self, MSN_WOBJECT);

		return RP_RCONE;
	}

	return R_P;
}
