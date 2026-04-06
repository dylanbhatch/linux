/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ARM64_UNWIND_SFRAME_H
#define _ASM_ARM64_UNWIND_SFRAME_H

#include <linux/sframe.h>
#include <asm/sections.h>

#define SFRAME_REG_SP	31
#define SFRAME_REG_FP	29

static inline bool sframe_func_start_addr_valid(struct sframe_section *sec,
						unsigned long func_addr)
{
	/*
	 * The .rodata.text section is outside the normal kernel .text, but the
	 * toolchain still generates sframe data for it. Allow sframe lookups
	 * for these functions, even though they are never executed from the
	 * kernel mapping.
	 */
	if (sec->sec_type == SFRAME_KERNEL && sec == &kernel_sfsec &&
	    func_addr >= (unsigned long)_srodatatext &&
	    func_addr < (unsigned long)_erodatatext)
		return true;

	return (sec->text_start <= func_addr && func_addr < sec->text_end);
}
#define sframe_func_start_addr_valid sframe_func_start_addr_valid

#endif /* _ASM_ARM64_UNWIND_SFRAME_H */
