/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_UNWIND_TYPES_H
#define _LINUX_UNWIND_TYPES_H

#define UNWIND_RULE_DEREF			BIT(31)

enum unwind_cfa_rule {
	UNWIND_CFA_RULE_SP_OFFSET,		/* CFA = SP + offset */
	UNWIND_CFA_RULE_FP_OFFSET,		/* CFA = FP + offset */
	UNWIND_CFA_RULE_REG_OFFSET,	/* CFA = reg + offset */
	/* DEREF variants */
	UNWIND_CFA_RULE_REG_OFFSET_DEREF =	/* CFA = *(reg + offset) */
		UNWIND_CFA_RULE_REG_OFFSET | UNWIND_RULE_DEREF,
};

struct unwind_cfa_rule_data {
	enum unwind_cfa_rule rule;
	s32 offset;
	unsigned int regnum;
};

enum unwind_rule {
	UNWIND_RULE_RETAIN,		/* entity = entity */
	UNWIND_RULE_CFA_OFFSET,		/* entity = CFA + offset */
	UNWIND_RULE_REG_OFFSET,		/* entity = register + offset */
	/* DEREF variants */
	UNWIND_RULE_CFA_OFFSET_DEREF =	/* entity = *(CFA + offset) */
		UNWIND_RULE_CFA_OFFSET | UNWIND_RULE_DEREF,
	UNWIND_RULE_REG_OFFSET_DEREF =	/* entity = *(register + offset) */
		UNWIND_RULE_REG_OFFSET | UNWIND_RULE_DEREF,
};

struct unwind_rule_data {
	enum unwind_rule rule;
	s32 offset;
	unsigned int regnum;
};

struct unwind_frame {
	struct unwind_cfa_rule_data cfa;
	struct unwind_rule_data ra;
	struct unwind_rule_data fp;
	bool outermost;
};

#endif /* _LINUX_UNWIND_TYPES_H */
