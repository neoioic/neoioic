/*
 * 初始化 my_button2 的各级下级对象的 .h 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#ifndef NEOIOIC_MYBUTTON2_INITSUB_H
#define NEOIOIC_MYBUTTON2_INITSUB_H

#include "my_button2.h"

extern void my_button2_init_sub_button(struct object *self, enum esmybutton2 es,
				       const struct vr *caller_context);

#endif /* #ifndef NEOIOIC_MYBUTTON2_INITSUB_H */