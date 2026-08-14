#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mempolicy.h>
#include <linux/sched.h>

struct mempolicy *get_task_policy(struct task_struct *p);

static noinline void mod_print(void)
{
	struct mempolicy *p;
	pr_info("%s\n", __func__);
	p = get_task_policy(current);
	pr_info("current mempolicy home_node: %d\n", p->home_node);
}

static int mod_export_init(void)
{
	mod_print();
	return 0;
}

static void mod_export_exit(void)
{
	pr_info("%s\n", __func__);
}

module_init(mod_export_init);
module_exit(mod_export_exit);
MODULE_DESCRIPTION("Live patching demo for symbols exported for modules");
MODULE_LICENSE("GPL");
