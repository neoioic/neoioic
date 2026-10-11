

#ifndef OIOIC_WGI_H
#define OIOIC_WGI_H

#include "se.h"

/* 多边形结构体 */
struct polygon {
	POINT *p_apt;
	int npt;
};

/* Z轴多边形结构体。 */
struct zpolygon {
	struct polygon plg;
	int z;
};

extern HBITMAP load_picture_file(const TCHAR *adrame);
extern char is_point_in_polygon(int x, int y, const struct polygon *pplg);
extern char is_inter2_rects(const RECT *p_src_rect1, const RECT *p_src_rect2,
			    RECT *p_dst_rect);
extern void calcu_ora_coord(struct object *object, RECT *p_aor);

#endif /* #ifndef OIOIC_WGI_H */