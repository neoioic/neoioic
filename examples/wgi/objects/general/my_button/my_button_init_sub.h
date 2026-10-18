/*
 * 初始化 my_button 的各级下级对象的 .h 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#ifndef NEOIOIC_MYBUTTON_INITSUB_H
#define NEOIOIC_MYBUTTON_INITSUB_H

#include "my_button.h"

extern void my_button_init_sub_button(struct object *self, enum esmybutton es,
				      const struct vr *caller_context);

#endif /* #ifndef NEOIOIC_MYBUTTON_INITSUB_H */