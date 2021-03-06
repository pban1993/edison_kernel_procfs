#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>	/* Access jiffies */

#define FILE_NAME "buffer"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("/proc fs example");

/* Print jiffies value */
static int proc_file_show(struct seq_file *m, void *v) {
  	seq_printf(m, "%lu\n", jiffies);
	return 0;
}

/* Calls the function that prints jiffies value */
static int proc_file_open(struct inode *i, struct  file *f) {
	return single_open(f, proc_file_show, NULL);
}

/* Defines /proc file's operations */
static const struct file_operations proc_fops = {
  	.owner = THIS_MODULE,
  	.open = proc_file_open,
  	.read = seq_read,
  	.llseek = seq_lseek,
  	.release = single_release,
};

/* Initialization - create /proc/buffer file */
static int __init proc_file_init(void) {
  	proc_create(FILE_NAME, 0, NULL, &proc_fops);
	return 0;
}

/* Cleanup - remove /proc/buffer file */
static void __exit proc_file_exit(void) {
  	remove_proc_entry(FILE_NAME, NULL);
}

module_init(proc_file_init);
module_exit(proc_file_exit);
