

#include "wgidemo.h"

/* OICC label */

/* <oicc> */
/* <ibn> OIOIC </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int wgidemo_open(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	if (1 == self->ref_count)
		return RP_RCONE;

	return R_P;
}

static int wgidemo_input(struct object *self, unsigned char *input_stream,
			 unsigned int quantity, const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int wgidemo_output(struct object *self, unsigned char *output_stream,
			  unsigned int capacity, unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int wgidemo_io_put(struct object *self, unsigned char *input_stream,
			  unsigned int quantity, unsigned char *output_stream,
			  unsigned int capacity, unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int wgidemo_interact0(struct object *self, unsigned int action,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int wgidemo_interact1(struct object *self, unsigned int action,
			     unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int wgidemo_interact2(struct object *self, unsigned int action,
			     unsigned char *input_stream, unsigned int quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int wgidemo_interact3(struct object *self, unsigned int action,
			     unsigned char *input_stream, unsigned int quantity,
			     unsigned char *output_stream,
			     unsigned int capacity,
			     unsigned int *output_quantity,
			     const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int wgidemo_close(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	if (0 == self->ref_count)
		return RP_RCZERO;

	return R_P;
}

/* TOG */

void tog_wgidemo(struct object *object)
{
	object->open = wgidemo_open;
	object->input = wgidemo_input;
	object->output = wgidemo_output;
	object->io_put = wgidemo_io_put;
	object->interact0 = wgidemo_interact0;
	object->interact1 = wgidemo_interact1;
	object->interact2 = wgidemo_interact2;
	object->interact3 = wgidemo_interact3;
	object->close = wgidemo_close;
}

/* Function(s) */
