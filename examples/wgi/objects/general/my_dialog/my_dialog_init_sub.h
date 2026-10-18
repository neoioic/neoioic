/*
 * 初始化 Dialog 的各级下级对象的 .h 文件。
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 * 备    注：InitSub - initialize subordinate
 */

#ifndef NEOIOIC_MYDIALOG_INITSUB_H
#define NEOIOIC_MYDIALOG_INITSUB_H

#include "my_dialog.h"

extern void my_dialog_init_sub_button(struct object *self, enum esmydialog es,
				      const struct vr *caller_context);
extern void my_dialog_init_sub_edit(struct object *self, enum esmydialog es,
				    const struct vr *caller_context);

#endif /* #ifndef NEOIOIC_MYDIALOG_INITSUB_H */