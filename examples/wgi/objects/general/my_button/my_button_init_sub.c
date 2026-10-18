/*
 * 初始化 my_button 的各级下级对象的 .c 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#include "my_button_init_sub.h"
#include "../c_object/c_object.h"

void my_button_init_sub_button(struct object *self, enum esmybutton es,
			       const struct vr *caller_context)
{
	struct em_mybutton *members = (struct em_mybutton *)self->members;
	struct em_vobject *pem_vob =
		(struct em_vobject *)members->visual_node->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	ivob.p_superior = self;
	ivob.rsc.rcinner.left = 0;
	ivob.rsc.rcinner.top = 0;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;
	ivob.arr_hbitmap[VOB_STATE_NORMAL] =
		members->arr_hbitmap[BUTTON_NORMAL_BMP_MY_BUTTON];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
		members->arr_hbitmap[BUTTON_FOCUS_OVER_BMP_MY_BUTTON];
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
		members->arr_hbitmap[BUTTON_FOCUS_ON_BMP_MY_BUTTON];
	ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
		members->arr_hbitmap[BUTTON_ACTIVE_BMP_MY_BUTTON];
	ivob.arr_hbitmap[VOB_STATE_SEMI_ACTIVE] =
		members->arr_hbitmap[BUTTON_ABS_INACTIVE_BMP_MY_BUTTON];

	switch (es) {
	case BUTTON1_MY_BUTTON:
		ivob.rsc.rcouter.left = MYBUTTON_BUTTON1_L;
		ivob.rsc.rcouter.top = MYBUTTON_BUTTON1_T;
		ivob.p_prev_codt = members->arr_sub[BUTTON3_MY_BUTTON];
		ivob.p_next_codt = members->arr_sub[BUTTON2_MY_BUTTON];
		break;
	case BUTTON2_MY_BUTTON:
		ivob.rsc.rcouter.left = MYBUTTON_MYBUTTON_L;
		ivob.rsc.rcouter.top = MYBUTTON_MYBUTTON_T;
		ivob.p_prev_codt = members->arr_sub[BUTTON1_MY_BUTTON];
		ivob.p_next_codt = members->arr_sub[BUTTON3_MY_BUTTON];
		break;
	case BUTTON3_MY_BUTTON:
		ivob.rsc.rcouter.left = MYBUTTON_BUTTON3_L;
		ivob.rsc.rcouter.top = MYBUTTON_BUTTON3_T;
		ivob.p_prev_codt = members->arr_sub[BUTTON2_MY_BUTTON];
		ivob.p_next_codt = members->arr_sub[BUTTON1_MY_BUTTON];
		break;
	default:
		assert(0);
		break;
	}

	GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);

	ivob.rsc.rcinner.right = bm.bmWidth;
	ivob.rsc.rcinner.bottom = bm.bmHeight;
	ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
	ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
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