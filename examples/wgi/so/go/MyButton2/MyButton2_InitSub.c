/*
 * 初始化 MyButton2 的各级下级对象的 .c 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#include "MyButton2_InitSub.h"
#include "../CObject/CObject.h"

extern HBITMAP g_arr_hbitmap[NUM_BMP];

void my_button2_init_sub_button(struct object *self, enum esmybutton2 es,
				const struct vr *caller_context)
{
	struct em_mybutton2 *members = (struct em_mybutton2 *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	ivob.p_superior = self;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;

	switch (es) {
	case BUTTON_MY_BUTTON2:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			g_arr_hbitmap[BUTTON2_NORMAL_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			g_arr_hbitmap[BUTTON2_FOCUS_OVER_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			g_arr_hbitmap[BUTTON2_FOCUS_ON_BMP];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			g_arr_hbitmap[BUTTON2_ACTIVE_BMP];
		ivob.arr_hbitmap[VOB_STATE_SEMI_ACTIVE] =
			g_arr_hbitmap[BUTTON2_ABS_INACTIVE_BMP];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYBUTTON2_BUTTON_L;
		ivob.rsc.rcouter.top = MYBUTTON2_BUTTON_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 4;
		ivob.rsc.rcinner.top = 4;
		ivob.rsc.rcinner.right = bm.bmWidth - 4;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 4;
		ivob.p_prev_codt = members->arr_sub[BUTTON_MY_BUTTON2];
		ivob.p_next_codt = members->arr_sub[BUTTON_MY_BUTTON2];
		break;
	default:
		assert(0);
		break;
	}

	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.p_wnd_handle = pem_vob->p_wnd_handle;

	vo_open(members->arr_sub[es], caller_context);
	vo_interact2(get_base_node(members->arr_sub[es], MSN_VOBJECT),
		     CMD_INITIALIZE, (unsigned char *)&ivob,
		     sizeof(struct init_vobject), caller_context);
	vo_interact2(get_base_node(members->arr_sub[es], MSN_COBJECT),
		     CMD_INITIALIZE, (unsigned char *)&icob,
		     sizeof(struct init_cobject), caller_context);
	vo_interact0(members->arr_sub[es], CMD_PREPARE, caller_context);

	return;
}
