/*
 * Copyright (c) 2016-2019 Wuklab, Purdue University. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _ASM_X86_TSC_H_
#define _ASM_X86_TSC_H_

extern unsigned int cpu_khz;
extern unsigned int tsc_khz;

void __init tsc_init(void);

#endif /* _ASM_X86_TSC_H_ */
