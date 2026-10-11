

#include "CObject.h"

int c_object_i_open(struct object *self, const struct vr *caller_context);
int c_object__cmd_initialize(struct object *self,
			     const struct init_cobject *picob,
			     const struct vr *caller_context);
int c_object__cmd_wgi_move(struct object *self, const struct move *pmove,
			   const struct vr *caller_context);

/* OICC label */

/* <oicc> */
/* <ibn> VObject </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int c_object_open(struct object *self, const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	return c_object_i_open(self, &caller);
}

static int c_object_input(struct object *self, unsigned char *input_stream,
			  unsigned int quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int c_object_output(struct object *self, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int c_object_io_put(struct object *self, unsigned char *input_stream,
			   unsigned int quantity, unsigned char *output_stream,
			   unsigned int capacity, unsigned int *output_quantity,
			   const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int c_object_interact0(struct object *self, unsigned int action,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int c_object_interact1(struct object *self, unsigned int action,
			      unsigned char *output_stream,
			      unsigned int capacity,
			      unsigned int *output_quantity,
			      const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int c_object_interact2(struct object *self, unsigned int action,
			      unsigned char *input_stream,
			      unsigned int quantity,
			      const struct vr *caller_context)
{
	struct vr caller;

	caller.cr = caller_context->cr;
	caller.mr = self->oid;

	switch (action) {
	case CMD_INITIALIZE:
		assert(sizeof(struct init_cobject) == quantity);
		return c_object__cmd_initialize(
			self, (struct init_cobject *)input_stream, &caller);
	case CMD_WGI_MOVE:
		assert(sizeof(struct move) == quantity);
		return c_object__cmd_wgi_move(self, (struct move *)input_stream,
					      &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int c_object_interact3(struct object *self, unsigned int action,
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

static int c_object_close(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	if (0 == self->ref_count)
		return RP_RCZERO;

	return R_P;
}

/* TOG */

void tog_c_object(struct object *object)
{
	object->open = c_object_open;
	object->input = c_object_input;
	object->output = c_object_output;
	object->io_put = c_object_io_put;
	object->interact0 = c_object_interact0;
	object->interact1 = c_object_interact1;
	object->interact2 = c_object_interact2;
	object->interact3 = c_object_interact3;
	object->close = c_object_close;
}

/* Function(s) */

int c_object_i_open(struct object *self, const struct vr *caller_context)
{
	struct em_cobject *members = (struct em_cobject *)self->members;

	if (1 == self->ref_count) {
		members->oioic_node = get_base_node(self, MSN_OIOIC);
		members->visual_node = get_base_node(self, MSN_VOBJECT);

		return RP_RCONE;
	}

	return R_P;
}

int c_object__cmd_initialize(struct object *self,
			     const struct init_cobject *picob,
			     const struct vr *caller_context)
{
	struct em_cobject *members = (struct em_cobject *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;

	pem_vob->p_wnd_handle = picob->p_wnd_handle;

	return R_P;
}

int c_object__cmd_wgi_move(struct object *self, const struct move *pmove,
			   const struct vr *caller_context)
{
	struct em_cobject *members = (struct em_cobject *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;

	pem_vob->rsc.rcouter.left += pmove->dx_ul;
	pem_vob->rsc.rcouter.top += pmove->dy_ul;
	pem_vob->rsc.rcouter.right += pmove->dx_lr;
	pem_vob->rsc.rcouter.bottom += pmove->dy_lr;
	pem_vob->rsc.z += pmove->dz;

	/* [只是移动，应该不需要，去掉]	vo_interact0(pem->visual_node, MAK_WGI_CURRENTBITMAP0, caller_context); */
	vo_interact0(members->visual_node, CMD_WGI_REPAINTSUPERIOR,
		     caller_context);

	return R_P;
}
