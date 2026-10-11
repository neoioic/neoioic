

#include <olectl.h>
#include "wgi.h"
#include "../so/go/VObject/VObject.h"

/*
 * 加载图片文件。
 * 加载图片文件，SE函数。
 * 参    数：	adrame - [IN] address and name，图片地址和名称。
 * 返    回：	非NULL - 加载成功；NULL - 加载失败。
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
HBITMAP load_picture_file(const TCHAR *adrame)
{
	IPicture *picture = NULL;
	OLE_HANDLE handle;
	HBITMAP bitmap = NULL;
	HRESULT result = OleLoadPicturePath((LPOLESTR)adrame, NULL, 0, 0,
					    &IID_IPicture, (void **)&picture);
	if (FAILED(result))
		return NULL;
	if (SUCCEEDED(picture->lpVtbl->get_Handle(picture, &handle)))
		bitmap = CopyImage((HANDLE)(uintptr_t)(uint32_t)handle,
				   IMAGE_BITMAP, 0, 0, 0);
	picture->lpVtbl->Release(picture);
	return bitmap;
}

/*
 * 判断一点是否在一个多边形内。
 * 判断一点是否在一个多边形内，SE函数。
 * 参    数：	x - [IN] 点的X轴坐标；
 *               y - [IN] 点的Y轴坐标；
 *               pplg - [IN] 指向多边形。
 * 返    回：	TRUE - 点在多边形内，FALSE - 点不在多边形内。
 * 定 义 者：	赵平智
 * 设 计 者：	尹斌
 * 实 现 者：	尹斌
 */
char is_point_in_polygon(int x, int y, const struct polygon *pplg)
{
	return TRUE;
}

/*
 * 判断两个在同一平面的矩形是否相交。
 * 判断两个在同一平面的矩形是否相交（包括内含），SE函数。
 * 参    数：	p_src_rect1 - [IN] 第一个平面多边形。
 *               p_src_rect2 - [IN] 第二个平面多边形。
 *               p_dst_rect - [OUT] 这个参数可以为NULL，如果不为NULL,输出两个矩形相交的部分（也是矩形）,如果两个矩形不相交,就把这个结构体置空。
 * 返    回：	TRUE - 两平面矩形相交，FALSE - 两平面矩形不相交。
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 */
char is_inter2_rects(const RECT *p_src_rect1, const RECT *p_src_rect2,
		     RECT *p_dst_rect)
{
	if (NULL == p_dst_rect) {
		RECT rc;
		return IntersectRect(&rc, p_src_rect1, p_src_rect2);
	} else {
		return IntersectRect(p_dst_rect, p_src_rect1, p_src_rect2);
	}
}

/*
 * 计算可视对象外部矩形的绝对坐标值。
 * 计算可视对象外部矩形的绝对坐标值，SE函数。
 * 参    数：	object - [IN] 对象指针，必须是VObject节点的派生对象；
 *                 p_aor - [OUT] 接收外部矩形的绝对坐标值（AOR,Absolute Outer Rectangle（绝对外部矩形，
 * 				即坐标值转换为相对于桌面左上角后的外部矩形））。
 * 返    回：	无
 * 定 义 者：	赵平智
 * 设 计 者：	赵平智
 * 实 现 者：	赵平智
 * 备    注：	Calcu - Calculate
 */
void calcu_ora_coord(struct object *object, RECT *p_aor)
{
	struct em_vobject *pem_vob =
		(struct em_vobject *)get_base_members(object, MSN_VOBJECT);

	assert(pem_vob != NULL);

	*p_aor = pem_vob->rsc.rcouter;

	while (pem_vob->p_superior) {
		pem_vob = (struct em_vobject *)get_base_members(
			pem_vob->p_superior, MSN_VOBJECT);
		p_aor->top +=
			pem_vob->rsc.rcinner.top + pem_vob->rsc.rcouter.top;
		p_aor->bottom +=
			pem_vob->rsc.rcinner.top + pem_vob->rsc.rcouter.top;
		p_aor->left +=
			pem_vob->rsc.rcinner.left + pem_vob->rsc.rcouter.left;
		p_aor->right +=
			pem_vob->rsc.rcinner.left + pem_vob->rsc.rcouter.left;
	}

	return;
}
