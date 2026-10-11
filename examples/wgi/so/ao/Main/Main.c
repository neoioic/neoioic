

#include <wchar.h>
#include "Main.h"
#include <stdio.h>
#include "../../go/VObject/VObject.h"
#include "../../go/WObject/WObject.h"

#define _CRTDBG_MAP_ALLOC

extern struct object *g_po_main_wnd;
extern void load_bitmaps();
extern void unload_bitmaps();

/* Global Variables: */
const TCHAR g_sz_dialog_class[] = TEXT("Dialog"); /* main window class name. */
const TCHAR g_sz_dialog_name[] = TEXT("Dialog");  /* main window name. */
HINSTANCE g_h_instance = NULL;

/* OICC label */

/* <oicc> */
/* <ibn> OIOIC </ibn> */
/* <crt> */
/* </crt> */
/* </oicc> */

/* Interface */

static int main_open(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。 */

	if (1 == self->ref_count)
		return RP_RCONE;

	return R_P;
}

static int main_input(struct object *self, unsigned char *input_stream,
		      unsigned int quantity, const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INPUT;
}

static int main_output(struct object *self, unsigned char *output_stream,
		       unsigned int capacity, unsigned int *output_quantity,
		       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_OUTPUT;
}

static int main_io_put(struct object *self, unsigned char *input_stream,
		       unsigned int quantity, unsigned char *output_stream,
		       unsigned int capacity, unsigned int *output_quantity,
		       const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_IOPUT;
}

static int main_interact0(struct object *self, unsigned int action,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT0;
}

static int main_interact1(struct object *self, unsigned int action,
			  unsigned char *output_stream, unsigned int capacity,
			  unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT1;
}

static int main_interact2(struct object *self, unsigned int action,
			  unsigned char *input_stream, unsigned int quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT2;
}

static int main_interact3(struct object *self, unsigned int action,
			  unsigned char *input_stream, unsigned int quantity,
			  unsigned char *output_stream, unsigned int capacity,
			  unsigned int *output_quantity,
			  const struct vr *caller_context)
{

	/* 在上面完成接口自己的任务。 */

	SBO_OBJECT_INTERACT3;
}

static int main_close(struct object *self, const struct vr *caller_context)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。 */

	if (0 == self->ref_count)
		return RP_RCZERO;

	return R_P;
}

/* TOG */

void tog_main(struct object *object)
{
	object->open = main_open;
	object->input = main_input;
	object->output = main_output;
	object->io_put = main_io_put;
	object->interact0 = main_interact0;
	object->interact1 = main_interact1;
	object->interact2 = main_interact2;
	object->interact3 = main_interact3;
	object->close = main_close;
}

/* main */

/* 主体函数。 */
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE h_prev_instance,
		     LPSTR lp_cmd_line, int show_command)
{
	struct vr caller = { OID_MAIN, OID_WGIDEMO };
	HWND window_handle;
	MSG msg = { 0 };
	int exit_code = 0;
	struct object *object;
	struct init_vobject ivob;
	struct init_wobject iwob;
	HCURSOR cursor;
	int r;
	BITMAP bm;
	HBITMAP h_bmp_normal, h_bmp_focus_over, h_bmp_focus_on,
		h_bmp_active; /* Dialog's bitmaps */
	TCHAR sz_file_path[MAX_PATH + 1];
	TCHAR *p;

	window_handle = FindWindow(g_sz_dialog_class, g_sz_dialog_name);
	if (window_handle != NULL) {
		SetForegroundWindow(window_handle);
		return 0;
	}

	g_h_instance = instance;
	if (FAILED(OleInitialize(NULL)))
		return -1;

	cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);

	GetModuleFileName(NULL, sz_file_path, MAX_PATH);
	p = wcsrchr(sz_file_path, L'\\') + 1;
	p += swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		      TEXT("skins\\"));

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Dialog_Normal.jpg"));
	h_bmp_normal = load_picture_file(sz_file_path);
	assert(h_bmp_normal);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Dialog_FocusOver.jpg"));
	h_bmp_focus_over = load_picture_file(sz_file_path);
	assert(h_bmp_focus_over);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Dialog_FocusOn.jpg"));
	h_bmp_focus_on = load_picture_file(sz_file_path);
	assert(h_bmp_focus_on);

	swprintf(p, MAX_PATH + 1 - (size_t)(p - sz_file_path), TEXT("%ls"),
		 TEXT("Dialog_Active.jpg"));
	h_bmp_active = load_picture_file(sz_file_path);
	assert(h_bmp_active);

	load_bitmaps();

	/* create and open object */
	r = create_object(MSN_MYDIALOG, 0, 0, 1, &g_po_main_wnd);
	if (RN(r)) {
		OleUninitialize();
		return -1;
	}
	r = vo_open(g_po_main_wnd, &caller);
	assert(RP(r));

	memset(&ivob, 0, sizeof(struct init_vobject));
	memset(&iwob, 0, sizeof(struct init_wobject));

	GetObject(h_bmp_normal, sizeof(bm), &bm);

	ivob.arr_hbitmap[VOB_STATE_NORMAL] = h_bmp_normal;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_OVER] = h_bmp_focus_over;
	ivob.arr_hbitmap[VOB_STATE_FOCUS_ON] = h_bmp_focus_on;
	ivob.arr_hbitmap[VOB_STATE_ACTIVE] = h_bmp_active;
	ivob.rsc.rcouter.left = 50;
	ivob.rsc.rcouter.top = 50;
	ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
	ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
	ivob.rsc.rcinner.left = 5;
	ivob.rsc.rcinner.top = 5;
	ivob.rsc.rcinner.right = bm.bmWidth - 5;
	ivob.rsc.rcinner.bottom = bm.bmHeight - 5;
	ivob.scenew = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.sceneh = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;
	ivob.state = VOB_STATE_ACTIVE;

	iwob.instance = instance;
	iwob.p_class_name = g_sz_dialog_class;
	iwob.p_window_name = g_sz_dialog_name;

	object = get_base_node(g_po_main_wnd, MSN_VOBJECT);
	r = vo_interact2(object, CMD_INITIALIZE, (unsigned char *)&ivob,
			 sizeof(struct init_vobject), &caller);
	if (!RP(r))
		goto initialization_failed;
	object = get_base_node(g_po_main_wnd, MSN_WOBJECT);
	r = vo_interact2(object, CMD_INITIALIZE, (unsigned char *)&iwob,
			 sizeof(struct init_wobject), &caller);
	if (!RP(r))
		goto initialization_failed;
	r = vo_interact0(g_po_main_wnd, CMD_PREPARE, &caller);
	if (!RP(r))
		goto initialization_failed;
	r = vo_interact0(g_po_main_wnd, CMD_RUN, &caller);
	if (!RP(r))
		goto initialization_failed;

	/* main message loop: */
	while (GetMessage(&msg, NULL, 0, 0) > 0) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	exit_code = (int)msg.wParam;
	goto cleanup;

initialization_failed:
	fprintf(stderr,
		"WGI initialization failed: result=%d, Windows error=%lu\n", r,
		GetLastError());
	exit_code = 1;

cleanup:

	/* close and destroy object */
	r = vo_close(g_po_main_wnd, &caller);
	assert(RP_RCZERO == r);
	destroy_object(g_po_main_wnd);

	DeleteObject(h_bmp_normal);
	DeleteObject(h_bmp_focus_over);
	DeleteObject(h_bmp_focus_on);
	DeleteObject(h_bmp_active);
	unload_bitmaps();
	OleUninitialize();

	return exit_code;
}

/* Function(s) */
