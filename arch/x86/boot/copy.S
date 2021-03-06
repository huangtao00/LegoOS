/*
 * Copyright (c) 2016-2019 Wuklab, Purdue University. All rights reserved.
 *
 * Memory copy routines
 */

#include <lego/linkage.h>

	.code16
	.text

GLOBAL(memcpy)
	pushw	%si
	pushw	%di
	movw	%ax, %di
	movw	%dx, %si
	pushw	%cx
	shrw	$2, %cx
	rep; movsl
	popw	%cx
	andw	$3, %cx
	rep; movsb
	popw	%di
	popw	%si
	retl
ENDPROC(memcpy)

GLOBAL(memset)
	pushw	%di
	movw	%ax, %di
	movzbl	%dl, %eax
	imull	$0x01010101,%eax
	pushw	%cx
	shrw	$2, %cx
	rep; stosl
	popw	%cx
	andw	$3, %cx
	rep; stosb
	popw	%di
	retl
ENDPROC(memset)

GLOBAL(copy_from_fs)
	pushw	%ds
	pushw	%fs
	popw	%ds
	calll	memcpy
	popw	%ds
	retl
ENDPROC(copy_from_fs)

GLOBAL(copy_to_fs)
	pushw	%es
	pushw	%fs
	popw	%es
	calll	memcpy
	popw	%es
	retl
ENDPROC(copy_to_fs)

#if 0 /* Not currently used, but can be enabled as needed */
GLOBAL(copy_from_gs)
	pushw	%ds
	pushw	%gs
	popw	%ds
	calll	memcpy
	popw	%ds
	retl
ENDPROC(copy_from_gs)

GLOBAL(copy_to_gs)
	pushw	%es
	pushw	%gs
	popw	%es
	calll	memcpy
	popw	%es
	retl
ENDPROC(copy_to_gs)
#endif
