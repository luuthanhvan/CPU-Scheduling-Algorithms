#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/syscalls.h>	

asmlinkage long sys_print_self(void){
	/* declare a pointer of struct task_struct type */
	/* struct task_struct type is circular doubly-linked list data structure that defined in linux/sched.h */
	struct task_struct *task;
	printk("Process ID\t Process state\t Program name\n");
	/* use for_each_process() macros to traverse through the entire task list */
	for_each_process(task){
		printk("%ld\t%ld\t%s\n", (long)task_pid_nr(task), (long)task->state,  task->comm);
	}
	return 0;
}

