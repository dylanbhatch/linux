/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ARM64_UNWIND_SFRAME_H
#define _ASM_ARM64_UNWIND_SFRAME_H

#include <linux/module.h>
#include <linux/sframe.h>
#include <asm/sections.h>

#define SFRAME_REG_SP	31
#define SFRAME_REG_FP	29

static inline bool sframe_func_start_addr_valid(struct sframe_section *sec,
						unsigned long func_addr)
{
	/* Common case for unwinding */
	if (sec->text_start <= func_addr && func_addr < sec->text_end)
		return true;

	if (sec->sec_type != SFRAME_KERNEL)
		return false;

	/*
	 * Account for vmlinux and module code outside the normal .text section.
	 * The toolchain still generates sframe data for these functions, so
	 * sframe lookups on them should be allowed.
	 */
	if (sec == &kernel_sfsec) {
		if (is_kernel_inittext(func_addr))
			return true;

		/* .exit.text is retained in vmlinux on arm64. */
		if (func_addr >= (unsigned long)__exittext_begin &&
		    func_addr < (unsigned long)__exittext_end)
			return true;


		/*
		 * .rodata.text is never executed from the kernel mapping, but
		 * still has sframe data
		 */
		if (func_addr >= (unsigned long)_srodatatext &&
		    func_addr < (unsigned long)_erodatatext)
			return true;
	} else {
		struct module *mod = container_of(sec, struct module,
						  arch.sframe_sec);
		if (within_module_mem_type(func_addr, mod, MOD_INIT_TEXT))
			return true;
	}

	return false;
}
#define sframe_func_start_addr_valid sframe_func_start_addr_valid

#endif /* _ASM_ARM64_UNWIND_SFRAME_H */
