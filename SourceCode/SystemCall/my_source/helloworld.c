#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_helloworld(void){
	printk("Hello, My full name is Luu Thanh Van.\n My student ID is B1709639.\n");
	return 0;
}

