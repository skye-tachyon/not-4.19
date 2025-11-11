#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

ATOMIC_NOTIFIER_HEAD(show_mem_extra_notifier);

/**
 * Call show_mem notifiers to print out extra memory information
 * @s: seq_file into which print log out, if Null print to kernel log buffer
 */
static void __show_mem_extra_call_notifiers(struct seq_file *s)
{
	atomic_notifier_call_chain(&show_mem_extra_notifier, 0, s);
	if (s == NULL)
		printk("\n");
}

int show_mem_extra_notifier_register(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&show_mem_extra_notifier, nb);
}

int show_mem_extra_notifier_unregister(struct notifier_block *nb)
{
	return  atomic_notifier_chain_unregister(&show_mem_extra_notifier, nb);
}

void show_mem_extra_call_notifiers(void)
{
	__show_mem_extra_call_notifiers(NULL);
}

static int meminfo_extra_proc_show(struct seq_file *m, void *v)
{
	__show_mem_extra_call_notifiers(m);
	return 0;
}

static int meminfo_extra_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_extra_proc_show, NULL);
}

static const struct proc_ops meminfo_extra_proc_ops = {
	.proc_open	= meminfo_extra_proc_open,
	.proc_read	= seq_read,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
};

static int __init proc_meminfo_extra_init(void)
{
	proc_create("meminfo_extra", 0444, NULL, &meminfo_extra_proc_ops);
	return 0;
}
fs_initcall(proc_meminfo_extra_init);

