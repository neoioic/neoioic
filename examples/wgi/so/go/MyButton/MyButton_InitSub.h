/*
 * 初始化 MyButton 的各级下级对象的 .h 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#ifndef OIOIC_MYBUTTON_INITSUB_H
#define OIOIC_MYBUTTON_INITSUB_H

#include "MyButton.h"

extern void my_button_init_sub_button(struct object *self, enum esmybutton es,
				      const struct vr *caller_context);

#endif /* #ifndef OIOIC_MYBUTTON_INITSUB_H */