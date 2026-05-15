#ifndef __ASM_LINKAGE_H
#define __ASM_LINKAGE_H

#ifdef __ASSEMBLER__
#include <asm/assembler.h>

/*
 * Do not generate .eh_frame.  Only generate .debug_frame and optionally
 * .sframe (via assembler option --gsframe[-N]).
 */
	.cfi_sections .debug_frame
#endif

#define __ALIGN		.balign CONFIG_FUNCTION_ALIGNMENT
#define __ALIGN_STR	".balign " #CONFIG_FUNCTION_ALIGNMENT

/*
 * When using in-kernel BTI we need to ensure that PCS-conformant
 * assembly functions have suitable annotations.  Override
 * SYM_FUNC_START to insert a BTI landing pad at the start of
 * everything, the override is done unconditionally so we're more
 * likely to notice any drift from the overridden definitions.
 */
#define SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)	\
	bti c ;

#define SYM_FUNC_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)	\
	bti c ;

#define SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)	\
	bti c ;

#define SYM_FUNC_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)	\
	bti c ;

#define SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)	\
	bti c ;

#define SYM_FUNC_START_WEAK_NOALIGN(name)		\
	SYM_START(name, SYM_L_WEAK, SYM_A_NONE)		\
	bti c ;

#define SYM_TYPED_FUNC_START(name)				\
	SYM_TYPED_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)	\
	bti c ;


/*
 * SYM_[TYPED_]LEAF_FUNC_[START|END] macros add CFI minimal CFI directives
 * allowing .sframe data to be generated for functions which do not modify the
 * LR (x30). Unwind data will not be correct if these macros are used on
 * non-leaf functions, as additional CFI directives would be necessary in such
 * cases.
 */
#define SYM_LEAF_FUNC_START(name)			\
	.cfi_startproc ;				\
	SYM_FUNC_START(name)

#define SYM_LEAF_FUNC_END(name)				\
	.cfi_endproc ;					\
	SYM_FUNC_END(name)

#define SYM_LEAF_FUNC_START_LOCAL(name)			\
	.cfi_startproc ;				\
	SYM_FUNC_START_LOCAL(name)

#define SYM_TYPED_LEAF_FUNC_START(name)			\
	.cfi_startproc ;				\
	SYM_TYPED_FUNC_START(name)

#endif
