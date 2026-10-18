/*
 * 初始化 my_dialog 的各级下级对象的 .c 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#include "my_dialog_init_sub.h"
#include "../c_object/c_object.h"
#include "../c_edit/c_edit.h"

extern HBITMAP g_arr_hbitmap[NUM_BMP];

void my_dialog_init_sub_button(struct object *self, enum esmydialog es,
			       const struct vr *caller_context)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	BITMAP bm;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));

	ivob.p_superior = self;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;

	switch (es) {
	case TRC_CLOSE_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			g_arr_hbitmap[TRC_CLOSE_NORMAL_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			g_arr_hbitmap[TRC_CLOSE_FOCUS_OVER_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			g_arr_hbitmap[TRC_CLOSE_FOCUS_ON_BMP];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			g_arr_hbitmap[TRC_CLOSE_NORMAL_BMP];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_TRCCLOSE_L;
		ivob.rsc.rcouter.top = MYDIALOG_TRCCLOSE_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.p_prev_codt = members->arr_sub[EDIT_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[MR_CONTROL_MY_DIALOG];
		break;
	case MR_CONTROL_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[MR_CONTROL_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap
				[MR_CONTROL_FOCUS_OVER_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap[MR_CONTROL_FOCUS_ON_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap[MR_CONTROL_FOCUS_ON_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRCONTROL_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRCONTROL_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.p_prev_codt = members->arr_sub[TRC_CLOSE_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[MR_MENU_DEMO_MY_DIALOG];
		break;
	case MR_MENU_DEMO_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[MR_MENU_DEMO_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap
				[MR_MENU_DEMO_FOCUS_OVER_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap
				[MR_MENU_DEMO_FOCUS_ON_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap
				[MR_MENU_DEMO_FOCUS_ON_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRMENUDEMO_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRMENUDEMO_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.p_prev_codt = members->arr_sub[MR_CONTROL_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[MR_HELP_MY_DIALOG];
		break;
	case MR_HELP_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[MR_HELP_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap[MR_HELP_FOCUS_OVER_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap[MR_HELP_FOCUS_ON_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap[MR_HELP_FOCUS_ON_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_MRHELP_L;
		ivob.rsc.rcouter.top = MYDIALOG_MRHELP_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.p_prev_codt = members->arr_sub[MR_MENU_DEMO_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[BUTTON1_MY_DIALOG];
		break;
	case BUTTON1_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[BUTTON1_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap[BUTTON1_FOCUS_OVER_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap
				[BUTTON1_ACTIVE_BMP_MY_DIALOG]; /* pem->arr_hbitmap[BUTTON1_FOCUS_ON_BMP_MY_DIALOG]; */
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap[BUTTON1_ACTIVE_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_SEMI_ACTIVE] =
			members->arr_hbitmap
				[BUTTON1_ABS_INACTIVE_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON1_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON1_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = bm.bmWidth;
		ivob.rsc.rcinner.bottom = bm.bmHeight;
		ivob.p_prev_codt = members->arr_sub[MR_HELP_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[BUTTON2_MY_DIALOG];
		break;
	case BUTTON2_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			g_arr_hbitmap[BUTTON2_NORMAL_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			g_arr_hbitmap[BUTTON2_FOCUS_OVER_BMP];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] = g_arr_hbitmap
			[BUTTON2_ACTIVE_BMP]; /* g_arr_hbitmap[BUTTON2_FOCUS_ON_BMP]; */
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			g_arr_hbitmap[BUTTON2_ACTIVE_BMP];
		ivob.arr_hbitmap[VOB_STATE_SEMI_ACTIVE] =
			g_arr_hbitmap[BUTTON2_ABS_INACTIVE_BMP];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON2_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON2_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 4;
		ivob.rsc.rcinner.top = 4;
		ivob.rsc.rcinner.right = bm.bmWidth - 4;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 4;
		ivob.p_prev_codt = members->arr_sub[BUTTON1_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[BUTTON3_MY_DIALOG];
		break;
	case BUTTON3_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[BUTTON3_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap[BUTTON3_FOCUS_OVER_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap
				[BUTTON3_ACTIVE_BMP_MY_DIALOG]; /* pem->arr_hbitmap[BUTTON3_FOCUS_ON_BMP_MY_DIALOG]; */
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap[BUTTON3_ACTIVE_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_SEMI_ACTIVE] =
			members->arr_hbitmap
				[BUTTON3_ABS_INACTIVE_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON3_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON3_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 6;
		ivob.rsc.rcinner.top = 6;
		ivob.rsc.rcinner.right = bm.bmWidth - 6;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 6;
		ivob.p_prev_codt = members->arr_sub[BUTTON2_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[EDIT_MY_DIALOG];
		break;
	default:
		assert(0);
		break;
	}

	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.p_wnd_handle = &pem_wob->window_handle;

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

void my_dialog_init_sub_edit(struct object *self, enum esmydialog es,
			     const struct vr *caller_context)
{
	struct em_mydialog *members = (struct em_mydialog *)self->members;
	struct em_wobject *pem_wob =
		(struct em_wobject *)members->window_node->members;
	struct init_vobject ivob;
	struct init_cobject icob;
	struct init_cedit iced;
	BITMAP bm;

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&icob, 0, sizeof(struct init_cobject));
	memset(&iced, 0, sizeof(struct init_cedit));

	ivob.p_superior = self;
	ivob.style |= VOBS_NOSEMIACTIVE;
	ivob.state = VOB_STATE_NORMAL;

	switch (es) {
	case EDIT_MY_DIALOG:
		ivob.arr_hbitmap[VOB_STATE_NORMAL] =
			members->arr_hbitmap[EDIT_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] =
			members->arr_hbitmap[EDIT_NORMAL_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] =
			members->arr_hbitmap[EDIT_ACTIVE_BMP_MY_DIALOG];
		ivob.arr_hbitmap[VOB_STATE_ACTIVE] =
			members->arr_hbitmap[EDIT_ACTIVE_BMP_MY_DIALOG];
		GetObject(ivob.arr_hbitmap[VOB_STATE_NORMAL], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_EDIT_L;
		ivob.rsc.rcouter.top = MYDIALOG_EDIT_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 6;
		ivob.rsc.rcinner.top = 7;
		ivob.rsc.rcinner.right = bm.bmWidth - 9;
		ivob.rsc.rcinner.bottom = bm.bmHeight - 6;
		ivob.p_prev_codt = members->arr_sub[BUTTON3_MY_DIALOG];
		ivob.p_next_codt = members->arr_sub[TRC_CLOSE_MY_DIALOG];
		wcscpy(members->edttext, TEXT("0\n1\n2"));
		iced.ti.text = members->edttext;
		iced.ti.cpty = sizeof(members->edttext) / sizeof(TCHAR);
		iced.ti.clen = wcslen(members->edttext);
		iced.format |= ETF_LEFT; /* ETF_HCENTER | ETF_VCENTER; */
		break;
	default:
		assert(0);
		break;
	}

	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.p_wnd_handle = &pem_wob->window_handle;

	vo_open(members->arr_sub[es], caller_context);
	vo_interact2(get_base_node(members->arr_sub[es], MSN_VOBJECT),
		     CMD_INITIALIZE, (unsigned char *)&ivob,
		     sizeof(struct init_vobject), caller_context);
	vo_interact2(get_base_node(members->arr_sub[es], MSN_COBJECT),
		     CMD_INITIALIZE, (unsigned char *)&icob,
		     sizeof(struct init_cobject), caller_context);
	vo_interact2(members->arr_sub[es], CMD_INITIALIZE,
		     (unsigned char *)&iced, sizeof(struct init_cedit),
		     caller_context);
	vo_interact0(members->arr_sub[es], CMD_PREPARE, caller_context);

	return;
}