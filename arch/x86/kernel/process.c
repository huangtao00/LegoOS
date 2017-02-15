/*
 * Copyright (c) 2016-2017 Wuklab, Purdue University. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <lego/sched.h>
#include <lego/kernel.h>
#include <lego/string.h>

#include <asm/asm.h>
#include <asm/msr.h>
#include <asm/ptrace.h>
#include <asm/processor.h>
#include <asm/switch_to.h>

/*
 * per-CPU TSS segments. Threads are completely 'soft' on LegoOS,
 * no more per-task TSS's. The TSS size is kept cacheline-aligned
 * so they are allowed to end up in the .data..cacheline_aligned
 * section. Since TSS's are completely CPU-local, we want them
 * on exact cacheline boundaries, to eliminate cacheline ping-pong.
 */

struct tss_struct cpu_tss = {
	.x86_tss = {
		.sp0 = TOP_OF_INIT_STACK,
	 },
};

int copy_thread_tls(unsigned long clone_flags, unsigned long sp,
		unsigned long arg, struct task_struct *p, unsigned long tls)
{
	struct pt_regs *childregs;
	struct fork_frame *fork_frame;
	struct inactive_task_frame *frame;

	p->thread.sp0 = (unsigned long)task_stack_page(p) + THREAD_SIZE;
	childregs = task_pt_regs(p);
	fork_frame = container_of(childregs, struct fork_frame, regs);
	frame = &fork_frame->frame;
	frame->bp = 0;
	frame->ret_addr = (unsigned long)ret_from_fork;
	p->thread.sp = (unsigned long)fork_frame;
	p->thread.io_bitmap_ptr = NULL;

	if (unlikely(p->flags & PF_KTHREAD)) {
		/* kernel thread */
		memset(childregs, 0, sizeof(struct pt_regs));
		frame->bx = sp;		/* function */
		frame->r12 = arg;
		return 0;
	}
	frame->bx = 0;
	*childregs = *task_pt_regs(current);

	childregs->ax = 0;
	if (sp)
		childregs->sp = sp;

	return 0;
}

void user_thread_bug_now(void)
{
	panic("%s\n", __func__);
}
